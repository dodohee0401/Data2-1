#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 30
#define PHONE_LEN 20

typedef struct Contact {
    char name[NAME_LEN];
    char phone[PHONE_LEN];
    struct Contact* next;
} Contact;

Contact* addContact(Contact* head, const char* name, const char* phone) {
    Contact* newNode = (Contact*)malloc(sizeof(Contact));
    strcpy(newNode->name, name);
    strcpy(newNode->phone, phone);
    newNode->next = head;
    return newNode;
}

void findContact(Contact* head, const char* name) {
    Contact* current = head;
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            printf("이름: %s, 전화번호: %s\n", current->name, current->phone);
            return;
        }
        current = current->next;
    }
    printf("연락처를 찾을 수 없습니다: %s\n", name);
}

Contact* removeContact(Contact* head, const char* name) {
    Contact* current = head;
    Contact* before = NULL;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (before == NULL) {
                head = current->next;
            } else {
                before->next = current->next;
            }
            free(current);
            printf("연락처 삭제 완료: %s\n", name);
            return head;
        }
        before = current;
        current = current->next;
    }

    printf("삭제할 연락처를 찾을 수 없습니다: %s\n", name);
    return head;
}

void showAllContacts(Contact* head) {
    Contact* current = head;
    printf("=== 전화번호부 ===\n");
    while (current != NULL) {
        printf("이름: %s, 전화번호: %s\n", current->name, current->phone);
        current = current->next;
    }
}

void clearContacts(Contact* head) {
    Contact* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Contact* head = NULL;

    head = addContact(head, "최지우", "010-1234-5678");
    head = addContact(head, "김도희", "010-8765-4321");
    head = addContact(head, "이철수", "010-1357-2468");

    showAllContacts(head);

    printf("\n[검색] 이름: 김도희\n");
    findContact(head, "김도희");

    printf("\n[삭제] 이름: 최지우\n");
    head = removeContact(head, "최지우");

    printf("\n[최종 전화번호부 출력]\n");
    showAllContacts(head);

    clearContacts(head);
    return 0;
}
