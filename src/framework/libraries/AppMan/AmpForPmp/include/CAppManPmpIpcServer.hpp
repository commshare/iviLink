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





#ifndef CAPPMANPMPIPCSERVER_HPP_
#define CAPPMANPMPIPCSERVER_HPP_

#include "utils/misc/include/Logger.hpp"
#include "framework/libraries/AppMan/Pmp/include/IPmpHandler.hpp"
#include "framework/libraries/AppMan/Pmp/include/IPmpRequest.hpp"
#include "framework/libraries/AppMan/AmpForPmp/include/IPmpConnectionStatus.hpp"
#include "utils/ipc/include/CIpc.hpp"
#include "utils/ipc/include/ICallbackHandler.hpp"

namespace AXIS
{
   namespace AppMan
   {
      namespace Ipc
      {

         /**
          * Class implements IPC between PMP and AMP (server side, side of AMP)
          */
         class CAppManPmpIpcServer  : public IPmpHandler
                                    , public AXIS::Ipc::ICallbackHandler
         {
         public:
            /**
             * Constructor
             */
            CAppManPmpIpcServer();

            /**
             * Virtual destructor
             */
            virtual ~CAppManPmpIpcServer();

            /**
             * Inits handlers of incoming requests
             * @param pRequest is handler of requests from PMP
             * @param pConnectionStatus is handler of connection status
             */
            void init(IPmpRequest * pRequest, IPmpConnectionStatus * pConnectionStatus);

            /**
             * Main loop of connection
             */
            void loop();

            /**
             * Functin is used to disconnect from PMP
             */
            void disconnect();

            /**
             * Returns true if connection with PMP is OK
             */
            bool checkConnection() const;

         private:
            /**
             * Callback is called in case of start connection with PMP
             */
            virtual void OnConnection(AXIS::Ipc::DirectionID dirId);

            /**
             * Callback is called in case of losing connection with PMP
             */
            virtual void OnConnectionLost(AXIS::Ipc::DirectionID dirId);

            /**
             * Handles incoming IPC requests
             */
            virtual void OnRequest(AXIS::Ipc::MsgID id, UInt8 const* pPayload,
                  UInt32 payloadSize, UInt8* const pResponseBuffer,
                  UInt32& bufferSize, AXIS::Ipc::DirectionID dirId);

            //Requests to PMP
            /**
             * Says to PMP about starting session problems
             * @param session is UID of session
             */
            virtual void appRequestError(AXIS::Service::SessionUid session);

            /**
             * it's used only on clients side
             */
            virtual void appManConnectionLost();

            /**
             * generates IDs for IPC messages
             */
            AXIS::Ipc::MsgID genId();

            IPmpRequest * mpRequest;                     ///< handler of PMP requests
            IPmpConnectionStatus * mpConnectionStatus;   ///< handler of connection status
            AXIS::Ipc::CIpc * mpIpc;                     ///< pointer to IPC connection
            AXIS::Ipc::MsgID mId;                        ///< ID of last message
            CSignalSemaphore mConLostSem;                ///< is used to handle connection status
            bool mBe;                                    ///< is false if needs to exit from connection thread
            volatile bool mNoConnection;                 ///< is true in case of connection problems

            static Logger msLogger;                      ///< logger object
         };

      }

   }

}

#endif /* CAPPMANPMPIPCSERVER_HPP_ */
