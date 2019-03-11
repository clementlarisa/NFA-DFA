#include <iostream>

#include "AUTOMAT.h"

using namespace std;

int main()
{
    AUTOMAT newautomata;

    newautomata.BuildNFA();
    newautomata.PrintNFA();
    newautomata.BuildDFA();
    newautomata.PrintDFA();

    return 0;
}
