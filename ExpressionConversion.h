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

    void InfixToSuffix(vector<string> infix, vector<string>& suffix);    //��׺ת��׺

    int GetPriority(char ch);                                           //�õ����ŵ����ȼ�

};

