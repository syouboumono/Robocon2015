#include <pic16f1829.h>
#include <xc.h>
#include "pic16f1829_config.h"
#include "spi.h"

void interrupt interspi(void)
{
    r_data = slaveread();
}

void main(void)
{    
    OSCCON  = 0x72;
    slave_reg();
    
    while(1){
        
        if(r_data == 0x01){
            RB7 = 1;
        }else{
            RB7 = 0;
        }
    }
}
    
