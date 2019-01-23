
#include "dict.hpp"

#include <iostream>
#include <string>

using MyDict = cppdict::Dict<int, double, std::string>;



int main()
{
    MyDict md;
    md["test"]["super"] = 2;
    std::cout << md["test"]["super"].to<int>() << "\n";

    cppdict::add("toto/tata/titi", 2.5, md);
    std::cout << "at toto/tata/titi : " << md["toto"]["tata"]["titi"].to<double>() << "\n";
}
