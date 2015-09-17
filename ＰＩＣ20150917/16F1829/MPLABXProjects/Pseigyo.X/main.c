#include <pic16f1829.h>
#include <xc.h>
#include "pic16f1829_config.h"
#include "usart.h"
#include "spi.h"
//#define ONE_COUNT 0.000001

int time = 0;
int target = (127*3)/2; //SPIで受けた値を3倍して計算する
int count = 0;
int max_ope = 124;      //pwm最大値
int p_band = 5;
int kp; 
int dev;            //偏差
double min_rad = 0.72;  //分解能



void interrupt inter(void){
 
    if(IOCAFbits.IOCAF4 == 1){
        if(RA5 == 1){
            count++;
        }else{
            count--;
        }
        IOCAFbits.IOCAF4 = 0;
    }
    
    if(T0IF == 1){
        TMR0 = 156;
        time++;
        T0IF = 0;
    }
    
    target = slaveread();
}

void main(void)
{
    kp = max_ope / p_band;
    
    OSCCON  = 0x72;
    TRISA   = 0x30;
    TRISB   = 0x70;
    TRISC   = 0x40;
    PORTA   = 0x00;
    PORTB   = 0x00;
    PORTC   = 0x00;
    ANSELA  = 0x00;
    ANSELB  = 0x00;
    ANSELC  = 0x00;
    WPUA    = 0x30;
    
    //PWM
    CCPTMRS     = 0x00; //Timer2
    CCP1CON     = 0xCC; //other 0x4C
    PSTR1CON    = 0x0A;
    CCPR1L      = 0;    //change the dutty
    P1CSEL      = 0;
    P1DSEL      = 0;
    T2CON       = 0x00; //*1
    PR2         = max_ope;  //PWMf 16kHz
    CCPR1L      = 0;
    CCPR1H      = 0;
    TMR2        = 0;
    TMR2ON      = 1;
    
    //USART設定
    RXDTSEL = 0;
    TXCKSEL = 0;
    TXSTA   = 0b00100100;     
    RCSTA   = 0b10010000;     
    SPBRG   = 51;  
    
    //SPI設定
    slave_reg();
    
    //割り込みの許可
    OPTION_REG  = 0x01; //プリスケール*2,プルアップ抵抗ON
    //timer
    TMR0        = 156;
    T0IF        = 0;
    T0IE        = 1;
    //pin
    IOCAP       = 0x10;
    IOCAF       = 0;
    IOCIE       = 1;
    //周辺、全体
    PEIE        = 1;
    GIE         = 1;
    
    
    
    while(1){
        
        if(time == 500){ //サンプリングレート50ms
            dev = target-count;
            sousin(target-count); 
            time = 0;
            count = 0;
        }
        
        //P制御
        if(dev >= p_band){
            CCPR1L = max_ope;
        }else if(dev >= 0){
            CCPR1L = kp * dev;
        }else{  
            CCPR1L = 0;
        }
        
    }
}
