# Stack
Using Generics in C++.


## Usage

    
void stack_init(stack *s, int elementSize, void(*free_function)(void*));

void stack_destroy(stack *s);

void stack_push(stack *s, void *elementAddress);

void stack_pop(stack *s, void *elementAddress);

