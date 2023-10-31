#include "MathExpressionTree.h"
#include "ExpressionConversion.h"
#include <sstream>

MathExpressionTree::MathExpressionTree() {
    root = new TreeNode;
}

MathExpressionTree::MathExpressionTree(string expression) {
    root = new TreeNode;
    root->lchild = root->rchild = ParseExpression(expression);	//调用函数建树
}

MathExpressionTree::~MathExpressionTree() {
	ReleaseTree(root);	//调用函数释放树
}

double MathExpressionTree::GetResult() {
	return Evaluate(root->lchild);	//调用函数获取表达式最后值
}

string MathExpressionTree::ToString() {
	return ToString(root->lchild);	
}

/**
 * @brief 表达式遍历求值过程
 * @param node 传入根节点
 * @return 计算结果
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
		return stod(node->data);	//将字符串类型转为double类型
	}
}

/**
 * @brief 将二叉树转换为字符串（以广义表形式）
 * @param node //传入根节点
 * @return 转换结果
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

	ReleaseTree(node->lchild);	//递归释放左子树
	ReleaseTree(node->rchild);	//递归释放右子树
	delete node;				//释放根节点
}

/**
 * @brief 解析表达式，建立表达式树
 * @param expression 原表示
 * @return 表达式树的根节点
*/
TreeNode* MathExpressionTree::ParseExpression(string expression) {
	vector<string> inffix;					//分割后子字符串容器
	ExpressionSplit(expression, inffix);	//将原表达式转换为数字运算符分离的子字符串

	ExpressionConversion ec;				//用于将中缀表达式转为后缀表达式
	vector<string> suffix;					//后缀表达式子字符串容器
	ec.InfixToSuffix(inffix, suffix);		//转换函数

	Stack<TreeNode* > treestack;			//用于进行表达式转为树的栈
	for (auto& i_suffix : suffix) {			//遍历容器
		switch (i_suffix[0]) {				
		case '+':
		case '-':
		case '*':
		case '/': {							//判断首元素即可判断是数字还是运算符
			TreeNode* bufnode = new TreeNode(i_suffix);		//是运算符新建节点
			bufnode->rchild = treestack.Pop();
			bufnode->lchild = treestack.Pop();
			treestack.Push(bufnode);						//操作完后入栈
			break;
		}
		default: {
			if (i_suffix[0] >= '0' && i_suffix[0] <= '9') {	//若是数字
				treestack.Push(new TreeNode(i_suffix));		//直接入栈
				break;
			}
			break;
		}
		}
	}
	return treestack.Pop();
}

/**
 * @brief 将数字和运算符分割成子字符串存入vector向量中
 * @param expreesion 原表达式
 * @param result 分割后的子字符串向量
*/
void ExpressionSplit(string expreesion, vector<string>& result) {
	int i = 0;
	while (expreesion[i] != '\0') {			//循环读取表达式内容
		switch (expreesion[i]) {
		case '(':
		case ')':
		case '+':
		case '-':
		case '*':
		case '/': {							//若为运算符
			string bufstrings;				//临时字符串
			bufstrings += expreesion[i];	//赋给临时字符串
			result.push_back(bufstrings);	//放入字符串向量容器中
			i++;
			break;
		}
		default: {
			string bufstring;
			while ((expreesion[i] >= '0' && expreesion[i] <= '9')
				|| expreesion[i] == '.') {	//若为数字或小数点，循环读取到不是数字或小数点为止
				bufstring += expreesion[i];	//用临时字符串接收
				i++;
			}
			result.push_back(bufstring);	//放入容器
			break;
		}
		}
	}
}