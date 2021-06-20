/*
 * PasswordBasedDoorLock.c
 *
 * Created: 6/10/2019 9:22:31 PM
 * Author : Sharuka Thirimanne
 */ 
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include "Keypad.h"

void LCDPinConfig(void){
	PORTB |= 0B11000000; //Enable RS and E of the LCD
	PORTA |= 0xFF; //Enable D0,D1,D2,D3,D4,D5,D6,D7 on LCD
}
void LCDDDRConfig(void){
	DDRB |= 0B11000000; //Data Direction of Rs and E
	DDRA |= 0xFF; //Data Direction of D0,D1,D2,D3,D4,D5,D6,D7
}
void send_a_command (unsigned char command)
{
	PORTA=command;
	PORTB&= 0B01111111;
	PORTB|= 0B01000000;
	_delay_ms(25);
	PORTB &= 0B10111111;
}
void send_a_character (unsigned char character)
{
	PORTA=character;
	PORTB |= 0B11000000;
	_delay_ms(50);
	PORTB &= 0B10111111;
}

void send_a_string(char *stringchar){
	while(*stringchar>0){
		send_a_character(*stringchar++);
	}
}



int main(void)
{
	LCDDDRConfig();
	LCDPinConfig();
	
	send_a_command(0x01);// sending all clear command
	send_a_command(0x38);// 16*2 line LCD
	send_a_command(0x0C);// screen ON

	send_a_string("ENTER THE CODE");
	send_a_command(0xC0);
	
    /* Replace with your application code */
    while (1) 
    {
		for (int i=0;i<4;i++)
		{
			KP_KeyPressed();
			KP_WaitRelease();
			KP_GetKeyISR();
			ReadRows();
			ReadColumns();
			ToggleRC();
		}
    }
}

