//基本

#include "pic16f1827_config.h"
#include "spi.h"

#define DEG_LOCKED  0
#define DEG_0 6
#define DEG_90 12
#define DEG_180 17
#define DELAY_TIME 300

#define DEG_OPEN 6
#define DEG_CLOSE 12


#define SLOT_BULLET 3
#define BUTTON_PUSH 0
#define SENSOR_INCIDENT 1

int slot_state[SLOT_BULLET] = {0,1,1}; //0:輪なし　1:輪あり
int load_flag;                         //0:装填なし　1:装填あり

void shot();
void load();

void interrupt inter(){

    //コントローラからの入力
    if(slave_read() == 0){
        if(r_data == 0x01){
            SSP1IE = 0;
            if(slot_state[0] == 1){
                //通常発射
                load_flag = 1;
                shot();
            }else if(slot_state[0] == 0){
                load();
                SSP1IF = 0;
                SSP1IE = 1;
            }
            
        }else{
            NOP();
        }
        //SSP1IF = 0;   
    }
    
    if(IOCIF == 1){
        if(IOCBFbits.IOCBF5 == SENSOR_INCIDENT){
            //スリットを認識したとき
            IOCIE  = 0;
            
            RB0 = 0;
            
            __delay_ms(500);
            
            if(load_flag == 1){
                load();
            }else if(load_flag == 0){
                slot_state[0] = 1;
            }
             
            SSP1IF = 0;
            SSP1IE = 1;
        }
    }

}

void main(void)
{
    pic_reg();
    slave_reg();
    
    //PWM設定
    CCPTMRS = 0b00000000;           //TMR2を使用する
    CCP3CON = 0b00001100;           //シングルPWMを選択
    CCP4CON = 0b00001100;           //シングルPWMを選択
    T2CON   = 0b01111111;
    PR2     = 155;                  //TMR2プリスケーラ
    CCPR3L  = 0;
    CCPR3H  = 0;
    CCPR4L  = 0;
    CCPR4H  = 0;
    TMR2    = 0;                    //タイマ2クリア
    TMR2ON  = 1;
    
    CCPR3L = DEG_CLOSE;
    CCPR4L = DEG_CLOSE;
    __delay_ms(DELAY_TIME);
    CCPR3L = DEG_LOCKED;
    CCPR4L = DEG_LOCKED;
    
    PEIE    = 1;
    GIE     = 1;
    
    while(1){
        
        if(RB7 == BUTTON_PUSH){
            load_flag = 0;
            shot();
        }
    }       
     
}

void shot(){
    slot_state[0] = 0;
    RB0 = 1;
    IOCBFbits.IOCBF5 = 0;
    IOCIF = 0;
    IOCIE = 1;
}

void load(){
   
    //装填機構に輪がある場合
            
    if((slot_state[0] == 0) && (slot_state[1] == 1)){
        //一段目
        CCPR3L = DEG_OPEN;
        __delay_ms(DELAY_TIME);
        CCPR3L = DEG_LOCKED;
            
        slot_state[0] = 1;
        slot_state[1] = 0;
            
        return;
            
    }
    
    if((slot_state[0] == 0) && (slot_state[1] == 0) && (slot_state[2] == 1)){
        //二段目
        CCPR4L = DEG_OPEN;
        __delay_ms(DELAY_TIME);
        CCPR4L = DEG_LOCKED;
            
        slot_state[0] = 1;
        slot_state[2] = 0;
            
        return;
        
    }
    
    if((slot_state[0] == 0) && (slot_state[1] == 0) && (slot_state[2] == 0)){    
        //装填機構に輪がない場合
        CCPR3L = DEG_CLOSE;
        CCPR4L = DEG_CLOSE;
    
        __delay_ms(DELAY_TIME);
    
        CCPR3L = DEG_LOCKED;
        CCPR4L = DEG_LOCKED;
    
        slot_state[0] = 0;
        slot_state[1] = 1;
        slot_state[2] = 1;
        
        return;
    }
}