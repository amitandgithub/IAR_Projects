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
	inline ClockManager*     GetClockManager()    { return ClockManager::GetInstance();}
	inline PortManager*      GetPortManager ()    { return PortManager::GetInstance();}
	inline InterruptManager* GetInterruptManager(){ return InterruptManager::GetInstance();}
};

}//namespace Bsp


#endif /* APP_INC_PERIPHERAL_HPP_ */
