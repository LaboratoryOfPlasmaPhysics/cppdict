#ifndef DICT_H
#define DICT_H

#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <variant>
#include <vector>

namespace cppdict
{
template<typename T1, typename... T2>
constexpr bool is_in()
{
    return std::disjunction_v<std::is_same<T1, T2>...>;
}


struct NoValue
{
};


template<typename... Types>
struct Dict
{
    using node_ptr = std::unique_ptr<Dict>;
    using map_t    = std::map<std::string, node_ptr>;
    using data_t   = std::variant<NoValue, map_t, Types...>;

    data_t data = NoValue{};

    Dict& operator[](const std::string& key)
    {
        if (std::holds_alternative<map_t>(data))
        {
            // std::cout << key << "\n";
            auto& map = std::get<map_t>(data);

            if (std::end(map) == map.find(key))
            {
                map[key] = std::make_unique<Dict>();
            }

            return *std::get<map_t>(data)[key];
        }
        else if (std::holds_alternative<NoValue>(data))
        {
            data      = map_t{};
            auto& map = std::get<map_t>(data);
            map[key]  = std::make_unique<Dict>();

            return *std::get<map_t>(data)[key];
        }

        else
        {
            throw std::runtime_error("invalid key");
        }
    }


    bool isFinal() const
    {
        return !std::holds_alternative<map_t>(data) && !std::holds_alternative<NoValue>(data);
    }



    template<typename T, typename U = std::enable_if_t<is_in<T, Types...>()>>
    Dict& operator=(const T& value)
    {
        data = value;
        return *this;
    }

    template<typename T>
    T& to()
    {
        if (std::holds_alternative<T>(data))
        {
            return std::get<T>(data);
        }
        else
        {
            throw std::runtime_error("invalid type");
        }
    }

    template<typename T>
    T& to(T&& defaultValue)
    {
        if (std::holds_alternative<T>(data))
        {
            return std::get<T>(data);
        }
        else if (std::holds_alternative<NoValue>(data))
        {
            return defaultValue;
        }
        else
        {
            throw std::runtime_error("not a map or not default");
        }
    }
};


} // namespace cppdict
#endif
