#include <pic16f1827.h>
#include <xc.h>
#include "Init.h"
#include "SPI.h"

void main(void)
{

    OSCCON   = 0x72;  //clkf=8MHz
    MasterInit();

    //���W�X�^���Z�b�g
    MasterSend(SS_RA2,0x00);
    MasterSend(SS_RA2,0x00);
    MasterSend(SS_RA2,0x00);
    MasterSend(SS_RA2,0x00);

    //���^�h�����Z�b�g
    MasterSend(SS_RA2,0xc0);
    //�X�e�b�v���[�h(1/128)
    MasterSend(SS_RA2,0x16);
    MasterSend(SS_RA2,0x77);
    //�����̎d��
    MasterSend(SS_RA2,0x05);
    MasterSend(SS_RA2,0x00);
    MasterSend(SS_RA2,0x10);
    //�����̎d��
    MasterSend(SS_RA2,0x06);
    MasterSend(SS_RA2,0x00);
    MasterSend(SS_RA2,0x10);

    MasterSend(SS_RA2,0x50);
    MasterSend(SS_RA2,0x00);
    MasterSend(SS_RA2,0x00);
    MasterSend(SS_RA2,0x10);
  
    while(1){
        
    }


}