/*
 * This file is part of the mps430-ioexp project.
 *
 * Copyright (C) 2011 Stefan Wendler <sw@kaltpost.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ioexp.hpp"

#define CMD_RESET       0xA0
#define CMD_FW_TYPE		0xF0
#define CMD_FW_VERSION	0xF1

ioexp::IOExp::IOExp(ioexp::I2CMasterBus *bus, int slaveAddress)
{
	mbus = bus;

	address = slaveAddress;
}

ioexp::IOExp::~IOExp()
{
}

ioexp::IOExpType ioexp::IOExp::getType()
{
	std::vector<unsigned char> res = mbus->read(address, CMD_FW_TYPE, 1);

	switch(res[0]) {
		case 0x01: return ioexp::IOExpType::DIO;
	}

	return ioexp::IOExpType::UNKNOWN;
}

unsigned char ioexp::IOExp::getFirmwareVersion() 
{
	std::vector<unsigned char> res = mbus->read(address, CMD_FW_VERSION, 1);

	return res[0];
}

void ioexp::IOExp::reset()
{
	std::vector<unsigned char> msg = {CMD_RESET};
	mbus->write(address, msg);
}

