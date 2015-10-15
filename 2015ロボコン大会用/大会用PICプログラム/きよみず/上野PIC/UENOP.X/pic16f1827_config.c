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
    
    OPTION_REG = 0x00;  //�v���A�b�v��R�̐ݒ�(�L����)
    WPUB = 0xE0;              //RB7,6,5���v���A�b�v
    
    //�s�����荞��
    IOCBNbits.IOCBN5   = 1;
    IOCBFbits.IOCBF5   = 0;
    IOCIF   = 0;
    IOCIE   = 0;
      
}