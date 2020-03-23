#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    printf("Введите ваше первое число:\n");
    char stringOne[100], stringTwo[100];
    scanf("%99s", stringOne);
    printf("Введите ваше второе число:\n");
    scanf("%99s", stringTwo);
    long long int numberOne = 0, numberTwo = 0, numberThree = 0;
    numberOne = atoi (stringOne);
    numberTwo = atoi (stringTwo);
    numberThree = numberOne + numberTwo;
    printf("%llu", numberThree);
    return 0;
}
