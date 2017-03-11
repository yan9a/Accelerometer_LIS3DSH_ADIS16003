//#############################################################################
//Interface to accelerometer
//File Name   : ADIS16003.c
//Programmer  : Yan Naing Aye
//Date        : 15 April 2011
//Last Updated: 15 April 2011
//#############################################################################
#include "Headers.h"
//*****************************************************************************
//-----------------------------------------------------------------------------
ui08 idata x1l,x2l,x3l,x4l,x1h,x2h,x3h,x4h;
ui08 idata y1l,y2l,y3l,y4l,y1h,y2h,y3h,y4h;
//-----------------------------------------------------------------------------
void AccInit()
{
	_CS =1; 
	_TCS=1; 
	SCLK=1; 
	MOSI=1; 
	MIS1=1; 
	MIS2=1; 
	MIS3=1; 
	MIS4=1;
}
//-----------------------------------------------------------------------------
void AccRdX()
{
	ui08 d=0x04;
	ui08 i;

	//SysDI();//Enter critical section
	SCLK=1;		
	_CS=0; //enable
	for(i=0;i<16;i++)
	{
		if(i<8)
		{
			MOSI=(d & 0x80)?1:0;
			//Delay(period/2)-optional for slower SPI bus speed			
			SCLK=0;
			d<<=1;
			x1h<<=1;
			x2h<<=1;
			x3h<<=1;
			x4h<<=1;
			//Delay(period/2)-optional for slower SPI bus speed
			SCLK=1;			
			x1h|=MIS1;
			x2h|=MIS2;
			x3h|=MIS3;
			x4h|=MIS4;
		}
		else
		{
			MOSI=0;
			//Delay(period/2)-optional for slower SPI bus speed
			SCLK=0;			
			x1l<<=1;
			x2l<<=1;
			x3l<<=1;
			x4l<<=1;
			//Delay(period/2)-optional for slower SPI bus speed
			SCLK=1;
			x1l|=MIS1;
			x2l|=MIS2;
			x3l|=MIS3;
			x4l|=MIS4;
		}
	}
	_CS=1;
	//SysEI();//Exit critical section
	//ComPrintHex(x1h);	
	//ComPrintHex(x1l);
	//ComPutch(0x0a);		
}
//-----------------------------------------------------------------------------
void AccRdY()
{
	ui08 d=0x0C;
	ui08 i;

	//SysDI();//Enter critical section
	SCLK=1;

	_CS=0; //enable
	for(i=0;i<16;i++)
	{
		if(i<8)
		{
			MOSI=(d & 0x80)?1:0;
			//Delay(period/2)-optional for slower SPI bus speed
			SCLK=0;
			d<<=1;
			y1h<<=1;
			y2h<<=1;
			y3h<<=1;
			y4h<<=1;
			//Delay(period/2)-optional for slower SPI bus speed
			SCLK=1;
			y1h|=MIS1;
			y2h|=MIS2;
			y3h|=MIS3;
			y4h|=MIS4;
		}
		else
		{
			MOSI=0;
			//Delay(period/2)-optional for slower SPI bus speed
			SCLK=0;
			y1l<<=1;
			y2l<<=1;
			y3l<<=1;
			y4l<<=1;
			//Delay(period/2)-optional for slower SPI bus speed
			SCLK=1;
			y1l|=MIS1;
			y2l|=MIS2;
			y3l|=MIS3;
			y4l|=MIS4;
		}
	}
	_CS=1;
	//SysEI();//Exit critical section	
}
//-----------------------------------------------------------------------------
void AccUpdate()
{	
	AccRdX();	
	AccRdY();
}
//-----------------------------------------------------------------------------
void AccGetVal(ui08 val[])
{
	val[0]=x1h;
	val[1]=x1l;
	val[2]=y1h;
	val[3]=y1l;

	val[4]=x2h;
	val[5]=x2l;
	val[6]=y2h;
	val[7]=y2l;

	val[8]=x3h;
	val[9]=x3l;
	val[10]=y3h;
	val[11]=y3l;

	val[12]=x4h;
	val[13]=x4l;
	val[14]=y4h;
	val[15]=y4l;
}
//-----------------------------------------------------------------------------