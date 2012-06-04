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





#ifndef ILAUNCHTHREAD_HPP_
#define ILAUNCHTHREAD_HPP_

#include "utils/misc/include/UID.hpp"

namespace AXIS
{
   namespace AMP
   {
      /**
       * Interface of thread with launcher
       */
      class ILaunchThread
      {
      public:
         /**
          * Launches application
          * @param session is UID of session
          * @param dbId is id of app in database
          */
         virtual void launchApp(AXIS::Service::SessionUid session, int dbId) = 0;

         /**
          * Destructor
          */
         virtual ~ILaunchThread(){}
      };
   }
}

#endif /* ILAUNCHTHREAD_HPP_ */
