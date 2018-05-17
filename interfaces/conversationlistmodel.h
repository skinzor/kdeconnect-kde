/*
 * This file is part of KDE Telepathy Chat
 *
 * Copyright (C) 2018 Aleix Pol Gonzalez <aleixpol@kde.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef CONVERSATIONLISTMODEL_H
#define CONVERSATIONLISTMODEL_H

#include <QStandardItemModel>
#include <QLoggingCategory>

#include "interfaces/conversationmessage.h"
#include "interfaces/dbusinterfaces.h"

#include "interfaces/kdeconnectinterfaces_export.h"

Q_DECLARE_LOGGING_CATEGORY(KDECONNECT_SMS_CONVERSATIONS_LIST_MODEL)

class KDECONNECTINTERFACES_EXPORT ConversationListModel
    : public QStandardItemModel
{
    Q_OBJECT
    Q_PROPERTY(QString deviceId READ deviceId WRITE setDeviceId)

public:
    ConversationListModel(QObject* parent = nullptr);
    ~ConversationListModel();

    enum Roles { FromMeRole = Qt::UserRole };

    QString deviceId() const { return m_deviceId; }
    void setDeviceId(const QString &/*deviceId*/);

public Q_SLOTS:
    void handleCreatedConversation(const QString& conversationId);
    void createRowFromMessage(const ConversationMessage& message);
    void printDBusError(const QDBusError& error);

private:
    /**
     * Get all conversations currently known by the conversationsInterface, if any
     */
    void prepareConversationsList();

    DeviceConversationsDbusInterface* m_conversationsInterface;
    QString m_deviceId;
};

#endif // CONVERSATIONLISTMODEL_H
