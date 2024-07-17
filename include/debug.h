#ifndef F1A1516F_2335_47F3_B4CA_77990137372F
#define F1A1516F_2335_47F3_B4CA_77990137372F

#include "SEGGER_RTT.h"
#include <stdbool.h>
#include <stdint.h>
#define DEBUG_ENABLED 1

enum STATE
{
    LOW_POWER = 0,
    ACTIVE = 1,
    ULTRA_LOW_POWER = 2,
};
#define	LL_PRINT			(0xFF)
#define	LL_INFO			(0x01 << 0)
#define	LL_DEBUG		(0x01 << 1)
#define	LL_WARNING		(0x01 << 2)
#define	LL_ERROR		(0x01 << 3)

#define	LL_TEXT(level)	( (level == LL_INFO)?"INFO":( (level == LL_DEBUG)?"DEBUG":( (level == LL_WARNING)?"WARNING":"ERROR") ) )	
	
#ifdef DEBUG_ENABLED
  #define	print(level,msg,...)						\
	if(level == LL_PRINT)							\
	{												\
		SEGGER_RTT_printf(0,msg,##__VA_ARGS__);		\
	}												\
	else if(level )			    \
	{												\
		if(level == LL_ERROR)						\
		{											\
			SEGGER_RTT_printf(0,RTT_CTRL_TEXT_RED "%s: %s +%d " msg RTT_CTRL_RESET,	\
			LL_TEXT(level),							\
			__FILE__,								\
			__LINE__,								\
			##__VA_ARGS__);							\
		}											\
		else										\
		{											\
			SEGGER_RTT_printf(0, "%s: %s +%d " msg,	\
			LL_TEXT(level),							\
			__FILE__,								\
			__LINE__,								\
			##__VA_ARGS__);							\
		}											\
	}

#else
  #define print(level,msg,...)	
#endif

#define	printF(msg,...)								\
		SEGGER_RTT_printf(0,msg,##__VA_ARGS__)	
                

#define ABS(x)  ( (x > 0) ? x : (-x) )

#endif /* F1A1516F_2335_47F3_B4CA_77990137372F */
