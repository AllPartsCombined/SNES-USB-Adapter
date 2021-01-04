/*
This is the part of the ProTrinketGamepad code that is exposed to the user
See the header file for more comments on the functions

Copyright (c) 2015 Adafruit Industries
All rights reserved.

ProTrinketGamepad is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

ProTrinketGamepad is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with ProTrinketGamepad. If not, see
<http://www.gnu.org/licenses/>.
*/

#include "cmdline_defs.h"
#include "ProTrinketGamepad.h"
#include "ProTrinketGamepadC.h"

#include <stdint.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// create an instance that the user can use
Trinket_Gamepad TrinketGamepad;

// empty constructor
Trinket_Gamepad::Trinket_Gamepad()
{
	// nothing to do
}

// starts the USB driver, causes re-enumeration
void Trinket_Gamepad::begin()
{
	usbBegin();
}

// makes a gamepad movement, must be called at least once every 10ms, even if no movement

void Trinket_Gamepad::move(uint16_t buttonMask1, uint16_t buttonMask2, uint16_t buttonMask3, uint16_t buttonMask4)
{
	//int16_t * signed_ptr = (int16_t *)report_buffer;
	uint8_t * unsigned_ptr = (uint8_t *)report_buffer;
	unsigned_ptr[0] = 1;
	unsigned_ptr[1] = (uint8_t)(buttonMask1 & 0xff);
	unsigned_ptr[2] = (uint8_t)(buttonMask1 >> 8);
	unsigned_ptr[3] = 2;
	unsigned_ptr[4] = (uint8_t)(buttonMask2 & 0xff);
	unsigned_ptr[5] = (uint8_t)(buttonMask2 >> 8);
	unsigned_ptr[6] = 3;
	unsigned_ptr[7] = (uint8_t)(buttonMask3 & 0xff);
	unsigned_ptr[8] = (uint8_t)(buttonMask3 >> 8);
	unsigned_ptr[9] = 4;
	unsigned_ptr[10] = (uint8_t)(buttonMask4 & 0xff);
	unsigned_ptr[11] = (uint8_t)(buttonMask4 >> 8);
	
	usbReportSend();
}

// checks if USB is connected, 0 if not connected
char Trinket_Gamepad::isConnected()
{
	return usb_hasCommed;
}
