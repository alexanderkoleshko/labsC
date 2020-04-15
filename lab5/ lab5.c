//Для проверки на совершенство, использовал правильно, что если перевести число в двоичную систему счисления, то в совершенном числе количество первых единиц будет на 1 больше последующего количества нулей. Например, 6 в двоичной это 110, а 6 это совершенное число и оно подчиняется нашему правилу, и так работает со всеми совершенными числами.
#include <stdio.h>
#include <malloc.h>
#include <math.h>
 
typedef struct item {
    struct item* next;
    struct item* prev;
    int digit;
}Item;
 
typedef struct list {
    Item* head;
    Item* tail;
    int amount;
}List;
 
List Calculation(List number) {
 
 
    Item* temp = number.tail;
    while (number.tail) {
        number.tail->digit *= 2;
        number.tail = number.tail->prev;
    }
    number.tail = temp;
    while (number.tail->prev) {
        if (number.tail->digit / 10 > 0) {
            int tmp = number.tail->digit / 10;
            number.tail->prev->digit += tmp;
            number.tail->digit %= 10;
 
        }
        number.tail = number.tail->prev;
    }
 
    if (number.tail->digit / 10 > 0) {
        Item* p = (Item*)malloc(sizeof(Item));
        p->digit = number.tail->digit / 10;
        p->prev = NULL;
        number.tail->digit %= 10;
        p->next = number.tail;
        number.tail->prev = p;
        number.head = p;
        number.amount++;
    }
 
    number.tail = temp;
 
    return number;
}
 
List Difference(List one, List two) {
    Item* temp = (Item*)malloc(sizeof(Item));
    temp = one.tail;
    while (two.amount) {
        if (one.tail->digit < two.tail->digit) {
            one.tail->prev->digit -= 1;
            one.tail->digit += 10;
            one.tail->digit -= two.tail->digit;
        }
        else {
            one.tail->digit -= two.tail->digit;
        }
        one.tail = one.tail->prev;
        two.tail = two.tail->prev;
        two.amount--;
    }
    one.tail = temp;
    return one;
 
}
 
List DivByTwo(List number) {
    Item* temp = (Item*)malloc(sizeof(Item));
    temp = number.head;
    while (number.head) {
 
        if (number.head->digit == 0) {
            number.head = number.head->next;
            number.head->prev = NULL;
 
        }
        if (number.head->digit % 2 == 1 && number.head->next) {
            number.head->next->digit += 10;
        }
        number.head->digit /= 2;
        number.head = number.head->next;
    }
 
    number.head = temp;
 
    return number;
}
 
int Counter(List number, int x) {
    Item* temp = (Item*)malloc(sizeof(Item));
    temp = number.head;
    int count = 0;
    while (number.head) {
        if (number.head->digit == x) {
            count++;
        }
        number.head = number.head->next;
    }
    return count;
}
 
List InBinary(List number) {
    List bin_number = { NULL,NULL,0 };
    while (number.tail->digit != 0) {
 
        Item* p = (Item*)malloc(sizeof(Item));
        p->digit = 0;
        if (number.tail->digit % 2 == 1) {
            p->digit = 1;
 
        }
 
 
        if (!bin_number.head) {
 
            p->next = p->prev = NULL;
            bin_number.head = bin_number.tail = p;
            bin_number.amount++;
        }
        else {
            p->prev = NULL;
            p->next = bin_number.head;
            bin_number.head->prev = p;
            bin_number.head = p;
            bin_number.amount++;
        }
 
        number = DivByTwo(number);
 
 
    }
    return bin_number;
}
 
List CreateNum(int pow) {
    List number = { NULL,NULL,0 };
    for (int i = 0; i < pow; i++)
    {
 
 
        if (!number.head) {
            Item* n = (Item*)malloc(sizeof(Item));
            n->digit = 2;
            n->next = n->prev = NULL;
            number.head = number.tail = n;
            number.amount++;
        }
        else {
            number = Calculation(number);
 
 
        }
    }
    return number;
}
 
void Print(List num) {
    Item* p = num.head;
    while (p) {
        printf("%d", p->digit);
        p = p->next;
    }
 
}
 
int main()
{
    List num_1 = CreateNum(39873);
    List num_2 = CreateNum(19936);
    List num_3 = Difference(num_1, num_2);
    num_3 = InBinary(num_3);
    int count_of_zero = Counter(num_3, 0);
    int count_of_one = Counter(num_3, 1);
    if (count_of_one - count_of_zero == 1) {
        printf("Число совершенное!");
    }
    else {
        printf("Число несовершенное!");
    }
    return 0;
}
