/* 
 * File:   MAIN.c
 * Author: makki
 *
 * Created on 2015/07/24, 12:07
 */

#include <pic16f1829.h>  //pic16f1827���g�p
#include "pic16f1829_config.h"  //����݂����C�u�����g�p
#include <xc.h>  //XC8
#include<stdio.h>
#include"usart.h"



void main(){

    int a = -12345;

     //�����ݒ�
     OSCCON = 0x72;     // �����N���b�N��8�l�g��
     ANSELA = 0x00;     // ���ׂăf�W�^���Ɋ��蓖��
     TRISA  = 0x20;     // �s���͑S�ďo�͂Ɋ��蓖��
     PORTA  = 0x00;     // �o�̓s��������
     ANSELB = 0x00;     // ���ׂăf�W�^���Ɋ��蓖��
     TRISB    = 0x00;    // �s���͑S�ďo�͂Ɋ��蓖��
     PORTB    = 0x00;    // �o�̓s��������
     // �t�r�`�q�s�@�\�̐ݒ���s��
     //RXDTSEL�ݒ�c�c ��0�Ȃ�RB5���g���B���P�Ȃ�RC5���g���B
     //TXCKSEL�ݒ�c�c ��0�Ȃ�RB7���g���B���P�Ȃ�RC4���g���B
     RXDTSEL = 1;             // 5�ԃs��(RC5)���q�w��M�s���Ƃ���
     TXCKSEL = 1;             // 6�ԃs��(RC4)���s�w���M�s���Ƃ���
     TXSTA  = 0b00100100;     // ���M���ݒ�F�񓯊����[�h�@�W�r�b�g�E�m���p���e�B
     RCSTA  = 0b10010000;     // ��M���ݒ�
     SPBRG  = 51;             // �{�[���[�g���X�U�O�O(�������[�h)�ɐݒ�

     __delay_ms(500);               // �T�b��ɊJ�n����



     while(1) {

       sousin(a);
     
     }

}




