#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* insertFirst(Node* head, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = head;
    return newNode;
}

Node* insertLast(Node* head, int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;

    if (head == NULL) return newNode;

    Node* current = head;
    while (current->next != NULL)
        current = current->next;

    current->next = newNode;
    return head;
}

void insertAfterValue(Node* head, int targetValue, int newData) {
    Node* current = head;
    while (current != NULL) {
        if (current->data == targetValue) {
            Node* newNode = (Node*)malloc(sizeof(Node));
            newNode->data = newData;
            newNode->next = current->next;
            current->next = newNode;
            return;
        }
        current = current->next;
    }
}

void printList(Node* head) { // 실습 1-4
    Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

Node* deleteNode(Node* head, int targetValue) {
    if (head == NULL) return NULL;

    if (head->data == targetValue) {
        Node* temp = head;
        head = head->next;
        free(temp);
        return head;
    }

    Node* current = head;
    while (current->next != NULL && current->next->data != targetValue) {
        current = current->next;
    }

    if (current->next == NULL) {
        return head;
    }

    Node* temp = current->next;
    current->next = current->next->next;
    free(temp);
    return head;
}

Node* deleteHead(Node* head) {
    if (head == NULL) return NULL;
    Node* temp = head;
    head = head->next;
    free(temp);
    return head;
}

Node* deleteLast(Node* head) {
    if (head == NULL) return NULL;
    if (head->next == NULL) {
        free(head);
        return NULL;
    }

    Node* current = head;
    while (current->next->next != NULL)
        current = current->next;

    free(current->next);
    current->next = NULL;
    return head;
}

int searchValue1(Node* head, int val) { // 실습 1-5
    int index = 0;
    while (head != NULL) {
        if (head->data == val) return index;
        head = head->next;
        index++;
    }
    return -1;
}

void searchValue2(Node* head, int val) { // 실습 1-5
    Node* prev = NULL;
    Node* current = head;

    while (current != NULL) {
        if (current->data == val) {
            printf("값 %d를 찾았습니다.\n", val);
            if (prev)
                printf("앞 노드 값: %d\n", prev->data);
            else
                printf("앞 노드가 없습니다.\n");

            if (current->next)
                printf("뒤 노드 값: %d\n", current->next->data);
            else
                printf("뒤 노드가 없습니다.\n");

            return;
        }
        prev = current;
        current = current->next;
    }

    printf("값 %d를 찾을 수 없습니다.\n", val);
}

void freeList(Node* head) { // 실습 1-5
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node* head = NULL;

    head = insertFirst(head, 30);
    head = insertFirst(head, 20);
    head = insertFirst(head, 10);
    head = insertLast(head, 70);
    head = insertLast(head, 80);
    head = insertLast(head, 90);
    insertAfterValue(head, 30, 40);
    insertAfterValue(head, 40, 50);
    insertAfterValue(head, 50, 60);

    printf("현재 리스트:\n");
    printList(head);

    head = deleteHead(head);
    head = deleteLast(head);
    head = deleteNode(head, 40);
    head = deleteNode(head, 70);
    head = deleteNode(head, 100);

    printf("\n삭제 후 리스트:\n");
    printList(head);

    int val = 30;
    int pos = searchValue1(head, val); // 실습 1-5
    if (pos != -1)
        printf("\n%d의 위치는 %d번째입니다.\n", val, pos);
    else
        printf("\n%d는 리스트에 없습니다.\n", val);

    printf("\nsearchValue2 결과:\n");
    searchValue2(head, val); // 실습 1-5

    freeList(head); // 실습 1-5
    return 0;
}
