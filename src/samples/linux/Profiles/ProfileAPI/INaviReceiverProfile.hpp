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
 

#ifndef INAVI_RECEIVER_PROFILE_API_HPP
#define INAVI_RECEIVER_PROFILE_API_HPP

//Profile Api Base header, must be included
#include "framework/public/appLib/CProfileApiBase.hpp"
#include <deque>

// IBasicSampleProfile_API class (abstract class describing profile API) inherits CProfileApiBase class
class INaviReceiverProfile_API : public iviLink::CProfileApiBase
{
   // Macro returns the argument 
   IVILINK_PROFILE_API_UID(NaviReceiverProfile_PAPI_UID)
   public:

      // Callbacks class (abstract class describing callbacks) inherits IProfileCallbackProxy class
      class Callbacks : public iviLink::Profile::IProfileCallbackProxy
      {
         public:
            virtual void playTracks(std::deque<std::string> tracks) = 0;
      };
}; 


#endif /* IBASIC_SAMPLE_PROFILE_API_HPP */
