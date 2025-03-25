
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int scores[10];
    int sum = 0;
    double average;
    int studentNumber;
    
    srand(time(0)); 
    
    for(int i = 0; i < 10; i++){
        scores[i] = rand() % 101;
        sum+= scores[i];
    }
    
    average = sum / 10.0;
    printf("평균 점수: %.2f ", average);
    
    printf("학생 번호를 입력하세요(1~10): ");
    scanf("%d", &studentNumber);
    
    if(studentNumber >= 1 && studentNumber <= 10){
        printf("%d번 학생의 점수: %d", studentNumber, scores[studentNumber - 1]);
    }else{
        printf("유효하지 않은 학생 번호임");
    }
    
    return 0;
}
