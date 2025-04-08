#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100
#define TRUE 1
#define FALSE 0


int precedence(char op);
void infixToPostfix(char* infix, char* postfix);
int evaluatePostfix(char* postfix);

int main(void) {
    char infix[MAX];
    char postfix[MAX];
    int result;

    
    printf(":중위표기식 입력 : ");
    scanf("%s", infix);

    
    infixToPostfix(infix, postfix);
    printf("후위표기식 : %s\n", postfix);

    
    result = evaluatePostfix(postfix);
    printf("후위표기식 계산 결과 : %d\n", result);

    return 0;
}


int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}


void infixToPostfix(char* infix, char* postfix) {
    char stack[MAX];
    int top = -1;
    int j = 0;
    
    for (int i = 0; infix[i] != '\0'; i++) {
        char current = infix[i];
        
        
        if (isdigit(current)) {
            postfix[j++] = current;
        }
        
        else if (current == '(') {
            stack[++top] = current;
        }
        
        else if (current == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[j++] = stack[top--];
            }
            top--;  
        }
        
        else {
            while (top != -1 && precedence(stack[top]) >= precedence(current)) {
                postfix[j++] = stack[top--];
            }
            stack[++top] = current;
        }
    }
    
    
    while (top != -1) {
        postfix[j++] = stack[top--];
    }
    postfix[j] = '\0';
}


int evaluatePostfix(char* postfix) {
    int stack[MAX];
    int top = -1;
    
    for (int i = 0; postfix[i] != '\0'; i++) {
        char current = postfix[i];
        
        
        if (isdigit(current)) {
            stack[++top] = current - '0'; // 문자 '0'을 숫자 0으로 변환
        }
        
        else {
            int b = stack[top--];  // 두 번째 피연산자
            int a = stack[top--];  // 첫 번째 피연산자
            
            switch (current) {
                case '+':
                    stack[++top] = a + b;
                    break;
                case '-':
                    stack[++top] = a - b;
                    break;
                case '*':
                    stack[++top] = a * b;
                    break;
                case '/':
                    stack[++top] = a / b;
                    break;
            }
        }
    }
    
    return stack[top];  
}

