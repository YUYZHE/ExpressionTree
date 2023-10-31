#include "Stack.h"
#include <stdexcept>
#include <sstream>		// ���ڽ���������ת��Ϊ�ַ����� stringstream ͷ�ļ�

template<typename E>
Stack<E>::Stack() {
	top = new Node<E>;
}

template<typename E>
Stack<E>::~Stack() {
	Node<E>* p = top->next;
	while (p) {
		Node<E>* q = p;
		p = p->next;
		delete q;
	}
	delete top;
}

template<typename E>
int Stack<E>::GetLen() {
	int len = 0;
	Node<E>* p = top->next;
	while (p) {
		len++;
		p = p->next;
	}
	return len;
}

template<typename E>
bool Stack<E>::IsEmpty() {
	return top->next == nullptr;
}

template<typename E>
void Stack<E>::Push(E elem) {
	Node<E>* node = new Node<E>;
	node->data = elem;
	node->next = top->next;
	top->next = node;
}

template<typename E>
E Stack<E>::Pop() {
	if (IsEmpty())
		throw std::out_of_range("Stack is empty!");	//�׳�ջ���쳣

	Node<E>* node = top->next;
	top->next = node->next;
	node->next = nullptr;
	return node->data;
}

template<typename E>
E Stack<E>::GetTop() {
	if (IsEmpty())
		throw std::out_of_range("Stack is empty!");	//�׳�ջ���쳣

	return top->next->data;
}

template<typename E>
void Stack<E>::Clear() {
	Node<E>* p = top->next;
	while (p) {
		Node<E>* q = p;
		p = p->next;
		delete q;
	}
	top->next = nullptr;
}

template<typename E>
Node<E>* Stack<E>::GetTopHand() {
	return top;
}

template<typename E>
std::string Stack<E>::ToString(Stack<E>* yuorStack) {
	std::stringstream ss;
	ss << "top -> ";
	Node<E>* p = yuorStack->GetTopHand()->next;
	while (p) {
		ss << p->data << " -> ";
		p = p->next;
	}
	ss << "/\\";
	return ss.str();
}

