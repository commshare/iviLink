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
 

#ifndef IPMPCORETOSYSCTRL_HPP_
#define IPMPCORETOSYSCTRL_HPP_

namespace iviLink
{
   namespace PMP
   {
      /**
       * PMP Core interface for System controller
       */
      class IPmpCoreToSysCtrl
      {
      public:

         /**
          * Unlocks auth profile by system controller request
          * @retval true success
          * @retval false auth profile is unknown
          */
         virtual bool unlockAuthProfile() = 0;

         /**
          * Unlocks all Profiles by system controller request
          */
         virtual void unlockBySysCtrlAll() = 0;

      protected:

         virtual ~IPmpCoreToSysCtrl() { }
      };
   }
}

#endif /* IPMPCORETOSYSCTRL_HPP_ */
