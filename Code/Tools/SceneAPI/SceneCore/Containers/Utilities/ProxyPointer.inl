/*
 * Copyright (c) Contributors to the Open 3D Engine Project
 * 
 * SPDX-License-Identifier: Apache-2.0 OR MIT
 *
 */

namespace AZ
{
    namespace SceneAPI
    {
        namespace Containers
        {
            template<typename Type>
            ProxyPointer<Type>::ProxyPointer(const Type& value)
                : m_value(value)
            {
            }

            template<typename Type>
            Type& ProxyPointer<Type>::operator*()
            {
                return m_value;
            }

            template<typename Type>
            Type* ProxyPointer<Type>::operator->()
            {
                return &m_value;
            }

            template<typename Type>
            ProxyPointer<Type&>::ProxyPointer(Type& value)
                : m_value(value)
            {
            }

            template<typename Type>
            Type& ProxyPointer<Type&>::operator*()
            {
                return m_value;
            }

            template<typename Type>
            Type* ProxyPointer<Type&>::operator->()
            {
                return &m_value;
            }
        } // Containers
    } // SceneAPI
} // AZ
