#include <iostream>
#include <stdlib.h>

template<typename T>
class Stack {
private:
	T* stack;
	int top;         
	int StackSize; //���� ������ ũ��
	int StackCapacity; // ���� ������ �ִ� ũ��
public:
	Stack(){
		stack = new T[10]; 
		top = -1; 
		StackSize = 0;
		StackCapacity = 10;
}

	~Stack() {
		delete[] stack;
	}

	bool isEmpty() { //stack�� ������� üũ
		if (top == -1) return true;
		else return false;
	}

	bool isFull() { //stack�� ���� á���� üũ
		if (top == StackCapacity - 1) return true;
		else return false;
	}

	int capacity() {
		return StackCapacity;
	}

	int size() {
		return StackSize;
	}

	void printStack() {
		std::cout << "STACK SIZE [" << StackCapacity << "]" << std::endl;
		std::cout << "STACK [ ";
		for (int i = 0; i <= top; i++) {
			std::cout << stack[i] << " ";
		}
		std::cout << "]" << std::endl;
	}

	void sort() {
		// Bubble sort
		for (int i = 0; i < top; i++) {
			for (int j = 0; j < top - i; j++) {
				if (stack[j] > stack[j + 1]) {
					T temp = stack[j];
					stack[j] = stack[j + 1];
					stack[j + 1] = temp;
				}
			}
		}
	}

	void push(T& value) {
		if (isFull()) {
			std::cout << "���� ������ ����" << std::endl;
			// ������ ���� �� ������ ũ�⸦ �÷��ش�.
			int NewCapacity = StackCapacity + 10;
			T* NewStack = new T[NewCapacity];

			// ���� ������ ���ο� �������� ����.
			for (int i = 0; i <= top; ++i) {
				NewStack[i] = stack[i];
			}

			// ���ο� �������� ��ü.
			delete[] stack;
			stack = NewStack;
			StackCapacity = NewCapacity;
		}

		stack[++top] = value;
		StackSize++;
	}

	void pushAt(int location, T& value) {
		if (location < 0 || location > top + 1) {
			std::cerr << "�ùٸ��� ���� ��ġ�Դϴ�!" << std::endl;
			return;
		}

		// ������ ���� �� ������ ũ�⸦ �ø���.
		if (isFull()) {
			std::cout << "���� ������ ����" << std::endl;
			int NewCapacity = StackCapacity + 10;
			T* NewStack = new T[NewCapacity];

			// ���� ������ ���ο� �������� ����.
			for (int i = 0; i <= top; ++i) {
				NewStack[i] = stack[i];
			}

			// ���ο� �������� ��ü�Ѵ�.
			delete[] stack;
			stack = NewStack;
			StackCapacity = NewCapacity;
		}

		// ��Ҹ� �߰��� ��ġ ������ ��ҵ��� �� ĭ�� �ڷ� �̵�.
		for (int i = top; i >= location; --i) {
			stack[i + 1] = stack[i];
		}
		stack[location] = value;
		top++;
		StackSize++;
	}

	T pop() {
		if (isEmpty()) {
			std::cerr << "������ ����ֽ��ϴ�!" << std::endl;
			return T();
		}

		T value = stack[top--];
		StackSize--;
		if (size() % StackCapacity == 0)
		{
			std::cout << "���� ������ ����" << std::endl;
			// ���� ������ ����
			int NewCapacity = StackCapacity - 10;
			T* NewStack = new T[NewCapacity];
			// ���� ������ ���ο� �������� ����.
			for (int i = 0; i <= top; ++i) {
				NewStack[i] = stack[i];
			}
			delete[] stack;
			stack = NewStack;
			StackCapacity = NewCapacity;
		}
		return value;
	}

	T popAt(int location) {
		if (isEmpty() || location < 0 || location > top) {
			std::cerr << "pop�� �Ұ����մϴ�!" << std::endl;
			return T();
		}

		T value = stack[location];
		for (int i = location; i < top; i++) {
			stack[i] = stack[i + 1];
		}
		top--;
		StackSize--;
		if (size() % StackCapacity == 0)
		{
			std::cout << "���� ������ ����" << std::endl;
			// ���� ������ ����
			int NewCapacity = StackCapacity - 10;
			T* NewStack = new T[NewCapacity];
			// ���� ������ ���ο� �������� ����.
			for (int i = 0; i <= top; ++i) {
				NewStack[i] = stack[i];
			}
			delete[] stack;
			stack = NewStack;
			StackCapacity = NewCapacity;
		}
		return value;
	}



	// ������ ���Ҹ� ����ϴ� ����
};

int main() {
	Stack<int> intStack;
	Stack<double> doubleStack;

	// int ���ÿ� ������ �߰�
	for (int i = 0; i < 5; ++i) {
		intStack.push(i);
	}

	// double ���ÿ� ������ �߰�
	for (double i = 0.1; i < 0.6; i += 0.1) {
		doubleStack.push(i);
	}

	// int ���� ���
	intStack.printStack();

	// double ���� ���
	doubleStack.printStack();

	return 0;
	return 0;
}