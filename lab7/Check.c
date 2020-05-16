#include "Check.h"
#include "List.h"
#include "PriorSource.h"
#include "PriorBank.h"
int check_time(char* str)
{
	char time_all[] = "1234567890";
	int leng = strlen(str);
	if (leng != 10) return 1;
	if (strchr("0123", str[0]) == NULL) return 1;
	if (str[0] == '3' && strchr("01", str[1]) == NULL) return 1;
	if (strchr(time_all, str[1]) == NULL) return 1;
	if (str[2] != '.') return 1;
	if (strchr("01", str[3]) == NULL) return 1;
	if (str[3] == '1' && strchr("012", str[4]) == NULL) return 1;
	if (strchr(time_all, str[4]) == NULL) return 1;
	if (str[5] != '.') return 1;
	for (int i = 6; i < 10; i++)
	{
		if (strchr(time_all, str[i]) == NULL) return 1;
	}
	return 0;
}

int check_eng(char* str, const char* eng)
{
	int leng = strlen(str);
	for (int i = 0; i < leng; i++)
	{
		if (strchr(eng, str[i]) == NULL) return 1;
	}
	return 0;
}

char* check_deposit(void)
{
	printf("1 Savings contribution\n");
	printf("2 Cumulative contribution\n");
	printf("3 Specialized contribution\n");
	int index = check("Enter number: ", 0, 4);
	char* temp;
	switch (index)
	{
		case 1:
			temp = (char*)calloc(21, sizeof(char));
			strcpy(temp, "Savings contribution");
			return temp;
		case 2:
			temp = (char*)calloc(24, sizeof(char));
			strcpy(temp, "Cumulative contribution");
			return temp;
		case 3:
			temp = (char*)calloc(25, sizeof(char));
			strcpy(temp, "Specialized contribution");
			return temp;
	}
}

char* get_time(const char* str)
{
	char* time = (char*)calloc(11, sizeof(char));
	do
	{
		time = check_string(str, "1234567890,.");
		if (check_time(time) == 0)
			break;
		printf("Error. Invalid date.\n");
	} while (1);
	return time;
}

char* check_string(const char* funcpointer, const char* eng)
{
	char* str = (char*)calloc(265, sizeof(char));
	do
	{
		printf(funcpointer);
		scanf("%s", str);
		rewind(stdin);
		if (!check_eng(str, eng))
			break;
		printf("Invalid Text.\n");
	} while (1);
	return str;
}

unsigned long long int check_long(const char* funcpointer)
{
	unsigned long long int num;
	char temp = '\n';
	do
	{
		printf("%s\n", funcpointer);
		if (scanf("%lld%c", &num, &temp) == 2 && temp == '\n')
		{
			break;
		}
		printf("Error: 0x51267, Incorrect input. Press any key to continue\n");
		rewind(stdin);
		getchar();
		system("cls");

	} while (1);
	return num;
}

int check(const char* funcpointer, int min, int max)
{
	int num;
	char temp = '\n';
	do
	{
		printf("%s\n", funcpointer);
		if (scanf("%d%c", &num, &temp) == 2 && temp == '\n' && num > min && num < max)
		{
			break;
		}
		printf("Error: 0x51267, Incorrect input. Press any key to continue\n");
		rewind(stdin);
		getchar();

	} while (1);
	return num;
}
