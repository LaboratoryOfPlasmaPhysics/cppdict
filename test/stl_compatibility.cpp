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
    SECTION("an empty dic has size == 0") { REQUIRE(std::size(dict) == 0); }
    dict["first"]           = 3.14;
    dict["second"]          = 1;
    dict["third"]["level2"] = std::string{"hello"};
    SECTION("A dic with 3 elements has size == 3") { REQUIRE(std::size(dict) == 3); }
}

TEST_CASE("iterate over children", "[cppdict::Dict<int, double, std::string> stl_compat]")
{
    Dict dict;
    dict["first"]           = 3.14;
    dict["second"]          = 1;
    dict["third"]["level2"] = std::string{"hello"};
    SECTION("A dict with 3 elements has size == 3")
    {
        REQUIRE(std::accumulate(std::cbegin(dict), std::cend(dict), 0UL,
                                [](std::size_t i, const auto&) { return i + 1; })
                == 3UL);
    }
    SECTION("Can't iterate a leaf")
    {
        REQUIRE_THROWS_WITH(std::begin(dict["first"]), "cppdict: can't iterate this node");
    }
    SECTION("Can't iterate an empty node")
    {
        REQUIRE_THROWS_WITH(std::begin(dict["this node is empty"]),
                            "cppdict: can't iterate this node");
    }
}

TEST_CASE("Visit node's children", "[cppdict::Dict<int, double, std::string> stl_compat>]")
{
    Dict dict;
    dict["first"]           = 3.14;
    dict["second"]          = 1;
    dict["third"]["level2"] = std::string{"hello"};
    dict["fourth"]          = std::string{"world"};
    dict["empty"];
    SECTION("Can visit in read only mode")
    {
        auto node_count   = 0UL;
         auto empty_count   = 0UL;
        auto int_count    = 0UL;
        auto double_count = 0UL;
        auto string_count = 0UL;
        dict.visit(
            cppdict::visit_all_nodes,
            [&node_count](const std::string&, const auto&) { node_count++; },
            [&empty_count](const std::string&, const Dict::empty_leaf_t&) { empty_count++; },
            [&double_count](const std::string&, double) { double_count++; },
            [&int_count](const std::string&, int) { int_count++; },
            [&string_count](const std::string&, const std::string&) { string_count++; });
        REQUIRE(node_count == 1UL);
        REQUIRE(empty_count == 1UL);
        REQUIRE(int_count == 1UL);
        REQUIRE(double_count == 1UL);
        REQUIRE(string_count == 1UL);
    }
    SECTION("Can visit values only, IE filter out nodes")
    {
        auto node_count   = 0UL;
        auto int_count    = 0UL;
        auto double_count = 0UL;
        auto string_count = 0UL;
        dict.visit(
            cppdict::visit_values_only,
            [&node_count](const std::string&, const auto&) { node_count++; },
            [&double_count](const std::string&, double) { double_count++; },
            [&int_count](const std::string&, int) { int_count++; },
            [&string_count](const std::string&, const std::string&) { string_count++; });
        REQUIRE(node_count == 0UL);
        REQUIRE(int_count == 1UL);
        REQUIRE(double_count == 1UL);
        REQUIRE(string_count == 1UL);
    }
    SECTION("Can visit values only(default visit), IE filter out nodes")
    {
        auto node_count   = 0UL;
        auto int_count    = 0UL;
        auto double_count = 0UL;
        auto string_count = 0UL;
        dict.visit([&node_count](const std::string&, const auto&) { node_count++; },
                   [&double_count](const std::string&, double) { double_count++; },
                   [&int_count](const std::string&, int) { int_count++; },
                   [&string_count](const std::string&, const std::string&) { string_count++; });
        REQUIRE(node_count == 0UL);
        REQUIRE(int_count == 1UL);
        REQUIRE(double_count == 1UL);
        REQUIRE(string_count == 1UL);
    }
    SECTION("Visitor can modify values")
    {
        dict.visit(
            cppdict::visit_all_nodes, [](const std::string&, const auto&) {},
            [](const std::string&, double) {}, [](const std::string&, int& value) { value = 42; },
            [](const std::string&, const std::string&) {});
        REQUIRE(dict["second"].to<int>() == 42);
    }
    SECTION("Visiting leaves is forbiden")
    {
        REQUIRE_THROWS_WITH(dict["first"].visit([](const std::string&, const auto&) {}),
                            "cppdict: can only visit node");
    }
}

TEST_CASE("Visit leaves", "[cppdict::Dict<int, double, std::string> stl_compat>]")
{
    Dict dict;
    dict["first"]                       = 3.14;
    dict["second"]                      = 1;
    dict["third"]["level2"]             = std::string{"hello"};
    dict["third"]["level2_2"]           = .2;
    dict["third"]["level2_3"]           = 55;
    dict["third"]["level2_4"]["level3"] = 33;
    SECTION("Can visit in read only mode")
    {
        auto node_count   = 0UL;
        auto int_count    = 0UL;
        auto double_count = 0UL;
        auto string_count = 0UL;
        dict.visit_leaves(
            [&node_count](const std::string&, const auto&) { node_count++; },
            [&double_count](const std::string&, double) { double_count++; },
            [&int_count](const std::string&, int) { int_count++; },
            [&string_count](const std::string&, const std::string&) { string_count++; });
        REQUIRE(node_count == 0UL);
        REQUIRE(int_count == 3UL);
        REQUIRE(double_count == 2UL);
        REQUIRE(string_count == 1UL);
    }
}
