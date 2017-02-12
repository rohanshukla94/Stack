#ifndef _STACK_H
#define _STACK_H

typedef struct 
{
	void * elements;
	int elementSize;
	int logLength;
	int allocLength;
	void(*free_function)(void*);
};

void stack_init(stack *s, int elementSize, void(*free_function)(void*));
void stack_destroy(stack *s);
void stack_push(stack *s, void *elementAddress);
void stack_pop(stack *s, void *elementAddress);


#endif
