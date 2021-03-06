#include "mbed.h"
#include "uLCD_4DGL.h"

uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;

DigitalIn upbutton(D3);
DigitalIn downbutton(D9);
DigitalIn confirmbutton(D5);

AnalogOut aout(PA_4);
AnalogIn ain(D11);

double ADCdata[500];

int main(){
	uLCD.text_width(1);
	uLCD.text_height(1);
	uLCD.color(RED);

    	int display_frequency = 30;
	int frequency = 30;
	double piece = 0.0;
	double T = 1000.0 / frequency;
	int index = 0;
	int sample = 25;
	int count=0;

	while(1){
		if(upbutton){
			display_frequency += 10;
			uLCD.locate(1, 2);
			uLCD.printf("%4d %4d\n", display_frequency, frequency);
		}
		if(downbutton){
			display_frequency -= 10;
			uLCD.locate(1, 2);
			uLCD.printf("%4d %4d\n", display_frequency, frequency);
		}
		// the GUI bar display the scale of frequency
		// uLCD.line(0, 100, display_frequency/10, 100, WHITE);
		// uLCD.line(display_frequency/10, 100, 1000, 100, RED);
		if (confirmbutton){
			frequency = display_frequency;
			T = 1000.0 / frequency;
			uLCD.locate(1, 2);
			uLCD.printf("%4d %4d\n", display_frequency, frequency);
			sample = 100 * frequency / 500;
			for(int i=0; i<500; i++){
				printf("%.3f\r\n", ADCdata[i]);
			}
		}
		// display the next frequency we choose and current frequency
		
		if(piece >= T){
			piece = 0;
		}
		else if(piece <= 0.5*T){
			aout = piece / (0.55*T);
		} 
		else {
			aout = (T-piece) / (0.55*T);
		}
		piece += (T/100.0);

		if(index >= 500){
			count = 0;
			index = 0;
		}
		else if(index<500 && (count % sample == 0)){
			ADCdata[index] = ain;
			index++;
		}
		count++;
		wait_us(T*10-30);
	}
}
