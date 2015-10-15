 #include <pic16f1827.h>
#include <xc.h>
#include "pic16f1827_config.h"
#include "spi.h"
//#define DEG_90 12
//#define DEG_0 6
#define DEG_180 17
#define DELAY_TIME 200

#define DEG_LOCKED  0           //サーボ角度ロック
#define DEG_LOADED 12           //サーボ装填位置
#define DEG_EMPTY   6           //サーボ発射位置

#define SHOOTER_UNITS   3       //自陣向け発射機構の数

//サーボ位置の状態フラグ
#define PS_KEEP    2            //現状保持(再起動時の暴発防止用)
#define PS_LOADED  1            //装填済み
#define PS_EMPTY   0            //未装填

//自陣向け発射機構(サーボ)の状態管理用
char loaded_flg[SHOOTER_UNITS];


//割り込み処理
void interrupt slave(void)
{

    //使用する発射機構の選択情報をr_dataに格納
    r_data = slaveread();       //関数内部で割り込みを一括不許可しているので注意

    if(r_data == 0x01){//コントローラからの命令による割り込み(発射時)

        //1段目が装填済み
        if(loaded_flg[0] == PS_LOADED){
            CCPR1L              = DEG_EMPTY;            //サーボを発射位置まで回転
            __delay_ms(DELAY_TIME);                     //回転完了(見込)まで待つ
            CCPR1L              = DEG_LOCKED;           //サーボをロック
            loaded_flg[0]       = PS_EMPTY;             //発射済みフラグを設定
            __delay_ms(DELAY_TIME);                     //完了(見込)まで待つ
        }

        //2段目が装填済み
        else if(loaded_flg[1] == PS_LOADED){
            CCPR2L              = DEG_EMPTY;            //サーボを発射位置まで回転
            __delay_ms(DELAY_TIME);                     //回転完了(見込)まで待つ
            CCPR2L              = DEG_LOCKED;           //サーボをロック
            loaded_flg[1]       = PS_EMPTY;             //発射済みフラグを設定
            __delay_ms(DELAY_TIME);                     //完了(見込)まで待つ
        }

        //3段目が装填済み
        else if(loaded_flg[2] == PS_LOADED){
            CCPR3L              = DEG_EMPTY;            //サーボを発射位置まで回転
            __delay_ms(DELAY_TIME);                     //回転完了(見込)まで待つ
            CCPR3L              = DEG_LOCKED;           //サーボをロック
            loaded_flg[2]       = PS_EMPTY;             //発射済みフラグを設定
            __delay_ms(DELAY_TIME);                     //完了(見込)まで待つ
        }
    }

    else if(IOCIF == 1){//ロボット据付ボタンによる割り込み(装填時)

        //1段目を装填
        if(RB5 == 0){
            CCPR1L              = DEG_LOADED;           //サーボを発射位置まで回転
            __delay_ms(DELAY_TIME);                     //回転完了(見込)まで待つ
            CCPR1L              = DEG_LOCKED;           //サーボをロック
            loaded_flg[0]       = PS_LOADED;            //発射済みフラグを設定
        }

        //2段目を装填
        else if(RB7 == 0){
            CCPR2L              = DEG_LOADED;           //サーボを発射位置まで回転
            __delay_ms(DELAY_TIME);                     //回転完了(見込)まで待つ
            CCPR2L              = DEG_LOCKED;           //サーボをロック
            loaded_flg[1]       = PS_LOADED;            //発射済みフラグを設定
        }

        //3段目を装填
        else if(RB2 == 0){
            CCPR3L              = DEG_LOADED;           //サーボを発射位置まで回転
            __delay_ms(DELAY_TIME);                     //回転完了(見込)まで待つ
            CCPR3L              = DEG_LOCKED;           //サーボをロック
            loaded_flg[2]       = PS_LOADED;            //発射済みフラグを設定
        }

    }

    IOCBF       = 0;                    //状態変化フラグをリセット
    IOCIF       = 0;                    //状態変化フラグをリセット
    GIE = 1;        //(多重)割り込み禁止を解除
    
}

void main(void)
{
    //レジスタ設定
    OSCCON = 0x62;                  //オシレータ設定

    //ピン設定
    TRISA    = 0xE7;
    TRISB    = 0xB3;                //1011 0011
    PORTA    = 0x00;
    PORTB    = 0x00;
    ANSELA   = 0x00;
    ANSELB   = 0x00;

    //PWM設定
    CCPTMRS = 0b00000000;           //TMR2を使用する
    CCP1CON = 0b00001100;           //シングルPWMを選択
    CCP2CON = 0b00001100;           //シングルPWMを選択
    CCP3CON = 0b00001100;           //シングルPWMを選択
    CCP4CON = 0b00001100;           //シングルPWMを選択
    T2CON   = 0b01111111;           //
    PR2     = 155;                  //TMR2プリスケーラ
    CCPR1L  = 0;
    CCPR1H  = 0;
    CCPR2L  = 0;
    CCPR2H  = 0;
    CCPR3L  = 0;
    CCPR3H  = 0;
    CCPR4L  = 0;
    CCPR4H  = 0;
    TMR2    = 0;                    //タイマ2クリア
    TMR2ON  = 1;
    CCP1SEL = 0;
    CCP2SEL = 0;
    OPTION_REG = 0b00000000;        //プルアップ抵抗の設定(有効化)
    WPUB = 0b11111111;              //Bポート全てプルアップ有効

    //割り込み設定
    IOCIF   = 0;                    //状態変化割り込みフラグリセット
    IOCBN   = 0xFF;                 //ボタンが押されたことを検知する
    IOCBP   = 0x00;                 //ボタンを放したことは検知しない
    IOCIE   = 1;                    //状態変化割り込みを許可

    //サーボ情報初期化

    //開放状態にする
    CCPR1L = PS_EMPTY;
    CCPR2L = PS_EMPTY;
    CCPR3L = PS_EMPTY;
    CCPR4L = PS_EMPTY;
    __delay_ms(DELAY_TIME);

    //サーボの角度をロック
    CCPR1L = DEG_LOCKED;
    CCPR2L = DEG_LOCKED;
    CCPR3L = DEG_LOCKED;
    CCPR4L = DEG_LOCKED;

    loaded_flg[0] = PS_EMPTY;
    loaded_flg[1] = PS_EMPTY;
    loaded_flg[2] = PS_EMPTY;

    //割り込みの許可
    IOCIF   = 0;                        //ピンの状態変化割り込み状態をクリア
    IOCIE   = 1;                        //ピンの状態変化割り込みを許可

    slave_reg();                        //SPI通信設定(スレーブ)

    while(1);

}
