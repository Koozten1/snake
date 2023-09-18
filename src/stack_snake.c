#include "stack_snake.h"


stack_snake *head_create(int x, int y){
    stack_snake *root  = malloc(sizeof(stack_snake));
    
    root->x = x;
    root->y = y;
    root->next = NULL;
    root->before = NULL;

    return root;

}

stack_snake *tail_create(int x, int y, stack_snake *old_tail){
    stack_snake *root  = malloc(sizeof(stack_snake));
    
    root->x = x;
    root->y = y;
    root->before = old_tail;
    root->next = NULL;
    old_tail->next = root;

    return root;

}

void clear_stack(stack_snake *snake_linck){
    while(snake_linck->next != NULL){
        clear_stack(snake_linck->next);
    }

    free(snake_linck);
    return;

}
