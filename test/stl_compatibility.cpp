#define CATCH_CONFIG_MAIN
#if __has_include(<catch2/catch.hpp>)
#include <catch2/catch.hpp>
#else
#include <catch.hpp>
#endif

#include "dict.hpp"
using Dict = cppdict::Dict<int, double, std::string>;

TEST_CASE("can get size", "[cppdict::Dict<int, double, std::string> stl_compat]")
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

TEST_CASE("iterate over children", "[cppdict::Dict<int, double, std::string> stl_compat]")
{
    Dict dict;
    dict["first"] = 3.14;
    dict["second"] = 1;
    dict["third"]["level2"] = std::string{"hello"};
    SECTION("A dict with 3 elements has size == 3")
    {
        REQUIRE( std::accumulate(std::cbegin(dict), std::cend(dict),0UL,[](std::size_t i, const auto&){return i+1;}) == 3UL);
    }
    SECTION("Can't iterate a leaf")
    {
        REQUIRE_THROWS_WITH(std::begin(dict["first"]), "cppdict: can't iterate this node");
    }
    SECTION("Can't iterate an empty node")
    {
        REQUIRE_THROWS_WITH(std::begin(dict["this node is empty"]), "cppdict: can't iterate this node");
    }
}

TEST_CASE("Visit node's children", "[cppdict::Dict<int, double, std::string> stl_compat>]")
{
    Dict dict;
    dict["first"] = 3.14;
    dict["second"] = 1;
    dict["third"]["level2"] = std::string{"hello"};
    auto node_count=0UL;
    auto int_count=0UL;
    auto double_count=0UL;
    auto string_count=0UL;
    dict.visit(
        [&node_count](const std::string&, const auto& ){node_count++;},
        [&double_count](const std::string&, double){double_count++;},
        [&int_count](const std::string&, int){int_count++;},
        [&string_count](const std::string&, const std::string& ){string_count++;}
        );
    REQUIRE(node_count==1UL);
    REQUIRE(int_count==1UL);
    REQUIRE(double_count==1UL);
    REQUIRE(string_count==0UL);
}
