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

#include "Logger.h"
#include "MsTimer.h"

#include "pack2.h"

bool Network::socket_init = false;
bool Network::thread_running = false;
bool Network::thread_should_run = false;
int Network::n_fd = 0;
pthread_t Network::thread;
double Network::right_camera_x = 0.0;
double Network::right_camera_y = 0.0;
double Network::left_camera_x = 0.0;
double Network::left_camera_y = 0.0;
bool Network::left_sees_cube = false;
bool Network::right_sees_cube = false;
ip_t Network::left_pi_ip = 0;
ip_t Network::right_pi_ip = 0;

void Network::init()
{
	socket_init = false;
    thread_running = false;
    thread_should_run = false;
    right_camera_x = 0.0;
    right_camera_y = 0.0;
    right_sees_cube = false;
    left_camera_x = 0.0;
    left_camera_y = 0.0;
    left_sees_cube = false;
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
    if(socket_init)
        close(n_fd);
}

bool Network::initThread()
{
    if(thread_running)
        return true;

    thread_should_run = true;

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
    if(thread_running)
    	thread_should_run = false;

    while(thread_running) { usleep(USLEEP_TIME); }

    Logger::log("Closed thread");
}

void *Network::threadLoop(void *args)
{
	size_t send_sig_len = strlen(PI_UPDATE_SIG);
	ip_t ip;
	unsigned short port;

	unsigned char buf[RECEIVE_LEN];

	thread_running = true;

	ms_t lastLeftCubeTime = 0, lastRightCubeTime = 0;

	while(thread_should_run)
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
	    		right_pi_ip = ip;

	    		right_sees_cube = (x < DOESNT_SEE_CUBE && y < DOESNT_SEE_CUBE);
	    		lastRightCubeTime = time;

	    		if(right_sees_cube) {
	    			right_camera_x = x;
	    			right_camera_y = y;
	    		}
	    	}
	    	else if(buf[send_sig_len] == 'L') {
	    		left_pi_ip = ip;

	    		left_sees_cube = (x < DOESNT_SEE_CUBE && y < DOESNT_SEE_CUBE);
	    		lastLeftCubeTime = time;

	    		if(left_sees_cube) {
	    			left_camera_x = x;
	    			left_camera_y = y;
	    		}
	    	}
	    }

	    if((time - lastLeftCubeTime) > SEE_CUBE_TIMEOUT) {
	    	left_sees_cube = false;
	    }

	    if((time - lastRightCubeTime) > SEE_CUBE_TIMEOUT) {
	   	   right_sees_cube = false;
	    }
	}

	thread_running = false;

	return NULL;
}

ssize_t Network::receivePacket(unsigned char *buf, size_t buf_len, ip_t *ip, unsigned short *port, bool nullTerminate=false)
{
    if(!socket_init)
        return -1;

    struct sockaddr_in remote_addr;
    socklen_t addr_len = sizeof(remote_addr);

    size_t len = nullTerminate ? (buf_len - 1) : buf_len;

    ssize_t recvlen = recvfrom(n_fd, buf, len, 0, (struct sockaddr*)&remote_addr, &addr_len);

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

void Network::sendMode(E_SEARCH_MODE m, int times)
{
	size_t send_sig_len = strlen(SEND_MODE_SIG);
	unsigned char buf[send_sig_len + 1];

	strcpy((char*)buf, SEND_MODE_SIG);
	pack(buf + send_sig_len, "C", (int)m);

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
	if(!socket_init)
		return false;

	struct sockaddr_in dest_addr;
	memset((char*)&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(PI_PORT);
    dest_addr.sin_addr.s_addr = ip;

    printf("Send %s\n", buf);

    return (sendto(n_fd, buf, buf_len, 0, (struct sockaddr*)&dest_addr, sizeof(dest_addr)) > -1);
}
