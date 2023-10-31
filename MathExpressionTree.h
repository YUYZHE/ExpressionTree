#pragma once

#include <string>
#include <vector>

using namespace std;

struct TreeNode {				//�����
	string data;				//�ַ������ͣ��Ա���ж�λ�͸�����������
	TreeNode* lchild, * rchild;	//���ҽ��

	TreeNode() {
		data = "NULL";
		lchild = rchild = nullptr;
	}
	TreeNode(string data) {
		this->data = data;
		lchild = rchild = nullptr;
	}
};

class MathExpressionTree {
	TreeNode* root;									//�����
public:
	MathExpressionTree();							//�޲ι���
	MathExpressionTree(string expression);			//���ι��죬�������ʽ��
	~MathExpressionTree();							//����

	double GetResult();								//��ȡ���

	string ToString();								


private:
	TreeNode* ParseExpression(string expression);	//�������ʽ����
	double Evaluate(TreeNode* node);				//����������ʽ��ֵ
	string ToString(TreeNode* node);				//תΪ�ַ���

	void ReleaseTree(TreeNode* node);				//�ͷŽ��ռ�
};

/* �ַ����ָ� */
void ExpressionSplit(string expreesion, vector<string>& result);