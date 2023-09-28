#ifndef ANALYSE_1_H
#define ANALYSE_1_H

#include "analyse_1_global.h"
#include<string>
#include <cstring>


class ANALYSE_1_EXPORT Analyse_1
{
public:
    Analyse_1();
    void GetToken();
    bool strComparation(char op[3], std::string s);
    std::string analyse(std::string str);
};

#endif // ANALYSE_1_H
