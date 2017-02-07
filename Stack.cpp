#include "Stack.h"


void StackLib::StackNew(stack *s, int elementSize)
{
	assert(s->elementSize > 0);
	s->elementSize = elementSize;
	s->logLength = 0;
	s->allocLength = 4;
	s->elements = (int *)malloc(4 * elementSize);

	assert(s->elements != nullptr);

}

__declspec(naked) void* StackLib::m_memcpy(void* Dst, void* src, int len)
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



void StackLib::StackPush(stack *s, void *elementAddress)
{
	if (s->logLength == s->allocLength)
		StackLib::StackGrow(s);

	void *target = (char*)s->elements + s->logLength*s->elementSize;

	StackLib::m_memcpy(target, elementAddress, s->elementSize);
	s->logLength++;


}

void StackLib::StackRemove(stack *s)
{
	delete(s->elements); //why not just delete 's'? Think.
}

void StackLib::StackGrow(stack *s)
{
	s->allocLength *= 2;
	s->elements = realloc(s->elements, s->allocLength*s->elementSize);
}

void StackLib::StackPop(stack *s, void* elementAddress)
{
	void *source = (char *)s->elements + (s->logLength - 1) * s->elementSize;

	StackLib::m_memcpy(elementAddress, source, s->elementSize);
	
	s->logLength--;
}


