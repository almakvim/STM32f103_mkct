
#ifndef __CONTROL_H
#define __CONTROL_H

#include "main.h"
#include "system.h"
#include "USART.h"

// Параметры
#define VARR_STATE      0      // R: состояние
//--------------------------------------------------
//#define CMD_PAR         20  // 0x14: значения параметра (ответ на запрос)
#define CMD_SET_PAR     21  // 0x15: установка параметра
#define CMD_GET_PAR     22  // 0x16: запрос значения параметра

#define CMD_RESET		0		// Сброс регистра CMD
//--------------------------------------------------
#define STATUS_NULL  	    0x0000	// Null
#define STATUS_RELE_1    	0x0001	// Включить/выключить реле 1
#define STATUS_RELE_2    	0x0002	// Включить/выключить реле 2
#define STATUS_TIMER_1     	0x0010	// Запустить на выключение таймер 1
#define STATUS_TIMER_2     	0x0020	// Запустить на выключение таймер 2
#define STATUS_RELE1_ON    	0x0100	// Отабражает состояние (Setup.rele_on[0]) включения реле 1 при запуске
#define STATUS_RELE2_ON    	0x0200	// Отабражает состояние (Setup.rele_on[1]) включения реле 2 при запуске
//--------------------------------------------------
#define PAR_STATE  		0x0001	//0 запрос параметра 0


// Переменные настроек
enum CONTROL_VAR
{
	CONTROL_STAT,			// состояние
	PARAM_TIME1_OFF, 	
	PARAM_TIME2_OFF, 	
	PARAM_RELE1_ON, 	
	PARAM_RELE2_ON, 	
	CONTROL_PULS1,			// состояние
	CONTROL_PULS2,			// состояние
//	CONTROL_START1,			// состояние
//	CONTROL_START2,			// состояние

	CONTROL_VAR_NUM    		// количество переменных
};

#pragma pack (1)
typedef struct
{
    u16 status;
	u16 start[2];		// Регистр Старта
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

// Функция обработки
void CONTROL_Proc(void);

#endif // __CONTROL_H
