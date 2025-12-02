
#include <bur/plctypes.h>

#ifdef _DEFAULT_INCLUDES
	#include <AsDefault.h>
#endif

void increase_counters(void);


void _INIT ProgramInit(void)
{
	AxisX_HW.EncIf1_Typ = ncSDC_ENC16;
	AxisX_HW.DiDoIf_Typ = ncSDC_DIDO;
	AxisX_HW.DrvIf_Typ = ncSDC_DRVSERVO16;
	
	strcpy(AxisX_HW.EncIf1_Name, "Axis_X_EncIf");
	strcpy(AxisX_HW.DrvIf_Name, "Axis_X_DrvIf");
	strcpy(AxisX_HW.DiDoIf_Name, "Axis_X_DiDoIf");
	
	AxisX_EncIf.iEncOK = 1;
	AxisX_DrvIf.iDrvOK = 1;
	AxisX_DrvIf.iStatusEnable = 1;
	AxisX_DiDoIf.iDriveReady = 1;
	
	fb_controller.k_p = 0.002;
	fb_controller.k_i = 0.16;
	fb_controller.dt = 0.002;
	fb_controller.integrator.dt = 0.002;
	fb_controller.max_abs_value = 20;
	pwm_period = 200;
	
	to_side = 1;
	to_mid = 0;
	
	enable = 1;
}

void _CYCLIC ProgramCyclic(void)
{
	if (coil_powered)
	{
		if (to_side == 1 && to_mid == 0)
		{
			AxisX_DrvIf.oSetPos = 10000;
			axis_X.direction = 1;	
			axis_X.ENABLE = 1;
			if (axis_X.endswitch_a_reached)
			{
				to_side = 0;
				to_mid = 1;
				global_pos = 0;
				axis_X.counter = 0;
			}
			FB_Axis(&axis_X);
			
		}
		else if (to_side == 0 && to_mid == 1)
		{
			AxisX_DrvIf.oSetPos = -10000;
			axis_X.direction = 0;	
			axis_X.ENABLE = 1;
			if (axis_X.counter == 500)
			{
				to_side = 0;
				to_mid = 0;
			}
			FB_Axis(&axis_X);
		}
		else if (to_side  == 0 && to_mid == 0)
		{
			if((forward.go && backward.go) || (forward.go == 0 && backward.go == 0))
			{
				AxisX_DrvIf.oSetPos = 0; // по идее при этом случае отрубается питание, но все же
				axis_X.ENABLE = 0;
			}
			if (forward.go)
			{
				AxisX_DrvIf.oSetPos = 10000;
				axis_X.direction = 1;	
				axis_X.ENABLE = 1;
			}
			else if (backward.go)
			{
				AxisX_DrvIf.oSetPos = -10000;
				axis_X.direction = 0;
				axis_X.ENABLE = 1;
			}
			FB_Axis(&axis_X);
		}

	}
	else
		axis_X.ENABLE = 0;

	
	// счетчики ЖИЗНИИИИ
	AxisX_EncIf.iLifeCnt++;
	AxisX_DiDoIf.iLifeCntDriveEnable++;
	AxisX_DiDoIf.iLifeCntDriveReady++;
	AxisX_DiDoIf.iLifeCntNegHwEnd++;
	AxisX_DiDoIf.iLifeCntPosHwEnd++;
	AxisX_DiDoIf.iLifeCntReference++;
	AxisX_DrvIf.iLifeCnt++;
	// конец счетчикво ЖИЗНИ
	
	
	
	// Чет странное делаем!!!!
	if (axis_X.direction == 1)
	{
		global_pos+=axis_X.counter+1;
	}
	else
		global_pos-=axis_X.counter+1;
	
	if (global_pos < -10000)
	{
		global_pos = -10000;
	}
	if (global_pos > 100)
	{
		global_pos = 100;
	}
	
	
	AxisX_EncIf.iActPos = axis_X.counter; // меняем коунтер по иксу и управляем положением оси
	
	AxisX_EncIf.iActTime = (INT)AsIOTimeCyclicStart();
	AxisX_DiDoIf.iPosHwEnd = axis_X.endswitch_a_reached;
	AxisX_DiDoIf.iNegHwEnd = axis_X.endswitch_b_reached;
	
	if(coil_powered)
	{
		axis_X.reset_counter = 0;
		
		FB_Axis(&axis_X);
		
		coil_pwm_value = 32767;
		
		FB_Controller(&fb_controller);
		axis_X.in = fb_controller.out; // in - это НАПРЯЖЕНИЕ НА МОТОРЫЫЫЫЫЫЫЫЫЫЫЫЫЫЫ
		FB_Axis(&axis_X);
		
		fb_controller.in = AxisX_DrvIf.oSetPos * 10 - axis_X.speed;
		FB_Controller(&fb_controller);
		
		axis_X.in = fb_controller.out;
		FB_Axis(&axis_X);
		
		if (axis_X.endswitch_b_reached)
		{
			if (axis_X.direction == 0)
				axis_X.ENABLE = 0;
			else
				axis_X.ENABLE = 1;
		}
		if (axis_X.endswitch_a_reached)
		{
			if (axis_X.direction == 1)
				axis_X.ENABLE = 0;
			else
				axis_X.ENABLE = 1;
		}
		FB_Axis(&axis_X);
	}
	
	else
	{
		coil_pwm_value = 0;
	}
	
}

void _EXIT ProgramExit(void)
{
	// Insert code here 

}

