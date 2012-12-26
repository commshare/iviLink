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
 

#ifndef __MUTEX_LOCKER_HPP
#define __MUTEX_LOCKER_HPP

#include "CMutex.hpp"

namespace authentication {
   /*&class MutexLocker
   {
      CMutex mMutex;
      public:
         MutexLocker(CMutex mutex)
         {
            mMutex = mutex;
            mMutex.lock();
         }
         
         ~MutexLocker() { mMutex.unlock(); }
    };*/
    
    
    class noncopyable {
      protected:
         noncopyable() {}
         ~noncopyable() {}
      private:
         noncopyable( const noncopyable& );
         noncopyable& operator=( const noncopyable& );
   };


   class MutexLocker : noncopyable {
      public:
         explicit MutexLocker( CMutex& m ) : m(m) { m.lock(); }
         ~MutexLocker() { m.unlock(); }
      private:
         CMutex& m;
   };
} // namespace

#endif //__MUTEX_LOCKER_HPP
