#include <xc.h>
#include <pic16f1827.h>

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = OFF      // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
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

int Tcount = 0;
int Xcount = 0;
int Ycount = 0;


void interrupt Timer(void)
{
    if(TMR0IF == 1){
        TMR0 = 246;
        Tcount++;
        TMR0IF = 0;
    }
}

void main(void)
{
    OSCCON       = 0x72;  //clkf=8MHz
    TRISA        = 0b00101100;
    PORTA        = 0x00;  //pin all low
    ANSELA       = 0x00;  //not analog
    TRISB        = 0b00000010;  //RB1:SDI1 RB2:SDO RB3:Motor RB4:SCK RB5:PWM RB6:Motor RB7:PWM
    PORTB        = 0x00;  //pin all low
    ANSELB       = 0x00;  //not analog

    //Timer
    OPTION_REG   = 0b00000000; //pr2
    TMR0         = 0;
    TMR0IF       = 0;
    TMR0IE       = 0;
    GIE          = 1;

    /*SPI Master
    SDO1SEL      = 0;     //RB2:SDO
    SS1SEL       = 1;     //RA5:SS
    SSP1CON1     = 0x20;  //CHP:low
    SSP1STAT     = 0x00;  //CKE:up Smple:center*/

    while(1){
        //Xcheck
        while(RA2 == 1);
        while(RA2 == 0);
        TMR0 = 246;
        Tcount = 0;

        while(RA2 == 1);
        Xcount = Tcount;

        //Ycheck
        while(RA3 == 1);
        while(RA3 == 0);
        TMR0 = 246;
        Tcount = 0;

        while(RA3 == 1);
        Ycount = Tcount;

        //Filter
        if(Xcount >= 140 && Xcount <= 160){
            RB6 = 0;
        }else{
            RB6 = 1;
        }

        if(Ycount >= 140 && Ycount <= 160){
            RB7 = 0;
        }else{
            RB7 = 1;
        }

 

    }
}