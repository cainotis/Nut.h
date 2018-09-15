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
#include <i2cmaster.h>
#include <Arduino.h>
#include <Servo.h>
#include <Nut.h>
#include <Wire.h>

LDR::LDR(int door,int pimR,int pimG,int pimB){
	port=door;
	ledArray[0]=pimR;
	ledArray[1]=pimG;
	ledArray[2]=pimB;
}
void LDR::setBalance(){
	delay(5000);
	for(int i = 0;i<=2;i++){
		analogWrite(ledArray[i],900);
		delay(100);
		getReading(5);
		whiteArray[i] = avgRead;
		analogWrite(ledArray[i],0);
		delay(100);
	}
	delay(5000);
	for(int i = 0;i<=2;i++){
		analogWrite(ledArray[i],900);
		delay(100);
		getReading(5);
		blackArray[i] = avgRead;
		analogWrite(ledArray[i],0);
		delay(100);
	}
	delay(5000);
}
float* LDR::checkColour(){
	for(int i = 0;i<=2;i++){
		analogWrite(ledArray[i],900);
		delay(100);
		getReading(5);
		colourArray[i] = avgRead;
		float greyDiff = whiteArray[i] - blackArray[i];
		colourArray[i] = (colourArray[i] - blackArray[i])/(greyDiff)*255;
		analogWrite(ledArray[i],0);
		delay(100);
	}
	return colourArray;
}
void LDR::getReading(int times){
	int reading;
	int tally=0;
	for(int i = 0;i < times;i++){
		reading = analogRead(port);
		tally = reading + tally;
		delay(10);
	}
	avgRead = (tally)/times;
}

LED::LED(short pimR,short pimG,short pimB){
	pinR = pimR;
	pinG = pimG;
	pinB = pimB;
}
void  LED::Update(short red,short green,short blue){
	analogWrite(pinR, red  );
	analogWrite(pinG, green);
	analogWrite(pinB, blue );
}

MLX::MLX(byte address){
	addr=address;
}
float MLX::temperature(){
	int dev = addr<<1;
    int data_low = 0;
    int data_high = 0;
    int pec = 0;
    
    i2c_start_wait(dev+I2C_WRITE);
    i2c_write(0x07);
    
    i2c_rep_start(dev+I2C_READ);
    data_low = i2c_readAck(); 
    data_high = i2c_readAck(); 
    pec = i2c_readNak();
    i2c_stop();
    
    double tempFactor = 0.02; 
    double tempData = 0x0000; 
    int frac; 
    
    tempData = (double)(((data_high & 0x007F) << 8) + data_low);
    tempData = (tempData * tempFactor)-0.01;
    
    float celcius = tempData - 273.15;
    return celcius;
}

point operator+(point a,point b){
	return point(a.x+b.x,a.y+b.y);
}
point operator-(point a,point b){
	return point(a.x-b.x,a.y-b.y);
}
bool operator==(point a,point b){
	return (a.x==b.x && a.y==b.y);
}

bool operator!(cardinals a){
	if(a.n || a.e || a.s || a.o) return false;
	return true;
}
