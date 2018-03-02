/*
 * RangeFinder.h
 *
 *  Created on: Feb 19, 2018
 *      Author: vassy
 */

#ifndef SRC_RANGEFINDER_H_
#define SRC_RANGEFINDER_H_

#define RANGE_MES_LEN  6

#include <SerialPort.h>

#include "Utils/Logger.h"

class RangeFinder {
public:
	RangeFinder(frc::SerialPort::Port port);
	virtual ~RangeFinder();

	void update();

	inline double getDistance() const { return m_d; }

private:
	frc::SerialPort::Port port;
	frc::SerialPort sensor;
	char buffer[RANGE_MES_LEN + 1];
	double m_d;
};

#endif /* SRC_RANGEFINDER_H_ */
