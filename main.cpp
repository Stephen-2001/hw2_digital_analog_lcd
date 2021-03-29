#include "mbed.h"
#include "uLCD_4DGL.h"

uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;

DigitalIn upbutton(D7);
DigitalIn downbutton(D8);
DigitalIn confirmbutton(D9);


int main(){
	uLCD.text_width(1);
	uLCD.text_height(1);
	uLCD.color(RED);

    int display_frequency = 100;
	int frequency = 100;
	bool uplimit = false;
	bool downlimit = false;
	bool confirmlimit = false;

	while(1){
		// set up the UP button
		// after push, display_frequency +10
		if(upbutton){
			if(!uplimit){
				display_frequency += 10;
				uplimit = true;
				ThisThread::sleep_for(1ms);
			}
		} else {
			uplimit = false;
		}
		// set up the DOWN button
		// after push, display_frequency -10
		if(downbutton){
			if(!downlimit){
				display_frequency -= 10;
				downlimit = true;
				ThisThread::sleep_for(1ms);
			}
		} else {
			downlimit = false;
		}
		// set up the CONFIRM button
		// after push, frequency = display_frequency
		if (confirmbutton){
			if(!confirmlimit){
				frequency = display_frequency;
				confirmlimit = true;
				ThisThread::sleep_for(1ms);
			}
		} else {
			confirmlimit = false;
		}

		uLCD.locate(1, 2);
		uLCD.printf("%4d %4d\n", display_frequency, frequency);
		uLCD.line(0, 100, display_frequency/10, 100, WHITE);
		uLCD.line(display_frequency/10, 100, 1000, 100, RED);
	}
	
}