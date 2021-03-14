//
// Created by Nikolay Fedotenko on 05.03.2021.
//

#pragma once

/*! \file
 *  This header defines template container for graphs data storage
 */

#include <cstdlib>

/*! \class
 *  Template STL-like container in the form of array to store graphs data
 *  \tparam T elements type
 *  \tparam N size
 *
 *  \note This class may be considered as std::vector with less functionality
 */
template <typename T, size_t N>
class Container
{
public:
    using size_type       = size_t;
    using reference       = T&;
    using const_reference = const T&;

    /*!
     *  \overload
     */
    reference       operator [](size_type n);
    const_reference operator [](size_type n) const;

private:
    T m_data[N];
};

template <typename T, size_t N>
typename Container<T, N>::reference Container<T, N>::operator [](size_type n)
{
    return m_data[n];
}

template <typename T, size_t N>
typename Container<T, N>::const_reference Container<T, N>::operator [](size_type n) const
{
    return m_data[n];
}
