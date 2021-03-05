//
// Created by Nikolay Fedotenko on 05.03.2021.
//

#pragma once

#include <cstdlib>

template <typename T, size_t N>
class Container
{
public:
    using size_type = size_t;
    using reference = T&;
    using const_reference = const T&;

    reference operator [](size_type n);
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
