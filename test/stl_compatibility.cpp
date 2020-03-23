#define CATCH_CONFIG_MAIN
#if __has_include(<catch2/catch.hpp>)
#include <catch2/catch.hpp>
#else
#include <catch.hpp>
#endif

#include "dict.hpp"
using Dict = cppdict::Dict<int, double, std::string>;

TEST_CASE("can get size", "[simple cppdict::Dict<int, double, std::string>]")
{
    Dict dict;
    SECTION("an empty dic has size == 0")
    {
        REQUIRE( std::size(dict) == 0);
    }
    dict["first"] = 3.14;
    dict["second"] = 1;
    dict["third"]["level2"] = std::string{"hello"};
    SECTION("A dic with 3 elements has size == 3")
    {
        REQUIRE( std::size(dict) == 3);
    }
}

TEST_CASE("iterate over children", "[simple cppdict::Dict<int, double, std::string>]")
{
    Dict dict;
    dict["first"] = 3.14;
    dict["second"] = 1;
    dict["third"]["level2"] = std::string{"hello"};
    SECTION("A dict with 3 elements has size == 3")
    {
        REQUIRE( std::accumulate(std::cbegin(dict), std::cend(dict),0UL,[](std::size_t i, const auto&){return i+1;}) == 3UL);
    }
}
