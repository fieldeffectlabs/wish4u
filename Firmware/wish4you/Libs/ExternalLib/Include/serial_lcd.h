/** \file serial_lcd.h
 *  \brief header file for the Serial LCD Grove device library
 */

/**
\addtogroup 
@{
*/

/* **************************************************************************																					
 *                                OpenPicus                 www.openpicus.com
 *                                                            italian concept
 * 
 *            openSource wireless Platform for sensors and Internet of Things	
 * **************************************************************************
 *  FileName:        serial_lcd.h
 *  Dependencies:    Microchip configs files
 *  Module:          FlyPort WI-FI
 *  Compiler:        Microchip C30 v3.12 or higher
 *
 *  Author               Rev.    Date              Comment
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *  Davide Vicca   1.0     01/07/2013		   First release  (core team)
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

extern const void *SerialLcd;

#ifndef SERIAL_LCD_H
#define SERIAL_LCD_H


//Initialization Commands or Responses
#define SLCD_INIT	0xA3
#define SLCD_INIT_ACK	0xA5
#define SLCD_INIT_DONE	0xAA

//WorkingMode Commands or Responses
#define SLCD_CONTROL_HEADER	0x9F
#define SLCD_CHAR_HEADER	0xFE
#define SLCD_CURSOR_HEADER	0xFF
#define SLCD_CURSOR_ACK		0x5A

#define SLCD_RETURN_HOME	0x61
#define SLCD_INVALIDCOMMAND	0x46

//Flyport Commands
#define SLCD_PRNT			0xFE
#define SLCD_CNTL			0x9F
#define SLCD_POST			0xFF



/****DISPLAY function****/
#define SLCD_DISPLAY_OFF	0x63
#define SLCD_DISPLAY_ON		0x64
#define SLCD_CLEAR_DISPLAY	0x65

/****CURSOR function****/
#define SLCD_CURSOR_OFF		0x66
#define SLCD_CURSOR_ON		0x67

/****BLINKING function****/
#define SLCD_BLINK_OFF		0x68
#define SLCD_BLINK_ON		0x69

/****SCROLLING function****/
#define SLCD_SCROLL_LEFT	0x6C
#define SLCD_SCROLL_RIGHT	0x72
//#define SLCD_NO_AUTO_SCROLL	0x6A
//#define SLCD_AUTO_SCROLL	0x6D

/****MOVING function****/
#define SLCD_LEFT_TO_RIGHT	0x70
#define SLCD_RIGHT_TO_LEFT	0x71

/****POWER function****/
#define SLCD_POWER_ON    	0x83
#define SLCD_POWER_OFF  	0x82


/****BACKLIGTH function****/
#define SLCD_BACKLIGHT_ON	0x81
#define SLCD_BACKLIGHT_OFF	0x80

#endif

