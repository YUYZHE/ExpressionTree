#include "ExpressionConversion.h"
#include <cstring>

/**
 * @brief 将中缀表达式转为后缀表达式（表达式为已经进行数字运算符分离后的容器）
 * @param infix 中缀表达式
 * @param suffix 后缀表达式
*/
void ExpressionConversion::InfixToSuffix(vector<string> infix, vector<string>& suffix) {
	for (auto& i_infix : infix) {		//遍历中缀表达式
		switch (i_infix[0]) {			//字符串首元素即可判断是数字还是运算符
		case '(': {						//如果是'('直接入栈（操作符栈）
			Push("(");
			break;
		}
		case ')': {						//如果为')'，弹栈，知道遇到'('为止，将元素放入后缀表达式容器
			string e = Pop();
			while (e[0] != '(') {
				suffix.push_back(e);
				e = Pop();
			}
			break;
		}
		case '+':
		case '-':
		case '*':
		case '/': {
			if (IsEmpty()) {			//栈为空则直接入栈
				Push(i_infix);
				break;
			}
			string e = GetTop();
			while (GetPriority(i_infix[0]) <= GetPriority(e[0])) {	//否则循环判断若当前元素优先级低则弹栈将其放入后缀表达式容器
				suffix.push_back(Pop());
				if (IsEmpty())
					break;
				e = GetTop();			
			}
			Push(i_infix);				//循环结束意味着当前元素优先级高，则入栈
			break;
		}
		default: {						//数字直接入后缀数组
			if (i_infix[0] >= '0' && i_infix[0] <= '9') {
				suffix.push_back(i_infix);
				break;
			}
			break;
		}
		}
	}
	while (!IsEmpty()) {				//扫描完中缀表达式后，将操作符栈中的所有操作符弹出并输出到后缀表达式栈
		suffix.push_back(Pop());
	}
}

/**
 * @brief 返回字符的优先级
 * @param ch 需要获取优先级的字符
 * @return 
*/
int ExpressionConversion::GetPriority(char ch) {
	switch (ch) {
	case '(':
		return 0;
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
		return 2;
	default:
		return -1;
	}
}
