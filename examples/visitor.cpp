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
