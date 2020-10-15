#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct Info{
    int64_t a;
} Info;

typedef struct Stack{
    Info info;
    struct Stack* next;
} Stack;

static Stack* head = NULL;

bool Push(const Info info);
bool Pop(void);
void Print(void);

int main(void)
{
    int choice;
    int term = 0;
    int64_t number_to_push;
    Info s;
    puts("\t====STACK MENU====\n"
         "1) Add a number\n"
         "2) Erase number on the top\n"
         "3) Show stack\n"
         "q to exit\n");
    printf("> ");
    while (scanf("%d", &choice)){
        switch(choice){
        case 1:
            puts("Enter a number you want to put in stack: ");
            scanf("%lld", &number_to_push);
            s.a = number_to_push;
            if (!Push(s))
                term = 1;
            break;
        case 2:
            if (!Pop())
                term = 1;
            break;
        case 3:
            Print();
            break;
        default:
            term = 1;
            break;
        }
        if (term){
            puts("Terminating");
            break;
        }
        printf("> ");
    }
    return 0;
}

bool Push(const Info info){
    Stack* new = (Stack *)malloc(sizeof (Stack));
    if (new != NULL){
        new->info = info;
        if (head == NULL)
            new->next = NULL;
        else
            new->next = head;
        head = new;
        return true;
    }
    else
        return false;
}

bool Pop(void){
    if (head == NULL)
        return false;
    Stack* tmp = head;
    head = tmp->next;
    free(tmp);
    return true;
}

void Print(void){
    if (head == NULL){
        printf("Stack is empty.\n");
        return;
    }
    Stack* iterator = head;
    while (iterator != NULL){
        printf("%lld ", iterator->info.a);
        iterator = iterator->next;
    }
    printf("\n");
}
