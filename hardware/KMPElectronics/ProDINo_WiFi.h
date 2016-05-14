/**************************************************************************
	Souliss Support for DINo WiFi
    Copyright (C) 2016  Veseo

    WiFi board based on ESP8266 with optoinput, relay and RS485
	
***************************************************************************/

/**************************************************************************
	Souliss
    Copyright (C) 2016  Veseo

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
	
	Originally developed by Dario Di Maio and Plamen Kovandjiev
	
***************************************************************************/
/*!
    \file 
    \ingroup
*/
#ifndef DINOWiFi_H
#define DINOWiFi_H

// KMP Electronics DINo Pinouts

#define RELAY4 				0x07
#define RELAY3 				0x06
#define RELAY2 				0x05
#define RELAY1 				0x04

#define IN1 				0x00
#define IN2 				0x01
#define IN3 				0x02
#define IN4 				0x03

#define CS 					15
#define STATLED 			16


#define	SetInput1()			MCP23S17M_mode(IN1, INPUT)
#define	SetInput2()			MCP23S17M_mode(IN2, INPUT)
#define	SetInput3()			MCP23S17M_mode(IN3, INPUT)
#define	SetInput4()			MCP23S17M_mode(IN4, INPUT)

#define	SetRelay1()			MCP23S17M_mode(RELAY1, OUTPUT)
#define	SetRelay2()			MCP23S17M_mode(RELAY2, OUTPUT)
#define	SetRelay3()			MCP23S17M_mode(RELAY3, OUTPUT)
#define	SetRelay4()			MCP23S17M_mode(RELAY4, OUTPUT)

#define	SetLED()			pinMode(STATLED, OUTPUT)
#define ToggleLED()			digitalWrite(STATLED, !digitalRead(STATLED))
#define	TurnOnLED()			digitalWrite(STATLED, LOW)
#define	TurnOffLED()		digitalWrite(STATLED, HIGH)
#define	StartupLED()		for(uint8_t l=0;l<10;l++){							\
								digitalWrite(STATLED, !digitalRead(STATLED));	\
								delay(500);}									\
								digitalWrite(STATLED, LOW)

// Set the Reset and PWDN pins in DINo version 2
#define	InitDINo()			MCP23S17M_Begin();					\
							SetInput1(); 						\
							SetInput2());						\
							SetInput3();						\
							SetInput4();						\
							SetRelay1();						\
							SetRelay2();						\
							SetRelay3();						\
							SetRelay4();						\
							delay(1000)	

// Reduce power consumption switching off the ESP8266 WiFi
#define	PowerDownWiFi()		WiFi.mode(WIFI_OFF);

void MCP23S17M_Begin();
void MCP23S17M_mode(uint8_t PortNum, uint8_t mode);
void MCP23S17M_write(uint8_t PortNum, uint8_t state);
bool MCP23S17M_read(uint8_t PortNum);
uint8_t MCP23S17M_readregister(uint8_t addr);
void MCP23S17M_writeregister(uint8_t addr, uint8_t data);
		
#endif
