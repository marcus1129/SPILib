/*
 * SPILib.c
 *
 * Created: 2/24/2022 2:56:10 PM
 * Author : Marcus Korre
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#define MASTER 0x00
#define SLAVE 0xff

/* Replace with your library code */
int init(char role){
	sei();
	if(role == MASTER){
		DDRB = 0b00000111; //Sets ss-not, MOSI and SCK to be outputs
		PORTB = 0b00000000;
		SPCR = 0b01011010; //Initiates control register
	}
	else if(role == SLAVE){
		DDRB = 0b00001000; //Sets MISO as output
		PORTB = 0b00000001; //Sets clock to pull high
		SPCR = 0b01001000; //Initiates control register
	}
	else{
		return 0;
	}
	return 1;
}

char transmit(char transmitionCode, int toggleRecieve){
	if((DDRB & 0b00000111) == 0b00000111){
		PORTB |= 0b00000001;
		SPDR = transmitionCode;
		while((SPSR & 0b10000000) != 0b10000000){} //Waits for transmition to finish
		PORTB &= 0b11111110;
		if(toggleRecieve == 1){
			return SPDR;
		}
		else if(toggleRecieve == 0){
			return 1;
		}
	}
	return 0;
}

ISR(SPI_STC_vect){
	
}
