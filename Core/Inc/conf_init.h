
#ifndef __conf_init_H
#define __conf_init_H
#ifdef __cplusplus
 extern "C" {
#endif

#include "system.h"
#include "control.h"

typedef uint8_t (*func_prop)(uint8_t par, uint8_t * name, uint8_t * prop, uint8_t * nbyte);
typedef void (*func_cmd)(uint8_t par, void * value);

enum UNIT_NUM   // Parent enum
{
	MAIN_UNIT,			
	SYSTEM_UNIT,				
	CONTROL_UNIT,			
	N_UNIT,     // Number of units (nodes)				
};

#pragma pack (1)
//-------------------------------------------------------
const char *namesUnit[] =	
{
	"RF_103_RELE_2",      // name_unit
	"System",               // name_unit
	"Control",              // name_unit
};
//--------------- Variant 1 ------------------------------
const u8 unitProp[][2] =	// Node tree structure 
{
    {MAIN_UNIT, 0},                 //  {parent, num_params },
    {MAIN_UNIT, SYSTEM_VAR_NUM},    //  {parent, num_params },
    {MAIN_UNIT, CONTROL_VAR_NUM},   //  {parent, num_params },
};
// Tree structure:
// DS18B20 + SHTC3-|
//                 |-System
//                 |-Control

//--------------- Variant 2 ------------------------------
//const u8 unitProp[][2] =	// Node tree structure 
//{
//    {MAIN_UNIT, 0},                  //  {parent, num_params },
//    {MAIN_UNIT, SYSTEM_VAR_NUM},     //  {parent, num_params },
//    {SYSTEM_UNIT, CONTROL_VAR_NUM},  //  {parent, num_params },
//    {SYSTEM_UNIT, DS18B20_VAR_NUM},  //  {parent, num_params },
//    {SYSTEM_UNIT, PARAM_VAR_NUM},    //  {parent, num_params },
//};
// Tree structure:
// DS18B20 + SHTC3-|
//                 |-System-|
//                          |-Control
//-------------------------------------------------------
func_prop Func_prop[] =		
{
    0,
	System_prop,	
	Control_prop,
};
//-------------------------------------------------------
func_cmd Func_get[] =		
{
    0,
	System_get,	
	Control_get,
};
//-------------------------------------------------------
func_cmd Func_set[] =		
{
    0,
	System_set,	
	Control_set,
};
//-------------------------------------------------------

#pragma pack (4)

#ifdef __cplusplus
}
#endif
#endif /*__conf_init_H */

