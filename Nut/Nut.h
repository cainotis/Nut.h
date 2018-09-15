/*
	Nut.h - Library for Rescue Maze
	Created by Cainã S. Galante, October 10, 2016.
	Updated, October 11, 2016
	Updated, October 18, 2016
	Updated, April 6, 2017
	Updated, May 3, 2017
	Updated, May 27, 2017
	Updated, July 7,2017
	Updated in Nagoya, July 29,2017
*/

#ifndef Nut_h
#define Nut_h

#include <i2cmaster.h>
#include <Arduino.h>
#include <Servo.h>
#include <Wire.h>

class LDR{
	public:
		LDR(int door,int pimR,int pimG,int pimB);
		void setBalance();
		float* checkColour();
	private:
		int ledArray[3];
		int port;
		void getReading(int times);
		float colourArray[3];
		float whiteArray[3];
		float blackArray[3];
		int avgRead;
};

class  LED{
	public:
		LED(short pimR,short pimG,short pimB);
		void Update(short red,short green,short blue);
	private:
		short pinR;
		short pinG;
		short pinB;
};

class MLX{
	public:
		MLX(byte address);
		float temperature();
	private:
		byte addr;
};

struct point{
	short x,y;
	point(short xx=0,short yy=0){
		x=xx;
		y=yy;
	}
};
point operator+(point a,point b);
point operator-(point a,point b);
bool operator==(point a,point b);

struct cardinals{
	bool n,e,s,o;
	cardinals(bool ff=false,bool rr=false,bool bb=false,bool ll=false){
		n=ff;
		e=rr;
		s=bb;
		o=ll;
	}
};
bool operator!(cardinals a);

#endif