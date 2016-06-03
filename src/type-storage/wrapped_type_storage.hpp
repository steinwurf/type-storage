// Copyright (c) 2014 Steinwurf ApS
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#pragma once

#include <tuple>

#include "type_storage.hpp"

namespace type_storage
{

    /// Container for multiple unique types
    /// All types are packed in template class Wrapper, so it is possible to
    /// have e.g. vectors of types MessageTypes, or even vectors of vectors
    /// of MessagesTypes.
    /// Wrapper<Type>-references can be extracted with the
    /// get<Type>() member function.
    template<template <typename> class Wrapper, typename... MessageTypes>
    class wrapped_type_storage
    {
    public:

        /// Finds the variable type Wrapper<T> in private member m_tuple.
        /// Does not compile if T is not in m_tuple.
        /// @return a reference to the requested variable, Wrapper<T>&
        template<typename T>
        Wrapper<T>& get()
        {
            return std::get <
                   detail::find_index<T, MessageTypes...>::value > (m_tuple);
        }

        // const version
        template<typename T>
        const Wrapper<T>& get() const
        {
            return std::get <
                   detail::find_index<T, MessageTypes...>::value > (m_tuple);
        }


    private:

        /// the native container
        std::tuple<Wrapper<MessageTypes>...> m_tuple;
    };
}
