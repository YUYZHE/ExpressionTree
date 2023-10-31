#include "MathExpressionTree.h"
#include "ExpressionConversion.h"
#include <sstream>

MathExpressionTree::MathExpressionTree() {
    root = new TreeNode;
}

MathExpressionTree::MathExpressionTree(string expression) {
    root = new TreeNode;
    root->lchild = root->rchild = ParseExpression(expression);	//���ú�������
}

MathExpressionTree::~MathExpressionTree() {
	ReleaseTree(root);	//���ú����ͷ���
}

double MathExpressionTree::GetResult() {
	return Evaluate(root->lchild);	//���ú�����ȡ���ʽ���ֵ
}

string MathExpressionTree::ToString() {
	return ToString(root->lchild);	
}

/**
 * @brief ���ʽ������ֵ����
 * @param node ������ڵ�
 * @return ������
*/
double MathExpressionTree::Evaluate(TreeNode* node) {
	if (node == nullptr)
		return 0.0;
	switch (node->data[0]) {
	case '+':
		return Evaluate(node->lchild) + Evaluate(node->rchild);
	case '-':
		return Evaluate(node->lchild) - Evaluate(node->rchild);
	case '*':
		return Evaluate(node->lchild) * Evaluate(node->rchild);
	case '/':
		return Evaluate(node->lchild) / Evaluate(node->rchild);
	default:
		return stod(node->data);	//���ַ�������תΪdouble����
	}
}

/**
 * @brief ��������ת��Ϊ�ַ������Թ������ʽ��
 * @param node //������ڵ�
 * @return ת�����
*/
string MathExpressionTree::ToString(TreeNode* node) {
	if (node == nullptr) {
		return "";
	}

	std::ostringstream oss;
	oss << node->data;
	if (node->lchild != nullptr || node->rchild != nullptr) {
		oss << "(";
		oss << ToString(node->lchild);
		oss << ",";
		if (node->rchild != nullptr)
			oss << ToString(node->rchild);
		oss << ")";
	}
	return oss.str();
}

void MathExpressionTree::ReleaseTree(TreeNode* node) {
	if (node == nullptr) return;

	ReleaseTree(node->lchild);	//�ݹ��ͷ�������
	ReleaseTree(node->rchild);	//�ݹ��ͷ�������
	delete node;				//�ͷŸ��ڵ�
}

/**
 * @brief �������ʽ���������ʽ��
 * @param expression ԭ��ʾ
 * @return ���ʽ���ĸ��ڵ�
*/
TreeNode* MathExpressionTree::ParseExpression(string expression) {
	vector<string> inffix;					//�ָ�����ַ�������
	ExpressionSplit(expression, inffix);	//��ԭ���ʽת��Ϊ�����������������ַ���

	ExpressionConversion ec;				//���ڽ���׺���ʽתΪ��׺���ʽ
	vector<string> suffix;					//��׺���ʽ���ַ�������
	ec.InfixToSuffix(inffix, suffix);		//ת������

	Stack<TreeNode* > treestack;			//���ڽ��б��ʽתΪ����ջ
	for (auto& i_suffix : suffix) {			//��������
		switch (i_suffix[0]) {				
		case '+':
		case '-':
		case '*':
		case '/': {							//�ж���Ԫ�ؼ����ж������ֻ��������
			TreeNode* bufnode = new TreeNode(i_suffix);		//��������½��ڵ�
			bufnode->rchild = treestack.Pop();
			bufnode->lchild = treestack.Pop();
			treestack.Push(bufnode);						//���������ջ
			break;
		}
		default: {
			if (i_suffix[0] >= '0' && i_suffix[0] <= '9') {	//��������
				treestack.Push(new TreeNode(i_suffix));		//ֱ����ջ
				break;
			}
			break;
		}
		}
	}
	return treestack.Pop();
}

/**
 * @brief �����ֺ�������ָ�����ַ�������vector������
 * @param expreesion ԭ���ʽ
 * @param result �ָ������ַ�������
*/
void ExpressionSplit(string expreesion, vector<string>& result) {
	int i = 0;
	while (expreesion[i] != '\0') {			//ѭ����ȡ���ʽ����
		switch (expreesion[i]) {
		case '(':
		case ')':
		case '+':
		case '-':
		case '*':
		case '/': {							//��Ϊ�����
			string bufstrings;				//��ʱ�ַ���
			bufstrings += expreesion[i];	//������ʱ�ַ���
			result.push_back(bufstrings);	//�����ַ�������������
			i++;
			break;
		}
		default: {
			string bufstring;
			while ((expreesion[i] >= '0' && expreesion[i] <= '9')
				|| expreesion[i] == '.') {	//��Ϊ���ֻ�С���㣬ѭ����ȡ���������ֻ�С����Ϊֹ
				bufstring += expreesion[i];	//����ʱ�ַ�������
				i++;
			}
			result.push_back(bufstring);	//��������
			break;
		}
		}
	}
}