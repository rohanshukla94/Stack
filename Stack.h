#ifndef _STACK_H_
#define _STACK_H_
#include <stdio.h>
#include <cstring>
#include <iostream>
#include <assert.h>

using namespace std;


class StackLib
{
protected:
	typedef struct {
		
		void *elements; //Here you can insert your vertex list I suppose?
		int elementSize;
		int logLength;
		int allocLength;

	} stack;
public:

	void StackNew(stack *s, int elemSize);
	void StackRemove(stack *s);
	void StackPush(stack *s, void *elementAddress);
	void StackPop(stack *s, void *elementAddress);
	static void StackGrow(stack *s);
	__declspec(naked) void* m_memcpy(void *dest, void* src, int len);

};

#endif
