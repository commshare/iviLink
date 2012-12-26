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
 

#include "CPmpProtoController.hpp"
#include "CPmpProtocol.hpp"
#include "CPmpProtoThread.hpp"

namespace iviLink
{

   namespace PMP
   {

      Logger CPmpProtoController::msLogger = Logger::getInstance(LOG4CPLUS_TEXT("profileManager.PMP.interaction.CPmpProtoController"));

      CPmpProtoController::CPmpProtoController()
         : mpProtocol(new CPmpProtocol()),
           mpProtoThread(new CPmpProtoThread(mpProtocol))

      {
         LOG4CPLUS_TRACE_METHOD(msLogger, __PRETTY_FUNCTION__ );
      }

      CPmpProtoController::~CPmpProtoController()
      {
         LOG4CPLUS_TRACE_METHOD(msLogger, __PRETTY_FUNCTION__ );
         stop();

         delete mpProtoThread;
         mpProtoThread = NULL;

         delete mpProtocol;
         mpProtocol = NULL;
      }

      IPmpProtocol * CPmpProtoController::protocol()
      {
         LOG4CPLUS_TRACE_METHOD(msLogger, __PRETTY_FUNCTION__ );
         return mpProtocol;
      }

      void CPmpProtoController::start()
      {
         LOG4CPLUS_TRACE_METHOD(msLogger, __PRETTY_FUNCTION__ );
         mpProtoThread->start();
      }

      void CPmpProtoController::stop()
      {
         LOG4CPLUS_TRACE_METHOD(msLogger, __PRETTY_FUNCTION__ );
         mpProtoThread->disconnect();
      }


   }

}
