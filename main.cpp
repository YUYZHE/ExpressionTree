#include "MathExpressionTree.h"
#include <iostream>

using namespace std;

//���Ժ���
void MathExpressionTreeTest() {
	string str[5];						//����������ʽ
	str[0] = "1+2*(3.3+4)/20";
	str[1] = "1+2*(5-3)/2";
	str[2] = "12/3+2.5/4-1";
	str[3] = "4.8*2+0.5-3";
	str[4] = "1+2-3*4/5+(6-7)*(8/9)";
	cout << "�����±��ʽ��" << endl;
	for (int i = 0; i < 5; i++) {
		cout << str[i] << endl;
	}
	cout << endl;

	MathExpressionTree met0(str[0]);	//���ʽת����������
	MathExpressionTree met1(str[1]);
	MathExpressionTree met2(str[2]);
	MathExpressionTree met3(str[3]);
	MathExpressionTree met4(str[4]);
	cout << "����Ϊ��������" << endl;	//ת�����
	cout << str[0] << "\t\t==> " << met0.ToString() << endl;
	cout << str[1] << "\t\t==> " << met1.ToString() << endl;
	cout << str[2] << "\t\t==> " << met2.ToString() << endl;
	cout << str[3] << "\t\t==> " << met3.ToString() << endl;
	cout << str[4] << "\t==> " << met4.ToString() << endl;
	cout << endl;

	cout << "��������" << endl;			//���ֵ
	cout << str[0] << "\t\t= " << met0.GetResult() << endl;
	cout << str[1] << "\t\t= " << met1.GetResult() << endl;
	cout << str[2] << "\t\t= " << met2.GetResult() << endl;
	cout << str[3] << "\t\t= " << met3.GetResult() << endl;
	cout << str[4] << "\t= " << met4.GetResult() << endl;
	
}

int main() {
	MathExpressionTreeTest();
	return 0;
}