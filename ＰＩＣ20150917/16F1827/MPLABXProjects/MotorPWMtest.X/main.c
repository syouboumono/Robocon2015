#include <xc.h>
#include <pic16f1827.h>

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable (Brown-out Reset disabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = OFF       // Internal/External Switchover (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is disabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config PLLEN = OFF      // PLL Enable (4x PLL disabled)
#pragma config STVREN = OFF     // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will not cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = OFF        // Low-Voltage Programming Enable (High-voltage on MCLR/VPP must be used for programming)

#define _XTAL_FREQ 8000000

void main(void)
{
    OSCCON   = 0x72;  //clkf=8MHz
    TRISA    = 0x20;
    PORTA    = 0x00;
    ANSELA   = 0x00;
    TRISB    = 0x00;
    PORTB    = 0x00;
    ANSELB   = 0x00;

    //PWM
    CCPTMRS  = 0x00;  //Timer2
    CCP1CON  = 0xCC;  //PWM     forwoard:4C    reverse:CC
    PSTR1CON = 0x0A;
    CCP1SEL  = 0;
    P1CSEL   = 0;
    P1DSEL   = 1;
    T2CON    = 0x00;  //*1
    PR2      = 124;   //PWMf 16kHz
    CCPR1L   = 0;     //dutty reset
    CCPR1H   = 0;
    TMR2     = 0;     //timer reset
    TMR2ON   = 1;     //timeron


//    int i = 0;

   
    CCPR1L = 52;

    while(1){
        NOP();
    }

}
