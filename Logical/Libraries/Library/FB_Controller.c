
#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "Library.h"
#ifdef __cplusplus
	};
#endif

void FB_Controller(struct FB_Controller* inst)

{
	
	float ABS(float x)
		{
		if (x > 0)
			return x;
		else
			return -x;
	}

	float SAT_POS(float x)
		{
		if(x < 0)
		{
			if(x < -inst->max_abs_value)
				return -inst->max_abs_value;
			else
				return x;
		}
		else
		{
			if(x > inst->max_abs_value)
				return inst->max_abs_value;
			else
				return x;
		}
	}
	float SAT(float x)
		{
		if (ABS(x) > inst->max_abs_value)
		{
			return inst->max_abs_value;
		}
		else
		{
			return ABS(x);
		}
	}
			
		
	inst->integrator.in = inst->in * inst->k_i * inst->dt + inst->iyOld;
	FB_Integrator(&inst->integrator);
	inst->out = SAT((SAT(inst->in * inst->k_p) + inst->integrator.out));
	
	inst->iyOld = inst->out - (SAT_POS(inst->in * inst->k_p) + inst->integrator.out);
	
}
