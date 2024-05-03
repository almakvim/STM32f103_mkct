
#ifndef __CONTROL_H
#define __CONTROL_H

#include "main.h"
#include "system.h"
#include "USART.h"

// ���������
#define VARR_STATE      0      // R: ���������
//--------------------------------------------------
//#define CMD_PAR         20  // 0x14: �������� ��������� (����� �� ������)
#define CMD_SET_PAR     21  // 0x15: ��������� ���������
#define CMD_GET_PAR     22  // 0x16: ������ �������� ���������

#define CMD_RESET		0		// ����� �������� CMD
//--------------------------------------------------
#define STATUS_NULL  	    0x0000	// Null
#define STATUS_RELE_1    	0x0001	// ��������/��������� ���� 1
#define STATUS_RELE_2    	0x0002	// ��������/��������� ���� 2
#define STATUS_TIMER_1     	0x0010	// ��������� �� ���������� ������ 1
#define STATUS_TIMER_2     	0x0020	// ��������� �� ���������� ������ 2
#define STATUS_RELE1_ON    	0x0100	// ���������� ��������� (Setup.rele_on[0]) ��������� ���� 1 ��� �������
#define STATUS_RELE2_ON    	0x0200	// ���������� ��������� (Setup.rele_on[1]) ��������� ���� 2 ��� �������
//--------------------------------------------------
#define PAR_STATE  		0x0001	//0 ������ ��������� 0


// ���������� ��������
enum CONTROL_VAR
{
	CONTROL_STAT,			// ���������
	PARAM_TIME1_OFF, 	
	PARAM_TIME2_OFF, 	
	PARAM_RELE1_ON, 	
	PARAM_RELE2_ON, 	
	CONTROL_PULS1,			// ���������
	CONTROL_PULS2,			// ���������
//	CONTROL_START1,			// ���������
//	CONTROL_START2,			// ���������

	CONTROL_VAR_NUM    		// ���������� ����������
};

#pragma pack (1)
typedef struct
{
    u16 status;
	u16 start[2];		// ������� ������
    u16 tick;
    u16 pulse_1;
    u16 pulse_2;
    
//    u16 sbus;
    u16 uart1_en;
    
	u32 realtime;   
	u32 count_pkt_in;   
	u32 count_pkt_out;   
	u32 count_pkt_err;
}
VAR_PAR;
#pragma pack(4)

extern VAR_PAR dev_var;

//----------------------------------------------------------------
uint8_t Control_prop(uint8_t par, uint8_t * name, uint8_t * prop, uint8_t * nbyte);
void Control_get(uint8_t par, void * value);
void Control_set(uint8_t par, void * value);
//----------------------------------------------------------------
u8 calc_CS(u8 * addr, u16 size);
u16 conv_baud_uint(u16 baud);

// ������� ���������
void CONTROL_Proc(void);

#endif // __CONTROL_H
