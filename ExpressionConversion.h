#pragma once
#include "Stack.h"
#include "Stack.cpp"
#include <vector>

using namespace std;

class ExpressionConversion :
    public Stack<string>
{
public:
    ExpressionConversion() :Stack() {}

    void InfixToSuffix(vector<string> infix, vector<string>& suffix);    //中缀转后缀

    int GetPriority(char ch);                                           //得到符号的优先级

};

