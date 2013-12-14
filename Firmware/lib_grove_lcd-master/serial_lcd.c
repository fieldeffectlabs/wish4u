/** \file serial_lcd.c
 *  \brief Grove devices support library 
 */

/**
\addtogroup Grove devices
@{
*/
/* **************************************************************************																					
 *                                OpenPicus                 www.openpicus.com
 *                                                            italian concept
 * 
 *            openSource wireless Platform for sensors and Internet of Things	
 * **************************************************************************
 *  FileName:        serial_lcd.c
 *  Dependencies:    OpenPicus libraries
 *  Module:          FlyPort WI-FI - FlyPort ETH
 *  Compiler:        Microchip C30 v3.12 or higher
 *
 *  Author               Rev.    Date              Comment
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  Davide Vicca	     1.0     01/07/2013		   First release  
 *  
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 *  Software License Agreement
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  This is free software; you can redistribute it and/or modify it under
 *  the terms of the GNU General Public License (version 2) as published by 
 *  the Free Software Foundation AND MODIFIED BY OpenPicus team.
 *  
 *  ***NOTE*** The exception to the GPL is included to allow you to distribute
 *  a combined work that includes OpenPicus code without being obliged to 
 *  provide the source code for proprietary components outside of the OpenPicus
 *  code. 
 *  OpenPicus software is distributed in the hope that it will be useful, but 
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 *  more details. 
 * 
 * 
 * Warranty
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * WE ARE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE.
 *
 **************************************************************************/

//#include <stdlib.h>
//#include <stdarg.h>
#include "taskFlyport.h"
#include "grovelib.h"
#include "serial_lcd.h"


struct Interface *attachSensorToUartBus(void *,int,int,BYTE,BYTE);

/**
 * struct SerialLcd - The structure for SerialLcd grove sensor 
 */
struct SerialLcd
{
	const void *class;
	struct Interface *inter;
	BYTE devaddress; 
	BYTE gain; 
	BYTE integr;
	BYTE uart_module;
	BYTE uart_interface;
};


/**
 * static void init (struct SerialLcd *self)
 * \param *self - pointer to the Serial LCD grove device class.
 * \return - None
*/
static void init(struct SerialLcd *self)
{
    UARTWriteCh(self->uart_module,SLCD_CONTROL_HEADER);
    UARTWriteCh(self->uart_module,SLCD_POWER_OFF);
	DelayMs(10);
    UARTWriteCh(self->uart_module,SLCD_CONTROL_HEADER);
    UARTWriteCh(self->uart_module,SLCD_POWER_ON);
	DelayMs(1);
	UARTFlush(self->uart_module);
	UARTWriteCh(self->uart_module,SLCD_INIT_ACK);
}

/**
 * static void *SerialLcd_ctor (void * _self, va_list *app) -SerialLcd grove device Constructor  
 * \param *_self - pointer to the SerialLcd grove device class.
 * \param *app - uart module to be used for communication
* \return - Pointer to the SerialLcd devices instantiated
*/
static void *SerialLcd_ctor (void * _self, va_list *app)
{
	struct SerialLcd *self = _self;
	self->uart_module =  va_arg(*app, BYTE);
	switch(self->uart_module)
	{
		case 2 :
		{
			self->uart_interface = 7;
			break;
		}
		case 3 :
		{
			self->uart_interface = 9;
			break;
		}
		case 4 :
		{
			self->uart_interface = 11;
			break;
		}			
	}
	self->inter = NULL;
	return self;
}

/**
 * static void SerialLcd_dtor (void * _sensor)- SerialLcd grove device Destructor  
 * \param *_sensor - pointer to the SerialLcd grove device class.
 * \return - None
*/
static void SerialLcd_dtor (void * _sensor)
{
	struct SerialLcd *sensor = _sensor;
	if(sensor->inter)
	{
		free(sensor->inter->port);
		free(sensor->inter);
	}
}


/**
 * static void* SerialLcd_attach (void * _board,void *_sensor,int n) - attach a SerialLcd grove device to the GroveNest digital I/O port  
 * \param *_board - pointer to the GroveNest 
 * \param *_sensor - pointer to the SerialLcd grove device class.
 * \param n - port number which SerialLcd device is connected to
 * \return 
 <UL>
	<LI><Breturn = Pointer to the digital interface created:</B> the operation was successful.</LI> 
	<LI><B>return = NULL:</B> the operation was unsuccessful.</LI> 
 </UL>
 */
static void *SerialLcd_attach (void * _board,void *_sensor,int port)
{
	struct SerialLcd *sensor = _sensor;
	sensor->inter = attachSensorToUartBus(_board,port,9600,sensor->uart_module,sensor->uart_interface);	
	UARTOff(sensor->uart_module);
	return sensor->inter;
}


/**
 *  static int SerialLcd_configure (void * _self, va_list *app) -  Configure the SerialLcd grove device
 * \param *_self - pointer to the device 
 * \param *app - none 
 * \return:
 	<LI><Breturn = 0:</B>when the Serial LCD device is properly configured </LI> 
 	<LI><Breturn = -1:</B>when the operation was unsucceful (the Serial LCD device will not work) </LI> 
 </UL>
 */
static int SerialLcd_config (void * _self, va_list *app)
{
	struct SerialLcd *self = _self;
	UARTOn(self->uart_module);
	init(self);
	//wait for ack from the Serial LCD device
	char message[4];
	//allow the Serial LCD to acknownledge the Flyport
	vTaskDelay(30);
	int toread = UARTBufferSize(self->uart_module); 
	UARTRead(self->uart_module,message, toread); 
	message[toread+1]='\0';
	char *mes = &message[0];
	while(*mes != '\0')
	{ /* ACK sent*/
		if((BYTE)*mes == SLCD_INIT_DONE)
		{    
			UARTWriteCh(self->uart_module,SLCD_CONTROL_HEADER);
			UARTWriteCh(self->uart_module,SLCD_LEFT_TO_RIGHT);
			return 0;
		}
		else
			mes++;
	}
	/*No ACK received (the Serial LCD device is not configured*/
	return -1;
}


/**
 * static float SerialLcd_set(void * _self,va_list *app) -  write into the SerialLcd device.
 * \param *_self - pointer to the device 
 *  	1- Command Type (SLCD_CNTL Serial LCD device control command)
 *						(SLCD_POST Serial LCD device cursor position command)
 * 						(SLCD_PRNT Serial LCD device printing command)
 *		2- Argument of Command
 *\return the status of the operation:
  	<LI><Breturn = 0:</B>when the command was properly interpreted </LI> 
 	<LI><Breturn = -1:</B>when the command sent was unknown </LI> 
*/
static int SerialLcd_set (void *_self,va_list *app)
{
	struct SerialLcd *self = _self;
	BYTE param = va_arg(*app, const BYTE);
	BYTE state;
	char *text;
	if(param == SLCD_PRNT)
	{	/***Printing command****/
		text =  va_arg(*app, char *);
		UARTWriteCh(self->uart_module,SLCD_CHAR_HEADER);
		UARTWrite(self->uart_module,text);
	}
	else if (param == SLCD_CNTL)
	{	/***Control command****/
		state = va_arg(*app, const BYTE);	
		UARTWriteCh(self->uart_module,SLCD_CONTROL_HEADER);
		UARTWriteCh(self->uart_module,state);
		if((state == SLCD_CLEAR_DISPLAY) || (state == SLCD_RETURN_HOME))
			vTaskDelay(5);
	}
	else if(param == SLCD_POST)
	{	/***Cursor position command****/
		BYTE column = va_arg(*app, const BYTE);
		BYTE row = va_arg(*app, const BYTE);
		UARTWriteCh(self->uart_module,SLCD_CONTROL_HEADER);
		UARTWriteCh(self->uart_module,SLCD_CURSOR_HEADER);			
		UARTWriteCh(self->uart_module,column);
		UARTWriteCh(self->uart_module,row);
	}
	else
		return -1;//command unknown
	//vTaskDelay(5);
	return 0; 
}

static const struct SensorClass _SerialLcd =
{	
	sizeof(struct SerialLcd),
	SerialLcd_ctor,
	SerialLcd_dtor,
	SerialLcd_attach,
	SerialLcd_config,
	SerialLcd_set,
	0
};

const void *SerialLcd = &_SerialLcd;

