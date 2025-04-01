#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 함수 선언
double calculateAverage(int scores[], int size);
int getStudentScore(int scores[], int size, int studentNumber);
void deleteStudent(int scores[], int *size, int studentNumber);
void addStudents(int **scores, int *size, int newStudents[], int newSize);

int main() {
    int scores[30]; // 30명의 학생 성적 저장
    int studentNumber, newSize = 2; // 전학 온 학생 수
    double average;

    // 난수 생성 초기화
    srand(time(0));

    // 성적 데이터 초기화
    for (int i = 0; i < 30; i++) {
        scores[i] = rand() % 101; // 0 ~ 100 사이의 난수 생성
    }

    // 평균 계산
    average = calculateAverage(scores, 30);
    printf("학급 평균 점수: %.2f\n", average);

    // 특정 학생 점수 검색
    printf("학생 번호를 입력하세요 (1 ~ 30): ");
    scanf("%d", &studentNumber);

    int score = getStudentScore(scores, 30, studentNumber);
    if (score != -1) {
        printf("%d번 학생의 점수: %d\n", studentNumber, score);
    } else {
        printf("유효하지 않은 학생 번호입니다.\n");
    }

    // 특정 학생 삭제 (전학 간 학생)
    printf("전학 간 학생 번호를 입력하세요 (1 ~ 30): ");
    scanf("%d", &studentNumber);
    deleteStudent(scores, &newSize, studentNumber);

    // 새로운 학생들 전학 온 성적 입력 받기
    int numNewStudents;
    printf("전학 온 학생 수를 입력하세요: ");
    scanf("%d", &numNewStudents);

    int *newStudents = (int *)malloc(numNewStudents * sizeof(int));

    for (int i = 0; i < numNewStudents; i++) {
        printf("전학 온 %d번째 학생의 성적을 입력하세요: ", i + 1);
        scanf("%d", &newStudents[i]);
    }

    // 새로 전학 온 학생들 추가
    addStudents(&scores, &newSize, newStudents, numNewStudents);

    // 수정 후 평균 재계산
    average = calculateAverage(scores, newSize);
    printf("학급 평균 점수 (변경 후): %.2f\n", average);

    // 메모리 해제
    free(newStudents);

    return 0;
}

// 평균 계산 함수
double calculateAverage(int scores[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += scores[i];
    }
    return sum / (double)size;
}

// 특정 학생 점수 검색 함수
int getStudentScore(int scores[], int size, int studentNumber) {
    if (studentNumber >= 1 && studentNumber <= size) {
        return scores[studentNumber - 1];
    } else {
        return -1; // 유효하지 않은 학생 번호
    }
}

// 학생 삭제 함수
void deleteStudent(int scores[], int *size, int studentNumber) {
    if (studentNumber < 1 || studentNumber > *size) {
        printf("유효하지 않은 학생 번호입니다.\n");
        return;
    }

    int index = studentNumber - 1;  // 배열 인덱스는 0부터 시작하므로 1을 빼줍니다.

    // 전학 간 학생의 자리를 -1로 설정
    scores[index] = -1;

    // 배열 크기 감소
    (*size)--;

    printf("%d번 학생이 전학을 갔습니다.\n", studentNumber);
}

// 학생 추가 함수
void addStudents(int **scores, int *size, int newStudents[], int newSize) {
    // 기존 배열의 크기보다 더 큰 새로운 크기를 할당
    *scores = realloc(*scores, (*size + newSize) * sizeof(int));

    // 새로운 학생의 점수 추가
    for (int i = 0; i < newSize; i++) {
        (*scores)[*size + i] = newStudents[i];
    }

    // 배열 크기 업데이트
    *size += newSize;

    printf("%d명의 학생이 전학 왔습니다.\n", newSize);
}
