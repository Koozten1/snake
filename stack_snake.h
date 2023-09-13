#include <stdlib.h>

struct stack_snake
{
    int x;
    int y;
    struct stack_snake *next;
}typedef stack_snake;

stack_snake *head_create(int x, int y);
stack_snake *tail_create(int x, int y, stack_snake *old_tail);
void clear_stack(stack_snake *snake_linck);

