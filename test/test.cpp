
#include "../include/dict.hpp"

#include <string>
#include <iostream>

using MyDict = cppdict::Dict<int, double, std::string>;



int main()
{
 MyDict md;
 md["test"]["super"] = 2;
 std::cout<< md["test"]["super"].to<int>() << "\n";
}
