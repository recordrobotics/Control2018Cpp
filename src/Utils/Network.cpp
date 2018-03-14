/*
 * Network.cpp
 *
 *  Created on: Feb 14, 2018
 *      Author: vassy
 */

#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <string.h>
#include <stdio.h>
#include <Utils/Network.h>

#include <SmartDashboard/SmartDashboard.h>

#include "Logger.h"
#include "MsTimer.h"

#include "pack2.h"

pthread_mutex_t Network::socket_mutex;
bool Network::socket_init = false;
int Network::n_fd = 0;
pthread_mutex_t Network::thread_mutex;
bool Network::thread_running = false;
bool Network::thread_should_run = false;
pthread_t Network::thread;
pthread_mutex_t Network::params_mutex;
double Network::right_camera_x = 0.0;
double Network::right_camera_y = 0.0;
double Network::left_camera_x = 0.0;
double Network::left_camera_y = 0.0;
bool Network::left_sees_target = false;
bool Network::right_sees_target = false;
ip_t Network::left_pi_ip = 0;
ip_t Network::right_pi_ip = 0;

void Network::init()
{
	socket_init = false;
    thread_running = false;
    thread_should_run = false;
    right_camera_x = 0.0;
    right_camera_y = 0.0;
    right_sees_target = false;
    left_camera_x = 0.0;
    left_camera_y = 0.0;
    left_sees_target = false;
    left_pi_ip = 0;
    right_pi_ip = 0;
    n_fd = 0;
    memset(&thread, 0, sizeof(pthread_t));

    if((n_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    	Logger::log("Error creating socket");
    	return;
    }

    struct sockaddr_in n_addr;

    memset((char*)&n_addr, 0, sizeof(n_addr));

    n_addr.sin_family = AF_INET;
    n_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    n_addr.sin_port = htons(LOCAL_PORT);

    if(bind(n_fd, (struct sockaddr*)&n_addr, sizeof(n_addr)) < 0) {
    	Logger::log("Socket binding failed");
    	return;
    }

    struct timeval tv;
    tv.tv_sec = RECEIVE_TIMEOUT_S;
    tv.tv_usec = RECEIVE_TIMEOUT_US;
    if (setsockopt(n_fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0) {
    	Logger::log("Could not set timeout");
    	return;
    }

    Logger::log("Network init");

    socket_init = true;

    initThread();
}

void Network::end()
{
	closeThread();

    if(socket_init)
        close(n_fd);
}

bool Network::initThread()
{
    if(thread_running)
        return true;

    thread_should_run = true;

    int r1 = pthread_mutex_init(&socket_mutex, NULL);
    int r2 = pthread_mutex_init(&thread_mutex, NULL);
    int r3 = pthread_mutex_init(&params_mutex, NULL);

    if(r1 != 0 || r2 != 0 || r3 != 0) {
    	thread_should_run = false;
    	Logger::log("Could not create thread locks");
    	return false;
    }

    if(pthread_create(&thread, NULL, Network::threadLoop, (void*)NULL) != 0) {
        thread_should_run = false;
        Logger::log("Could not create network thread");
        return false;
    }

    Logger::log("Thread created");

    return true;
}

void Network::closeThread()
{
	pthread_mutex_lock(&thread_mutex);
    if(thread_running)
    	thread_should_run = false;

    bool done = !thread_running;
    pthread_mutex_unlock(&thread_mutex);

    while(!done) {
    	usleep(USLEEP_TIME);

    	pthread_mutex_lock(&thread_mutex);
    	done = !thread_running;
    	pthread_mutex_unlock(&thread_mutex);
    }

    pthread_mutex_destroy(&socket_mutex);
    pthread_mutex_destroy(&thread_mutex);
    pthread_mutex_destroy(&params_mutex);

    Logger::log("Closed thread");
}

void *Network::threadLoop(void *args)
{
	size_t send_sig_len = strlen(PI_UPDATE_SIG);
	ip_t ip;
	unsigned short port;

	unsigned char buf[RECEIVE_LEN];

	pthread_mutex_lock(&thread_mutex);
	thread_running = true;
	pthread_mutex_unlock(&thread_mutex);

	ms_t lastLeftTargetTime = 0, lastRightTargetTime = 0;

	bool done = false;

	while(!done)
	{
		ssize_t r = receivePacket(buf, RECEIVE_LEN, &ip, &port, false);

		ms_t time = MsTimer::getMs();

		double x, y;

	    if(r != -1 && port == PI_PORT && r == (send_sig_len + 9) &&
	       (buf[send_sig_len] == 'R' || buf[send_sig_len] == 'L' ) &&
		   strncmp((char*)buf, PI_UPDATE_SIG, send_sig_len) == 0)
	    {
	    	unpack(buf + send_sig_len + 1, "dd", &x, &y);
	    	Logger::log("Camera data received for '%c': %f %f", buf[send_sig_len], x, y);

	    	if(buf[send_sig_len] == 'R') {
	    		pthread_mutex_lock(&params_mutex);
	    		right_pi_ip = ip;

	    		right_sees_target = (x < DOESNT_SEE_TARGET && y < DOESNT_SEE_TARGET);
	    		lastRightTargetTime = time;

	    		if(right_sees_target) {
	    			right_camera_x = x;
	    			right_camera_y = y;

	    			frc::SmartDashboard::PutNumber("RightCameraX", x);
	    			frc::SmartDashboard::PutNumber("RightCameraY", y);
	    		}

	    		pthread_mutex_unlock(&params_mutex);
	    	}
	    	else if(buf[send_sig_len] == 'L') {
	    		pthread_mutex_lock(&params_mutex);

	    		left_pi_ip = ip;

	    		left_sees_target = (x < DOESNT_SEE_TARGET && y < DOESNT_SEE_TARGET);
	    		lastLeftTargetTime = time;

	    		if(left_sees_target) {
	    			left_camera_x = x;
	    			left_camera_y = y;

	    			frc::SmartDashboard::PutNumber("LeftCameraX", x);
	    			frc::SmartDashboard::PutNumber("LeftCameraY", y);
	    		}

	    		pthread_mutex_unlock(&params_mutex);
	    	}
	    }

	    if((time - lastLeftTargetTime) > SEE_TARGET_TIMEOUT) {
	    	pthread_mutex_lock(&params_mutex);
	    	left_sees_target = false;
	    	pthread_mutex_unlock(&params_mutex);
	    }
	    if((time - lastRightTargetTime) > SEE_TARGET_TIMEOUT) {
	    	pthread_mutex_lock(&params_mutex);
	    	right_sees_target = false;
	    	pthread_mutex_unlock(&params_mutex);
	    }

	    pthread_mutex_lock(&thread_mutex);
	    if(!thread_should_run)
	    	done = true;
	    pthread_mutex_unlock(&thread_mutex);
	}

	pthread_mutex_lock(&thread_mutex);
	thread_running = false;
	pthread_mutex_unlock(&thread_mutex);

	return NULL;
}

ssize_t Network::receivePacket(unsigned char *buf, size_t buf_len, ip_t *ip, unsigned short *port, bool nullTerminate=false)
{
	pthread_mutex_lock(&socket_mutex);
    if(!socket_init) {
    	pthread_mutex_unlock(&socket_mutex);
        return -1;
    }

    struct sockaddr_in remote_addr;
    socklen_t addr_len = sizeof(remote_addr);

    size_t len = nullTerminate ? (buf_len - 1) : buf_len;

    ssize_t recvlen = recvfrom(n_fd, buf, len, 0, (struct sockaddr*)&remote_addr, &addr_len);

    pthread_mutex_unlock(&socket_mutex);

    if(recvlen == 0) {
        Logger::log("Peer has performed orderly shutdown");
        return 0;
    }
    else if(recvlen != -1) {
        if(nullTerminate)
            buf[len] = '\0';

        *ip = remote_addr.sin_addr.s_addr;
        *port = ntohs(remote_addr.sin_port);

        return recvlen;
    }

    return -1;
}

void Network::sendTarget(E_VISION_TARGET t, int times)
{
	size_t send_sig_len = strlen(SEND_MODE_SIG);
	unsigned char buf[send_sig_len + 1];

	strcpy((char*)buf, SEND_MODE_SIG);
	pack(buf + send_sig_len, "C", (int)t);

	if(left_pi_ip) {
		for(int i = 0; i < times; i++)
			sendPacket(left_pi_ip, buf, send_sig_len + 1);
	}

	if(right_pi_ip) {
		for(int i = 0; i < times; i++)
			sendPacket(right_pi_ip, buf, send_sig_len + 1);
	}
}

bool Network::sendPacket(ip_t ip, unsigned char *buf, size_t buf_len)
{
	pthread_mutex_lock(&socket_mutex);
	if(!socket_init) {
		pthread_mutex_unlock(&socket_mutex);
		return false;
	}

	struct sockaddr_in dest_addr;
	memset((char*)&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(PI_PORT);
    dest_addr.sin_addr.s_addr = ip;

    printf("Send %s\n", buf);

    int r = sendto(n_fd, buf, buf_len, 0, (struct sockaddr*)&dest_addr, sizeof(dest_addr));

    pthread_mutex_unlock(&socket_mutex);

    return (r > -1);
}
