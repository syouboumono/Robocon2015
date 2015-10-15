#include "pic16f1829_config.h"
#include "spi.h"
#include "pwm.h"

#define MAX_OPE 124

void interrupt inter()
{
    if((slave_read()) == 0){

        if((r_data & 0x7F) == 0x00){
            keep();
        }else if((r_data & 0x80) == 0x80){
            right();
            speed(r_data & 0x7E);
        }else if((r_data & 0x80) == 0x00){
            left();
            speed(r_data & 0x7E);
        }
        
    }

    GIE = 1;

}

void main(void)
{
    pic_reg();
    pwm_reg();
    keep();

    slave_reg();

    PEIE    = 1;
    GIE     = 1;

    while(1);
}


