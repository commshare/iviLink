/* 
 * 
 * iviLINK SDK, version 1.1.2
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
 * 
 */





#include "CMediaStreamingClientProfile.hpp"

#include "framework/components/ChannelSupervisor/Tube/ChannelSupervisorTube.hpp"
#include "samples/linux/Profiles/mediaCommon/CSenderThread.hpp"
#include "utils/threads/CMutex.hpp"
#include "utils/threads/CSignalSemaphore.hpp"

#include <cstring>
#include <cassert>
#include <iostream>

Logger CMediaStreamingClientProfile::msLogger = Logger::getInstance(LOG4CPLUS_TEXT("samples.Profiles.CMediaStreamingClientProfile"));

CMediaStreamingClientProfile::CMediaStreamingClientProfile(iviLink::Profile::IProfileCallbackProxy* pCbProxy)
: mChannelID(0)
, mpAppCallbacks(static_cast<IMediaStreamingClientProfile_API::Callbacks*> (pCbProxy))
, mpSenderThread(new CSenderThread(this))
, mpReqMutex(new CMutex())
, mpReqSemaphore(new CSignalSemaphore())
, mBe(true)
, mTag("CMediaStreamingClientProfile") {
    LOG4CPLUS_TRACE_METHOD(msLogger, __PRETTY_FUNCTION__);
    PropertyConfigurator::doConfigure(LOG4CPLUS_TEXT("log4cplus.properties"));
    mInfo.auForm = "mp3"; 
    mInfo.viForm = "h264";
}

CMediaStreamingClientProfile::~CMediaStreamingClientProfile() {
    LOG4CPLUS_TRACE_METHOD(msLogger, __PRETTY_FUNCTION__);
    mBe = false;

    mpSenderThread->disconnect();
    delete mpSenderThread;
    delete mpReqMutex;

    while (!mReqQueue.empty()) {
        CBuffer buf = mReqQueue.front();
        mReqQueue.pop();
        delete [] buf.getBuffer();
    }
}

void CMediaStreamingClientProfile::streamingAccepted() {
    LOG4CPLUS_TRACE_METHOD(msLogger, __PRETTY_FUNCTION__);
    prepareRequest(STREAMINGACCEPTED);
}

void CMediaStreamingClientProfile::streamingUnaccepted() {
    LOG4CPLUS_TRACE_METHOD(msLogger, __PRETTY_FUNCTION__);
    prepareRequest(STREAMINGUNACCEPTED);
}

void CMediaStreamingClientProfile::prepareRequest(PROCEDURES_STREAMING_IDS proc) {
    LOG4CPLUS_TRACE_METHOD(msLogger, __PRETTY_FUNCTION__);
    const UInt32 size = 4;
    CBuffer buf(new UInt8[size], size);
    if (buf.write((UInt16) proc)) {
        mpReqMutex->lock();
        mReqQueue.push(buf);
        mpReqMutex->unlock();
        mpReqSemaphore->signal();
    } else {
        LOG4CPLUS_ERROR(msLogger, "Unable to prepare buffer - buffer size is not enough");
        delete [] buf.getBuffer();
    }
}

void CMediaStreamingClientProfile::procInfo(std::string const& info) {

    size_t pos = info.find(";"); 
    if (mInfo.auForm == info.substr(0, pos) && mInfo.viForm == info.substr(pos + 1))
    { 
        streamingAccepted();
        mpAppCallbacks->onStreamingClientAccepted();
    }   
    else 
    {
        streamingUnaccepted();
        mpAppCallbacks->onStreamingClientUnaccepted();
    }
                          
}

void CMediaStreamingClientProfile::onEnable() {
    LOG4CPLUS_TRACE_METHOD(msLogger, __PRETTY_FUNCTION__);
    mChannelID = iviLink::Channel::allocateChannel(mTag, this);
    if (mChannelID) {
        LOG4CPLUS_INFO(msLogger, "Channel allocated, starting the communication...");
        mpSenderThread->start();
    } else {
        LOG4CPLUS_WARN(msLogger, "allocate Channel failed");
    }
}

void CMediaStreamingClientProfile::onDisable() {
    CError err = iviLink::Channel::deallocateChannel(mChannelID);
    if (!err.isNoError()) {
        LOG4CPLUS_WARN(msLogger, "Unable to deallocate channel: " + static_cast<std::string> (err));
    }
}

//from CChannelHandler

void CMediaStreamingClientProfile::bufferReceived(const iviLink::Channel::tChannelId channel, iviLink::CBuffer const& buffer) {
    LOG4CPLUS_TRACE_METHOD(msLogger, __PRETTY_FUNCTION__);
    if (mChannelID != channel) {
        LOG4CPLUS_INFO(msLogger, "mChannelID != channel_id");
        return;
    } else {
        LOG4CPLUS_INFO(msLogger, "mChannelID == channel_id");
    }

 
    UInt16 tmp;
    if (!buffer.read(tmp)) {
        LOG4CPLUS_WARN(msLogger, "Unable to read request type from buffer");
        return;
    }
    
   PROCEDURES_STREAMING_IDS proc = static_cast<PROCEDURES_STREAMING_IDS>(tmp);
   
    if (proc == SENDSTREAMINGINFO)
   {
         LOG4CPLUS_INFO(msLogger, "case SENDSTREAMINGINFO");
         std::string info; 
         if (buffer.read(info))
         procInfo(info);
   }
   else
   {
         LOG4CPLUS_WARN(msLogger, "Unknown request type");
   }

}

void CMediaStreamingClientProfile::channelDeletedCallback(const UInt32 channel_id) {
    LOG4CPLUS_TRACE_METHOD(msLogger, __PRETTY_FUNCTION__);

    if (mChannelID == channel_id)
        mChannelID = 0;

    CError err = iviLink::Channel::deallocateChannel(channel_id);
    if (!err.isNoError()) {
        LOG4CPLUS_WARN(msLogger, "Unable to deallocate channel: " + static_cast<std::string> (err));
    }
}

void CMediaStreamingClientProfile::connectionLostCallback() {
    LOG4CPLUS_TRACE_METHOD(msLogger, __PRETTY_FUNCTION__);
}

void CMediaStreamingClientProfile::senderLoop() {
    LOG4CPLUS_TRACE_METHOD(msLogger, __PRETTY_FUNCTION__);
    while (mBe) {
        if (hasRequests()) {
            handleRequest();
        } else {
            mpReqSemaphore->wait();
        }
    }
}

bool CMediaStreamingClientProfile::hasRequests() {
    mpReqMutex->lock();
    bool res = !mReqQueue.empty();
    mpReqMutex->unlock();
    return res;
}

void CMediaStreamingClientProfile::handleRequest() {
    mpReqMutex->lock();
    CBuffer buf = mReqQueue.front();
    mReqQueue.pop();
    mpReqMutex->unlock();

    CError err = iviLink::Channel::sendBuffer(mChannelID, buf);
    if (!err.isNoError()) {
        LOG4CPLUS_INFO(msLogger, "CMediaStreamingClientProfile::handleRequest() :: Send error"
                + static_cast<std::string> (err));
    }

    delete [] buf.getBuffer();
}
