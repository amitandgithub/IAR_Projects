/*
 * SysTickTimer.hpp
 *
 *  Created on: 19-Oct-2017
 *      Author: Amit Chaudhary
 */

#ifndef APP_INC_SYSTICKTIMER_HPP_
#define APP_INC_SYSTICKTIMER_HPP_

namespace Bsp
{

class SysTickTimer
{
public:
	const u32 SYS_TICK_FREQ = 1000UL;
	static bool HwInit(u32 SysTickFreq);
	static inline u32 GetTicks(){ return m_ticks;}
	static inline u32 GetMicroTicks(){ return (m_ticks*1000UL +  (SysTick->LOAD - SysTick->VAL) );}

	static void DelayTicks (u32 Ticks);

	static inline u32 GetTicksSince(u32 LastTicks)
	{
		u32 CurrentTicks = GetTicks();

		return ( (CurrentTicks >= LastTicks)? (CurrentTicks - LastTicks ) :   (CurrentTicks - LastTicks + 0xFFFFFFFFUL) );
	}

	static SysTickTimer* GetInstance();
	static inline void IncrementTicks(){m_ticks++;}
	~SysTickTimer(){};

private:
	//SysTickTimer(){m_pSysTickTimer = nullptr;}
	//static SysTickTimer* m_pSysTickTimer;
	static volatile uint32_t m_ticks;

};













}



#endif /* APP_INC_SYSTICKTIMER_HPP_ */
