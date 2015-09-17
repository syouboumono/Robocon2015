#include <xc.h>
#include <pic16f1829.h>
#include "spi.h"



/*Slave*/

//Slave�s���ݒ�֐�

//SDO1  RC7                 �o��
//SDI1  RB4                 ����
//SCK1  RB6                 ����
//SS1   RC6                 ����
void slave_reg()
{
    //�s���ݒ�
    TRISA   = 0x00;
    TRISB   = 0x50;
    TRISC   = 0x40;
    PORTA   = 0x00;
    PORTB   = 0x00;
    PORTC   = 0x00;
    ANSELA  = 0x00;
    ANSELB  = 0x00;
    ANSELC  = 0x00;

    //SPI�ݒ�
    SSP1CON1    = 0b00100100;
    SSP1STAT    = 0b00000000;
    
    //���荞�݂̋���
    SSP1IF  = 0;
    SSP1IE  = 1;
    PEIE    = 1;
    GIE     = 1;
}


//SPI�Ŏ󂯎�����f�[�^��Ԃ��֐�
//���荞�ݓ��Ŏ��s���Ă�������
//�Ԃ�l char�^ 
unsigned char slaveread()
{
	//SPI�̃f�[�^����M���Ă��邩�̃`�F�b�N
    if((SSP1IF == 1) && (SSP1STATbits.BF != 0)){
        SSP1IF  = 0;
        return (SSP1BUF);
    }

    return 0;

}



/*Master*/

//Master�s���ݒ�

//SDO1  RC7                 �o��
//SDI1  RB1                 ����
//SCK1  RB4                 �o��
void master_reg()
{
    //�s���ݒ�
    TRISA   = 0x00;
    TRISB   = 0x02;
    TRISC   = 0x00;
    PORTA   = 0x00;
    PORTB   = 0x00;
    PORTC   = 0x00;
    ANSELA  = 0x00;
    ANSELB  = 0x00;
    ANSELC  = 0x00;

    //SPI�ݒ�
    SSP1CON1    = 0b00100001;//������4
    SSP1STAT    = 0b00000000;

    //���荞�݂̋���
    SSP1IF  = 0;
    SSP1IE  = 1;
    PEIE    = 1;
    GIE     = 1;

}

//SPI�Ńf�[�^�𑗂�֐�
//obj   :SS�s���̖��O(SS_XX)
//s_data:����f�[�^(8bit)

unsigned char mastersend(int obj,unsigned char s_data)
{
    if(obj == SS_RA0){
        RA0 = 0;
        SSP1BUF = s_data;
        while(SSP1STATbits.BF == 0);
        RA0 = 1;
        return (SSP1BUF);
    }

    if(obj == SS_RA1){
        RA1 = 0;
        SSP1BUF = s_data;
        while(SSP1STATbits.BF == 0);
        RA1 = 1;
        return (SSP1BUF);
    }

    if(obj == SS_RA2){
        RA2 = 0;
        SSP1BUF = s_data;
        while(SSP1STATbits.BF == 0);
        RA2 = 1;
        return (SSP1BUF);
    }

    if(obj == SS_RA3){
        RA3 = 0;
        SSP1BUF = s_data;
        while(SSP1STATbits.BF == 0);
        RA3 = 1;
        return (SSP1BUF);
    }

    if(obj == SS_RA4){
        RA4 = 0;
        SSP1BUF = s_data;
        while(SSP1STATbits.BF == 0);
        RA4 = 1;
        return (SSP1BUF);
    }

    if(obj == SS_RA5){
        RA5 = 0;
        SSP1BUF = s_data;
        while(SSP1STATbits.BF == 0);
        RA5 = 1;
        return (SSP1BUF);
    }

    if(obj == SS_RB5){
        RB5 = 0;
        SSP1BUF = s_data;
        while(SSP1STATbits.BF == 0);
        RB5 = 1;
        return (SSP1BUF);
    }

    if(obj == SS_RB7){
        RB7 = 0;
        SSP1BUF = s_data;
        while(SSP1STATbits.BF == 0);
        r_data = SSP1BUF;
        RB7 = 1;
        return (SSP1BUF);
    }

    if(obj == SS_RC0){
        RC0 = 0;
        SSP1BUF = s_data;
        while(SSP1STATbits.BF == 0);
        RC0 = 1;
        return (SSP1BUF);
    }

    if(obj == SS_RC1){
        RC1 = 0;
        SSP1BUF = s_data;
        while(SSP1STATbits.BF == 0);
        RC1 = 1;
        return (SSP1BUF);
    }
    
    if(obj == SS_RC2){
        RC2 = 0;
        SSP1BUF = s_data;
        while(SSP1STATbits.BF == 0);
        RC2 = 1;
        return (SSP1BUF);
    }
    
    if(obj == SS_RC3){
        RC3 = 0;
        SSP1BUF = s_data;
        while(SSP1STATbits.BF == 0);
        RC3 = 1;
        return (SSP1BUF);
    }
    
    if(obj == SS_RC4){
        RC4 = 0;
        SSP1BUF = s_data;
        while(SSP1STATbits.BF == 0);
        RC4 = 1;
        return (SSP1BUF);
    }
    
    if(obj == SS_RC5){
        RC5 = 0;
        SSP1BUF = s_data;
        while(SSP1STATbits.BF == 0);
        RC5 = 1;
        return (SSP1BUF);
    }
}

