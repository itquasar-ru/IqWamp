/**********************************************************************************
 **
 ** Copyright © 2016 Pavel A. Puchkov 
 **
 ** This file is part of IqMeteoServer. 
 **
 ** IqMeteoServer is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU Lesser General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** IqMeteoServer is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU Lesser General Public License for more details.
 **
 ** You should have received a copy of the GNU Lesser General Public License
 ** along with IqMeteoServer.  If not, see <http://www.gnu.org/licenses/>.
 **
 **********************************************************************************/

#ifndef IQWAMPABSTRACTCLIENT_H
#define IQWAMPABSTRACTCLIENT_H

#include <QObject>
#include "iqwampregistration.h"
#include "iqwampyieldresult.h"
#include <functional>
#include "iqwamp_global.h"
#include "iqwampcallerror.h"

class IQWAMPSHARED_EXPORT IqWampAbstractClient: public QObject
{
    Q_OBJECT
public:
    IqWampAbstractClient(QObject *parent = 0);

    virtual ~IqWampAbstractClient();

    bool publish(const QString &topic, const QJsonArray &arguments, const QJsonObject &argumentsKw);
    bool publish(const QString &topic, const QJsonObject &argumentsKw);
    bool publish(const QString &topic, const QJsonArray &arguments);

    bool call(const QString &procedure,
              std::function<void (const QJsonArray &, const QJsonObject &)> callback,
              std::function<void (const IqWampCallError &)> errorCallback = [](const IqWampCallError &){});
    bool call(const QString &procedure,
              std::function<void (const QJsonArray &)> callback,
              std::function<void (const IqWampCallError &)> errorCallback = [](const IqWampCallError &){});
    bool call(const QString &procedure,
              std::function<void (const QJsonObject &)> callback,
              std::function<void (const IqWampCallError &)> errorCallback = [](const IqWampCallError &){});
    bool call(const QString &procedure,
              std::function<void ()> callback,
              std::function<void (const IqWampCallError &)> errorCallback = [](const IqWampCallError &){});
    bool call(const QString &procedure,
              const QJsonArray &arguments,
              std::function<void (const QJsonArray &, const QJsonObject &)> callback,
              std::function<void (const IqWampCallError &)> errorCallback = [](const IqWampCallError &){});
    bool call(const QString &procedure,
              const QJsonArray &arguments,
              std::function<void (const QJsonArray &)> callback,
              std::function<void (const IqWampCallError &)> errorCallback = [](const IqWampCallError &){});
    bool call(const QString &procedure,
              const QJsonArray &arguments,
              std::function<void (const QJsonObject &)> callback,
              std::function<void (const IqWampCallError &)> errorCallback = [](const IqWampCallError &){});
    bool call(const QString &procedure,
              const QJsonArray &arguments,
              std::function<void ()> callback,
              std::function<void (const IqWampCallError &)> errorCallback = [](const IqWampCallError &){});
    bool call(const QString &procedure,
              const QJsonObject &argumentsKw,
              std::function<void (const QJsonArray &, const QJsonObject &)> callback,
              std::function<void (const IqWampCallError &)> errorCallback = [](const IqWampCallError &){});
    bool call(const QString &procedure,
              const QJsonObject &argumentsKw,
              std::function<void (const QJsonArray &)> callback,
              std::function<void (const IqWampCallError &)> errorCallback = [](const IqWampCallError &){});
    bool call(const QString &procedure,
              const QJsonObject &argumentsKw,
              std::function<void (const QJsonObject &)> callback,
              std::function<void (const IqWampCallError &)> errorCallback = [](const IqWampCallError &){});
    bool call(const QString &procedure,
              const QJsonObject &argumentsKw,
              std::function<void ()> callback,
              std::function<void (const IqWampCallError &)> errorCallback = [](const IqWampCallError &){});
    bool call(const QString &procedure,
              const QJsonArray &arguments,
              const QJsonObject &argumentsKw,
              std::function<void (const QJsonArray &, const QJsonObject &)> callback,
              std::function<void (const IqWampCallError &)> errorCallback = [](const IqWampCallError &){});
    bool call(const QString &procedure,
              const QJsonArray &arguments,
              const QJsonObject &argumentsKw,
              std::function<void (const QJsonArray &)> callback,
              std::function<void (const IqWampCallError &)> errorCallback = [](const IqWampCallError &){});
    bool call(const QString &procedure,
              const QJsonArray &arguments,
              const QJsonObject &argumentsKw,
              std::function<void (const QJsonObject &)> callback,
              std::function<void (const IqWampCallError &)> errorCallback = [](const IqWampCallError &){});
    bool call(const QString &procedure,
              const QJsonArray &arguments,
              const QJsonObject &argumentsKw,
              std::function<void ()> callback,
              std::function<void (const IqWampCallError &)> errorCallback = [](const IqWampCallError &){});

    template <typename Obj>
    bool call(const QString &procedure,
              Obj *object,
              void (Obj::*callback)(),
              void (Obj::*errorCallback)(const IqWampCallError &) = Q_NULLPTR)
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object);

        std::function<void (const IqWampCallError &)> errorCallbackFunction = [](const IqWampCallError &){};
        if (errorCallback)
            errorCallbackFunction = std::bind(errorCallback, object, std::placeholders::_1);

        return callProcedure(procedure, QJsonArray(), QJsonObject(), callbackFunction, errorCallbackFunction);
    }

    template <typename Obj>
    bool call(const QString &procedure,
              Obj *object,
              void ((Obj::*callback)() const),
              void (Obj::*errorCallback)(const IqWampCallError &) = Q_NULLPTR)
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object);

        std::function<void (const IqWampCallError &)> errorCallbackFunction = [](const IqWampCallError &){};
        if (errorCallback)
            errorCallbackFunction = std::bind(errorCallback, object, std::placeholders::_1);

        return callProcedure(procedure, QJsonArray(), QJsonObject(), callbackFunction, errorCallbackFunction);
    }

    template <typename Obj>
    bool call(const QString &procedure,
              Obj *object,
              void (Obj::*callback)(const QJsonArray &),
              void (Obj::*errorCallback)(const IqWampCallError &) = Q_NULLPTR)
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_1);

        std::function<void (const IqWampCallError &)> errorCallbackFunction = [](const IqWampCallError &){};
        if (errorCallback)
            errorCallbackFunction = std::bind(errorCallback, object, std::placeholders::_1);

        return callProcedure(procedure, QJsonArray(), QJsonObject(), callbackFunction, errorCallbackFunction);
    }

    template <typename Obj>
    bool call(const QString &procedure,
              Obj *object,
              void ((Obj::*callback)(const QJsonArray &) const),
              void (Obj::*errorCallback)(const IqWampCallError &) = Q_NULLPTR)
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_1);

        std::function<void (const IqWampCallError &)> errorCallbackFunction = [](const IqWampCallError &){};
        if (errorCallback)
            errorCallbackFunction = std::bind(errorCallback, object, std::placeholders::_1);

        return callProcedure(procedure, QJsonArray(), QJsonObject(), callbackFunction, errorCallbackFunction);
    }

    template <typename Obj>
    bool call(const QString &procedure,
              Obj *object,
              void (Obj::*callback)(const QJsonObject &),
              void (Obj::*errorCallback)(const IqWampCallError &) = Q_NULLPTR)
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_2);

        std::function<void (const IqWampCallError &)> errorCallbackFunction = [](const IqWampCallError &){};
        if (errorCallback)
            errorCallbackFunction = std::bind(errorCallback, object, std::placeholders::_1);

        return callProcedure(procedure, QJsonArray(), QJsonObject(), callbackFunction, errorCallbackFunction);
    }

    template <typename Obj>
    bool call(const QString &procedure,
              Obj *object,
              void ((Obj::*callback)(const QJsonObject &) const),
              void (Obj::*errorCallback)(const IqWampCallError &) = Q_NULLPTR)
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_2);

        std::function<void (const IqWampCallError &)> errorCallbackFunction = [](const IqWampCallError &){};
        if (errorCallback)
            errorCallbackFunction = std::bind(errorCallback, object, std::placeholders::_1);

        return callProcedure(procedure, QJsonArray(), QJsonObject(), callbackFunction, errorCallbackFunction);
    }

    template <typename Obj>
    bool call(const QString &procedure,
              Obj *object,
              void (Obj::*callback)(const QJsonArray &, const QJsonObject &),
              void (Obj::*errorCallback)(const IqWampCallError &) = Q_NULLPTR)
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_1, std::placeholders::_2);

        std::function<void (const IqWampCallError &)> errorCallbackFunction = [](const IqWampCallError &){};
        if (errorCallback)
            errorCallbackFunction = std::bind(errorCallback, object, std::placeholders::_1);

        return callProcedure(procedure, QJsonArray(), QJsonObject(), callbackFunction, errorCallbackFunction);
    }

    template <typename Obj>
    bool call(const QString &procedure,
              Obj *object,
              void ((Obj::*callback)(const QJsonArray &, const QJsonObject &) const),
              void (Obj::*errorCallback)(const IqWampCallError &) = Q_NULLPTR)
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_1, std::placeholders::_2);

        std::function<void (const IqWampCallError &)> errorCallbackFunction = [](const IqWampCallError &){};
        if (errorCallback)
            errorCallbackFunction = std::bind(errorCallback, object, std::placeholders::_1);

        return callProcedure(procedure, QJsonArray(), QJsonObject(), callbackFunction, errorCallbackFunction);
    }

    template <typename Obj>
    bool call(const QString &procedure,
              const QJsonArray &arguments,
              Obj *object,
              void (Obj::*callback)(),
              void (Obj::*errorCallback)(const IqWampCallError &) = Q_NULLPTR)
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object);

        std::function<void (const IqWampCallError &)> errorCallbackFunction = [](const IqWampCallError &){};
        if (errorCallback)
            errorCallbackFunction = std::bind(errorCallback, object, std::placeholders::_1);

        return callProcedure(procedure, arguments, QJsonObject(), callbackFunction, errorCallbackFunction);
    }

    template <typename Obj>
    bool call(const QString &procedure,
              const QJsonArray &arguments,
              Obj *object,
              void ((Obj::*callback)() const),
              void (Obj::*errorCallback)(const IqWampCallError &) = Q_NULLPTR)
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object);

        std::function<void (const IqWampCallError &)> errorCallbackFunction = [](const IqWampCallError &){};
        if (errorCallback)
            errorCallbackFunction = std::bind(errorCallback, object, std::placeholders::_1);

        return callProcedure(procedure, arguments, QJsonObject(), callbackFunction, errorCallbackFunction);
    }

    template <typename Obj>
    bool call(const QString &procedure,
              const QJsonArray &arguments,
              Obj *object,
              void (Obj::*callback)(const QJsonArray &),
              void (Obj::*errorCallback)(const IqWampCallError &) = Q_NULLPTR)
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_1);

        std::function<void (const IqWampCallError &)> errorCallbackFunction = [](const IqWampCallError &){};
        if (errorCallback)
            errorCallbackFunction = std::bind(errorCallback, object, std::placeholders::_1);

        return callProcedure(procedure, arguments, QJsonObject(), callbackFunction, errorCallbackFunction);
    }

    template <typename Obj>
    bool call(const QString &procedure,
              const QJsonArray &arguments,
              Obj *object,
              void ((Obj::*callback)(const QJsonArray &) const),
              void (Obj::*errorCallback)(const IqWampCallError &) = Q_NULLPTR)
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_1);

        std::function<void (const IqWampCallError &)> errorCallbackFunction = [](const IqWampCallError &){};
        if (errorCallback)
            errorCallbackFunction = std::bind(errorCallback, object, std::placeholders::_1);

        return callProcedure(procedure, arguments, QJsonObject(), callbackFunction, errorCallbackFunction);
    }

    template <typename Obj>
    bool call(const QString &procedure,
              const QJsonArray &arguments,
              Obj *object,
              void (Obj::*callback)(const QJsonObject &),
              void (Obj::*errorCallback)(const IqWampCallError &) = Q_NULLPTR)
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_2);

        std::function<void (const IqWampCallError &)> errorCallbackFunction = [](const IqWampCallError &){};
        if (errorCallback)
            errorCallbackFunction = std::bind(errorCallback, object, std::placeholders::_1);

        return callProcedure(procedure, arguments, QJsonObject(), callbackFunction, errorCallbackFunction);
    }

    template <typename Obj>
    bool call(const QString &procedure,
              const QJsonArray &arguments,
              Obj *object,
              void ((Obj::*callback)(const QJsonObject &) const),
              void (Obj::*errorCallback)(const IqWampCallError &) = Q_NULLPTR)
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_2);

        std::function<void (const IqWampCallError &)> errorCallbackFunction = [](const IqWampCallError &){};
        if (errorCallback)
            errorCallbackFunction = std::bind(errorCallback, object, std::placeholders::_1);

        return callProcedure(procedure, arguments, QJsonObject(), callbackFunction, errorCallbackFunction);
    }

    template <typename Obj>
    bool call(const QString &procedure,
              const QJsonArray &arguments,
              Obj *object,
              void (Obj::*callback)(const QJsonArray &, const QJsonObject &),
              void (Obj::*errorCallback)(const IqWampCallError &) = Q_NULLPTR)
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_1, std::placeholders::_2);

        std::function<void (const IqWampCallError &)> errorCallbackFunction = [](const IqWampCallError &){};
        if (errorCallback)
            errorCallbackFunction = std::bind(errorCallback, object, std::placeholders::_1);

        return callProcedure(procedure, arguments, QJsonObject(), callbackFunction, errorCallbackFunction);
    }

    template <typename Obj>
    bool call(const QString &procedure,
              const QJsonArray &arguments,
              Obj *object,
              void ((Obj::*callback)(const QJsonArray &, const QJsonObject &) const),
              void (Obj::*errorCallback)(const IqWampCallError &) = Q_NULLPTR)
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_1, std::placeholders::_2);

        std::function<void (const IqWampCallError &)> errorCallbackFunction = [](const IqWampCallError &){};
        if (errorCallback)
            errorCallbackFunction = std::bind(errorCallback, object, std::placeholders::_1);

        return callProcedure(procedure, arguments, QJsonObject(), callbackFunction, errorCallbackFunction);
    }

    template <typename Obj>
    bool call(const QString &procedure,
              const QJsonObject &argumentsKw,
              Obj *object,
              void (Obj::*callback)(),
              void (Obj::*errorCallback)(const IqWampCallError &) = Q_NULLPTR)
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object);

        std::function<void (const IqWampCallError &)> errorCallbackFunction = [](const IqWampCallError &){};
        if (errorCallback)
            errorCallbackFunction = std::bind(errorCallback, object, std::placeholders::_1);

        return callProcedure(procedure, QJsonArray(), argumentsKw, callbackFunction, errorCallbackFunction);
    }

    template <typename Obj>
    bool call(const QString &procedure,
              const QJsonObject &argumentsKw,
              Obj *object,
              void ((Obj::*callback)() const),
              void (Obj::*errorCallback)(const IqWampCallError &) = Q_NULLPTR)
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object);

        std::function<void (const IqWampCallError &)> errorCallbackFunction = [](const IqWampCallError &){};
        if (errorCallback)
            errorCallbackFunction = std::bind(errorCallback, object, std::placeholders::_1);

        return callProcedure(procedure, QJsonArray(), argumentsKw, callbackFunction, errorCallbackFunction);
    }

    template <typename Obj>
    bool call(const QString &procedure,
              const QJsonObject &argumentsKw,
              Obj *object,
              void (Obj::*callback)(const QJsonArray &),
              void (Obj::*errorCallback)(const IqWampCallError &) = Q_NULLPTR)
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_1);

        std::function<void (const IqWampCallError &)> errorCallbackFunction = [](const IqWampCallError &){};
        if (errorCallback)
            errorCallbackFunction = std::bind(errorCallback, object, std::placeholders::_1);

        return callProcedure(procedure, QJsonArray(), argumentsKw, callbackFunction, errorCallbackFunction);
    }

    template <typename Obj>
    bool call(const QString &procedure,
              const QJsonObject &argumentsKw,
              Obj *object,
              void ((Obj::*callback)(const QJsonArray &) const),
              void (Obj::*errorCallback)(const IqWampCallError &) = Q_NULLPTR)
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_1);

        std::function<void (const IqWampCallError &)> errorCallbackFunction = [](const IqWampCallError &){};
        if (errorCallback)
            errorCallbackFunction = std::bind(errorCallback, object, std::placeholders::_1);

        return callProcedure(procedure, QJsonArray(), argumentsKw, callbackFunction, errorCallbackFunction);
    }

    template <typename Obj>
    bool call(const QString &procedure,
              const QJsonObject &argumentsKw,
              Obj *object,
              void (Obj::*callback)(const QJsonObject &),
              void (Obj::*errorCallback)(const IqWampCallError &) = Q_NULLPTR)
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_2);

        std::function<void (const IqWampCallError &)> errorCallbackFunction = [](const IqWampCallError &){};
        if (errorCallback)
            errorCallbackFunction = std::bind(errorCallback, object, std::placeholders::_1);

        return callProcedure(procedure, QJsonArray(), argumentsKw, callbackFunction, errorCallbackFunction);
    }

    template <typename Obj>
    bool call(const QString &procedure,
              const QJsonObject &argumentsKw,
              Obj *object,
              void ((Obj::*callback)(const QJsonObject &) const),
              void (Obj::*errorCallback)(const IqWampCallError &) = Q_NULLPTR)
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_2);

        std::function<void (const IqWampCallError &)> errorCallbackFunction = [](const IqWampCallError &){};
        if (errorCallback)
            errorCallbackFunction = std::bind(errorCallback, object, std::placeholders::_1);

        return callProcedure(procedure, QJsonArray(), argumentsKw, callbackFunction, errorCallbackFunction);
    }

    template <typename Obj>
    bool call(const QString &procedure,
              const QJsonObject &argumentsKw,
              Obj *object,
              void (Obj::*callback)(const QJsonArray &, const QJsonObject &),
              void (Obj::*errorCallback)(const IqWampCallError &) = Q_NULLPTR)
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_1, std::placeholders::_2);

        std::function<void (const IqWampCallError &)> errorCallbackFunction = [](const IqWampCallError &){};
        if (errorCallback)
            errorCallbackFunction = std::bind(errorCallback, object, std::placeholders::_1);

        return callProcedure(procedure, QJsonArray(), argumentsKw, callbackFunction, errorCallbackFunction);
    }

    template <typename Obj>
    bool call(const QString &procedure,
              const QJsonObject &argumentsKw,
              Obj *object,
              void ((Obj::*callback)(const QJsonArray &, const QJsonObject &) const),
              void (Obj::*errorCallback)(const IqWampCallError &) = Q_NULLPTR)
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_1, std::placeholders::_2);

        std::function<void (const IqWampCallError &)> errorCallbackFunction = [](const IqWampCallError &){};
        if (errorCallback)
            errorCallbackFunction = std::bind(errorCallback, object, std::placeholders::_1);

        return callProcedure(procedure, QJsonArray(), argumentsKw, callbackFunction, errorCallbackFunction);
    }

    template <typename Obj>
    bool call(const QString &procedure,
              const QJsonArray &arguments,
              const QJsonObject &argumentsKw,
              Obj *object,
              void (Obj::*callback)(),
              void (Obj::*errorCallback)(const IqWampCallError &) = Q_NULLPTR)
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object);

        std::function<void (const IqWampCallError &)> errorCallbackFunction = [](const IqWampCallError &){};
        if (errorCallback)
            errorCallbackFunction = std::bind(errorCallback, object, std::placeholders::_1);

        return callProcedure(procedure, arguments, argumentsKw, callbackFunction, errorCallbackFunction);
    }

    template <typename Obj>
    bool call(const QString &procedure,
              const QJsonArray &arguments,
              const QJsonObject &argumentsKw,
              Obj *object,
              void ((Obj::*callback)() const),
              void (Obj::*errorCallback)(const IqWampCallError &) = Q_NULLPTR)
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object);

        std::function<void (const IqWampCallError &)> errorCallbackFunction = [](const IqWampCallError &){};
        if (errorCallback)
            errorCallbackFunction = std::bind(errorCallback, object, std::placeholders::_1);

        return callProcedure(procedure, arguments, argumentsKw, callbackFunction, errorCallbackFunction);
    }

    template <typename Obj>
    bool call(const QString &procedure,
              const QJsonArray &arguments,
              const QJsonObject &argumentsKw,
              Obj *object,
              void (Obj::*callback)(const QJsonArray &),
              void (Obj::*errorCallback)(const IqWampCallError &) = Q_NULLPTR)
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_1);

        std::function<void (const IqWampCallError &)> errorCallbackFunction = [](const IqWampCallError &){};
        if (errorCallback)
            errorCallbackFunction = std::bind(errorCallback, object, std::placeholders::_1);

        return callProcedure(procedure, arguments, argumentsKw, callbackFunction, errorCallbackFunction);
    }

    template <typename Obj>
    bool call(const QString &procedure,
              const QJsonArray &arguments,
              const QJsonObject &argumentsKw,
              Obj *object,
              void ((Obj::*callback)(const QJsonArray &) const),
              void (Obj::*errorCallback)(const IqWampCallError &) = Q_NULLPTR)
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_1);

        std::function<void (const IqWampCallError &)> errorCallbackFunction = [](const IqWampCallError &){};
        if (errorCallback)
            errorCallbackFunction = std::bind(errorCallback, object, std::placeholders::_1);

        return callProcedure(procedure, arguments, argumentsKw, callbackFunction, errorCallbackFunction);
    }

    template <typename Obj>
    bool call(const QString &procedure,
              const QJsonArray &arguments,
              const QJsonObject &argumentsKw,
              Obj *object,
              void (Obj::*callback)(const QJsonObject &),
              void (Obj::*errorCallback)(const IqWampCallError &) = Q_NULLPTR)
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_2);

        std::function<void (const IqWampCallError &)> errorCallbackFunction = [](const IqWampCallError &){};
        if (errorCallback)
            errorCallbackFunction = std::bind(errorCallback, object, std::placeholders::_1);

        return callProcedure(procedure, arguments, argumentsKw, callbackFunction, errorCallbackFunction);
    }

    template <typename Obj>
    bool call(const QString &procedure,
              const QJsonArray &arguments,
              const QJsonObject &argumentsKw,
              Obj *object,
              void ((Obj::*callback)(const QJsonObject &) const),
              void (Obj::*errorCallback)(const IqWampCallError &) = Q_NULLPTR)
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_2);

        std::function<void (const IqWampCallError &)> errorCallbackFunction = [](const IqWampCallError &){};
        if (errorCallback)
            errorCallbackFunction = std::bind(errorCallback, object, std::placeholders::_1);

        return callProcedure(procedure, arguments, argumentsKw, callbackFunction, errorCallbackFunction);
    }

    template <typename Obj>
    bool call(const QString &procedure,
              const QJsonArray &arguments,
              const QJsonObject &argumentsKw,
              Obj *object,
              void (Obj::*callback)(const QJsonArray &, const QJsonObject &),
              void (Obj::*errorCallback)(const IqWampCallError &) = Q_NULLPTR)
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_1, std::placeholders::_2);

        std::function<void (const IqWampCallError &)> errorCallbackFunction = [](const IqWampCallError &){};
        if (errorCallback)
            errorCallbackFunction = std::bind(errorCallback, object, std::placeholders::_1);

        return callProcedure(procedure, arguments, argumentsKw, callbackFunction, errorCallbackFunction);
    }

    template <typename Obj>
    bool call(const QString &procedure,
              const QJsonArray &arguments,
              const QJsonObject &argumentsKw,
              Obj *object,
              void ((Obj::*callback)(const QJsonArray &, const QJsonObject &) const),
              void (Obj::*errorCallback)(const IqWampCallError &) = Q_NULLPTR)
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_1, std::placeholders::_2);

        std::function<void (const IqWampCallError &)> errorCallbackFunction = [](const IqWampCallError &){};
        if (errorCallback)
            errorCallbackFunction = std::bind(errorCallback, object, std::placeholders::_1);

        return callProcedure(procedure, arguments, argumentsKw, callbackFunction, errorCallbackFunction);
    }


    bool subscribe(const QString &topic, std::function<void (const QJsonArray &, const QJsonObject &)> callback);
    bool subscribe(const QString &topic, const QJsonObject &options, std::function<void (const QJsonArray &, const QJsonObject &)> callback);
    bool subscribe(const QString &topic, std::function<void ()> callback);
    bool subscribe(const QString &topic, const QJsonObject &options, std::function<void ()> callback);
    bool subscribe(const QString &topic, std::function<void (const QJsonArray &)> callback);
    bool subscribe(const QString &topic, const QJsonObject &options, std::function<void (const QJsonArray &)> callback);
    bool subscribe(const QString &topic, std::function<void (const QJsonObject &)> callback);
    bool subscribe(const QString &topic, const QJsonObject &options, std::function<void (const QJsonObject &)> callback);

    template <typename Obj>
    bool subscribe(const QString &topic,
                   Obj *object,
                   void (Obj::*callback)())
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object);

        return subscribeToTopic(topic, QJsonObject(), callbackFunction);
    }

    template <typename Obj>
    bool subscribe(const QString &topic,
                   Obj *object,
                   void ((Obj::*callback)() const))
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object);

        return subscribeToTopic(topic, QJsonObject(), callbackFunction);
    }

    template <typename Obj>
    bool subscribe(const QString &topic,
                   const QJsonObject &arguments,
                   Obj *object,
                   void (Obj::*callback)())
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object);

        return subscribeToTopic(topic, arguments, callbackFunction);
    }

    template <typename Obj>
    bool subscribe(const QString &topic,
                   const QJsonObject &arguments,
                   Obj *object,
                   void ((Obj::*callback)() const))
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object);

        return subscribeToTopic(topic, arguments, callbackFunction);
    }

    template <typename Obj>
    bool subscribe(const QString &topic,
                   Obj *object,
                   void (Obj::*callback)(const QJsonObject &))
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_2);

        return subscribeToTopic(topic, QJsonObject(), callbackFunction);
    }

    template <typename Obj>
    bool subscribe(const QString &topic,
                   Obj *object,
                   void ((Obj::*callback)(const QJsonObject &) const))
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_2);

        return subscribeToTopic(topic, QJsonObject(), callbackFunction);
    }

    template <typename Obj>
    bool subscribe(const QString &topic,
                   const QJsonObject &arguments,
                   Obj *object,
                   void (Obj::*callback)(const QJsonObject &))
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_2);

        return subscribeToTopic(topic, arguments, callbackFunction);
    }

    template <typename Obj>
    bool subscribe(const QString &topic,
                   const QJsonObject &arguments,
                   Obj *object,
                   void ((Obj::*callback)(const QJsonObject &) const))
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_2);

        return subscribeToTopic(topic, arguments, callbackFunction);
    }

    template <typename Obj>
    bool subscribe(const QString &topic,
                   Obj *object,
                   void (Obj::*callback)(const QJsonArray &))
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_1);

        return subscribeToTopic(topic, QJsonObject(), callbackFunction);
    }

    template <typename Obj>
    bool subscribe(const QString &topic,
                   Obj *object,
                   void ((Obj::*callback)(const QJsonArray &) const))
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_1);

        return subscribeToTopic(topic, QJsonObject(), callbackFunction);
    }

    template <typename Obj>
    bool subscribe(const QString &topic,
                   const QJsonObject &arguments,
                   Obj *object,
                   void (Obj::*callback)(const QJsonArray &))
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_1);

        return subscribeToTopic(topic, arguments, callbackFunction);
    }

    template <typename Obj>
    bool subscribe(const QString &topic,
                   const QJsonObject &arguments,
                   Obj *object,
                   void ((Obj::*callback)(const QJsonArray &) const))
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_1);

        return subscribeToTopic(topic, arguments, callbackFunction);
    }

    template <typename Obj>
    bool subscribe(const QString &topic,
                   Obj *object,
                   void (Obj::*callback)(const QJsonArray &, const QJsonObject &))
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_1, std::placeholders::_2);

        return subscribeToTopic(topic, QJsonObject(), callbackFunction);
    }

    template <typename Obj>
    bool subscribe(const QString &topic,
                   Obj *object,
                   void ((Obj::*callback)(const QJsonArray &, const QJsonObject &) const))
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_1, std::placeholders::_2);

        return subscribeToTopic(topic, QJsonObject(), callbackFunction);
    }

    template <typename Obj>
    bool subscribe(const QString &topic,
                   const QJsonObject &arguments,
                   Obj *object,
                   void (Obj::*callback)(const QJsonArray &, const QJsonObject &))
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_1, std::placeholders::_2);

        return subscribeToTopic(topic, arguments, callbackFunction);
    }

    template <typename Obj>
    bool subscribe(const QString &topic,
                   const QJsonObject &arguments,
                   Obj *object,
                   void ((Obj::*callback)(const QJsonArray &, const QJsonObject &) const))
    {
        std::function<void (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_1, std::placeholders::_2);

        return subscribeToTopic(topic, arguments, callbackFunction);
    }




    bool registerProcedure(const QString &procedure, std::function<IqWampYieldResult (const QJsonArray &, const QJsonObject &)> callback);
    bool registerProcedure(const QString &procedure, std::function<IqWampYieldResult()> callback);
    bool registerProcedure(const QString &procedure, std::function<IqWampYieldResult(const QJsonArray &)> callback);
    bool registerProcedure(const QString &procedure, std::function<IqWampYieldResult(const QJsonObject &)> callback);

    template <typename Obj>
    bool registerProcedure(const QString &procedure,
                           Obj *object,
                           IqWampYieldResult (Obj::*callback)())
    {
        std::function<IqWampYieldResult (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object);

        return registerProcedureCallback(procedure, callbackFunction);
    }

    template <typename Obj>
    bool registerProcedure(const QString &procedure,
                           Obj *object,
                           IqWampYieldResult ((Obj::*callback)() const))
    {
        std::function<IqWampYieldResult (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object);

        return registerProcedureCallback(procedure, callbackFunction);
    }

    template <typename Obj>
    bool registerProcedure(const QString &procedure,
                           Obj *object,
                           IqWampYieldResult (Obj::*callback)(const QJsonArray &))
    {
        std::function<IqWampYieldResult (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_1);

        return registerProcedureCallback(procedure, callbackFunction);
    }

    template <typename Obj>
    bool registerProcedure(const QString &procedure,
                           Obj *object,
                           IqWampYieldResult ((Obj::*callback)(const QJsonArray &) const))
    {
        std::function<IqWampYieldResult (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_1);

        return registerProcedureCallback(procedure, callbackFunction);
    }

    template <typename Obj>
    bool registerProcedure(const QString &procedure,
                           Obj *object,
                           IqWampYieldResult (Obj::*callback)(const QJsonObject &))
    {
        std::function<IqWampYieldResult (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_2);

        return registerProcedureCallback(procedure, callbackFunction);
    }
    template <typename Obj>
    bool registerProcedure(const QString &procedure,
                           Obj *object,
                           IqWampYieldResult ((Obj::*callback)(const QJsonObject &) const))
    {
        std::function<IqWampYieldResult (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_2);

        return registerProcedureCallback(procedure, callbackFunction);
    }

    template <typename Obj>
    bool registerProcedure(const QString &procedure,
                           Obj *object,
                           IqWampYieldResult (Obj::*callback)(const QJsonArray &, const QJsonObject &))
    {
        std::function<IqWampYieldResult (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_1, std::placeholders::_2);

        return registerProcedureCallback(procedure, callbackFunction);
    }
    template <typename Obj>
    bool registerProcedure(const QString &procedure,
                           Obj *object,
                           IqWampYieldResult ((Obj::*callback)(const QJsonArray &, const QJsonObject &) const))
    {
        std::function<IqWampYieldResult (const QJsonArray &, const QJsonObject &)> callbackFunction = std::bind(callback, object, std::placeholders::_1, std::placeholders::_2);

        return registerProcedureCallback(procedure, callbackFunction);
    }

protected:
    virtual bool subscribeToTopic(const QString &topic,
                                  const QJsonObject &options,
                                  std::function<void (const QJsonArray &, const QJsonObject &)> callback) = 0;

    virtual bool publishEvent(const QString &topic,
                              const QJsonArray &arguments,
                              const QJsonObject &argumentsKw) = 0;

    virtual bool registerProcedureCallback(const QString &procedure,
                                           std::function<IqWampYieldResult (const QJsonArray &, const QJsonObject &)> callback) = 0;

    virtual bool callProcedure(const QString &procedure,
                               const QJsonArray &arguments,
                               const QJsonObject &argumentsKw,
                               std::function<void (const QJsonArray &, const QJsonObject &)> callback,
                               std::function<void (const IqWampCallError &error)> errorCallback) = 0;
};

#endif //IQWAMPABSTRACTCLIENT_H
