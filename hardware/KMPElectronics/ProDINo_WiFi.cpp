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

#include "Typicals.h"
#include "GetConfig.h"
#include "ProDINo.h"


uint8_t  TX_Data[16];
uint8_t  RX_Data[16];

/**************************************************************************
/*!
	Init the MCP23S17M I/O module
*/	
/**************************************************************************/
void MCP23S17M_Begin()
{
	SPI.begin();
	SPI.setHwCs(15);
	SPI.setFrequency(1000000);
	SPI.setDataMode(SPI_MODE0);

	pinMode(CS, OUTPUT);
	digitalWrite(CS, HIGH);
}

/**************************************************************************
/*!
	Set the I/O direction for the MCP23S17M pins
*/	
/**************************************************************************/
void MCP23S17M_mode(uint8_t PortNum, uint8_t mode)
{
	uint8_t Tmp = EXPReadREG(IODIR);
	if (INPUT == mode)Tmp |= (1 << PortNum); else Tmp &= ~(1 << PortNum);
	MCP23S17M_writeregister(IODIR, Tmp);
}

/**************************************************************************
/*!
	Write the MCP23S17M pins
*/	
/**************************************************************************/
void MCP23S17M_write(uint8_t PortNum, uint8_t state)
{
	uint8_t Tmp = EXPReadREG(OLAT);
	if (HIGH == state)Tmp |= (1 << PortNum); else Tmp &= ~(1 << PortNum);
	MCP23S17M_writeregister(OLAT, Tmp);
}

/**************************************************************************
/*!
	Read the MCP23S17M pins
*/	
/**************************************************************************/
bool MCP23S17M_read(uint8_t PortNum)
{
	uint8_t Tmp = MCP23S17M_readregister(GPIO);
	if (Tmp&(1 << PortNum)) return true; else return false;
}

/**************************************************************************
/*!
	Read the MCP23S17M register
*/	
/**************************************************************************/
uint8_t MCP23S17M_readregister(uint8_t addr)
{
	TX_Data[0] = READ_CMD;
	TX_Data[1] = addr;
	digitalWrite(CS, LOW);
	SPI.transferBytes(TX_Data, RX_Data, 3);
	digitalWrite(CS, HIGH);
	return RX_Data[2];
}

/**************************************************************************
/*!
	Write the MCP23S17M register
*/	
/**************************************************************************/
void MCP23S17M_writeregister(uint8_t addr, uint8_t data)
{
	TX_Data[0] = WRITE_CMD;
	TX_Data[1] = addr;
	TX_Data[2] = data;
	digitalWrite(CS, LOW);
	SPI.transferBytes(TX_Data, RX_Data, 3);
	digitalWrite(CS, HIGH);
}

