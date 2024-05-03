
#include "string.h"
#include "setup.h"
#include "system.h"
#include "mk_conf_tree.h"
#include "USART.h"
#include "gpio.h"
#include "control.h"

VAR_PAR dev_var;
u32 mTimeout_cntrl = 0;
u32 mTimeout_shift = 0;
//============================================================================
uint8_t Control_prop( uint8_t par, uint8_t * name, uint8_t * prop, uint8_t * nbyte )
{
	char * str;
    uint8_t size = 0;
	if( name ) { switch( par )
        {
		case CONTROL_STAT       :	str ="Status"; break;
        case CONTROL_PULS1       :	str ="Counter OFF 1"; break;
        case CONTROL_PULS2       :	str ="Counter OFF 2"; break;		
        case PARAM_RELE1_ON      :	str ="Rele 1 start ON"; break;
        case PARAM_RELE2_ON      :	str ="Rele 2 start ON"; break;
        case PARAM_TIME1_OFF     :	str ="Time 1 OFF rele (sec,0=off)"; break;
        case PARAM_TIME2_OFF     :	str ="Time 2 OFF rele (sec,0=off)"; break;
        default: return 0;
        }
        while( *str ) { *name++ = *str++; size++; } *name = 0; 
    }
	if( prop ) switch( par )
        {
		case CONTROL_STAT       :	*prop = HEX ; break;
        case CONTROL_PULS1      :	
        case CONTROL_PULS2      :	*prop = UINT|RO; break;
        case PARAM_RELE1_ON     :	
        case PARAM_RELE2_ON     :	*prop = BOOL; break;
        case PARAM_TIME1_OFF    :	
        case PARAM_TIME2_OFF    :	*prop = UINT; break;
        default: return 0;
        }
	if( nbyte ) switch( par )
        {
		case CONTROL_STAT       :	
        case CONTROL_PULS1      :	
        case CONTROL_PULS2      :	
        case PARAM_TIME1_OFF    :	
        case PARAM_TIME2_OFF    :	*nbyte = 2; break;
        case PARAM_RELE1_ON     :	
        case PARAM_RELE2_ON     :	*nbyte = 1; break;
        default: return 0;
        }
    return size;
}
//============================================================================
void Control_get(uint8_t par, void * value)
{
    switch( par )
    {
        case CONTROL_STAT     	:	*(Uint32*)value = dev_var.status; break;
        case CONTROL_PULS1      :	*(Uint32*)value = dev_var.pulse_1/10; break;
        case CONTROL_PULS2      :	*(Uint32*)value = dev_var.pulse_2/10; break;
        case PARAM_RELE1_ON     :	*(Uint32*)value = Setup.rele_on[0]; break;
        case PARAM_RELE2_ON     :	*(Uint32*)value = Setup.rele_on[1]; break;
        case PARAM_TIME1_OFF     :	*(Uint32*)value = Setup.time_off[0]; break;
        case PARAM_TIME2_OFF     :	*(Uint32*)value = Setup.time_off[1]; break;
        default:;
    }
}
//============================================================================
void Control_set(uint8_t par, void * value)
{
	u16 i = *(u16*)value;
    switch( par )
    {
		case CONTROL_STAT	  :	dev_var.status = i; break;
		case PARAM_TIME1_OFF  :	Setup.time_off[0] = i; break; 
		case PARAM_TIME2_OFF  :	Setup.time_off[1] = i; break; 
		case PARAM_RELE1_ON	  :	Setup.rele_on[0] =  *(u8*)value; break; 
		case PARAM_RELE2_ON   :	Setup.rele_on[1] =  *(u8*)value; break; 
        default:;
    }
}
//=========================================================================
// Функция обработки
void CONTROL_Proc(void)
{
	static Uint32 timeout_uart = 0;
	static Uint32 timeout_type = 0;
    
	if(timeout_uart+1000 <= HAL_GetTick())
	{
        timeout_uart = HAL_GetTick();
//        dev_var.uart1_en = 0;
	}
//---------------------------------------------------------    
	if(dev_var.start[0] == 0)
	{
        dev_var.start[0] = 2;
        
        if(Setup.rele_on[0])
        {
            RELE1_set(1);
            dev_var.status |= STATUS_RELE_1;
            if(Setup.time_off[0]) 
            {
                dev_var.pulse_1 = Setup.time_off[0]*10;
                dev_var.start[0] = 1;
            }
            else dev_var.pulse_1 = 0;
            timeout_type = HAL_GetTick();
        }
	}
//---------------------------------------------------------    
	if(dev_var.start[1] == 0)
	{
        dev_var.start[1] = 2;
        
        if(Setup.rele_on[1])
        {
            RELE2_set(1);
            dev_var.status |= STATUS_RELE_2;
            if(Setup.time_off[1]) 
            {
                dev_var.pulse_2 = Setup.time_off[1]*10;
                dev_var.start[1] = 1;
            }
            else dev_var.pulse_2 = 0;
            timeout_type = HAL_GetTick();
        }
    }
//---------------------------------------------------------    
	if(timeout_type+100 <= HAL_GetTick())
	{
        timeout_type = HAL_GetTick();
//--------------------------------------------------------------        
        if(Setup.rele_on[0]) dev_var.status |= STATUS_RELE1_ON;
        else dev_var.status &= ~STATUS_RELE1_ON;
        if(Setup.rele_on[1]) dev_var.status |= STATUS_RELE2_ON;
        else dev_var.status &= ~STATUS_RELE2_ON;
//--------------------------------------------------------------        
        if(dev_var.status&STATUS_RELE_1)
        {
            RELE1_set(1);
            if(dev_var.start[0] == 1)
            {
                if(dev_var.pulse_1 > 0) dev_var.pulse_1--;
                if(dev_var.pulse_1 == 0)
                {
                    dev_var.start[0] = 2;
                    RELE1_set(0);
                    dev_var.status &= ~STATUS_RELE_1;
                }
            }
        }
        else
        {
            RELE1_set(0);
            dev_var.pulse_1 = 0;
            dev_var.start[0] = 2;
        }
//--------------------------------------------------------------        
        if(dev_var.status&STATUS_RELE_2)
        {
            RELE2_set(1);
            if(dev_var.start[1] == 1)
            {
                if(dev_var.pulse_2 > 0) dev_var.pulse_2--;
                if(dev_var.pulse_2 == 0)
                {
                    dev_var.start[1] = 2;
                    RELE2_set(0);
                    dev_var.status &= ~STATUS_RELE_2;
                }
            }
        }
        else
        {
            RELE2_set(0);
            dev_var.pulse_2 = 0;
            dev_var.start[1] = 2;
        }
//--------------------------------------------------------------
        if(dev_var.status&STATUS_TIMER_1)
        {
            dev_var.start[0] = 0;
            dev_var.status &= ~STATUS_TIMER_1;
        }
        if(dev_var.status&STATUS_TIMER_2)
        {
            dev_var.start[1] = 0;
            dev_var.status &= ~STATUS_TIMER_2;
        }
//--------------------------------------------------------------
	}
}
//=========================================================================

