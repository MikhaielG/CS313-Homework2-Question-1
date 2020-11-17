#include"stackADT.h"

//Default constructor
template<class Type>
linkedStackType<Type>::linkedStackType() {
	stackTop = nullptr;	//stackTop is initialized to null pointer
}

//Checking if the stack is empty
template<class Type>
bool linkedStackType<Type>::isEmptyStack() const {
	return(stackTop == nullptr);	//if pointer did not move from null that means nothing was stacked and the pointer did not move, thus empty
}

//Checking if the stack is full
template<class Type>
bool linkedStackType<Type>::isFullStack() const {
	return false;
}

//initializing the stack
template<class Type>
void linkedStackType<Type>::initializeStack() {
	nodeType<Type>* temp;	//temorarily store the pointer to the stackTop if the stackTop is not null pointer and helps assigning the stackTop to new pointer preventing memory leak

	while (stackTop != nullptr) {
		temp = stackTop;	//temp holds the pointer to the stackTop
		stackTop = stackTop->link;	//new pointer to the stackTop gets assigned
		delete temp;	//deallocating the memory in temp to avoid memory leak
	}
}

//pushing on the top of the stack
template<class Type>
void linkedStackType<Type>::push(const Type& newElement) {
	nodeType<Type>* newNode;	//pointer to the new node
	newNode = new nodeType<Type>;	//creating new node

	newNode->info = newElement;	//storing newElement's info in newNode
	newNode->link = stackTop;	//assigning the stacktop as the pointer of the newNode
	stackTop = newNode;	//setting stackTop as the pointer to the top node
}

//Getting the top element of a stack
template<class Type>
Type linkedStackType<Type>::top()const {
	assert(stackTop != nullptr);	//terminates if the condition fails

	return stackTop->info;
}

//deleting the top value
template<class Type>
void linkedStackType<Type>::pop() {
	nodeType<Type>* temp;	//temp  is being used to store the pointer to the top element so the pointer can be deallocated

	//checking if the stack is empty
	if (stackTop != nullptr) {
		temp = stackTop;	//setting temp to point to the top of the stack
		stackTop = stackTop->link;	//stackTop gets assigned to the next nodes pointer
		delete temp;	//deleting the top node
	}
	else {
		cout << "Can not remove from an empty stack" << endl;
	}
}

//copying from another stack
template<class Type>
void linkedStackType<Type>::copyStack(const linkedStackType<Type>& otherStack) {
	//creating pointers for 1st and last elemment of the other stack
	nodeType<Type>* current, * last;

	if (stackTop != nullptr)
		initializeStack();	//if stack is not emptyu make it empty

	if (otherStack.stackTop == nullptr)
		stackTop = nullptr;	//if the parameter is an empty stack the keep my stack(copy) empty

	else
	{
		//when the stack is not empty...
		current = otherStack.stackTop;	//current pointer will be same as the parameters top of the stack

		//creating a new stack to hold the copy
		stackTop = new nodeType<Type>;	//creating new node
		stackTop->info = current->info;	//copying the value
		stackTop->link = nullptr;	//new node pointing to null
		last = stackTop;	//last pointing to the top of the stack of the parameter

		current = current->link;	//current poins to the next node as the 1st node is assigned to the new stack
		//copying the remaining stack
		while (current != nullptr) {
			nodeType<Type>* newNode = new nodeType<Type>;	//creating new node to hold the copy

			newNode->info = current->info;	//copying the value
			newNode->link = nullptr;
			last->link = newNode;	//linking with previous node
			last = newNode;	//moving las from stackTop to newNode
			current = current->link;	//moving on to next link
		}
	}
}

//copy constructor
template<class Type>
linkedStackType<Type>::linkedStackType(const linkedStackType<Type>& otherStack) {
	stackTop = nullptr;
	copyStack(otherStack);
}

//destructor
template<class Type>
linkedStackType<Type>::~linkedStackType() {
	initializeStack();
}

//overloading the assignment operator
template<class Type>
const linkedStackType<Type>& linkedStackType<Type>:: operator=(const linkedStackType<Type>& otherStack) {
	if (this != &otherStack)	//avoiding making copy of itself
		copyStack(otherStack);	//copy of stack is assigned, for example: stack1 = stack2; makes stack1 a copy of stack 2

	return *this;
}