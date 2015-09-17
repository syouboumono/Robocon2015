#include <xc.h>
#include<pic16f1829.h>
#include<stdio.h>
#include"usart.h"

void henkan(int sdata){

    sprintf(str,"%d",sdata);
    

}

void sousin(int sdata){

    int i = 0;

     henkan(sdata);//int→char変換関数を用いる

       for(i=0;i<nul;i++){
          while(TXIF==0 && TRMT==0);     // 送信可能になるまで待つ
          TXREG = str[i];   // 送信中(TXIF == 1)
          TXIF = 0; //送信終了(送信可能TXIF == 0となる)
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
    
