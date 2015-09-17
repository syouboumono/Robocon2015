/* 
 * File:   MAIN.c
 * Author: makki
 *
 * Created on 2015/07/24, 12:07
 */

#include <pic16f1829.h>  //pic16f1827を使用
#include "pic16f1829_config.h"  //きよみずライブラリ使用
#include <xc.h>  //XC8
#include<stdio.h>
#include"usart.h"



void main(){

    int a = -12345;

     //初期設定
     OSCCON = 0x72;     // 内部クロックは8ＭＨｚ
     ANSELA = 0x00;     // すべてデジタルに割り当て
     TRISA  = 0x20;     // ピンは全て出力に割り当て
     PORTA  = 0x00;     // 出力ピン初期化
     ANSELB = 0x00;     // すべてデジタルに割り当て
     TRISB    = 0x00;    // ピンは全て出力に割り当て
     PORTB    = 0x00;    // 出力ピン初期化
     // ＵＳＡＲＴ機能の設定を行う
     //RXDTSEL設定…… ＝0ならRB5を使う。＝１ならRC5を使う。
     //TXCKSEL設定…… ＝0ならRB7を使う。＝１ならRC4を使う。
     RXDTSEL = 1;             // 5番ピン(RC5)をＲＸ受信ピンとする
     TXCKSEL = 1;             // 6番ピン(RC4)をＴＸ送信ピンとする
     TXSTA  = 0b00100100;     // 送信情報設定：非同期モード　８ビット・ノンパリティ
     RCSTA  = 0b10010000;     // 受信情報設定
     SPBRG  = 51;             // ボーレートを９６００(高速モード)に設定

     __delay_ms(500);               // ５秒後に開始する



     while(1) {

       sousin(a);
     
     }

}




