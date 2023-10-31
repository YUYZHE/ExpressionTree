#include "ExpressionConversion.h"
#include <cstring>

/**
 * @brief ����׺���ʽתΪ��׺���ʽ�����ʽΪ�Ѿ��������������������������
 * @param infix ��׺���ʽ
 * @param suffix ��׺���ʽ
*/
void ExpressionConversion::InfixToSuffix(vector<string> infix, vector<string>& suffix) {
	for (auto& i_infix : infix) {		//������׺���ʽ
		switch (i_infix[0]) {			//�ַ�����Ԫ�ؼ����ж������ֻ��������
		case '(': {						//�����'('ֱ����ջ��������ջ��
			Push("(");
			break;
		}
		case ')': {						//���Ϊ')'����ջ��֪������'('Ϊֹ����Ԫ�ط����׺���ʽ����
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
			if (IsEmpty()) {			//ջΪ����ֱ����ջ
				Push(i_infix);
				break;
			}
			string e = GetTop();
			while (GetPriority(i_infix[0]) <= GetPriority(e[0])) {	//����ѭ���ж�����ǰԪ�����ȼ�����ջ��������׺���ʽ����
				suffix.push_back(Pop());
				if (IsEmpty())
					break;
				e = GetTop();			
			}
			Push(i_infix);				//ѭ��������ζ�ŵ�ǰԪ�����ȼ��ߣ�����ջ
			break;
		}
		default: {						//����ֱ�����׺����
			if (i_infix[0] >= '0' && i_infix[0] <= '9') {
				suffix.push_back(i_infix);
				break;
			}
			break;
		}
		}
	}
	while (!IsEmpty()) {				//ɨ������׺���ʽ�󣬽�������ջ�е����в������������������׺���ʽջ
		suffix.push_back(Pop());
	}
}

/**
 * @brief �����ַ������ȼ�
 * @param ch ��Ҫ��ȡ���ȼ����ַ�
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
