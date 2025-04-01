#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 스택 구조체 정의
typedef struct {
    char *data;   // 데이터를 저장할 배열 (동적 할당)
    int top;      // 스택의 최상단 요소 인덱스
    int capacity; // 스택의 현재 용량
} Stack;

// 스택 초기화 함수
void initStack(Stack *s, int initialSize) {
    s->data = (char *)malloc(initialSize * sizeof(char));  // 초기 용량 할당
    if (s->data == NULL) {
        printf("메모리 할당 실패!\n");
        exit(1);
    }
    s->top = -1;
    s->capacity = initialSize;
}

// 스택이 비었는지 확인
int isEmpty(Stack *s) {
    return s->top == -1;
}

// 스택에 문자 추가 (push)
void push(Stack *s, char value) {
    s->data[++(s->top)] = value;
}

// 스택에서 문자 제거 (pop)
char pop(Stack *s) {
    if (isEmpty(s)) {
        return '\0';  // 스택이 비었을 때의 에러 값
    }
    return s->data[(s->top)--];
}

// 스택 메모리 해제
void freeStack(Stack *s) {
    free(s->data);
}

// 괄호가 올바른지 검사하는 함수
int isValidBrackets(char *str) {
    Stack s;
    initStack(&s, 100);  // 스택 초기화 (최대 100자까지 처리)

    for (int i = 0; str[i] != '\0'; i++) {
        char c = str[i];

        // 여는 괄호일 경우 스택에 추가
        if (c == '(' || c == '{' || c == '[') {
            push(&s, c);
        }
        // 닫는 괄호일 경우
        else if (c == ')' || c == '}' || c == ']') {
            char top = pop(&s);
            if ((c == ')' && top != '(') ||
                (c == '}' && top != '{') ||
                (c == ']' && top != '[')) {
                freeStack(&s);
                return 0;  // 유효하지 않은 괄호
            }
        }
    }

    // 스택이 비었으면 모든 괄호가 짝이 맞는 것
    int result = isEmpty(&s);
    freeStack(&s);
    return result;
}

int main() {
    char str[101];

    printf("문자열을 입력하세요: ");
    fgets(str, sizeof(str), stdin);  // 문자열 입력 받기
    str[strcspn(str, "\n")] = '\0';  // 개행 문자 제거

    if (isValidBrackets(str)) {
        printf("유효한 괄호\n");
    } else {
        printf("유효하지 않은 괄호\n");
    }

    return 0;
}

