#include <xc.h>
#include<pic16f1829.h>
#include<stdio.h>
#include"usart.h"

void henkan(int sdata){

    sprintf(str,"%d",sdata);
    

}

void sousin(int sdata){

    int i = 0;

     henkan(sdata);//int��char�ϊ��֐���p����

       for(i=0;i<nul;i++){
          while(TXIF==0 && TRMT==0);     // ���M�\�ɂȂ�܂ő҂�
          TXREG = str[i];   // ���M��(TXIF == 1)
          TXIF = 0; //���M�I��(���M�\TXIF == 0�ƂȂ�)
       }
       while(TXIF==0 && TRMT==0);
       TXREG = '\n';
       TXIF = 0;
       while(TXIF==0 && TRMT==0);
       TXREG = '\r';
       TXIF = 0;




}

/*void sousin(int sdata){
    
    while(TXIF == 0);
    TXREG = sdata >> 8; 
    TXIF = 0;
    while(TXIF == 0);
    TXREG = sdata &0x00FF; 
    TXIF = 0;
    while(TXIF==0);
    TXREG = '\n';
    TXIF = 0;
    while(TXIF==0);
    TXREG = '\r';
    TXIF = 0;
    
}*/    
    
