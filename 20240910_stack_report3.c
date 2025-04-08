#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100
#define TRUE 1
#define FALSE 0

// 함수 선언
int precedence(char op);
void infixToPostfix(char* infix, char* postfix);
int evaluatePostfix(char* postfix);

int main(void) {
    char infix[MAX];
    char postfix[MAX];
    int result;

    // 중위 표기식 입력 받기
    printf(":중위표기식 입력 : ");
    scanf("%s", infix);

    // 중위 표기식을 후위 표기식으로 변환
    infixToPostfix(infix, postfix);
    printf("후위표기식 : %s\n", postfix);

    // 후위 표기식을 계산하여 결과 출력
    result = evaluatePostfix(postfix);
    printf("후위표기식 계산 결과 : %d\n", result);

    return 0;
}

// 연산자의 우선순위 함수
int precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

// 중위 표기식을 후위 표기식으로 변환하는 함수
void infixToPostfix(char* infix, char* postfix) {
    char stack[MAX];
    int top = -1;
    int j = 0;
    
    for (int i = 0; infix[i] != '\0'; i++) {
        char current = infix[i];
        
        // 숫자일 경우 후위표기식에 추가
        if (isdigit(current)) {
            postfix[j++] = current;
        }
        // '('일 경우 스택에 푸시
        else if (current == '(') {
            stack[++top] = current;
        }
        // ')'일 경우 '('를 만날 때까지 스택에서 팝
        else if (current == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[j++] = stack[top--];
            }
            top--;  // '('를 팝
        }
        // 연산자일 경우
        else {
            while (top != -1 && precedence(stack[top]) >= precedence(current)) {
                postfix[j++] = stack[top--];
            }
            stack[++top] = current;
        }
    }
    
    // 스택에 남아있는 연산자들 팝
    while (top != -1) {
        postfix[j++] = stack[top--];
    }
    postfix[j] = '\0';
}

// 후위 표기식 계산 함수
int evaluatePostfix(char* postfix) {
    int stack[MAX];
    int top = -1;
    
    for (int i = 0; postfix[i] != '\0'; i++) {
        char current = postfix[i];
        
        // 숫자일 경우 스택에 푸시
        if (isdigit(current)) {
            stack[++top] = current - '0'; // 문자 '0'을 숫자 0으로 변환
        }
        // 연산자일 경우
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
    
    return stack[top];  // 최종 계산 결과 반환
}

