#include "preemptive_methods.h"

bool PA_IsProcessDying2()
{
    PA_Variable params;
    return PA_GetBooleanVariable(PA_ExecuteCommandByID(CMD_Process_aborted, &params, 0));
}

PA_long32 PA_GetCurrentProcessNumber2()
{
    PA_Variable params;
    return PA_GetLongintVariable(PA_ExecuteCommandByID(CMD_Current_process, &params, 0));
}

void PA_PutProcessToSleep2(PA_long32 process, double delay)
{
    PA_Variable params[2];
    params[0] = PA_CreateVariable(eVK_Longint);
    PA_SetLongintVariable(&params[0], process);

    params[1] = PA_CreateVariable(eVK_Real);
    PA_SetRealVariable(&params[1], delay);

    PA_ExecuteCommandByID(CMD_DELAY_PROCESS, params, 2);
    
    PA_ClearVariable(&params[0]);
    PA_ClearVariable(&params[1]);
}
