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

#include "iqwampcalleesubscription.h"
#include "iqwampabstractcallee.h"

IqWampCalleeSubscription::IqWampCalleeSubscription(int id, const QString &topic, IqWampAbstractCallee *callee):
    IqWampSubscription(id, topic)
{
    addCallee(callee);
}

bool IqWampCalleeSubscription::hasCallee(const IqWampAbstractCallee *callee) const
{
    return m_callees.contains(const_cast<IqWampAbstractCallee *>(callee));
}

void IqWampCalleeSubscription::addCallee(IqWampAbstractCallee *callee)
{
    m_callees.insert(callee);
}

void IqWampCalleeSubscription::removeCallee(const IqWampAbstractCallee *callee)
{
    m_callees.remove(const_cast<IqWampAbstractCallee *>(callee));
}

QSet<IqWampAbstractCallee *> IqWampCalleeSubscription::callees() const
{
    return m_callees;
}


