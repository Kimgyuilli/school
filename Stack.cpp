#include <iostream>
#include <stdlib.h>

template<typename T>
class Stack {
private:
	T* stack;
	int top;         
	int StackSize; //현재 스택의 크기
	int StackCapacity; // 현재 스택의 최대 크기
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

	bool isEmpty() { //stack이 비었는지 체크
		if (top == -1) return true;
		else return false;
	}

	bool isFull() { //stack이 가득 찼는지 체크
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
			std::cout << "스택 사이즈 증가" << std::endl;
			// 스택이 가득 차 있으면 크기를 늘려준다.
			int NewCapacity = StackCapacity + 10;
			T* NewStack = new T[NewCapacity];

			// 기존 스택을 새로운 스택으로 복사.
			for (int i = 0; i <= top; ++i) {
				NewStack[i] = stack[i];
			}

			// 새로운 스택으로 교체.
			delete[] stack;
			stack = NewStack;
			StackCapacity = NewCapacity;
		}

		stack[++top] = value;
		StackSize++;
	}

	void pushAt(int location, T& value) {
		if (location < 0 || location > top + 1) {
			std::cerr << "올바르지 않은 위치입니다!" << std::endl;
			return;
		}

		// 스택이 가득 차 있으면 크기를 늘린다.
		if (isFull()) {
			std::cout << "스택 사이즈 증가" << std::endl;
			int NewCapacity = StackCapacity + 10;
			T* NewStack = new T[NewCapacity];

			// 기존 스택을 새로운 스택으로 복사.
			for (int i = 0; i <= top; ++i) {
				NewStack[i] = stack[i];
			}

			// 새로운 스택으로 교체한다.
			delete[] stack;
			stack = NewStack;
			StackCapacity = NewCapacity;
		}

		// 요소를 추가할 위치 이후의 요소들을 한 칸씩 뒤로 이동.
		for (int i = top; i >= location; --i) {
			stack[i + 1] = stack[i];
		}
		stack[location] = value;
		top++;
		StackSize++;
	}

	T pop() {
		if (isEmpty()) {
			std::cerr << "스택이 비어있습니다!" << std::endl;
			return T();
		}

		T value = stack[top--];
		StackSize--;
		if (size() % StackCapacity == 0)
		{
			std::cout << "스택 사이즈 감소" << std::endl;
			// 스택 사이즈 감소
			int NewCapacity = StackCapacity - 10;
			T* NewStack = new T[NewCapacity];
			// 기존 스택을 새로운 스택으로 복사.
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
			std::cerr << "pop이 불가능합니다!" << std::endl;
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
			std::cout << "스택 사이즈 감소" << std::endl;
			// 스택 사이즈 감소
			int NewCapacity = StackCapacity - 10;
			T* NewStack = new T[NewCapacity];
			// 기존 스택을 새로운 스택으로 복사.
			for (int i = 0; i <= top; ++i) {
				NewStack[i] = stack[i];
			}
			delete[] stack;
			stack = NewStack;
			StackCapacity = NewCapacity;
		}
		return value;
	}



	// 스택의 원소를 출력하는 연산
};

int main() {
	Stack<int> intStack;
	Stack<double> doubleStack;

	// int 스택에 데이터 추가
	for (int i = 0; i < 5; ++i) {
		intStack.push(i);
	}

	// double 스택에 데이터 추가
	for (double i = 0.1; i < 0.6; i += 0.1) {
		doubleStack.push(i);
	}

	// int 스택 출력
	intStack.printStack();

	// double 스택 출력
	doubleStack.printStack();

	return 0;
	return 0;
}