#define CATCH_CONFIG_MAIN
#if __has_include(<catch2/catch.hpp>)
#include <catch2/catch.hpp>
#else
#include <catch.hpp>
#endif

#include "dict.hpp"
using Dict = cppdict::Dict<int, double, std::string>;

TEST_CASE("Can (depp)copy nodes with operator=", "[simple cppdict::Dict<int, double, std::string>]")
{
    Dict dict;
    dict["this"]["is"]["the"]["source"] = 3.14;
    dict["destination"]                 = dict["this"];
    REQUIRE(dict["destination"]["is"]["the"]["source"].to<double>() == 3.14);
}

TEST_CASE("Can add values and retrieve them", "[simple cppdict::Dict<int, double, std::string>]")
{
    Dict dict;
    dict["first"]  = 3.14;
    dict["second"] = 1;
    dict["third"]  = std::string{"hello"};
    SECTION("Added values should be retrievable")
    {
        REQUIRE(dict["first"].to<double>() == 3.14);
        REQUIRE(dict["second"].to<int>() == 1);
        REQUIRE(dict["third"].to<std::string>() == std::string{"hello"});
    }
    SECTION("Values are retrieved with the exact type")
    {
        REQUIRE_THROWS_WITH(dict["first"].to<int>(), "cppdict: to<T> invalid type");
        REQUIRE_THROWS_WITH(dict["second"].to<double>(), "cppdict: to<T> invalid type");
    }
    SECTION("Dictionaries are also hierarchical")
    {
        dict["level1"]["level2"]["level3"] = std::string{"some data"};
        REQUIRE(dict["level1"]["level2"]["level3"].to<std::string>() == std::string{"some data"});
    }
}

TEST_CASE("Deals with both references and values",
          "[simple cppdict::Dict<int, double, std::string>]")
{
    Dict dict;
    dict["0"]["1"]                = 3.5;
    dict["0"]["2"]["1"]           = 55.;
    dict["0"]["2"]["2"]           = 56.;
    dict["0"]["2"]["3"]["1"]["1"] = 666.;
    SECTION("Values acces by value does a copy")
    {
        auto v = dict["0"]["1"].to<double>();
        v      = 10.;
        REQUIRE(v != dict["0"]["1"].to<double>());
    }
    SECTION("Values access by ref doesn't copy")
    {
        auto& v = dict["0"]["1"].to<double>();
        v       = 10.;
        REQUIRE(v == dict["0"]["1"].to<double>());
    }
    SECTION("Nodes access by value does copy")
    {
        auto node = dict["0"];
        node["1"] = 100;
        REQUIRE(dict["0"]["1"].to<double>() == 3.5);
        node                = dict["2"];
        node["3"]["1"]["1"] = 42;
        REQUIRE(dict["0"]["2"]["3"]["1"]["1"].to<double>() == 666.);
    }
    SECTION("Nodes access by ref doesn't copy")
    {
        auto& node               = dict["0"];
        node["1"]                = 100;
        node["2"]["3"]["1"]["1"] = 42;
        REQUIRE(dict["0"]["1"].to<int>() == 100);
        REQUIRE(dict["0"]["2"]["3"]["1"]["1"].to<int>() == 42);
    }
}


TEST_CASE("Contains expects true or false", "[simple cppdict::Dict<int, double, std::string>]")
{
    Dict dict;
    dict["this"]["is"]["the"]["source"] = 3.14;

    REQUIRE(dict["this"].contains("is"));
    REQUIRE(!dict.contains("is"));
    REQUIRE(dict["this"]["is"]["the"].contains("source"));
    REQUIRE(!dict["this"]["is"]["the"]["source"].contains("nothing"));
}


TEST_CASE("Dict const accessor", "[simple cppdict::Dict<int>]")
{
    Dict dict;
    dict["first"]           = 3.14;
    dict["second"]["third"] = 3;

    auto const& dictRef = dict;

    REQUIRE(dictRef["first"].to<double>() == 3.14);
    REQUIRE_THROWS_WITH(dictRef["second"].to<double>(), "cppdict: to<T> invalid type");
    REQUIRE_THROWS_WITH(dictRef["one"]["two"].to<double>(), "cppdict: invalid key: one");
}
