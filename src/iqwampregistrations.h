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

#ifndef IQWAMPREGISTRATIONS_H
#define IQWAMPREGISTRATIONS_H

#include "iqwampregistrationsbase.h"

template <typename T>
class IqWampRegistrations : public IqWampRegistrationsBase
{
public:
    explicit IqWampRegistrations(QObject *parent = 0) :
        IqWampRegistrationsBase(parent)
    {
    }

    QSharedPointer<T> registration(const QString &procedure) const
    {
        return qSharedPointerCast<T>(IqWampRegistrationsBase::registration(procedure));
    }

    QSharedPointer<T> registration(int id) const
    {
        return qSharedPointerCast<T>(IqWampRegistrationsBase::registration(id));
    }

    QSharedPointer<T> take(int id)
    {
        return qSharedPointerCast<T>(IqWampRegistrationsBase::take(id));
    }
};

#endif //IQMETEOSERVER_IQWAMPREGISTRATIONS_H
