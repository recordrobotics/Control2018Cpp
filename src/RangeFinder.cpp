/*
 * RangeFinder.cpp
 *
 *  Created on: Feb 19, 2018
 *      Author: vassy
 */

#include <RangeFinder.h>

RangeFinder::RangeFinder(frc::SerialPort::Port port) : port(port), sensor(9600, port, 8, frc::SerialPort::Parity::kParity_None,
						 frc::SerialPort::StopBits::kStopBits_One), m_d(-1.0)
{
	sensor.SetReadBufferSize(1);
}

void RangeFinder::update()
{
	int n = sensor.Read(buffer, RANGE_MES_LEN);
	buffer[n] = '\0';
	Logger::log("Range data: '%s' (%d bytes)", buffer, n);

	m_d = -1.0;
}

RangeFinder::~RangeFinder()
{

}

