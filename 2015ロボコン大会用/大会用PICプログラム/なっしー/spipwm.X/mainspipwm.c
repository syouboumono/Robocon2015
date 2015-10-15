 #include <pic16f1827.h>
#include <xc.h>
#include "pic16f1827_config.h"
#include "spi.h"
//#define DEG_90 12
//#define DEG_0 6
#define DEG_180 17
#define DELAY_TIME 200

#define DEG_LOCKED  0           //�T�[�{�p�x���b�N
#define DEG_LOADED 12           //�T�[�{���U�ʒu
#define DEG_EMPTY   6           //�T�[�{���ˈʒu

#define SHOOTER_UNITS   3       //���w�������ˋ@�\�̐�

//�T�[�{�ʒu�̏�ԃt���O
#define PS_KEEP    2            //����ێ�(�ċN�����̖\���h�~�p)
#define PS_LOADED  1            //���U�ς�
#define PS_EMPTY   0            //�����U

//���w�������ˋ@�\(�T�[�{)�̏�ԊǗ��p
char loaded_flg[SHOOTER_UNITS];


//���荞�ݏ���
void interrupt slave(void)
{

    //�g�p���锭�ˋ@�\�̑I������r_data�Ɋi�[
    r_data = slaveread();       //�֐������Ŋ��荞�݂��ꊇ�s�����Ă���̂Œ���

    if(r_data == 0x01){//�R���g���[������̖��߂ɂ�銄�荞��(���ˎ�)

        //1�i�ڂ����U�ς�
        if(loaded_flg[0] == PS_LOADED){
            CCPR1L              = DEG_EMPTY;            //�T�[�{�𔭎ˈʒu�܂ŉ�]
            __delay_ms(DELAY_TIME);                     //��]����(����)�܂ő҂�
            CCPR1L              = DEG_LOCKED;           //�T�[�{�����b�N
            loaded_flg[0]       = PS_EMPTY;             //���ˍς݃t���O��ݒ�
            __delay_ms(DELAY_TIME);                     //����(����)�܂ő҂�
        }

        //2�i�ڂ����U�ς�
        else if(loaded_flg[1] == PS_LOADED){
            CCPR2L              = DEG_EMPTY;            //�T�[�{�𔭎ˈʒu�܂ŉ�]
            __delay_ms(DELAY_TIME);                     //��]����(����)�܂ő҂�
            CCPR2L              = DEG_LOCKED;           //�T�[�{�����b�N
            loaded_flg[1]       = PS_EMPTY;             //���ˍς݃t���O��ݒ�
            __delay_ms(DELAY_TIME);                     //����(����)�܂ő҂�
        }

        //3�i�ڂ����U�ς�
        else if(loaded_flg[2] == PS_LOADED){
            CCPR3L              = DEG_EMPTY;            //�T�[�{�𔭎ˈʒu�܂ŉ�]
            __delay_ms(DELAY_TIME);                     //��]����(����)�܂ő҂�
            CCPR3L              = DEG_LOCKED;           //�T�[�{�����b�N
            loaded_flg[2]       = PS_EMPTY;             //���ˍς݃t���O��ݒ�
            __delay_ms(DELAY_TIME);                     //����(����)�܂ő҂�
        }
    }

    else if(IOCIF == 1){//���{�b�g���t�{�^���ɂ�銄�荞��(���U��)

        //1�i�ڂ𑕓U
        if(RB5 == 0){
            CCPR1L              = DEG_LOADED;           //�T�[�{�𔭎ˈʒu�܂ŉ�]
            __delay_ms(DELAY_TIME);                     //��]����(����)�܂ő҂�
            CCPR1L              = DEG_LOCKED;           //�T�[�{�����b�N
            loaded_flg[0]       = PS_LOADED;            //���ˍς݃t���O��ݒ�
        }

        //2�i�ڂ𑕓U
        else if(RB7 == 0){
            CCPR2L              = DEG_LOADED;           //�T�[�{�𔭎ˈʒu�܂ŉ�]
            __delay_ms(DELAY_TIME);                     //��]����(����)�܂ő҂�
            CCPR2L              = DEG_LOCKED;           //�T�[�{�����b�N
            loaded_flg[1]       = PS_LOADED;            //���ˍς݃t���O��ݒ�
        }

        //3�i�ڂ𑕓U
        else if(RB2 == 0){
            CCPR3L              = DEG_LOADED;           //�T�[�{�𔭎ˈʒu�܂ŉ�]
            __delay_ms(DELAY_TIME);                     //��]����(����)�܂ő҂�
            CCPR3L              = DEG_LOCKED;           //�T�[�{�����b�N
            loaded_flg[2]       = PS_LOADED;            //���ˍς݃t���O��ݒ�
        }

    }

    IOCBF       = 0;                    //��ԕω��t���O�����Z�b�g
    IOCIF       = 0;                    //��ԕω��t���O�����Z�b�g
    GIE = 1;        //(���d)���荞�݋֎~������
    
}

void main(void)
{
    //���W�X�^�ݒ�
    OSCCON = 0x62;                  //�I�V���[�^�ݒ�

    //�s���ݒ�
    TRISA    = 0xE7;
    TRISB    = 0xB3;                //1011 0011
    PORTA    = 0x00;
    PORTB    = 0x00;
    ANSELA   = 0x00;
    ANSELB   = 0x00;

    //PWM�ݒ�
    CCPTMRS = 0b00000000;           //TMR2���g�p����
    CCP1CON = 0b00001100;           //�V���O��PWM��I��
    CCP2CON = 0b00001100;           //�V���O��PWM��I��
    CCP3CON = 0b00001100;           //�V���O��PWM��I��
    CCP4CON = 0b00001100;           //�V���O��PWM��I��
    T2CON   = 0b01111111;           //
    PR2     = 155;                  //TMR2�v���X�P�[��
    CCPR1L  = 0;
    CCPR1H  = 0;
    CCPR2L  = 0;
    CCPR2H  = 0;
    CCPR3L  = 0;
    CCPR3H  = 0;
    CCPR4L  = 0;
    CCPR4H  = 0;
    TMR2    = 0;                    //�^�C�}2�N���A
    TMR2ON  = 1;
    CCP1SEL = 0;
    CCP2SEL = 0;
    OPTION_REG = 0b00000000;        //�v���A�b�v��R�̐ݒ�(�L����)
    WPUB = 0b11111111;              //B�|�[�g�S�ăv���A�b�v�L��

    //���荞�ݐݒ�
    IOCIF   = 0;                    //��ԕω����荞�݃t���O���Z�b�g
    IOCBN   = 0xFF;                 //�{�^���������ꂽ���Ƃ����m����
    IOCBP   = 0x00;                 //�{�^������������Ƃ͌��m���Ȃ�
    IOCIE   = 1;                    //��ԕω����荞�݂�����

    //�T�[�{��񏉊���

    //�J����Ԃɂ���
    CCPR1L = PS_EMPTY;
    CCPR2L = PS_EMPTY;
    CCPR3L = PS_EMPTY;
    CCPR4L = PS_EMPTY;
    __delay_ms(DELAY_TIME);

    //�T�[�{�̊p�x�����b�N
    CCPR1L = DEG_LOCKED;
    CCPR2L = DEG_LOCKED;
    CCPR3L = DEG_LOCKED;
    CCPR4L = DEG_LOCKED;

    loaded_flg[0] = PS_EMPTY;
    loaded_flg[1] = PS_EMPTY;
    loaded_flg[2] = PS_EMPTY;

    //���荞�݂̋���
    IOCIF   = 0;                        //�s���̏�ԕω����荞�ݏ�Ԃ��N���A
    IOCIE   = 1;                        //�s���̏�ԕω����荞�݂�����

    slave_reg();                        //SPI�ʐM�ݒ�(�X���[�u)

    while(1);

}
