
#include <bur/plctypes.h>
#ifdef __cplusplus
	extern "C"
	{
#endif
	#include "Library_MC.h"
#ifdef __cplusplus
	};
#endif
/* TODO: Add your comment here */
void FB_Regulator(struct FB_Regulator* inst)
{
	REAL u1;
	REAL u2;
	REAL sum_u;
	/*TODO: Add your code here*/
	u1 = inst->e*inst->k_p;
	
	if ((u1)>inst->max_abs_value || u1<-inst->max_abs_value)
	{
		if (u1>0)
		{
			u1 = inst->max_abs_value;
		}
		if (u1<0)
		{
			u1 = -inst->max_abs_value;
		}
	}
	
	u2 = inst->e*inst->k_i + inst->iyOld;
	
	inst->integrator.in = u2;
	FB_Integrator(&(inst->integrator));
	u2=inst->integrator.out;
	
	sum_u = u1+u2;
	
	if (sum_u>inst->max_abs_value || sum_u<-inst->max_abs_value)
	{
		if (sum_u>0)
		{
			sum_u = inst->max_abs_value;
		}
		if (sum_u<0)
		{
			sum_u = -inst->max_abs_value;
		}
	}
	inst->u = sum_u;
	inst->iyOld = inst->u - sum_u;
	
}
 