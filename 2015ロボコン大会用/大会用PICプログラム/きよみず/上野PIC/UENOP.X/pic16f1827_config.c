#include <pic16f1827.h>
#include <xc.h>
void pic_reg()
{
    
    OSCCON  = 0x62;
    TRISA   = 0x20;
    TRISB   = 0xF2;
    PORTA   = 0x00;
    PORTB   = 0x00;
    ANSELA  = 0x00;
    ANSELB  = 0x00;
    
    OPTION_REG = 0x00;  //プルアップ抵抗の設定(有効化)
    WPUB = 0xE0;              //RB7,6,5をプルアップ
    
    //ピン割り込み
    IOCBNbits.IOCBN5   = 1;
    IOCBFbits.IOCBF5   = 0;
    IOCIF   = 0;
    IOCIE   = 0;
      
}