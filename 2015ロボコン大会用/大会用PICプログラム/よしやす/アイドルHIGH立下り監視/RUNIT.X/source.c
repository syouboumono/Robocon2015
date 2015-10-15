//R

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

//unsigned int R_data;
bit hasshaflag1=0;
bit hasshaflag2=0;
bit hasshaflag3=0;
unsigned char G_Lmotor,G_Rmotor;
signed char G_hassha,G_hassha2;

void spi_send(unsigned char,unsigned char,unsigned char,unsigned char,signed char,signed char);
unsigned char absolute(signed char);

void interrupt InterSPI(void)
{
	unsigned int R_data;
	signed char x_level,y_level,senkai;
	signed char FL_BRmotor,FR_BLmotor;
	unsigned char FL_BRmotor2,FR_BLmotor2;				
	unsigned char Lmotor,Rmotor;
	signed char FLmotor,FRmotor,BLmotor,BRmotor;
	signed char hassha,hassha2;
	
   if(SSP1IF==1){

    	R_data=SSP1BUF;
        if(R_data<0b10000000){			//識別ビットが0の場合
				

			senkai=R_data-((char)(R_data/16))*16-8;
			if(senkai<0){				//左旋回
				Lmotor=0b10000000+absolute(senkai)*(127/8);
				Rmotor=0b00000000+absolute(senkai)*(127/8);
			}else{					//右旋回
				Lmotor=0b00000000+absolute(senkai)*(127/8);
				Rmotor=0b10000000+absolute(senkai)*(127/8);
			}

			if(((char)(R_data/16))==1 && hasshaflag1==0){	//発射機構サーボ
				hassha=1;
				hasshaflag1=1;
			}else{
				hassha=0;
			}
			if(((char)(R_data/16))!=1 && hasshaflag1==1){
				hasshaflag1=0;
			}

			if(((char)(R_data/16))==2 && hasshaflag2==0){	//上野さん
				hassha2=1;
				hasshaflag2=1;
			}else{
				hassha2=0;

				if(((char)(R_data/16))==3 && hasshaflag3==0){	//森本さん
					hassha2=2;
					hasshaflag3=1;
				}else{
					hassha2=0;
				}
			}

			if(((char)(R_data/16))!=3 && hasshaflag3==1){
				hasshaflag3=0;
			}
			if(((char)(R_data/16))!=2 && hasshaflag2==1){
				hasshaflag2=0;
			}

			G_Lmotor=Lmotor;
			G_Rmotor=Rmotor;
			G_hassha=hassha;
			G_hassha2=hassha2;
			
        }else{					//識別ビットが1の場合
        	R_data=R_data-0b10000000;	//識別ビットを0にする
        	y_level=((char)(R_data/16))-4;	//Y軸レベルを取得
        	x_level=R_data-y_level*16-72;	//X軸レベルを取得
        	
        	FL_BRmotor=-((y_level+x_level)*(9-absolute(x_level)/(2-(absolute(y_level)/4))));		//左前、右後の回転量
        	FR_BLmotor=-((y_level-x_level)*(9-absolute(x_level)/(2-(absolute(y_level)/4))));		//右前、左後の回転量
        									//それぞれ絶対値の最大値は42
        	FL_BRmotor2=(FL_BRmotor<0)*0b10000000+absolute(FL_BRmotor)*2;	//モータードライブに送信する形に
        	FR_BLmotor2=(FR_BLmotor<0)*0b10000000+absolute(FR_BLmotor)*2;

			if(G_Lmotor==0b00000000 || G_Lmotor==0b10000000){	//旋回優先
				FLmotor=FL_BRmotor2;
				FRmotor=FR_BLmotor2;
				BLmotor=FR_BLmotor2;
				BRmotor=FL_BRmotor2;
			}else{
				FLmotor=G_Lmotor;
				FRmotor=G_Rmotor;
				BLmotor=G_Lmotor;
				BRmotor=G_Rmotor;
			}
			spi_send(FLmotor,BLmotor,FRmotor,BRmotor,G_hassha,G_hassha2);			//送信
        }
	SSP1IF=0;
    }
}

void spi_send(unsigned char FLmotor, unsigned char BLmotor, unsigned char FRmotor, unsigned char BRmotor, signed char hasshakiko, signed char hasshakiko2)
{
	RA2=1;
	RA3=1;
	RA4=1;
	RA7=1;
	RB7=1;
	
	RA1=0;
	SSP2BUF=FLmotor;
	while(SSP2STATbits.BF==0);
	RA1=1;
	
	RA2=0;
	SSP2BUF=BLmotor;
	while(SSP2STATbits.BF==0);
	RA2=1;
	
	RA3=0;
	SSP2BUF=FRmotor;
	while(SSP2STATbits.BF==0);
	RA3=1;
	
	RA4=0;
	SSP2BUF=BRmotor;
	while(SSP2STATbits.BF==0);
	RA4=1;

 	if (hasshakiko!=0){
		RA7=0;
		SSP2BUF=hasshakiko;
		while(SSP2STATbits.BF==0);
		RA7=1;
	}
	if (hasshakiko2!=0){
		RB7=0;
		SSP2BUF=hasshakiko2;
		while(SSP2STATbits.BF==0);
		RB7=1;
	}
}	

unsigned char absolute(signed char a)
{
	if(a<0) return -a;
	return a;
}


void main(void)
{
    //Port etc
    OSCCON   = 0x72;  //clkf=8MHz
    TRISA    = 0b00100000;
    PORTA    = 0x00;
    ANSELA   = 0x00;
    TRISB    = 0b00010110;
    PORTB    = 0x00;
    ANSELB   = 0x00;

    //SPI
    SDO1SEL  = 1;     //RA6:SDO1
    SS1SEL   = 1;     //RA5:SS
    SSP1CON1 = 0b00110100;  //アイドルHIGH
    SSP1STAT = 0b01000000;  //立上がりを見る
	SSP2CON1 = 0b00100001;
	SSP2STAT = 0b00000000;

    //warikomi
    SSP1IF   = 0;     //SPIwarikomiflag
	SSP1IE   = 1;
    PEIE     = 1;
	GIE      = 1;

	RA1=1;
	RA2=1;
	RA3=1;
	RA4=1;
	RA7=1;
	RB7=1;

	while(1);

}
