// Copyright (c) 2014 Steinwurf ApS
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#pragma once

#include <queue>

#include <tuple>
#include <boost/variant.hpp>

namespace type_storage
{



    /// Container for multiple unique types
    /// References to contained objects can be extracted with the
    /// get<Type>() member function.
    template<template<typename...> typename Container, typename... Types>
    class typed_queue : public std::queue<boost::variant<Types...>,
        Container<boost::variant<Types...>>
    {

        using Base = std::queue<type, Container<type>>;

    public:

        using type = boost::variant<Types...>;

        template<typename ResultType>
        using visitor_base = boost::static_visitor<ResultType>;

        template<typename Visitor>
        front(Visitor& v)
        {
            static_assert(std::is_base_of<visitor_base, Visitor>::value,
                          "Visitor must be derived from visitor_base");
            auto& base_front = Base::front();
            boost::apply_visitor(v, base_front);
        }

        template<typename Visitor>
        back(Visitor& v)
        {
            static_assert(std::is_base_of<visitor_base, Visitor>::value,
                          "Visitor must be derived from visitor_base");
            auto& base_back = Base::back();
            boost::apply_visitor(v, base_back);
        }

        // /// This should be OK, but this need to be tested :)
        // template<typename T>
        // push(T& t)
        // {

        // }

        // /// This should be OK, but this need to be tested :)
        // template<typename T>
        // emplace(T& t)
        // {

        // }



        // using type boost::variant<Types...>;

        /// Can we just do protected inhertance and then overwrite a few of the
        /// element access methods?

        /// Methods needed to be overwritten / hidden
        /// In vector


        /// constructor etc
        /// at
        /// operator[]
        /// front
        /// back
        /// data (hide completely)

        /// begin
        /// end
        /// ...

        /// insert(?)
        /// emplace(?)
        /// push_back(?)

        /// We can just do TEMPLATED INHERTANCE



    private:

        /// the native container
        // std::vector<boost::variant<Types...>> m_queue;
    };
}

