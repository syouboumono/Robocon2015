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

    OPTION_REG = 0b00000000;  //�v���A�b�v��R�̐ݒ�(�L����)
    WPUB = 0xC0;              //RB7,6���v���A�b�v

    //�s�����荞��
    
    IOCBF       = 0;
    IOCIF       = 0;
    IOCIE       = 0;
    
}