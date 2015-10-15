#include <pic16f1827.h>
#include <xc.h>
void pic_reg()
{
    
    OSCCON  = 0x62;
    TRISA   = 0x28;
    TRISB   = 0xD6;
    PORTA   = 0x02;
    PORTB   = 0x00;
    ANSELA  = 0x00;
    ANSELB  = 0x00;

    OPTION_REG = 0b00000000;  //プルアップ抵抗の設定(有効化)
    WPUB = 0xC0;              //RB7,6をプルアップ

    //ピン割り込み
    
    IOCBF       = 0;
    IOCIF       = 0;
    IOCIE       = 0;
    
}