#include "taskFlyport.h"
#include "grovelib.h"
// LIB
#include "serial_lcd.h"
#include "rgb.h"

void FlyportTask()
{	
	TCP_SOCKET inSOCKET = INVALID_SOCKET;
	
	char BFF[500];
	char ch[10];
	char msg[33];
	int i=0,j,ji,jf;
	
	char GET[500];
	sprintf(GET,"GET /wish4u/message.php HTTP/1.1\r\nHost: www.fieldeffectlabs.org\r\n\r\n");
	
	vTaskDelay(100);
	UARTWrite(1,"Welcome to GROVE NEST example!\r\n");

	// GROVE board
	void *board = new(GroveNest);

	// GROVE devices
	
	// RGB leds
	void *rgb = new(Rgb, 2);
	// Attach devices
	attachToBoard(board, rgb, DIG1);
	
	// Initialize RGB
	configure(rgb, 1, 255, 0, 0);
	configure(rgb, 2, 0, 255, 0);
	set(rgb, ON);
	
	// -- 	LCD 	--
	void *slcd = new(SerialLcd,2);
	attachToBoard(board, slcd , DIG2);
	
	if(!configure(slcd))
		UARTWrite(1,"Serial LCD initialized properly!\r\n");
	else
		UARTWrite(1,"Error! The Serial LCD didn't reply\r\n");
	
		/***** Turn on the backlight ****/
	set(slcd,SLCD_CNTL,SLCD_BACKLIGHT_ON);
 
	/***Display text ***/
	set(slcd,SLCD_CNTL,SLCD_CLEAR_DISPLAY);
	set(slcd,SLCD_CNTL,SLCD_RETURN_HOME);
	set(slcd,SLCD_PRNT,"    #Wish4u");

	// -----
	
	
	
	
	
	// Digital Input
	void *button = new(Dig_io, IN);
	attachToBoard(board, button, DIG1);
	
	// Connection to Network
	#if defined (FLYPORT_WF)
	WFConnect(WF_DEFAULT);
	while (WFStatus != CONNECTED);
	#endif
	#if defined (FLYPORTETH)
	while(!MACLinked);
	#endif
	UARTWrite(1,"Flyport connected... hello world!\r\n");
	vTaskDelay(200);
	
	while(1)
	{
		i=0;
		if(!TCPisConn(inSOCKET))
		{
			TCPClientClose(inSOCKET);
			vTaskDelay(20);
			inSOCKET = INVALID_SOCKET;
			inSOCKET = TCPClientOpen("www.fieldeffectlabs.org","80");
		}
		while(!TCPisConn(inSOCKET)&&i<50)
		{
			vTaskDelay(200);
			i++;
			UARTWrite(1,".");
		}
		if(TCPisConn(inSOCKET))
		{
			TCPWrite(inSOCKET,GET,strlen(GET));
			vTaskDelay(200);

			while(TCPRxLen(inSOCKET)>0)
			{
				TCPRead(inSOCKET,ch,1);
				BFF[i]=ch[0];
				i++;
			}
			BFF[i]='\0';
			UARTWrite(1,GET);
			UARTWrite(1,BFF);
		}
		//trascrizione messaggio
		j=0;
		while(BFF[j]!='$')
			j++;
		ji=j+1;
		/*while(BFF[j]!='#')
			j++;
		jf=j-1;*/
		for(j=0;j<32;j++)
			msg[j]=BFF[j+ji];
		//visualizzazione messaggio
		set(slcd,SLCD_CNTL,SLCD_CLEAR_DISPLAY);
		set(slcd,SLCD_CNTL,SLCD_RETURN_HOME);
		set(slcd,SLCD_PRNT,msg);
		for(j=0;j<16;j++){
			set(slcd,SLCD_CNTL,SLCD_SCROLL_LEFT);
			vTaskDelay(100);
		}
	}
}







