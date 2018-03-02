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
#define PI_UPDATE_SIG         "q{A#;"
#define SEND_MODE_SIG         "j@9."
#define RECEIVE_LEN           256
#define DOESNT_SEE_CUBE       1.5
#define SEE_CUBE_TIMEOUT      1000

enum E_SEARCH_MODE {
	ESM_CUBE = 0,
	ESM_TAPE,
	ESM_COUNT
};

class Network {
public:
	static void init();
	static void end();

	static bool initThread();
	static void closeThread();

	inline static double getLeftCameraX() { return left_camera_x; }
	inline static double getLeftCameraY() { return left_camera_y; }
	inline static double getRightCameraX() { return right_camera_x; }
	inline static double getRightCameraY() { return right_camera_y; }

	inline static bool leftSeesCube() { return left_sees_cube; }
	inline static bool rightSeesCube() { return right_sees_cube; }

	// Send to pis whether they should be looking for cubes or tape
	static void sendMode(E_SEARCH_MODE m, int times);
	static bool sendPacket(ip_t ip, unsigned char *buf, size_t buf_len);

private:
	Network() { }

    static void *threadLoop(void *args);

    static ssize_t receivePacket(unsigned char *buf, size_t buf_len, ip_t *ip, unsigned short *port, bool nullTerminate);

    static bool socket_init;
    static bool thread_running;
    static bool thread_should_run;

    static pthread_t thread;
    static int n_fd;

    static double left_camera_x;
    static double left_camera_y;
    static double right_camera_x;
    static double right_camera_y;

    static bool left_sees_cube;
    static bool right_sees_cube;

    static ip_t left_pi_ip;
    static ip_t right_pi_ip;
};

#endif /* SRC_UTILS_NETWORK_H_ */
