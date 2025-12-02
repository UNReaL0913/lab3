
#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "Library.h"
#ifdef __cplusplus
	};
#endif
/* TODO: Add your comment here */
void FB_Axis(struct FB_Axis* inst)
{
	
	if(inst->ENABLE)
	{
		if (inst->direction)
			inst->pwm_value = (inst->in/24) * 32767;
		else
			inst->pwm_value= - (inst->in/24) * 32767;
	}
	else
		inst->pwm_value = 0;
		
	
	inst->speed = inst->counter - inst->last_counter;
	inst->speed = (inst->speed * 3000 / 24.0) / 0.002;
	inst->last_counter = inst->counter;
}
