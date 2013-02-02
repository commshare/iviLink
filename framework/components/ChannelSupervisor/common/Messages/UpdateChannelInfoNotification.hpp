/* 
 * iviLINK SDK, version 1.2
 * http://www.ivilink.net
 * Cross Platform Application Communication Stack for In-Vehicle Applications
 * 
 * Copyright (C) 2012-2013, Luxoft Professional Corp., member of IBS group
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


#ifndef UPDATE_CHANNELINFO_NOTIFICATION_HPP_
#define UPDATE_CHANNELINFO_NOTIFICATION_HPP_

#include "pugixml.hpp"
#include "Notification.hpp"
#include "Message.hpp"

namespace iviLink
{
namespace ChannelSupervisor
{
namespace Messages
{

class UpdateChannelInfoNotification: public Notification
{
public:

    UpdateChannelInfoNotification(const char* tag, const UInt32 channelId = 0);

    UpdateChannelInfoNotification(pugi::xml_document* doc);

    virtual ~UpdateChannelInfoNotification()
    {
    }

    virtual const char* GetMessageName() const
    {
        return m_notificationTypeMap[NOTIFICATIONTTYPE_UPDATE_CHANNEL_INFO].c_str();
    }

};

}  // Messages
}  // ChannelSupervisor
}  // iviLink

#endif // UPDATE_CHANNELINFO_NOTIFICATION_HPP_