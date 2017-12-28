/*
 * Peripheral.hpp
 *
 *  Created on: 14-Oct-2017
 *      Author: Amit Chaudhary
 */

#ifndef APP_INC_PERIPHERAL_HPP_
#define APP_INC_PERIPHERAL_HPP_

#include"ClockManager.hpp"
#include"PortManager.hpp"
#include"InterruptManager.hpp"

namespace Bsp
{


class Peripheral
{
protected:
	Peripheral(){};
	virtual~Peripheral(){}
	virtual bool HwInit() = 0;
	virtual bool HwConfig(void* pConfigStruct);
	virtual void HwEnable();
	virtual void HwDisable();
	virtual uint32_t HwGetFlagStatus(uint32_t aFlag );
	virtual bool HwConfigInterrupt(uint32_t InterruptNo);
	virtual bool HwEnableInterrupt(uint32_t InterruptNo);
	virtual bool HwDisableInterrupt(uint32_t InterruptNo);
	virtual bool HwClearInterrupt(uint32_t InterruptNo);
	inline ClockManager*     GetClockManager()    { return ClockManager::GetInstance();}
	inline PortManager*      GetPortManager ()    { return PortManager::GetInstance();}
	inline InterruptManager* GetInterruptManager(){ return InterruptManager::GetInstance();}
};

}//namespace Bsp


#endif /* APP_INC_PERIPHERAL_HPP_ */
