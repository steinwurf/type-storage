// Copyright (c) 2014 Steinwurf ApS
// All Rights Reserved
//
// Distributed under the "BSD License". See the accompanying LICENSE.rst file.

#pragma once

#include <vector>

#include <boost/variant.hpp>

namespace type_storage
{



    /// Container for multiple unique types
    /// References to contained objects can be extracted with the
    /// get<Type>() member function.
    template<typename... Types>
    class type_queue : protected std::vector<boost::variant<Types...>>
    {

        using type = boost::variant<Types...>;

        using Base = std::vector<type>;

    public:

        using Base::Base;
        using Base::operator=;
        using Base::empty;
        using Base::size;
        using Base::max_size;
        using Base::reserve;
        using Base::capacity;
        using Base::shrink_to_fit;
        using Base::clear;
        using Base::insert;
        using Base::emplace;
        using Base::erase;
        using Base::push_back;
        using Base::emplace_back;
        using Base::pop_back;
        using Base::resize;
        using Base::swap;

        template<typename ResultType>
        using visitor_base = boost::static_visitor<ResultType>;

        /// Access front element in the queue
        /// @param v The visitor accessing the element. The visitor must have
        /// ResultType operator(Type&) implemented for all types in Types...
        /// variadic template parameter. ResultType may not be void.
        template<typename Visitor>
        void front(Visitor& v)
        {
            // static_assert(std::is_base_of<visitor_base, Visitor>::value,
            //               "Visitor must be derived from visitor_base");
            auto& base_front = Base::front();
            boost::apply_visitor(v, base_front);
        }

        template<typename Visitor>
        void back(Visitor& v)
        {
            // static_assert(std::is_base_of<visitor_base, Visitor>::value,
            //               "Visitor must be derived from visitor_base");
            auto& base_back = Base::back();
            boost::apply_visitor(v, base_back);
        }

        template<typename Visitor>
        void at(uint32_t pos, Visitor& v)
        {
            auto& element = Base::at(pos);
            boost::apply_visitor(v, element);
        }
    };
}

