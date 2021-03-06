/**********************************************************************************
 **
 ** Copyright © 2016 Pavel A. Puchkov 
 **
 ** This file is part of IqMeteoGui. 
 **
 ** IqMeteoGui is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU Lesser General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** IqMeteoGui is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU Lesser General Public License for more details.
 **
 ** You should have received a copy of the GNU Lesser General Public License
 ** along with IqMeteoGui.  If not, see <http://www.gnu.org/licenses/>.
 **
 **********************************************************************************/

#include "iqwampsubscription.h"

IqWampSubscription::IqWampSubscription(int id, const QString &topic) :
<<<<<<< HEAD
    m_topic(topic),
    m_id(id)
=======
    m_id(id),
    m_topic(topic)
>>>>>>> 47d4c027f824f401bb90eb267e7b023187f9e899
{
}

QString IqWampSubscription::topic() const
{
    return m_topic;
}

int IqWampSubscription::id() const
{
    return m_id;
}
