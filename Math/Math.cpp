// Math.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "StringValue.h"

// (a/(b+c)) + (b/(a+c) + (c/(a+b)) = 4

int main()
{
    //std::cout << "hello world\n";

    StringValue v1("5512391209382139021032112190293109839128302130219039210380123929319381238219312031298301130232132105");
    StringValue v2("55123912093821390210321121902931098391283021302190392103801239293130232132105");
    std::cout << "v1 : " << v1 << "\n";
    std::cout << "v2 : " << v2 << "\n";
    auto v3 = v1 + v2 + v1;
    std::cout << "v3 : " << v3 << "\n";
    auto v4 = v1 * v2;
    std::cout << "v4 : " << v4 << "\n";

    StringValue v5("111");
    StringValue v6("55");
    auto v7 = v5 - v6;
    v7 -= v6;
    std::cout << v7 << "\n";

    std::cin.get();
    return 0;
}

