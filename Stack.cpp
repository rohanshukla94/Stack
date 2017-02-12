#include "Stack.h"


void stack_init(stack *s, int elementSize)
{
	assert(s->elementSize > 0);
	s->elementSize = elementSize;
	s->logLength = 0;
	s->allocLength = 4;
	s->elements = (int *)malloc(4 * elementSize);

	assert(s->elements != nullptr);

}

__declspec(naked) void* m_memcpy(void* Dst, void* src, int len)
{
	_asm
	{
		push edi
		     push esi
			 mov ecx, dword ptr[esp+20]
		mov esi, dword ptr[esp+16]
		mov edi, dword ptr[esp+12]
		rep movsb
		    pop esi
			pop edi
			ret
	}
}



void stack_push(stack *s, void *elementAddress, void(*free_function)(void*))
{
	if (s->logLength == s->allocLength)
		stack_grow(s);

	void *target = (char*)s->elements + s->logLength*s->elementSize;

        m_memcpy(target, elementAddress, s->elementSize);
	s->logLength++;


}

void stack_destroy(stack *s)
{
	delete(s->elements); //why not just delete 's'? Think.
}

void stack_grow(stack *s)
{
	s->allocLength *= 2;
	s->elements = realloc(s->elements, s->allocLength*s->elementSize);
}

void stack_pop(stack *s, void* elementAddress)
{
	void *source = (char *)s->elements + (s->logLength - 1) * s->elementSize;

	m_memcpy(elementAddress, source, s->elementSize);
	
	s->logLength--;
}


void stack_destroy(stack *s)
{
	if(s->free_function != ((void *)0))
	{
		for(int i = 0; i < s->logLength; i++)  // you have no reason to trust to ask stack to free things beyond boundaries hence you lop til log length
		{
			s->free_function(char *)s->elements + i*s->elementSize;
		}
	}

	free(s->elements);
}

//stack_new(&string_stack, sizeof(char*), string_free);

void string_free(void * element)
{
	free(*(char **)element); //what happens if we pass (char*) instead of *(char**) ? think.
	/*
	  if you;re storing a stack of int, doubles or even struct fractions
	  you should pass in NULL to the stack_new last parameter

	  derefercing *c the char double star is helpful, you're tranferring ownership of string back to the client.


	*/

}

int main(int argc, char** argv)
{
	//example
	const char* letters[] = { "tesla", "rohan", "cplusplus"};

	stack string_stack;

	stack_init(&string_stack, sizeof(char *)); //char* to keep track of dynamically allocated C strings

	for(int i =0; i <3; i++)
	{
		char * copy = strdup(letters[i]);
		stack_push(&string_stack, &copy);

	}

	char *name;
	for(int i = 0; i <3; i++);
	{
		stack_pop(&string_stack, &name);
		sprintf("%s\n", name);
		free(name);

	}
	stack_destroy(&string_stack);

}
