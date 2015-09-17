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

unsigned char R_data;
unsigned char old_R_data = 0;

void interrupt InterSPI(void)
{
    if((SSP1IF == 1) && (SSP1STATbits.BF != 0)){
        R_data = SSP1BUF;
        SSP1IF  = 0;
    }
}

void main(void)
{
    OSCCON   = 0x72;  //clkf=8MHz
    TRISA    = 0x20;  //RA5:SS
    PORTA    = 0x00;  //pin all low
    ANSELA   = 0x00;  //not analog
    TRISB    = 0x12;  //RB1:SDI1 RB2:SDO RB3:Motor RB4:SCK RB5:PWM RB6:Motor RB7:PWM
    PORTB    = 0x00;  //pin all low
    ANSELB   = 0x00;  //not analog

    //PWM
   /* CCPTMRS  = 0x00;  //Timer2
    PSTR1CON = 0x0A;
    CCP1SEL  = 0;
    P1CSEL   = 0;     //testnow
    P1DSEL   = 1;     //testnow
    T2CON    = 0x00;  //*1
    PR2      = 124;   //PWMf 16kHz
    CCPR1L   = 0;     //dutty reset
    CCPR1H   = 0;
    TMR2     = 0;     //timer reset
    TMR2ON   = 1;     //timeron*/

    CCPTMRS  = 0x00;  //Timer2
    PSTR1CON = 0x0A;
    CCP1SEL  = 0;
    P1CSEL   = 0;     //testnow
    P1DSEL   = 1;     //testnow
    T2CON    = 0x10;  //*16
    PR2      = 124;   //PWMf 16kHz
    CCPR1L   = 0;     //dutty reset
    CCPR1H   = 0;
    TMR2     = 0;     //timer reset
    TMR2ON   = 1;

    //SPI Slave
    SDO1SEL  = 0;     //RB2:SDO
    SS1SEL   = 1;     //RA5:SS
    SSP1CON1 = 0x24;  //CHP:low SS:enable
    SSP1STAT = 0x00;  //CKE:up

    //warikomi
    SSP1IF    = 0;     //SPIwarikomiflag reset
    SSP1IE    = 1;     //SPIwarikomi set
    PEIE      = 1;
    GIE       = 1;

    while(1){

        if((old_R_data != R_data) && ((R_data & 0x0F) > 99))  {
            CCPR1L = 0x00;
            old_R_data = R_data;
            __delay_ms(1);
        }

        if((R_data & 0x80) == 0x80){
            CCP1CON = 0xCC;
        }else{
            CCP1CON = 0x4C;
        }

        CCPR1L = (R_data & 0x0F)*8;

    }
}