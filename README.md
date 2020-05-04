[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![CPP17](https://img.shields.io/badge/Language-C++17-blue.svg)]()
![C/C++ CI](https://github.com/LaboratoryOfPlasmaPhysics/cppdict/workflows/C/C++%20CI/badge.svg?branch=master)
[![Coverage](https://codecov.io/gh/LaboratoryOfPlasmaPhysics/cppdict/coverage.svg?branch=master)](https://codecov.io/gh/LaboratoryOfPlasmaPhysics/cppdict/branch/master)

# cppdict (C++Dict)

C++Dict is a C++ single header fexible netsed dictionary where keys are std::string and values are any of user defined types plus dictionary type.
This allows you to build trees where each node has a name and leaves holds values of user defined types.

# How to use

## Basic example
```C++
#include "dict.hpp"

#include <iostream>
#include <string>
// define a dictionary type which can hold either int or double or std::string
using MyDict = cppdict::Dict<int, double, std::string>;

int main()
{
    MyDict md;
    md["test"]["super"] = 2;
    std::cout << md["test"]["super"].to<int>() << "\n";

    cppdict::add("toto/tata/titi", 2.5, md);
    std::cout << "at toto/tata/titi : " << md["toto"]["tata"]["titi"].to<double>() << "\n";
}

```

## Using visitors
Given a node you can visit all it's children and provide a specific function to handle each diferent child type.

```C++
#include "dict.hpp"
#include <iostream>
#include <string>

using MyDict = cppdict::Dict<int, double, std::string>;

int main()
{
    MyDict md;
    md["test"]["super"] = 2;
    md["PI"]            = 3.14;
    md["Key"]           = std::string{"Value"};
    md["key2"]          = 2;
    md["Empty leaf"];

    md.visit(
        [](const std::string& key, int value) {
            std::cout << "key: " << key << "\tvalue: " << value << "(int)"
                      << "\n";
        },
        [](const std::string& key, double value) {
            std::cout << "key: " << key << "\tvalue: " << value << "(double)"
                      << "\n";
        },
        [](const std::string& key, const std::string& value) {
            std::cout << "key: " << key << "\tvalue: " << value << "(std::string)"
                      << "\n";
        });

    // By default visit only exposes value type nodes, if you want to visit also other node types:
    md.visit(
        cppdict::visit_all_nodes,
        [](const std::string& key, const MyDict::node_t&) {
            std::cout << "key: " << key << " Got a node"
                      << "\n";
        },
        [](const std::string& key, const MyDict::empty_leaf_t&) {
            std::cout << "key: " << key << " Got an empty leaf"
                      << "\n";
        },
        [](const std::string& key, int value) {
            std::cout << "key: " << key << "\tvalue: " << value << "(int)"
                      << "\n";
        },
        [](const std::string& key, double value) {
            std::cout << "key: " << key << "\tvalue: " << value << "(double)"
                      << "\n";
        },
        [](const std::string& key, const std::string& value) {
            std::cout << "key: " << key << "\tvalue: " << value << "(std::string)"
                      << "\n";
        });

    // You can also use auto to either skip or group handling of some types:
    md.visit(
        cppdict::visit_all_nodes,
        [](const std::string& key, const MyDict::node_t&) {
            std::cout << "key: " << key << " Got a node"
                      << "\n";
        },
        [](const std::string& key, const MyDict::empty_leaf_t&) {
            std::cout << "key: " << key << " Got an empty leaf"
                      << "\n";
        },
        [](const std::string& key, const auto& value) {
            std::cout << "key: " << key << "\tvalue: " << value << "(int|double|string)"
                      << "\n";
        });
}
```
