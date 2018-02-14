/*
 * Network.h
 *
 *  Created on: Feb 14, 2018
 *      Author: vassy
 */

#ifndef SRC_UTILS_NETWORK_H_
#define SRC_UTILS_NETWORK_H_

#include <unistd.h>
#include <pthread.h>
#include <cstdint>

typedef uint32_t ip_t;

#define LOCAL_PORT            1024
#define PI_PORT               1024
#define RECEIVE_TIMEOUT_S     0
#define RECEIVE_TIMEOUT_US    200
#define USLEEP_TIME           20
#define SEND_SIG              "9.S;"
#define RECEIVE_LEN           256

class Network {
public:
	static void init();
	static void end();

	static bool initThread();
	static void closeThread();

	inline static double getCameraX() { return camera_x; }
	inline static double getCameraY() { return camera_y; }

private:
	Network() { }

    static void *threadLoop(void *args);

    static ssize_t receivePacket(unsigned char *buf, size_t buf_len, ip_t *ip, unsigned short *port, bool nullTerminate);

    static bool socket_init;
    static bool thread_running;
    static bool thread_should_run;

    static pthread_t thread;
    static int n_fd;

    static double camera_x;
    static double camera_y;
};

#endif /* SRC_UTILS_NETWORK_H_ */
