#pragma once	//to avoid multiple header declaration

#include<iostream>
#include<cassert>	//to call assert function

using namespace std;

//node structure
template <class Type>	//for using different types of objects in a stack
struct nodeType {
	Type info;	//to store the values
	nodeType<Type>* link;	//to get the pointer
};

template<class Type>
class linkedStackType {
public:
	//Default constructor: stackTop = nullptr;
	linkedStackType();

	//Copy constructor
	linkedStackType(const linkedStackType<Type>& otherStack);

	//Destructor: reomves all the elements of the stack
	~linkedStackType();

	//Operator overloading for '='
	const linkedStackType<Type>& operator= (const linkedStackType<Type>& otherStack);	//takes the other stack as reference and makes copy

	//Checks if the stack is empty
	bool isEmptyStack() const;

	//Checks if the stack is full
	bool isFullStack() const;

	//Making an empty stack
	void initializeStack();

	//"Pushing" elements on top of a stack
	void push(const Type& newItem);

	//Returning the top element of the stack
	Type top() const;

	//Removing the top elemnt of the stack
	void pop();


//member variables
private:
	//pointer to the stack top
	nodeType<Type>* stackTop;

	//Making copy of the other stack
	void copyStack(const linkedStackType<Type>& otherStack);
};