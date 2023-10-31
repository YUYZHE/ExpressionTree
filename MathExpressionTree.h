#pragma once

#include <string>
#include <vector>

using namespace std;

struct TreeNode {				//树结点
	string data;				//字符串类型，以便进行多位和浮点数的运算
	TreeNode* lchild, * rchild;	//左右结点

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
	TreeNode* root;									//根结点
public:
	MathExpressionTree();							//无参构造
	MathExpressionTree(string expression);			//带参构造，建立表达式树
	~MathExpressionTree();							//析构

	double GetResult();								//获取结果

	string ToString();								


private:
	TreeNode* ParseExpression(string expression);	//解析表达式建树
	double Evaluate(TreeNode* node);				//遍历计算表达式的值
	string ToString(TreeNode* node);				//转为字符串

	void ReleaseTree(TreeNode* node);				//释放结点空间
};

/* 字符串分割 */
void ExpressionSplit(string expreesion, vector<string>& result);