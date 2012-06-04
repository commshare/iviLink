/* 
 *  iviLINK SDK, version 0.9 (for preview only)                                      
 *    http://www.ivilink.net                                                         
 *  Cross Platform Application Communication Stack for In-Vehicle Applications       
 *                                                                                   
 *  Copyright (C) 2012, Luxoft Professional Corp., member of IBS group               
 *                                                                                   
 *  This library is free software; you can redistribute it and/or                    
 *  modify it under the terms of the GNU Lesser General Public                       
 *  License as published by the Free Software Foundation; version 2.1.               
 *                                                                                   
 *  This library is distributed in the hope that it will be useful,                  
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of                   
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU                
 *  Lesser General Public License for more details.                                  
 *                                                                                   
 *  You should have received a copy of the GNU Lesser General Public                 
 *  License along with this library; if not, write to the Free Software              
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA   
 * 
 * 
 * 
 * 
 */





#ifndef CHANNEL_LAYER_READY_HPP_
#define CHANNEL_LAYER_READY_HPP_

#include "framework/components/SystemController/ssm/states/include/CSystemState.hpp"

#include "utils/misc/include/Logger.hpp"

namespace SystemController
{

class CChannelLayerReady : public CSystemState
{
private:
   static Logger sLogger;

public:

   static CSystemState* getInstance();

   virtual string stateName() {return "CChannelLayerReady";}

protected:

   CChannelLayerReady();
   virtual ~CChannelLayerReady();

   virtual void onChannelSupervisorHandshakeDone(CSystemStateMachine* stateMachine);

private:

   static CChannelLayerReady* mIstance;

};

} /* namespace SystemController */
#endif /* CHANNEL_LAYER_READY_HPP_ */
