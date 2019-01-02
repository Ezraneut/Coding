/*
 * main.c
 *
 *  Created on: Jan 27, 2016
 *      Author: Ezra
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

//DS chapter 14, page 101: interrupts
//22 / $002A / TIMER0 COMPA / Timer/Counter0 Compare Match A --> TIM0_COMPA

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdbool.h>
#include <asf.h>

//#define ATMEGA2560
//#define ATMEGA8A

#define SREG_I_MASK			(0x80) //Global Interrupt Enable

//#define TCCR0A_WGM1_MASK	(0x02)
//#define TCCR0A_WGM0_MASK	(0x01)
//#define TCCR0B_WGM1_MASK	(0x08)
//#define TCCR0B_CS02_MASK	(0x04)
//#define TCCR0B_CS01_MASK	(0x02)
//#define TCCR0B_CS00_MASK	(0x01)
//#define TCNT0_TCNT0_MASK	(0xFF) //Writing to the TCNT0 Register blocks (removes) the Compare Match on the following timer clock.
//#define TCNT0_OCR0A_VALUE	(0xFF)
//#define TCNT0_OCR0B_VALUE	(0xFF)
//#define TIMSK_OCIE0B_MASK	(0x04) //Timer/Counter0 Compare Match B interrupt is enabled
//#define TIMSK_OCIE0A_MASK	(0x02) //Timer/Counter0 Compare Match A interrupt is enabled
//#define TIMSK_TOIE0_MASK	(0x01)
//#define TIFR0_OCF0B_MASK	(0x04)
//#define TIFR0_OCF0A_MASK	(0x02) //OCF0A bit is set when a Compare Match occurs between the Timer/Counter0 and the data in OCR0A
////OCF0A is cleared by hardware when executing the corresponding interrupt handling vector. Alternatively, OCF0A is cleared by writing a logic one to the flag
//#define TIFR0_TOV0_MASK		(0x01)


typedef struct pattern16 {
    uint16_t LEDs_ON;
    uint8_t ROW;
} pattern16_t;

typedef struct pattern8 {
    uint8_t LEDs_ON;
    uint8_t ROW;
} pattern8_t;

//void shift_out_16(pattern16_t p);
void shift_out_8(uint8_t p);
void shift_out_8_p(pattern8_t p);

void shift_out_16(uint16_t p, uint16_t layer);

void testShiftReg();

void init_TIM0INT();
//#if defined(ATMEGA2560)
//#define CUBE_LYR_PORT	PORTA
//#define SHIFT_DS_1 		(0U) //SER
//#define SHIFT_SHCP_1 	(1U) //SRCLK
//#define SHIFT_STCP_1 	(2U) //RCLK
//#define SHIFT_PORT_1 	PORTL
//
//#define SHIFT_DS_2 		(3U) //SER
//#define SHIFT_SHCP_2 	(4U) //SRCLK
//#define SHIFT_STCP_2 	(5U) //RCLK
//#define SHIFT_PORT_2	PORTL
//
//#define CUBE_LVL_1 		(0U)
//#define CUBE_LVL_2 		(1U)
//#define CUBE_LVL_3 		(2U)
//#define CUBE_LVL_4 		(3U)
//#define CUBE_LYR_PORT	PORTA
//#elif defined(ATMEGA8A)
//#define SHIFT_DS_1 		(0U) //SER
//#define SHIFT_SHCP_1 	(2U) //SRCLK
//#define SHIFT_STCP_1 	(1U) //RCLK
//#define SHIFT_PORT_1 	PORTC
//
//#define SHIFT_DS_2 		(3U) //SER
//#define SHIFT_SHCP_2 	(5U) //SRCLK
//#define SHIFT_STCP_2 	(4U) //RCLK
//#define SHIFT_PORT_2	PORTC
//
//#define CUBE_LVL_1 		(0U)
//#define CUBE_LVL_2 		(1U)
//#define CUBE_LVL_3 		(2U)
//#define CUBE_LVL_4 		(3U)
//#define CUBE_LYR_PORT	PORTD
//#endif

//#define DATA_OUT_HIGH_1()	SHIFT_PORT_1 |= (_BV(SHIFT_DS_1))
//#define DATA_OUT_LOW_1()	SHIFT_PORT_1 &=(~(_BV(SHIFT_DS_1)))
//#define SHIFT_PULSE_1()		SHIFT_PORT_1 |= (_BV(SHIFT_SHCP_1));\
							//SHIFT_PORT_1 &= (~(_BV(SHIFT_SHCP_1)))
//#define DATA_OUT_HIGH_2()	SHIFT_PORT_2 |= (1<<SHIFT_DS_2)
//#define DATA_OUT_LOW_2()	SHIFT_PORT_2 &= (~(1<<SHIFT_DS_2))
//#define SHIFT_PULSE_2()		SHIFT_PORT_2 |= (1<<SHIFT_SHCP_2);\
							//SHIFT_PORT_2 &= (~(1<<SHIFT_SHCP_2));

#define cube_layers 4

uint8_t layer_pins[cube_layers] = {CUBE_LVL_1, CUBE_LVL_2,CUBE_LVL_3,CUBE_LVL_4};

#define pattern_size 4

uint16_t pattern_rows[pattern_size][cube_layers] = {
    {0xF000, 0x0F00, 0x00F0, 0x000F},
    {0x0F00, 0x00F0, 0x000F, 0xF000},
    {0x00F0, 0x000F, 0xF000, 0x0F00},
    {0x000F, 0xF000, 0x0F00, 0x00F0}
};

//uint16_t pattern_plus_square[pattern_size][cube_layers] = {
//		{0xFFFF, 0xFAAF, 0xFAAF, 0xFFFF},
//		{0x0660, 0x6FF6, 0x6FF6, 0x0660}
//};


bool shift_out;

uint16_t buffer_out[cube_layers] = {0,0,0,0};
uint8_t buffer_index = 0;

ISR(TIMER0_OVF_vect)
{
	
    PORTD ^= _BV(7);

    shift_out = true;

    CUBE_LYR_PORT = _BV(layer_pins[buffer_index]);

    buffer_index++;
    if (!(buffer_index <= 3)) {
        buffer_index = 0;
    }
}

int main()
{
	board_init();
    //DDRA |= 0xFF;
    //DDRL |= 0xFF;
    DDRB |= 0xFF;
    DDRC |= 0xFF;
    DDRD |= 0xFF;

//	uint8_t j;
//	while (1) {
//		uint8_t j = 0x01;
//		for (int i = 0;i<8;i++) {
//			shift_out_8(j);
//			j=j<<1;
////			PORTD ^= _BV(7);
//			_delay_ms(500);
//		}
//	}

    //pattern8_t Pattern[4] = {{0x5A,0}, {0xA5,1}, {0x5A,2}, {0xA5,3}};
    //pattern16_t Pattern[4] = {{0xA55A,0}, {0x5AA5,1}, {0xA55A,2}, {0x5AA5,3}};

    uint8_t pattern_index = 0;

    init_TIM0INT();

//	sei();
    SREG |= SREG_I_MASK; // Enable global interrupt
    //The I-bit is cleared by hardware after an interrupt has occurred
//	__enable_interrupt();

    while (1) {

        if (shift_out) {
            shift_out_16(buffer_out[buffer_index], buffer_index);
            shift_out = false;
        }

//		shift_out_16(Pattern[i]);
//		CUBE_LYR_PORT |= (_BV(CUBE_LVL_1));
//		CUBE_LYR_PORT &= (~(_BV(CUBE_LVL_2) | _BV(CUBE_LVL_3) | _BV(CUBE_LVL_4)));
//        _delay_ms(200);

//		shift_out_8(0xA5,1);
//		_delay_ms(2000);
//		CUBE_LYR_PORT |= (_BV(CUBE_LVL_1));
//		CUBE_LYR_PORT &= (~(_BV(CUBE_LVL_2) | _BV(CUBE_LVL_3) | _BV(CUBE_LVL_4)));

        for (uint8_t i = 0; i < cube_layers; i++) {
            buffer_out[i] = pattern_rows[pattern_index][i];
        }

        pattern_index++;
        if (pattern_index == pattern_size) {
            pattern_index=0;
        }
        _delay_ms(100);
    }
    return 0;
}

void shift_out_16(uint16_t p, uint16_t layer)
{
    SHIFT_PORT_1&=(~((1<<SHIFT_STCP_1) | (1<<SHIFT_STCP_2)));
    for (uint8_t i = 0; i < 16; i++) {
        if (i < 8) {
            if (p & 0x8000) {
                DATA_OUT_HIGH_1();
            } else {
                DATA_OUT_LOW_1();
            }
            SHIFT_PULSE_1();
        } else {
            if (p & 0x8000) {
                DATA_OUT_HIGH_2();
            } else {
                DATA_OUT_LOW_2();
            }
            SHIFT_PULSE_2();
        }
        p = p<<1;
    }
    SHIFT_PORT_1 |= ((1<<SHIFT_STCP_1) | (1<<SHIFT_STCP_2));
}
//void shift_out_16(pattern16_t p){
//	SHIFT_PORT_1&=(~((1<<SHIFT_STCP_1) | (1<<SHIFT_STCP_2)));
//	for (uint8_t i = 0; i < 16; i++){
//		if (i < 8){
//			if (p.LEDs_ON & 0x8000){
//				DATA_OUT_HIGH_1();
//			}
//			else{
//				DATA_OUT_LOW_1();
//			}
//			SHIFT_PULSE_1();
//		}
//		else {
//			if (p.LEDs_ON & 0x8000){
//				DATA_OUT_HIGH_2();
//			}
//			else{
//				DATA_OUT_LOW_2();
//			}
//			SHIFT_PULSE_2();
//		}
//		p.LEDs_ON = p.LEDs_ON<<1;
//	}
//	SHIFT_PORT_1 |= ((1<<SHIFT_STCP_1) | (1<<SHIFT_STCP_2));
//
//	CUBE_LYR_PORT = _BV(p.ROW);
//}


void shift_out_8(uint8_t p)
{
    SHIFT_PORT_2&=(~(1<<SHIFT_STCP_2));
    for (uint8_t i = 0; i < 8; i++) {
        if (p & 0x80) {
            DATA_OUT_HIGH_2();
        } else {
            DATA_OUT_LOW_2();
        }
        SHIFT_PULSE_2();
        p = p<<1;
    }
    SHIFT_PORT_2 |= (1<<SHIFT_STCP_2);

}

void shift_out_8_p(pattern8_t p)
{
    SHIFT_PORT_1&=(~(1<<SHIFT_STCP_1));
    for (uint8_t i = 0; i < 8; i++) {
        if (p.LEDs_ON & 0x80) {
            DATA_OUT_HIGH_1();
        } else {
            DATA_OUT_LOW_1();
        }
        SHIFT_PULSE_1();
        p.LEDs_ON = p.LEDs_ON<<1;
    }
    SHIFT_PORT_1 |= (1<<SHIFT_STCP_1);

    CUBE_LYR_PORT = _BV(p.ROW);
}

void init_TIM0INT()
{

    //Clear TOV pending interrupt flag
    TIFR |= (1<<TOV0);

    //Timer overflow register interrupt
    TIMSK |= 1<<TOIE0;

    //Clear OCF0A pending interrupt flag
    //TIFR0 &= (~(1<<OCF0B));

    //Timer compare register interrupt
    //TCNT0 = 1<<OCR0A;

    //Clock select CS: CS00 = 0, CS01 = 1, CS02 = 0 -> CLK/8
    TCCR0 = 1<<CS01; // 8
//	TCCR0 |= 1<<CS02 | 1<<CS00; // 1024

    //Clear counter on compare match (CTC mode) WGM2 = 0, WGM1 = 1, WGM0 = 0
    //TCCR0A |= 1<<WGM01;

    // set timer0 counter initial value to 0
    TCNT0=0x00;
}

