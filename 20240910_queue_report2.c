#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10

typedef struct {
    char documentName[50];
    int numPages;
} PrintJob;

typedef struct {
    PrintJob queue[SIZE];
    int front;
    int rear;
    int count;
} PrintQueue;

void initQueue(PrintQueue *q) {
    q->front = 0;
    q->rear = 0;
    q->count = 0;
}

bool isEmpty(PrintQueue *q) {
    return q->count == 0;
}

bool isFull(PrintQueue *q) {
    return q->count == SIZE;
}

bool enqueue(PrintQueue *q, char *documentName, int numPages) {
    if (numPages > 50) {
        printf("문서 페이지 수가 50장을 초과하여 추가할 수 없습니다.\n");
        return false;
    }
    if (isFull(q)) {
        printf("대기열이 가득 찼습니다. 작업을 추가할 수 없습니다.\n");
        return false;
    }
    strcpy(q->queue[q->rear].documentName, documentName);
    q->queue[q->rear].numPages = numPages;
    q->rear = (q->rear + 1) % SIZE;
    q->count++;
    printf("작업 '%s' (%d 페이지)가 대기열에 추가되었습니다.\n", documentName, numPages);
    return true;
}

PrintJob dequeue(PrintQueue *q) {
    if (isEmpty(q)) {
        printf("대기열이 비어 있습니다. 작업이 없습니다.\n");
        PrintJob emptyJob = {"", 0};
        return emptyJob;
    }
    PrintJob job = q->queue[q->front];
    q->front = (q->front + 1) % SIZE;
    q->count--;
    return job;
}

bool cancelJob(PrintQueue *q, char *targetName) {
    if (isEmpty(q)) {
        printf("대기열이 비어 있습니다.\n");
        return false;
    }

    int idx = q->front;
    int found = -1;

    for (int i = 0; i < q->count; i++) {
        if (strcmp(q->queue[idx].documentName, targetName) == 0) {
            found = idx;
            break;
        }
        idx = (idx + 1) % SIZE;
    }

    if (found == -1) {
        printf("해당 문서가 없습니다.\n");
        return false;
    }

    // 작업 제거 후 이동
    int nextIdx = (found + 1) % SIZE;
    while (nextIdx != q->rear) {
        q->queue[found] = q->queue[nextIdx];
        found = nextIdx;
        nextIdx = (nextIdx + 1) % SIZE;
    }

    q->rear = (q->rear - 1 + SIZE) % SIZE;
    q->count--;
    printf("작업 '%s'이(가) 취소되었습니다.\n", targetName);
    return true;
}

void clearQueue(PrintQueue *q) {
    initQueue(q);
    printf("대기열 초기화\n");
}

void printQueue(PrintQueue *q) {
    if (isEmpty(q)) {
        printf("대기열이 비어 있습니다.\n");
        return;
    }

    printf("현재 대기 중인 작업:\n");
    int idx = q->front;
    for (int i = 0; i < q->count; i++) {
        printf("- %s (%d 페이지)\n", q->queue[idx].documentName, q->queue[idx].numPages);
        idx = (idx + 1) % SIZE;
    }
}

int main() {
    PrintQueue q;
    initQueue(&q);

    int choice;
    char documentName[50];
    int numPages;

    while (true) {
        printf("\n1. 작업 추가\n2. 작업 처리\n3. 인쇄 취소\n4. 대기열 출력\n5. 대기열 초기화\n6. 종료\n선택: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("문서 이름: ");
                scanf(" %[^\n]", documentName);
                printf("페이지 수: ");
                scanf("%d", &numPages);
                enqueue(&q, documentName, numPages);
                break;
            case 2: {
                PrintJob job = dequeue(&q);
                if (strlen(job.documentName) > 0) {
                    printf("작업 '%s' (%d 페이지)를 처리 중입니다...\n", job.documentName, job.numPages);
                }
                break;
            }
            case 3:
                printf("취소할 문서 이름: ");
                scanf(" %[^\n]", documentName);
                cancelJob(&q, documentName);
                break;
            case 4:
                printQueue(&q);
                break;
            case 5:
                clearQueue(&q);
                break;
            case 6:
                printf("프로그램을 종료합니다.\n");
                return 0;
            default:
                printf("잘못된 입력입니다. 다시 선택해 주세요.\n");
        }
    }

    return 0;
}
