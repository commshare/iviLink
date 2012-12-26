/* 
 * iviLINK SDK, version 1.1.19
 * http://www.ivilink.net
 * Cross Platform Application Communication Stack for In-Vehicle Applications
 * 
 * Copyright (C) 2012, Luxoft Professional Corp., member of IBS group
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; version 2.1.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 * 
 */ 
 

#ifndef CNOTIFICATIONS_PROFILE_HPP
#define CNOTIFICATIONS_PROFILE_HPP

#include <string>

#include "Logger.hpp"
#include "profileLib.hpp"
#include "INotificationsProfileAPI.hpp"

//namespace required for reading data was sending by other side
using iviLink::CBuffer;
//namespace required for working with channels
using iviLink::Channel::tChannelId;

IVILINK_PROFILE_BEGIN

class CNotificationsProfile: public INotificationsProfileAPI
                             , public iviLink::Channel::CChannelHandler
{
   IVILINK_PROFILE_DECLARE
   IVILINK_PROFILE_NAME(CNotificationsProfile)
   IVILINK_PROFILE_VERSION(1)
   IVILINK_PROFILE_UID(NotificationsProfile_UID)
   IVILINK_PROFILE_API_UID(NotificationsProfile_PAPI_UID)

   CNotificationsProfile(iviLink::Profile::IProfileCallbackProxy* pCbProxy);
   virtual ~CNotificationsProfile();
    
   //PAPI
   virtual void sendString(const std::string & data);

   // CChannelHandler
   virtual void onBufferReceived(const tChannelId channel, CBuffer const& buffer);

   virtual void onChannelDeleted(const UInt32 channel_id);

   virtual void onConnectionLost();

   virtual void onEnable();

   virtual void onDisable();

   //Channel ID
   tChannelId mChannelID;
   std::string mName;
   
   //Pointer to instance of class describing callbacks
   INotificationsProfileAPI::Callbacks* mpAppCallbacks;

   static Logger msLogger;
};

IVILINK_PROFILE_END(CNotificationsProfile)

#endif
