#include "PriorSource.h"
#include "PriorBank.h"
#include "List.h"
#include "Check.h"
#include <time.h>

unsigned long long int hashing_(char* key)
{
	int count = strlen(key);
	count += 17;
	char* temp = (char*)calloc(count + 16, sizeof(char));
	temp = strcpy(temp, key);
	strcpy((temp + count - 17), "3Ogh45TH24oEQWE");
	int length_hash = 10;
	int mod_hash = 100000000;
	const int HEX = 16;
	unsigned long long int hash = 0, p = temp[0];
	for (int i = 0; i < count; i++)
	{
		p *= (p + (int)temp[i]);
		hash += ((int)temp[i] * p);
		if (hash > mod_hash* mod_hash)
		{
			hash = hash / mod_hash + hash % mod_hash;
			p = temp[0];
		}
	}
	int i = 0;
	int hash_count = count;
	while (hash_count < length_hash)
	{
		hash += (((int)temp[i] * i + (int)temp[i - 1] % HEX + hash_count * hash) % 10) * count;
		i++;
		if (i > count)
		{
			i = 0;
		}
		hash_count++;
	}
	return hash;
}

unsigned long long int hashing(char* key)
{
	return hashing_(key);
}

char* lltoa(long long val, int base) {

	static char buf[64] = { 0 };

	int i = 62;
	int sign = (val < 0);
	if (sign) val = -val;

	if (val == 0) return "0";

	for (; val && i; --i, val /= base) {
		buf[i] = "0123456789abcdef"[val % base];
	}

	if (sign) {
		buf[i--] = '-';
	}
	return &buf[i + 1];

}

char* to_string_txt(unsigned long long int account)
{
	unsigned long long int temp = account;
	int count = 0;
	while (temp)
	{
		temp /= 10;
		count++;
	}
	char* result = (char*)calloc(count + 5, sizeof(char));
	if (result == NULL)
		return NULL;

	strcpy(result, lltoa(account, 10));
	strcpy((result + count), ".txt");
	return result;
}

int difference_years(char* pattern)
{
	char* temp = (char*)calloc(5, sizeof(char));
	for (int i = 6, j = 0; i < 10; i++, j++)
	{
		temp[j] = pattern[i];
	}
	struct tm* m_time;
	time_t t = time(NULL);
	m_time = localtime(&t);
	int year = atoi(temp);
	free(temp);
	if (year < m_time->tm_year + 1900)
		return 1;
	else
		return 0;
}


void delete_string(unsigned long long int account)
{
	char* txt = to_string_txt(account);
	FILE* f = fopen(txt, "r");
	if (f != NULL) {
		int const size = 1024;
		char pattern[1024];

		fseek(f, 0, SEEK_END);
		char* story_data = (char*)calloc(ftell(f) + 1, sizeof(char));
		char* ptr = story_data;
		*ptr = 0;
		fseek(f, 0, SEEK_SET);

		while (fgets(pattern, size, f)) {
			if (difference_years(pattern) == 0) {
				strcat(ptr, pattern);
				ptr += strlen(pattern);
			}
		}

		fclose(f);
		f = fopen(txt, "w");
		fputs(story_data, f);
		fclose(f);
		free(txt);

		free(story_data);
	}

}

void load_to_file(unsigned long long int account, const char* what, int sum)
{
	delete_string(account);
	FILE* fp;
	struct tm* m_time;
	time_t t = time(NULL);
	m_time = localtime(&t);
	char* txt = to_string_txt(account);
	fp = fopen(txt, "a+t");
	if (fp == NULL)
	{
		printf("Error read file");
		return;
	}
	fprintf(fp, "%02d.%02d.%02d account id: %lld. What happend: %s %d \n", m_time->tm_mday, m_time->tm_mon + 1, 1900 + m_time->tm_year, account, what, sum);
	fclose(fp);
	free(txt);
}

void get_balance(struct List* list, unsigned long long int account_number)
{
	struct Node* temp = find_account(list->head, account_number);
	if (temp == NULL)
	{
		printf("invalid account");
		return;
	}
	else
	{
		show_dep(temp);
		int index_deposit = check("Please enter index: ", 0, temp->dep_size + 2);
		index_deposit--;
		struct Deposit* dep = find_deposit(temp, index_deposit);
		if (dep == NULL)
		{
			printf("invelid deposit\n");
			return;
		}
		printf("Balance: %d\n", dep->balance);
		load_to_file(account_number, "Check Balance: ", dep->balance);
	}
}

void put_money(struct List* list, unsigned long long int account_number, int sum)
{
	struct Node* temp = find_account(list->head, account_number);
	if (temp == NULL)
	{
		printf("invalid account\n");
		return;
	}
	else
	{
		show_dep(temp);
		int index_deposit = check("Please enter number: ", 0, temp->dep_size + 2);
		index_deposit--;
		struct Deposit* dep = find_deposit(temp, index_deposit);
		if (dep == NULL || dep->is_lock == 0)
		{
			printf("invelid deposit or cant add deposit\n");
			return;
		}
		dep->balance += sum;
		printf("money was added. Balance: %d\n", dep->balance);
	}
	load_to_file(account_number, "money was added to account: +", sum);
}

void get_money(struct List* list, unsigned long long int account_number, int sum)
{
	struct Node* temp = find_account(list->head, account_number);
	if (temp == NULL)
	{
		printf("invalid passport series\n");
		return;
	}
	else
	{
		show_dep(temp);
		int index_deposit = check("Please enter number: ", 0, temp->dep_size + 2);
		index_deposit--;
		struct Deposit* dep = find_deposit(temp, index_deposit);
		if (dep == NULL || dep->is_lock == 1 || dep->balance < sum)
		{
			printf("invelid deposit or cant get deposit");
			return;
		}
		dep->balance -= sum;
		printf("money debited from your account. Balance: %d\n", dep->balance);
		load_to_file(account_number, "money debited account: -", sum);
	}
}

double get_percent(int sum,const char* from, const char* to)
{
	int day[2] = { (int)(from[0]) * 10 + (int)(from[1]), (int)(to[0]) * 10 + (int)(to[1]) };
	int year[2] = { (int)(from[3]) * 10 + (int)(from[4]), (int)(to[3]) * 10 + (int)(to[4]) };
	int month[2] = { (int)(from[6]) * 1000 + (int)(from[7]) * 100 + (int)(from[8]) * 10 + (int)(from[9]), (int)(to[6]) * 1000 + (int)(to[7]) * 100 + (int)(to[8]) * 10 + (int)(to[9]) };
	int res_year = year[1] - year[0];
	int res_month = month[1] - month[0];
	int res_day = day[1] - day[0];
	if (res_day < 0)
	{
		res_day += 30;
		res_month--;
	}
	if (res_month < 0)
	{
		res_month += 12;
		res_year--;
	}
	if (res_year < 0)
	{
		printf("error incorrect date\n");
		return 0;
	}
	int time = res_day + res_month * 30 + res_year * 365;
	return (sum * 11.5 * time) / (365 * 100);
}

void transfer(struct List* list, unsigned long long int from, unsigned long long int to, int sum)
{
	struct Deposit* dep1;
	struct Node* temp = find_account(list->head, from);
	if (temp == NULL)
	{
		printf("invalid account\n");
		return;
	}
	else
	{
		show_dep(temp);
		int index_deposit = check("Please enter number: ", 0, temp->dep_size + 2);
		index_deposit--;
		dep1 = find_deposit(temp, index_deposit);
	}
	struct Deposit* dep2;
	temp = find_account(list->head, to);
	if (temp == NULL)
	{
		printf("invalid account\n");
		return;
	}
	else
	{
		show_dep(temp);
		int index_deposit = check("Please enter number: ", 0, temp->dep_size + 2);
		index_deposit--;
		dep2 = find_deposit(temp, index_deposit);
	}

	if (dep1 != NULL && dep1->is_lock != 0 && dep2 != NULL && dep2->is_lock != 1 && sum < dep1->balance)
	{
		dep1->balance -= sum;
		dep2->balance += sum;
		load_to_file(from, "money debited account: -", sum);
		load_to_file(to, "money was added to account: +", sum);
		printf("succesfull\n");
	}
	else
	{
		printf("Error to tranfer money.\n");
	}
}



void show_history(unsigned long long int account)
{
	char* txt = to_string_txt(account);
	FILE* f = fopen(txt, "r");
	if (f != NULL) 
	{
		int const size = 1024;
		char pattern[1024];

		fseek(f, 0, SEEK_SET);

		while (fgets(pattern, size, f))
		{
			printf(pattern);
		}

		fclose(f);
	}
	free(txt);
}
