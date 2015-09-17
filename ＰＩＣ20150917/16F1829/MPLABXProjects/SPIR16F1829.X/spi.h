/*Slave*/

unsigned char r_data;

void slave_reg();
unsigned char slaveread();


/*Master*/

//mastersend‚Ìobj‚Ì’è‹`
#define SS_RA0 0
#define SS_RA1 1
#define SS_RA2 2
#define SS_RA3 3
#define SS_RA4 4
#define SS_RA5 5
#define SS_RB5 6
#define SS_RB7 7
#define SS_RC0 8
#define SS_RC1 9
#define SS_RC2 10
#define SS_RC3 11
#define SS_RC4 12
#define SS_RC5 13
#define SS_RC6 14

void master_reg();
void mastersend(int obj,unsigned char s_data);