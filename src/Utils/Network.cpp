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

#include "pack2.h"

bool Network::socket_init = false;
bool Network::thread_running = false;
bool Network::thread_should_run = false;
int Network::n_fd = 0;
pthread_t Network::thread;
double Network::camera_x = 0.0;
double Network::camera_y = 0.0;

void Network::init()
{
	socket_init = false;
    thread_running = false;
    thread_should_run = false;
    n_fd = 0;
    memset(&thread, 0, sizeof(pthread_t));

    if((n_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
    	printf("Error creating socket\n");
    	return;
    }

    struct sockaddr_in n_addr;

    memset((char*)&n_addr, 0, sizeof(n_addr));

    n_addr.sin_family = AF_INET;
    n_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    n_addr.sin_port = htons(LOCAL_PORT);

    if(bind(n_fd, (struct sockaddr*)&n_addr, sizeof(n_addr)) < 0) {
    	printf("Socket binding failed\n");
    	return;
    }

    struct timeval tv;
    tv.tv_sec = RECEIVE_TIMEOUT_S;
    tv.tv_usec = RECEIVE_TIMEOUT_US;
    if (setsockopt(n_fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0) {
    	printf("Could not set timeout\n");
    	return;
    }

    socket_init = true;
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

        printf("Could not create network thread\n");
        return false;
    }

    printf("Thread created\n");

    return true;
}

void Network::closeThread()
{
    if(thread_running)
    	thread_should_run = false;

    while(thread_running) { usleep(USLEEP_TIME); }

    printf("Closed thread\n");
}

void *Network::threadLoop(void *args)
{
	size_t send_sig_len = strlen(SEND_SIG);
	ip_t ip;
	unsigned short port;

	unsigned char buf[RECEIVE_LEN];

	while(thread_should_run)
	{
		ssize_t r = receivePacket(buf, RECEIVE_LEN, &ip, &port, true);

	    if(port == PI_PORT && r == (send_sig_len + 8) && strncmp((char*)buf, SEND_SIG, send_sig_len) == 0) {
	    	unpack(buf + send_sig_len, "dd", &camera_x, &camera_y);
	    }

	}
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
        printf("Peer has performed orderly shutdown\n");
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
