#pragma once
#include <string>

template <typename E>
struct Node {
	E data;
	Node<E>* next;

	Node() : data() {
		next = nullptr;
	}
};

template <typename E>
class Stack {
	Node<E>* top;
public:
	Stack();
	~Stack();

	int GetLen();		//获取栈的长度
	bool IsEmpty();		//判断是否为空
	void Push(E elem);	//入栈
	E Pop();			//出栈
	E GetTop();			//获取栈顶元素
	void Clear();		//清空栈

	Node<E>* GetTopHand();	//获取top指针
	
	/* 转为字符串 */
	static std::string ToString(Stack<E>* yuorStack);
};
