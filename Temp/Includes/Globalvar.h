/* Automation Studio generated header file */
/* Do not edit ! */

#ifndef _BUR_1764684359_2_
#define _BUR_1764684359_2_

#include <bur/plctypes.h>

/* Constants */
#ifdef _REPLACE_CONST
#else
#endif


/* Variables */
_GLOBAL plcbit to_mid;
_GLOBAL plcbit to_side;
_GLOBAL unsigned char homing;
_GLOBAL struct FB_Direction forward;
_GLOBAL struct FB_Direction backward;
_GLOBAL struct ARNC0CNC_typ CNCsys;
_GLOBAL plcbit gAxis03_ModuleOk;
_GLOBAL struct SdcDiDoIf_typ gAxis03_DiDoIf;
_GLOBAL struct SdcDrvIf16_typ gAxis03_DrvIf;
_GLOBAL struct SdcHwCfg_typ gAxis03_HW;
_GLOBAL struct ACP10AXIS_typ gAxis03;
_GLOBAL plcbit gAxisTest_ModuleOk;
_GLOBAL struct SdcDiDoIf_typ gAxisTest_DiDoIf;
_GLOBAL struct SdcDrvIf16_typ gAxisTest_DrvIf;
_GLOBAL struct SdcHwCfg_typ gAxisTest_HW;
_GLOBAL struct ACP10AXIS_typ gAxisTest;
_GLOBAL struct ACP10AXIS_typ gAxis02;
_GLOBAL struct ACP10AXIS_typ gAxis01;
_GLOBAL struct SdcHwCfg_typ AxisX_HW;
_GLOBAL struct SdcDiDoIf_typ AxisX_DiDoIf;
_GLOBAL struct SdcDrvIf16_typ AxisX_DrvIf;
_GLOBAL struct SdcEncIf16_typ AxisX_EncIf;
_GLOBAL struct ACP10AXIS_typ AxisX;
_GLOBAL signed short global_pos;





__asm__(".section \".plc\"");

/* Used IEC files */
__asm__(".ascii \"iecfile \\\"Logical/Global.var\\\" scope \\\"global\\\"\\n\"");
__asm__(".ascii \"iecfile \\\"Logical/Libraries/Library/Library.fun\\\" scope \\\"global\\\"\\n\"");

/* Exported library functions and function blocks */

__asm__(".previous");


#endif /* _BUR_1764684359_2_ */

