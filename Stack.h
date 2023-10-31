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

	int GetLen();		//��ȡջ�ĳ���
	bool IsEmpty();		//�ж��Ƿ�Ϊ��
	void Push(E elem);	//��ջ
	E Pop();			//��ջ
	E GetTop();			//��ȡջ��Ԫ��
	void Clear();		//���ջ

	Node<E>* GetTopHand();	//��ȡtopָ��
	
	/* תΪ�ַ��� */
	static std::string ToString(Stack<E>* yuorStack);
};
