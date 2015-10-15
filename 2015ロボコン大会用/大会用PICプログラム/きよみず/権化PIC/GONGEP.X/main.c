#include "pic16f1827_config.h"
#include "spi.h"

#define DEG_LOCKED  0
#define DEG_0 6
#define DEG_90 12
#define DEG_180 17
#define LOAD_DELAY_TIME 1000

#define BUTTON_PUSH 0
#define SENSOR_INCIDENT 1

int turn_flag = 0;

void shot();    

void interrupt inter(void){

    
    if(slave_read() == 0){
        if(r_data == 0x02){
            //ゲームパッドから発射
            SSP1IE = 0;

            master_send(SS_RA1,0xFF);
            
            IOCBF = 0;
            IOCIF = 0;
            IOCBP = 0x40;
            IOCIE = 1;

        }else{
            
            NOP();
            
        }
    }

    if(IOCIF == 1){
        
        if(IOCBFbits.IOCBF7 == SENSOR_INCIDENT){
            RB0 = 0;

            IOCBF = 0;
            IOCIF = 0;
            IOCBN = 0x00;
            IOCIE = 0;
            
            SSP1IF = 0;
            SSP1IE = 1;
            
        }

        
        if(IOCBFbits.IOCBF6 == SENSOR_INCIDENT){
            
            master_send(SS_RA1,0x00);

            if(turn_flag == 0){
                turn_flag = 1;
                
                __delay_ms(LOAD_DELAY_TIME);
                master_send(SS_RA1,0x7F);
                
                IOCBF = 0;
                IOCIF = 0;
                
            }else if(turn_flag == 1){
                turn_flag = 0;
                
                IOCBF = 0;
                IOCIF = 0;
                IOCBP = 0x00;
                IOCIE = 0;
                
                shot();

            }
                        
        }
       
    }
}

void main(void)
{
    
    pic_reg();
    slave_reg();
    master_reg();

    PEIE    = 1;
    GIE     = 1;

    while(1){
        
        if(RA3 == BUTTON_PUSH){
            //ボタンによるチャージ
            SSP1IE = 0;
            shot();
        }
        
    }
}

void shot(){

    RB0 = 1;
    
    IOCBF = 0;
    IOCIF = 0;
    IOCBN = 0x80;
    IOCIE = 1;

}


