/*
 * nokia.c
 *
 * Created: 27/03/2018 2:55:34
 * Author : ing_mauro
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "u8g2.h"
#include "u8x8.h"

#define false 0
#define true 1
// PD4=4 SCLK 
// PD5=5 MOSI/DIN/DATA 
// PD7=7 DC/A0
// PB0=8 CS 
// PC0=14 RESET 

u8g2_t u8g2;

uint8_t u8g2_gpio_and_delay_pcd8544(U8X8_UNUSED u8x8_t *u8x8, U8X8_UNUSED uint8_t msg, U8X8_UNUSED uint8_t arg_int, U8X8_UNUSED void *arg_ptr){
	
	switch(msg){
		//Initialize SPI peripheral
		case U8X8_MSG_GPIO_AND_DELAY_INIT:
			break;
		//Function which implements a delay, arg_int contains the amount of ms
		case U8X8_MSG_DELAY_MILLI:
			//_delay_us(arg_int*1000UL);
			for(uint8_t i=arg_int; i > 0; i--) { // Modified here, AVR5
				_delay_ms(1);
			}
			
			break;
		case U8X8_MSG_DELAY_10MICRO:
			_delay_us(10);
			break;
		//Function to define the logic level of the clockline
		case U8X8_MSG_GPIO_SPI_CLOCK:
			if (arg_int == 0) {				// arg_int=0: Output low at SCLK pin
				DDRD |= (1<<DDD4);
				PORTD &= ~(1<<PORTD4);
			} else {						// arg_int=1: Input dir with pullup high for SCLK pin
				DDRD &= ~(1<<PORTD4);		// The same with the rest of pins
				PORTD |= (1<<PORTD4);
			}
			break;
		case U8X8_MSG_GPIO_SPI_DATA:
			if (arg_int == 0) {
				DDRD |= (1<<DDD5);
				PORTD &= ~(1<<PORTD5);
			} else {	
				DDRD &= ~(1<<PORTD5);
				PORTD |= (1<<PORTD5);
			}	
			break;	
		case U8X8_MSG_GPIO_CS:	
			if (arg_int == 0) {
				DDRB |= (1<<DDB0);
				PORTB &= ~(1<<PORTB0);
			} else {	
				DDRB &= ~(1<<PORTB0);
				PORTB |= (1<<PORTB0);
			}	
			break;		
		case U8X8_MSG_GPIO_DC:		
			if (arg_int == 0) {
				DDRD |= (1<<DDD7);
				PORTD &= ~(1<<PORTD7);
			} else {	
				DDRD &= ~(1<<PORTD7);
				PORTD |= (1<<PORTD7);
			}
			break;		
		case U8X8_MSG_GPIO_RESET:
			if (arg_int == 0) {
				DDRC |= (1<<DDC0);
				PORTC &= ~(1<<PORTC0);
			} else {	
				DDRC &= ~(1<<PORTC0);
				PORTC |= (1<<PORTC0);
			}
			break;
		default:
			return 0; //A message was received which is not implemented, return 0 to indicate an error
		}							
	return 1; // command processed successfully.
}

/***************************************************************************
*
*	*	*	*	*	* Graphic Test Functions *	*	*	*	*	*	*	*
*
***************************************************************************/

void u8g2_prepare(void) {
	u8g2_SetFont(&u8g2, u8g2_font_6x10_tf);
	u8g2_SetFontRefHeightExtendedText(&u8g2);
	u8g2_SetDrawColor(&u8g2, 1);
	u8g2_SetFontPosTop(&u8g2);
	u8g2_SetFontDirection(&u8g2, 0);
}

void u8g2_box_frame(uint8_t a) {
	u8g2_DrawStr(&u8g2, 0, 0, "drawBox");
	u8g2_DrawBox(&u8g2, 5,10,20,10);
	u8g2_DrawBox(&u8g2, 10+a,15,30,7);
	u8g2_DrawStr(&u8g2, 0, 30, "drawFrame");
	u8g2_DrawFrame(&u8g2, 5,10+30,20,10);
	u8g2_DrawFrame(&u8g2, 10+a,15+30,30,7);
}


void u8g2_disc_circle(uint8_t a) {
	u8g2_DrawStr(&u8g2, 0, 0, "drawDisc");
	u8g2_DrawStr(&u8g2, 0, 30, "drawCircle");
	u8g2_DrawCircle(&u8g2, 10, 18+30, 9, U8G2_DRAW_ALL);
	u8g2_DrawCircle(&u8g2, 24+a, 16+30, 7, U8G2_DRAW_ALL);
	u8g2_DrawDisc(&u8g2, 10,18,9,U8G2_DRAW_ALL);
	u8g2_DrawDisc(&u8g2, 24+a,16,7,U8G2_DRAW_ALL);
}

void u8g2_r_frame(uint8_t a) {
	u8g2_DrawStr(&u8g2, 0, 0, "drawRFrame/Box");
	u8g2_DrawRFrame(&u8g2, 5, 10,40,30, a+1);
	u8g2_DrawRBox(&u8g2, 50, 10,25,40, a+1);
}

void u8g2_string(uint8_t a) {
	u8g2_SetFontDirection(&u8g2, 0);
	u8g2_DrawStr(&u8g2, 30+a,31, " 0");
	u8g2_SetFontDirection(&u8g2, 1);
	u8g2_DrawStr(&u8g2, 30,31+a, " 90");
	u8g2_SetFontDirection(&u8g2, 2);
	u8g2_DrawStr(&u8g2, 30-a,31, " 180");
	u8g2_SetFontDirection(&u8g2, 3);
	u8g2_DrawStr(&u8g2, 30,31-a, " 270");
}

void u8g2_line(uint8_t a) {
	u8g2_DrawStr(&u8g2, 0, 0, "drawLine");
	u8g2_DrawLine(&u8g2, 7+a, 10, 40, 55);
	u8g2_DrawLine(&u8g2, 7+a*2, 10, 60, 55);
	u8g2_DrawLine(&u8g2, 7+a*3, 10, 80, 55);
	u8g2_DrawLine(&u8g2, 7+a*4, 10, 100, 55);
}

void u8g2_triangle(uint8_t a) {
	uint16_t offset = a;
	u8g2_DrawStr(&u8g2,  0, 0, "drawTriangle");
	u8g2_DrawTriangle(&u8g2, 14,7, 45,30, 10,40);
	u8g2_DrawTriangle(&u8g2, 14+offset,7-offset, 45+offset,30-offset, 57+offset,10-offset);
	u8g2_DrawTriangle(&u8g2, 57+offset*2,10, 45+offset*2,30, 86+offset*2,53);
	u8g2_DrawTriangle(&u8g2, 10+offset,40+offset, 45+offset,30+offset, 86+offset,53+offset);
}

void u8g2_ascii_1() {
	char s[2] = " ";
	uint8_t x, y;
	u8g2_DrawStr(&u8g2, 0, 0, "ASCII page 1");
	for( y = 0; y < 6; y++ ) {
		for( x = 0; x < 16; x++ ) {
			s[0] = y*16 + x + 32;
			u8g2_DrawStr(&u8g2, x*7, y*10+10, s);
		}
	}
}

void u8g2_ascii_2() {
	char s[2] = " ";
	uint8_t x, y;
	u8g2_DrawStr(&u8g2, 0, 0, "ASCII page 2");
	for( y = 0; y < 6; y++ ) {
		for( x = 0; x < 16; x++ ) {
			s[0] = y*16 + x + 160;
			u8g2_DrawStr(&u8g2, x*7, y*10+10, s);
		}
	}
}

void u8g2_extra_page(uint8_t a)
{
	u8g2_DrawStr(&u8g2, 0, 0, "Unicode");
	u8g2_SetFont(&u8g2, u8g2_font_unifont_t_symbols);
	u8g2_SetFontPosTop(&u8g2);
	u8g2_DrawUTF8(&u8g2, 0, 24, "? ?");
	switch(a) {
		case 0:
		case 1:
		case 2:
		case 3:
		u8g2_DrawUTF8(&u8g2, a*3, 36, "?");
		break;
		case 4:
		case 5:
		case 6:
		case 7:
		u8g2_DrawUTF8(&u8g2, a*3, 36, "?");
		break;
	}
}

#define cross_width 24
#define cross_height 24
static const unsigned char cross_bits[] U8X8_PROGMEM  = {
	0x00, 0x18, 0x00, 0x00, 0x24, 0x00, 0x00, 0x24, 0x00, 0x00, 0x42, 0x00,
	0x00, 0x42, 0x00, 0x00, 0x42, 0x00, 0x00, 0x81, 0x00, 0x00, 0x81, 0x00,
	0xC0, 0x00, 0x03, 0x38, 0x3C, 0x1C, 0x06, 0x42, 0x60, 0x01, 0x42, 0x80,
	0x01, 0x42, 0x80, 0x06, 0x42, 0x60, 0x38, 0x3C, 0x1C, 0xC0, 0x00, 0x03,
	0x00, 0x81, 0x00, 0x00, 0x81, 0x00, 0x00, 0x42, 0x00, 0x00, 0x42, 0x00,
0x00, 0x42, 0x00, 0x00, 0x24, 0x00, 0x00, 0x24, 0x00, 0x00, 0x18, 0x00, };

#define cross_fill_width 24
#define cross_fill_height 24
static const unsigned char cross_fill_bits[] U8X8_PROGMEM  = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x18, 0x64, 0x00, 0x26,
	0x84, 0x00, 0x21, 0x08, 0x81, 0x10, 0x08, 0x42, 0x10, 0x10, 0x3C, 0x08,
	0x20, 0x00, 0x04, 0x40, 0x00, 0x02, 0x80, 0x00, 0x01, 0x80, 0x18, 0x01,
	0x80, 0x18, 0x01, 0x80, 0x00, 0x01, 0x40, 0x00, 0x02, 0x20, 0x00, 0x04,
	0x10, 0x3C, 0x08, 0x08, 0x42, 0x10, 0x08, 0x81, 0x10, 0x84, 0x00, 0x21,
0x64, 0x00, 0x26, 0x18, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, };

#define cross_block_width 14
#define cross_block_height 14
static const unsigned char cross_block_bits[] U8X8_PROGMEM  = {
	0xFF, 0x3F, 0x01, 0x20, 0x01, 0x20, 0x01, 0x20, 0x01, 0x20, 0x01, 0x20,
	0xC1, 0x20, 0xC1, 0x20, 0x01, 0x20, 0x01, 0x20, 0x01, 0x20, 0x01, 0x20,
0x01, 0x20, 0xFF, 0x3F, };

void u8g2_bitmap_overlay(uint8_t a) {
	uint8_t frame_size = 28;

	u8g2_DrawStr(&u8g2, 0, 0, "Bitmap overlay");

	u8g2_DrawStr(&u8g2, 0, frame_size + 12, "Solid / transparent");
	u8g2_SetBitmapMode(&u8g2, false);
	u8g2_DrawFrame(&u8g2, 0, 10, frame_size, frame_size);
	u8g2_DrawXBMP(&u8g2, 2, 12, cross_width, cross_height, cross_bits);
	if(a & 4)
	u8g2_DrawXBMP(&u8g2, 7, 17, cross_block_width, cross_block_height, cross_block_bits);

	u8g2_SetBitmapMode(&u8g2, true);
	u8g2_DrawFrame(&u8g2, frame_size + 5, 10, frame_size, frame_size);
	u8g2_DrawXBMP(&u8g2, frame_size + 7, 12, cross_width, cross_height, cross_bits);
	if(a & 4)
	u8g2_DrawXBMP(&u8g2, frame_size + 12, 17, cross_block_width, cross_block_height, cross_block_bits);
}

void u8g2_bitmap_modes(uint8_t transparent) {
	const uint8_t frame_size = 24;

	u8g2_DrawBox(&u8g2, 0, frame_size * 0.5, frame_size * 5, frame_size);
	u8g2_DrawStr(&u8g2, frame_size * 0.5, 50, "Black");
	u8g2_DrawStr(&u8g2, frame_size * 2, 50, "White");
	u8g2_DrawStr(&u8g2, frame_size * 3.5, 50, "XOR");
	
	if(!transparent) {
		u8g2_SetBitmapMode(&u8g2, false );
		u8g2_DrawStr(&u8g2, 0, 0, "Solid bitmap");
		} else {
		u8g2_SetBitmapMode(&u8g2, true);
		u8g2_DrawStr(&u8g2, 0, 0, "Transparent bitmap");
	}
	u8g2_SetDrawColor(&u8g2, 0);// Black
	u8g2_DrawXBMP(&u8g2, frame_size * 0.5, 24, cross_width, cross_height, cross_bits);
	u8g2_SetDrawColor(&u8g2, 1); // White
	u8g2_DrawXBMP(&u8g2, frame_size * 2, 24, cross_width, cross_height, cross_bits);
	u8g2_SetDrawColor(&u8g2, 2); // XOR
	u8g2_DrawXBMP(&u8g2, frame_size * 3.5, 24, cross_width, cross_height, cross_bits);
}

uint8_t draw_state = 0;

void draw(void) {
	u8g2_prepare();
	switch(draw_state >> 3) {
		case 0: u8g2_box_frame(draw_state&7); break;
		case 1: u8g2_disc_circle(draw_state&7); break;
		case 2: u8g2_r_frame(draw_state&7); break;
		case 3: u8g2_string(draw_state&7); break;
		case 4: u8g2_line(draw_state&7); break;
		case 5: u8g2_triangle(draw_state&7); break;
		case 6: u8g2_ascii_1(); break;
		case 7: u8g2_ascii_2(); break;
		case 8: u8g2_extra_page(draw_state&7); break;
		case 9: u8g2_bitmap_modes(0); break;
		case 10: u8g2_bitmap_modes(1); break;
		case 11: u8g2_bitmap_overlay(draw_state&7); break;
	}
}

/*****************************************************************/
void displayInit(void){
	u8g2_Setup_pcd8544_84x48_f(&u8g2, U8G2_R0, u8x8_byte_4wire_sw_spi, u8g2_gpio_and_delay_pcd8544);
	u8g2_InitDisplay(&u8g2);		//Send initialization code to the display
	u8g2_SetPowerSave(&u8g2, 0);
}

int main(void) {
	 displayInit();
	//u8g2.begin();
	while(1){
			// picture loop
		u8g2_ClearBuffer(&u8g2);
		draw();
		u8g2_SendBuffer(&u8g2);
	
		// increase the state
		draw_state++;
		if ( draw_state >= 12*8 )draw_state = 0;

		// deley between each page
		_delay_ms(10);
		
	}
}
