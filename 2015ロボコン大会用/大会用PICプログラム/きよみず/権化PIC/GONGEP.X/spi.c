#include <xc.h>
#include <pic16f1827.h>
#include "spi.h"



/*Slave*/

//Slave�s���ݒ�֐�

//SDO1SEL 0:(RB2) 1:(RA6) �o��
//SS1SEL  0:(RB5) 1:(RA5) ����
//SDI RB1                 ����
//SCK RB4                 ����
void slave_reg()
{
//    //�s���ݒ�
//    TRISA    = 0x20;
//    TRISB    = 0x12;
//    PORTA    = 0x00;
//    PORTB    = 0x00;
//    ANSELA   = 0x00;
//    ANSELB   = 0x00;

    //SPI�ݒ�
    SSP1CON1    = 0b00100100;
    SSP1STAT    = 0b00000000;
    SDO1SEL     = 1;
    SS1SEL      = 1;
    
    //���荞�݂̋���
    SSP1IF  = 0;
    SSP1IE  = 1;
//    PEIE    = 1;
//    GIE     = 1;
}


//SPI�Ŏ󂯎�����f�[�^��Ԃ��֐�
//���荞�ݓ��Ŏ��s���Ă�������
//�Ԃ�l char�^ 
int slave_read()
{
    //SPI�̃f�[�^����M���Ă��邩�̃`�F�b�N
    if((SSP1IF == 1) && (SSP1STATbits.BF != 0)){
        SSP1IF  = 0;
        r_data = SSP1BUF;

        return 0;
    }

    return 1;

}



/*Master*/

//Master�s���ݒ�

//SDO1SEL 0:(RB2) 1:(RA6) �o��
//SDI RB1                 ����
//SCK RB4                 �o��
void master_reg()
{
    //�s���ݒ�
//    TRISA    = 0x00;
//    TRISB    = 0x02;
//    PORTA    = 0x00;
//    PORTB    = 0x00;
//    ANSELA   = 0x00;
//    ANSELB   = 0x00;

    //SPI�ݒ�
    SSP2CON1 = 0b00100000;
	SSP2STAT = 0b00000000;

    //���荞�݂̋���
    SSP2IF  = 0;
    SSP2IE  = 0;
//    PEIE    = 1;
//    GIE     = 1;

}

//SPI�Ńf�[�^�𑗂�֐�
//obj   :SS�s���̖��O(SS_XX)
//s_data:����f�[�^(8bit)

void master_send(int obj,unsigned char s_data)
{
    if(obj == SS_RA0){
        RA0 = 0;
        SSP2BUF = s_data;
        while(SSP2STATbits.BF == 0);
        RA0 = 1;
        return;
    }

    if(obj == SS_RA1){
        SSP2IE = 1;
        RA1 = 0;
        SSP2BUF = s_data;
        while(SSP2STATbits.BF == 0);
        RA1 = 1;
        SSP2IF = 0;
        SSP2IE = 0;
        return;
    }

    if(obj == SS_RA2){
        RA2 = 0;
        SSP2BUF = s_data;
        while(SSP2STATbits.BF == 0);
        RA2 = 1;
        return;
    }

    if(obj == SS_RA3){
        RA3 = 0;
        SSP2BUF = s_data;
        while(SSP2STATbits.BF == 0);
        RA3 = 1;
        return;
    }

    if(obj == SS_RA4){
        RA4 = 0;
        SSP2BUF = s_data;
        while(SSP2STATbits.BF == 0);
        RA4 = 1;
        return;
    }

    if(obj == SS_RA7){
        RA7 = 0;
        SSP2BUF = s_data;
        while(SSP2STATbits.BF == 0);
        RA7 = 1;
        return;
    }

    if(obj == SS_RB0){
        RB0 = 0;
        SSP2BUF = s_data;
        while(SSP2STATbits.BF == 0);
        RB0 = 1;
        return;
    }

    if(obj == SS_RB3){
        RB3 = 0;
        SSP2BUF = s_data;
        while(SSP2STATbits.BF == 0);
        RB3 = 1;
        return;
    }

    if(obj == SS_RB6){
        RB6 = 0;
        SSP2BUF = s_data;
        while(SSP2STATbits.BF == 0);
        RB6 = 1;
        return;
    }

    if(obj == SS_RB7){
        RB7 = 0;
        SSP2BUF = s_data;
        while(SSP2STATbits.BF == 0);
        RB7 = 1;
        return;
    }
}

