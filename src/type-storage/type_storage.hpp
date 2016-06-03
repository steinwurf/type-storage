// Copyright (c) 2014 Steinwurf ApS
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#pragma once

#include <tuple>

namespace type_storage
{
    namespace detail
    {
        /// Helper struct for find_index. "Empty" non specialised struct.
        template<bool cond, typename... Ts>
        struct find_type
        {
            static_assert(cond, "Type not found in provided typelist");
        };

        /// Helper struct for find_index, true specialisation.
        /// template member index<>::value finds index based on the size of
        /// remaining paramter pack Ts... when a type match has been found.
        template<typename... Ts>
        struct find_type<true, Ts...>
        {
            /// specifies the index of the found type
            template<typename... Types>
            struct index
            {
                /// describes the index of requested type in Ts...
                static const size_t value = sizeof...(Types) - sizeof...(Ts);
            };
        };

        /// Helper struct for find_index, false specialization.
        /// Check for type match between U and T, and inherits from correct
        /// find_type specialisation. member index<>::value obtained by
        /// recursion (recurses until U == T )
        template<typename U, typename T, typename... Ts>
        struct find_type<false, U, T, Ts...>
            : find_type<std::is_same<U, T>::value, U, Ts...>
        {};


        /// Finds index of type U in template parameter pack Ts using find_type
        template<typename U, typename... Ts>
        struct find_index
        {
            /// describes the index of U in Ts...
            static const size_t value =
                find_type<false, U, Ts...>::template index <Ts...>::value;
        };
    }

    /// Get a object of specific type T from tuple regardless of its position.
    /// This function is basically a simple implementation of 
    /// C++14 std::get<T>(std::tuple<Types>&) function, using C++11 code.
    /// NB: If tuple contains more than one object of the specific type,
    /// a reference to the first found object with type T is returned.
    /// If type T is not contained in tuple the code cannot compile.
    /// @param tup the tuple of objects to look in
    template<typename T, typename... Types>
    T& get(std::tuple<Types...>& tup)
    {
        return std::get<detail::find_index<T, Types...>::value>(tup);
    }

    // Const version of above
    template<typename T, typename... Types>
    const T& get(const std::tuple<Types...>& tup)
    {
        return std::get<detail::find_index<T, Types...>::value>(tup);
    }
}

