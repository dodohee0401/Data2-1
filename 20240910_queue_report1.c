#include <stdio.h>
#include <stdbool.h>

#define SIZE 30

typedef struct {
    int data[SIZE];
    int front;
    int rear;
} LinearQueue;

void initQueue(LinearQueue *q) {
    q->front = 0;
    q->rear = -1;
}

bool isEmpty(LinearQueue *q) {
    return q->rear < q->front;
}

bool isFull(LinearQueue *q) {
    return q->rear == SIZE - 1;
}

bool enqueue(LinearQueue *q, int value) {
    if (isFull(q)) {
        printf("큐가 가득 찼습니다.\n");
        return false;
    }
    q->rear++;
    q->data[q->rear] = value;
    return true;
}

int dequeue(LinearQueue *q) {
    if (isEmpty(q)) {
        printf("큐가 비어 있습니다. 초기화합니다.\n");
        initQueue(q);
        return -1;
    }
    int value = q->data[q->front];
    q->front++;
    if (q->front > q->rear) {
        initQueue(q);
    }
    return value;
}

void printQueue(LinearQueue *q) {
    if (isEmpty(q)) {
        printf("큐가 비어 있습니다.\n");
        return;
    }

    printf("큐 내용: ");
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d ", q->data[i]);
    }
    printf("\n");
}

void printMenu() {
    printf("\n====== 큐 메뉴 ======\n");
    printf("1. 삽입\n");
    printf("2. 삭제\n");
    printf("3. 큐 데이터 출력\n");
    printf("4. 종료\n");
    printf("=====================\n");
    printf("선택: ");
}

int main() {
    LinearQueue queue;
    initQueue(&queue);

    int choice, value;

    while (1) {
        printMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("삽입할 값을 입력하세요: ");
                scanf("%d", &value);
                if (enqueue(&queue, value)) {
                    printf("%d 삽입 완료\n", value);
                }
                break;
            case 2:
                value = dequeue(&queue);
                if (value != -1) {
                    printf("삭제된 값: %d\n", value);
                }
                break;
            case 3:
                printQueue(&queue);
                break;
            case 4:
                printf("프로그램을 종료합니다.\n");
                return 0;
            default:
                printf("잘못된 입력입니다. 다시 선택하세요.\n");
        }
    }

    return 0;
}
