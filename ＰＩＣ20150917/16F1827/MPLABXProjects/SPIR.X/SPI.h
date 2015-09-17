/*Slave*/

unsigned char R_data;

void SlaveInit();
unsigned char SlaveRead();


/*Master*/

#define SS_RA0 0
#define SS_RA1 1
#define SS_RA2 2
#define SS_RA3 3
#define SS_RA4 4
#define SS_RA7 5
#define SS_RB0 6
#define SS_RB3 7
#define SS_RB6 8
#define SS_RB7 9

void MasterInit();
void MasterSend(int obj,unsigned char S_data);