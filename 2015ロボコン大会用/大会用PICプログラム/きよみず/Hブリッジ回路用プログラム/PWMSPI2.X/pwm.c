#include "pic16f1829_config.h"
#include "pwm.h"


void pwm_reg(){

    //PWM
    CCPTMRS     = 0x00; //Timer2
    CCP1CON     = 0xCC; //other 0x4C
    PSTR1CON    = 0x0A;
    CCPR1L      = 0;    //change the dutty
    P1CSEL      = 0;
    P1DSEL      = 0;
    T2CON       = 0x02; //*16 1:0x00 4:0x01 16:0x02 64:0x03
    PR2         = MAX_OPE;  //PWMf 1kHz
    CCPR1L      = 0;
    CCPR1H      = 0;
    TMR2        = 0;
    TMR2ON      = 1;


}

void stop(){
    PORTC   = 0x00;
    CCP1CON = 0x00;
}

void keep(){
    if(CCP1CON != 0x00){
        stop();
        __delay_us(DEAD_TIME);
    }
    PORTC   = 0x14;
}

void right(){
    if(CCP1CON != 0x4C){
        stop();
        __delay_us(DEAD_TIME);
    }
    CCP1CON = 0x4C;
}

void left(){
    if(CCP1CON != 0xCC){
        stop();
        __delay_us(DEAD_TIME);
    }
    CCP1CON = 0xCC;
}

void speed(uint8_t ration){
     if(ration >= MAX_OPE){
        CCPR1L = MAX_OPE;
     }else{
        CCPR1L  = ration;
     }
}