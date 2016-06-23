// Copyright (c) 2014 Steinwurf ApS
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#pragma once

#include <tuple>
#include <type_traits>
#include <utility>

namespace type_storage
{
    namespace detail
    {

        /// Helper struct for find_index. "Empty" non specialised struct.
        template<template<class, class> class P,
                 int i, typename U, bool cond, typename... Ts>
        struct find_type
        {
            static_assert(i != 0, "Type not found in provided typelist");
            static_assert(1 >= i , "Ambiguous types in provided typelist");
            static_assert(sizeof...(Ts) == 0, "Internal error: Ts not 0");
        };

        /// Helper struct for find_index, true specialisation.
        /// template member index<>::value finds index based on the size of
        /// remaining parameter pack Ts... when a type match has been found.
        template<template<class, class> class P,
                 int i, typename U, typename... Ts>
        struct find_type<P, i, U, true, Ts...>
            : find_type<P, i+1, U, false, Ts...>

        {
            /// specifies the index of the found type
            template<typename... Types>
            struct index
            {
                /// describes the index of requested type in Ts...
                static const size_t value = sizeof...(Types) - sizeof...(Ts) -1;
            };
        };

        /// Helper struct for find_index, false specialization.
        /// Check for type match between U and T, and inherits from correct
        /// find_type specialisation. member index<>::value obtained by
        /// recursion (recurses until U == T )
        template<template<class, class> class P,
                 int i, typename U, typename T, typename... Ts>
        struct find_type<P, i, U, false, T, Ts...>
            : find_type<P, i, U, P<U, T>::value, Ts...>
        { };

        /// Finds index of type U in template parameter pack Ts using find_type
        /// with success predicate P<U, Ts>...
        template<template<class, class> class P, class U, class... Ts>
        struct find_index
        {
            /// describes the index of U in Ts...
            static const size_t value =
                find_type<P, 0, U, false, Ts...>::template index <Ts...>::value;
        };


        /// Below helper structs are implementations of c++14 functionality with
        /// same name, can be discarded for c++14

        /// Remove constness from type T
        template<class T>
        struct remove_const
        {
            using type = T;
        };

        /// Remove constness from type T, specialized for const types
        template<class T>
        struct remove_const<const T>
        {
            using type = T;
        };

        /// Remove volatile from type T
        template<class T>
        struct remove_volatile
        {
            using type = T;
        };

        /// Remove volatile from type T, specialized for volatile types
        template<class T>
        struct remove_volatile<volatile T>
        {
            using type = T;
        };

        /// Remove constness and volatile from types
        template<class T>
        struct remove_cv
        {
            using type = typename remove_volatile<
                             typename remove_const<T>::type>::type;
        };

    }

    // is_base_of TMP comparison struct ignoring constness of types
    template<class T, class U>
    struct is_same : std::is_same<typename detail::remove_cv<T>::type,
                                  typename detail::remove_cv<U>::type>
    { };

    /// Get a object of specific type T from tuple regardless of its position.
    /// This function is basically a simple implementation of 
    /// C++14 std::get<T>(std::tuple<Types>&) function, using C++11 code.
    /// NB: If tuple contains more than one object of the reqeusted type T,
    /// the code cannot compile. Multiple objects of type different from T may
    /// exist in the tuple.
    /// If type T is not contained in tuple the code cannot compile.
    /// @param tup the tuple of objects to look in
    template<typename T, typename... Types>
    auto get(std::tuple<Types...>& tup)
        -> decltype(std::get<detail::find_index<is_same, 
                                                T, Types...>::value>(tup))
    {
        return std::get<detail::find_index<is_same, 
                                           T, Types...>::value>(tup);
    }

    // Const version of above
    template<typename T, typename... Types>
    auto get(const std::tuple<Types...>& tup)
        -> decltype(std::get<detail::find_index<is_same,
                                                T, Types...>::value>(tup))
    {
        return std::get<detail::find_index<is_same,
                                           T, Types...>::value>(tup);
    }

    // is_base_of TMP comparison struct ignoring constness of types
    template<class T, class U>
    struct is_base_of : std::is_base_of<typename detail::remove_cv<T>::type,
                                        typename detail::remove_cv<U>::type>
    { };


    /// Get an object from base type B from tuple regardless of its position.
    /// This function is virtually identical to get(), however the matching
    /// condition is on base types, not exact types.
    /// NB: If tuple contains more than one object of a matching base type,
    /// the code will not compile (static assertion). The same is valid if the
    /// tuple does not contain any types with matching base.
    /// Only the base type requested may cause a compile error, all other 
    /// types may be identical or share the same base, as long as they are 
    /// different from type B.
    /// @param tup the tuple of objects to look in
    template<typename B, typename... Types>
    auto baget(std::tuple<Types...>& tup)
        -> decltype(std::get<detail::find_index<is_base_of,
                                                B, Types...>::value>(tup))
    {
        return std::get<detail::find_index<is_base_of,
                                           B, Types...>::value>(tup);
    }

    // Const version of above
    template<typename B, typename... Types>
    auto baget(const std::tuple<Types...>& tup)
        -> decltype(std::get<detail::find_index<is_base_of,
                                                B, Types...>::value>(tup))
    {
        return std::get<detail::find_index<is_base_of,
                                           B, Types...>::value>(tup);
    }
}

