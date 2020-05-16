#include "PriorBank.h"
#include "List.h"
#include "PriorSource.h"
#include "Check.h"

void show_menu(void)
{
	printf("Menu\n");
	printf("1 add account\n");
	printf("2 add deposit\n");
	printf("3 remove account\n");
	printf("4 remove deposit\n");
	printf("5 Balance\n");
	printf("6 put money\n");
	printf("7 get money\n");
	printf("8 transfer money\n");
	printf("9 account statement\n");
	printf("10 calculate interest rate: \n");
	printf("11 Search\n");
	printf("12 Sort deposit\n");
	printf("13 exit\n");
}

void add_account(struct List* list)
{
	char* name = check_string("Please Enter name in Latin: ", "qwertyuioplkjhgfdsazxcvbnmQWERTYUIOPLKJHGFDSAZXCVBNM");
	char* surname = check_string("Please Enter surname in Latin: ", "qwertyuioplkjhgfdsazxcvbnmQWERTYUIOPLKJHGFDSAZXCVBNM");
	char* issuing_authority = check_string("Please Enter issuing authority: ", "qwertyuioplkjhgfdsazxcvbnmQWERTYUIOPLKJHGFDSAZXCVBNM");
	char* passport_series = check_string("Please Enter passport series: ", "QWERTYUIOPLKJHGFDSAZXCVBNM1234567890");
	char* time_in = get_time("Please Enter date of issue passport(##.##.####): ");
	char* time_expired = get_time("Please Enter passport validity(##.##.####): ");
	char* deposit_category = check_deposit();
	int Balance = check("Please Enter deposit summ: ", -1, 10000);
	push_back(deposit_category,
		name, surname, issuing_authority,
		time_in, time_expired, passport_series,
		Balance, list);
}


int main(void)
{
	struct List* list = (struct list*)calloc(1, sizeof(struct List));
	int switch_menu;
	unsigned long long int account_number;
	char* passport_series;
	int sum;
	char* surname;
	struct Node* account;
	while (1)
	{
		switch_menu = 0;
		show_menu();
		switch_menu = check("", -1, 14);
		switch (switch_menu)
		{
			case 1:
				add_account(list);
				break;
			case 2:
				account_number = check_long("Please Enter account: ");
				struct Node* account = find_account(list->head, account_number);
				if (account != NULL)
				{
					char* deposit_category = check_deposit();
					int Balance = check("Please Enter deposit summ: ", -1, 10000);
					add_deposit(account, account->passport_series, deposit_category, Balance);
				}
				else
				{
					printf("Invalid account.\n");
				}
				break;
			case 3:
			case 4:
				account_number = check_long("Please Enter account(you will lose all your money in deposit): ");
				account = find_account(list->head, account_number);
				if (account != NULL)
				{
					passport_series = check_string("Please Enter passport series(you will lose all your money in deposit): ",
						"QWERTYUIOPLKJHGFDSAZXCVBNM1234567890");
					if (strcmp(account->passport_series,passport_series) != 0)
					{
						printf("Error. Invalid passport_series.\n");
						break;
					}
					if (switch_menu == 4)
					{
						show_dep(account);
						int index = check("Please Enter index: ", 0, account->dep_size + 1);
						index--;
						pop(list, passport_series, index);
					}
					else
					{
						while (pop(list, passport_series, 0));
					}
					free(passport_series);
				}
				else
				{
					printf("Invalid account.\n");
				}
				break;
			case 5:
				account_number = check_long("Please Enter account: ");
				get_balance(list, account_number);
				break;
			case 6:
				account_number = check_long("Please Enter account: ");
				sum = check("Please Enter deposit summ: ", -1, 10000);
				put_money(list, account_number, sum);
				break;
			case 7:
				account_number = check_long("Please Enter account: ");
				sum = check("Please Enter deposit summ: ", -1, 10000);
				get_money(list, account_number, sum);
				break;
			case 8:
				account_number = check_long("Please Enter account from we take: ");
				unsigned long long int to= check_long("Please Enter account to we add: ");
				sum = check("Please Enter deposit summ: ", -1, 10000);
				transfer(list, account_number, to, sum);
				break;
			case 9:
				account_number = check_long("Please Enter account: ");
				show_history(account_number);
				break;
			case 10:
				sum = check("Please Enter deposit summ: ", -1, 10000);
				char* from_date = get_time("Please Enter deposit openning date(##.##.####): ");
				char* to_date = get_time("Please Enter deposit closing date(##.##.####): ");
				printf("Result: %lf\n", sum + get_percent(sum, from_date, to_date));
				free(from_date);
				free(to_date);
				break;
			case 11:
				surname = check_string("Please Enter surname in Latin: ", "qwertyuioplkjhgfdsazxcvbnmQWERTYUIOPLKJHGFDSAZXCVBNM");
				find_surname(list->head, surname);
				free(surname);
				break;
			case 12:
				account_number = check_long("Please Enter account: ");
				account = find_account(list->head, account_number);
				sort(account);
				break;
			case 13:
				free_list(list);
				free(list);
				return 0;
				break;
			default:
				break;
		}
		
	}
}
