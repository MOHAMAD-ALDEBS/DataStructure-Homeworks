#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

typedef struct {
    char data[MAX];
    int top;
} Stack;

Stack* createStack() {
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->top = -1;
    return stack;
}

void push(Stack *stack, char c) {
    if (stack->top < MAX - 1) {
        stack->data[++stack->top] = c;
    }
}

char pop(Stack *stack) {
    if (stack->top >= 0) {
        return stack->data[stack->top--];
    }
    return '\0';
}

char peek(Stack *stack) {
    if (stack->top >= 0) {
        return stack->data[stack->top];
    }
    return '\0';
}

int isEmpty(Stack *stack) {
    return stack->top == -1;
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

void infixToPostfix(char *infix, char *postfix) {
    Stack *stack = createStack();
    int k = 0;
    
    for (int i = 0; infix[i] != '\0'; i++) {
        char c = infix[i];
        
        if (isdigit(c) || (isdigit(c) && (i + 1 < strlen(infix) && isdigit(infix[i + 1])))) {
            postfix[k++] = c;
        } 
        else if (c == '(') {
            push(stack, c);
        } 
        else if (c == ')') {
            while (!isEmpty(stack) && peek(stack) != '(') {
                postfix[k++] = pop(stack);
            }
            pop(stack);
        } 
        else if (isOperator(c)) {
            while (!isEmpty(stack) && precedence(peek(stack)) >= precedence(c)) {
                if (c == '^' && peek(stack) == '^') break;
                postfix[k++] = pop(stack);
            }
            push(stack, c);
        }
    }
    
    while (!isEmpty(stack)) {
        postfix[k++] = pop(stack);
    }
    postfix[k] = '\0';
    
    free(stack);
}

int main() {
    char infix[MAX], postfix[MAX];
    
    printf("Infix ifade girin: ");
    scanf("%s", infix);
    
    infixToPostfix(infix, postfix);
    
    printf("Postfix ifade: %s\n", postfix);
    
    return 0;
}