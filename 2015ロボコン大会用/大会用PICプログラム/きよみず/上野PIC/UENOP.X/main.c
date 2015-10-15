//��{

#include "pic16f1827_config.h"
#include "spi.h"

#define DEG_LOCKED  0
#define DEG_0 6
#define DEG_90 12
#define DEG_180 17
#define DELAY_TIME 300

#define SLOT_BULLET 3
#define BUTTON_PUSH 0
#define SENSOR_INCIDENT 1

int slot_state[SLOT_BULLET] = {0,1,1}; //0:�ւȂ��@1:�ւ���
int load_flag;                         //0:���U�Ȃ��@1:���U����

void shot();
void load();

void interrupt inter(){

    //�R���g���[������̓���
    if(slave_read() == 0){
        if(r_data == 0x01){
            SSP1IE = 0;
            if(slot_state[0] == 1){
                //�ʏ픭��
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
            //�X���b�g��F�������Ƃ�
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
    
    //PWM�ݒ�
    CCPTMRS = 0b00000000;           //TMR2���g�p����
    CCP3CON = 0b00001100;           //�V���O��PWM��I��
    CCP4CON = 0b00001100;           //�V���O��PWM��I��
    T2CON   = 0b01111111;
    PR2     = 155;                  //TMR2�v���X�P�[��
    CCPR3L  = 0;
    CCPR3H  = 0;
    CCPR4L  = 0;
    CCPR4H  = 0;
    TMR2    = 0;                    //�^�C�}2�N���A
    TMR2ON  = 1;
    
    CCPR3L = DEG_0;
    CCPR4L = DEG_0;
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
   
    //���U�@�\�ɗւ�����ꍇ
            
    if((slot_state[0] == 0) && (slot_state[1] == 1)){
        //��i��
        CCPR3L = DEG_90;
        __delay_ms(DELAY_TIME);
        CCPR3L = DEG_LOCKED;
            
        slot_state[0] = 1;
        slot_state[1] = 0;
            
        return;
            
    }
    
    if((slot_state[0] == 0) && (slot_state[1] == 0) && (slot_state[2] == 1)){
        //��i��
        CCPR4L = DEG_90;
        __delay_ms(DELAY_TIME);
        CCPR4L = DEG_LOCKED;
            
        slot_state[0] = 1;
        slot_state[2] = 0;
            
        return;
        
    }
    
    if((slot_state[0] == 0) && (slot_state[1] == 0) && (slot_state[2] == 0)){    
        //���U�@�\�ɗւ��Ȃ��ꍇ
        CCPR3L = DEG_0;
        CCPR4L = DEG_0;
    
        __delay_ms(DELAY_TIME);
    
        CCPR3L = DEG_LOCKED;
        CCPR4L = DEG_LOCKED;
    
        slot_state[0] = 0;
        slot_state[1] = 1;
        slot_state[2] = 1;
        
        return;
    }
}