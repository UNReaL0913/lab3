
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
void FB_Integrator(struct FB_Integrator* inst)
{
	/*TODO: Add your code here*/
	inst->dt=0.02;
	inst->out = inst->dt*inst->in + inst->out; 
	
}
