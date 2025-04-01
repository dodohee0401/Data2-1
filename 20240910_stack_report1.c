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

// 스택이 가득 찼는지 확인
int isFull(Stack *s) {
    return s->top == s->capacity - 1;
}

// 스택 크기 확장
void expandStack(Stack *s) {
    int newCapacity = s->capacity + 5;  // 5개씩 크기 증가
    char *newData = (char *)realloc(s->data, newCapacity * sizeof(char));
    if (newData == NULL) {
        printf("메모리 재할당 실패!\n");
        exit(1);
    }
    s->data = newData;
    s->capacity = newCapacity;
}

// 스택에 문자 추가 (push)
void push(Stack *s, char value) {
    if (isFull(s)) {
        expandStack(s);
    }
    s->data[++(s->top)] = value;
}

// 스택에서 문자 제거 (pop)
char pop(Stack *s) {
    if (isEmpty(s)) {
        printf("스택 언더플로우! 제거할 요소가 없습니다.\n");
        return '\0';  // 에러 값
    }
    return s->data[(s->top)--];
}

// 스택 메모리 해제
void freeStack(Stack *s) {
    free(s->data);
    printf("스택 메모리를 해제했습니다.\n");
}

int main() {
    Stack s;
    char str[101];  // 최대 100자 이하의 문자열을 받을 배열

    printf("문자열을 입력하세요: ");
    fgets(str, sizeof(str), stdin);  // 사용자 입력 받기
    str[strcspn(str, "\n")] = '\0';  // 개행 문자 제거

    initStack(&s, strlen(str));  // 스택 초기화

    // 입력된 문자열을 스택에 저장
    for (int i = 0; i < strlen(str); i++) {
        push(&s, str[i]);
    }

    // 스택에서 하나씩 꺼내어 거꾸로 출력
    printf("거꾸로 출력된 문자열: ");
    while (!isEmpty(&s)) {
        printf("%c", pop(&s));
    }

    printf("\n");

    freeStack(&s);  // 메모리 해제

    return 0;
}
