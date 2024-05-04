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
		if (top == -1) 
			return true;
		else 
			return false;
	}

	bool isFull() { //stack이 가득 찼는지 체크
		if (top == StackCapacity - 1) 
			return true;
		else 
			return false;
	}

	int capacity() {
		return StackCapacity;
	}

	int size() {
		return StackSize;
	}

	void printStack() {
		std::cout << "STACK 수용량 [" << StackCapacity << "]" << std::endl;
		std::cout << "현재 STACK 크기 [" << StackSize << "]" << std::endl;
		std::cout << "STACK [ ";
		for (int i = 0; i <= top; i++) {
			std::cout << stack[i] << " ";
		}
		std::cout << "]\n" << std::endl;
	}

	void sort() {
		// 버블정렬
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

	void pushAt(int location, const T& value) {
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
		if (size() % 10 == 0)
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
		if (size() % 10 == 0)
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

	void push_range(T values[], int arrSize) { //한번에 여러 요소 삽입
			// 스택이 가득 차 있거나 배열을 넣었을 때 스택의 크기가 초과되면
			if (isFull() || StackSize + arrSize > StackCapacity) {
				std::cout << "스택 사이즈 증가" << std::endl;
				// 스택이 가득 차 있으면 크기를 늘려준다.
				int NewCapacity = (((StackSize + arrSize)/10) * 10) + 10;
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
			for(int i = 0; i < arrSize; i++){
				stack[++top] = values[i];
			}
			StackSize += arrSize;
	}

	void push_rangeAt(int location, T values[], int arrSize) {
		if (location < 0 || location > top + 1) {
			std::cerr << "올바르지 않은 위치입니다!" << std::endl;
			return;
		}
		// 스택이 가득 차 있거나 배열을 넣었을 때 스택의 크기가 초과되면
		if (isFull() || StackSize + arrSize > StackCapacity) {
			std::cout << "스택 사이즈 증가" << std::endl;
			// 스택이 가득 차 있으면 크기를 늘려준다.
			int NewCapacity = (((StackSize + arrSize) / 10) * 10) + 10;
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

		// 요소를 추가할 위치 이후의 요소들을 한 칸씩 뒤로 이동.
		for (int i = top; i >= location; --i) {
			stack[i + arrSize] = stack[i];
		}
		for (int i = 0; i < arrSize; i++) {
			stack[location + i] = values[i];
		}
		top += arrSize;
		StackSize += arrSize;
	}
};

int main() {
	Stack<int> iStack;
	Stack<double> dStack;
	bool plag = 0;


	if (plag) {
		// int 스택에 데이터 추가
		std::cout << "iStack 실행" << std::endl;
		std::cout << "push실행 0~15" << std::endl;
		for (int i = 0; i < 15; ++i) {
			iStack.push(i);
		}
		iStack.printStack();

		std::cout << "pop실행 5회" << std::endl;
		for (int i = 0; i < 5; ++i) {
			iStack.pop();
		}
		iStack.printStack();

		std::cout << "pushAt실행 index : 3, value: 11" << std::endl;
		iStack.pushAt(3, 11);
		iStack.printStack();

		std::cout << "popAt실행 index : 5" << std::endl;
		iStack.popAt(5);
		iStack.printStack();

		int a[21] = { 6, 3, 8, 3, 2, 4, 5, 6, 7, 3, 11, 3, 7, 14, 12, 71, 45, 61, 43, 23, 12 };

		std::cout << "push_range 실행 value : [ ";
		for (int i = 0; i < 21; i++) {
			std::cout << a[i] << " ";
		}
		std::cout << "]" << std::endl;
		iStack.push_range(a, 21);
		iStack.printStack();

		std::cout << "push_rangeAt 실행 index : 3, value : [ ";
		for (int i = 0; i < 21; i++) {
			std::cout << a[i] << " ";
		}
		std::cout << "]" << std::endl;
		iStack.push_rangeAt(3, a, 21);
		iStack.printStack();

		std::cout << "cpapcity() 실행" << std::endl;
		std::cout << iStack.capacity() << std::endl;

		std::cout << "\nsize() 실행" << std::endl;
		std::cout << iStack.size() << std::endl;

		std::cout << "\nsort() 실행" << std::endl;
		iStack.sort();
		iStack.printStack();
	}
	else {
		//double 스텍에 데이터 추가
		std::cout << "dStack실행" << std::endl;
		std::cout << "push실행 0~15" << std::endl;
		for (double i = 0.1; i < 15; ++i) {
			dStack.push(i);
		}
		dStack.printStack();

		std::cout << "pop실행 5회" << std::endl;
		for (int i = 0; i < 5; ++i) {
			dStack.pop();
		}
		dStack.printStack();

		std::cout << "pushAt실행 index : 3, value: 11" << std::endl;
		dStack.pushAt(3, 11.0);
		dStack.printStack();

		std::cout << "popAt실행 index : 5" << std::endl;
		dStack.popAt(5);
		dStack.printStack();

		double a[21] = { 6.1, 3.2, 8.3, 3.1, 2.2, 4.3, 5.1, 6.2, 7.3, 3.1, 11.3, 3.2, 7.1, 14.3, 12.4, 71.2, 45.2, 61.5, 43.1, 23.3, 12.2 };

		std::cout << "push_range 실행 value : [ ";
		for (int i = 0; i < 21; i++) {
			std::cout << a[i] << " ";
		}
		std::cout << "]" << std::endl;
		dStack.push_range(a, 21);
		dStack.printStack();

		std::cout << "push_rangeAt 실행 index : 3, value : [ ";
		for (int i = 0; i < 21; i++) {
			std::cout << a[i] << " ";
		}
		std::cout << "]" << std::endl;
		dStack.push_rangeAt(3, a, 21);
		dStack.printStack();

		std::cout << "cpapcity() 실행" << std::endl;
		std::cout << dStack.capacity() << std::endl;

		std::cout << "\nsize() 실행" << std::endl;
		std::cout << dStack.size() << std::endl;

		std::cout << "\nsort() 실행" << std::endl;
		dStack.sort();
		dStack.printStack();
	}

	return 0;
}
