#include <xc.h>
#include <pic16f1827.h>
#include "spi.h"



/*Slave*/

//Slaveピン設定関数

//SDO1SEL 0:(RB2) 1:(RA6) 出力
//SS1SEL  0:(RB5) 1:(RA5) 入力
//SDI RB1                 入力
//SCK RB4                 入力
void slave_reg()
{
    //ピン設定
//    TRISA    = 0x20;
//    TRISB    = 0x12;
//    PORTA    = 0x00;
//    PORTB    = 0x00;
//    ANSELA   = 0x00;
//    ANSELB   = 0x00;

    //SPI設定
    SSP1CON1    = 0b00100100;
    SSP1STAT    = 0b00000000;
    SDO1SEL     = 0;
    SS1SEL      = 1;
    
    //割り込みの許可
    SSP1IF  = 0;
    SSP1IE  = 1;
    PEIE    = 1;
    GIE     = 1;
}


//SPIで受け取ったデータを返す関数
//割り込み内で実行してください
//返り値 char型 
unsigned char slaveread()
{
	//SPIのデータが受信しているかのチェック
    if((SSP1IF == 1) && (SSP1STATbits.BF != 0)){
        GIE     = 0;
        SSP1IF  = 0;
        return (SSP1BUF);
    }

    return 0;

}



/*Master*/

void master_reg(void){
    //ピン設定
    TRISA    = 0x00;
    TRISB    = 0x02;
    PORTA    = 0x00;
    PORTA    = 0x00;
    ANSELA   = 0x00;
    ANSELB   = 0x00;

    //SPI設定
    SSP1CON1    = 0b00100000;//分周比4
    SSP1STAT    = 0b00000000;
    SDO1SEL     = 0;

    //割り込みの許可
    SSP1IF  = 0;
    SSP1IE  = 1;
    PEIE    = 1;
    GIE     = 1;

}
//Masterピン設定

//SPIでデータを送る関数
//obj   :SSピンの名前(SS_XX)
//s_data:送るデータ(8bit)

void mastersend(int obj,unsigned char s_data)
{
    if(obj == SS_RA0){
        RA0 = 0;
        SSP1BUF = s_data;
        while(SSP1STATbits.BF == 0);
        RA0 = 1;
        return;
    }

    if(obj == SS_RA1){
        RA1 = 0;
        SSP1BUF = s_data;
        while(SSP1STATbits.BF == 0);
        RA1 = 1;
        return;
    }

    if(obj == SS_RA2){
        RA2 = 0;
        SSP1BUF = s_data;
        while(SSP1STATbits.BF == 0);
        RA2 = 1;
        return; 
    }

    if(obj == SS_RA3){
        RA3 = 0;
        SSP1BUF = s_data;
        while(SSP1STATbits.BF == 0);
        RA3 = 1;
        return;
    }

    if(obj == SS_RA4){
        RA4 = 0;
        SSP1BUF = s_data;
        while(SSP1STATbits.BF == 0);
        RA4 = 1;
        return;
    }

    if(obj == SS_RA7){
        RA7 = 0;
        SSP1BUF = s_data;
        while(SSP1STATbits.BF == 0);
        RA7 = 1;
        return;
    }

    if(obj == SS_RB0){
        RB0 = 0;
        SSP1BUF = s_data;
        while(SSP1STATbits.BF == 0);
        RB0 = 1;
        return;
    }

    if(obj == SS_RB3){
        RB3 = 0;
        SSP1BUF = s_data;
        while(SSP1STATbits.BF == 0);
        RB3 = 1;
        return;
    }

    if(obj == SS_RB6){
        RB6 = 0;
        SSP1BUF = s_data;
        while(SSP1STATbits.BF == 0);
        RB6 = 1;
        return;
    }

    if(obj == SS_RB7){
        RB7 = 0;
        SSP1BUF = s_data;
        while(SSP1STATbits.BF == 0);
        RB7 = 1;
        return;
    }
}

