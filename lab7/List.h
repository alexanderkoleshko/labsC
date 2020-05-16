#pragma once

struct List
{
	struct Node
	{
		struct Node* next;
		struct Node* prev;
		unsigned long long int account_number;
		char* name;
		char* surname;
		char* issuing_authority;
		char* time_in;
		char* time_expired;
		char* passport_series;

		struct Deposit
		{
			int balance;
			char* deposit_category;
			int is_lock;
			struct Deposit* dep_next;
		};


		struct Deposit* dep_head;
		int dep_size;
	};
	int size;
	struct Node* head;
};

struct Stack
{
	int level;
	struct Deposit* dep;
};

void push_back(char* deposit_category,
				char* name, char* surname, char* issuing_authority,
				char* time_in, char* time_expired, char* passport_series,
				int balance, struct List* list);

int pop(struct List* list, const char* passport_series, const int index);

void clear(struct List* list, const char* passport_series);
struct Node* find_account(struct Node* node, unsigned long long int account_number);
struct Deposit* find_deposit(struct Node* node, const int index);

int GetSize(struct List* list);
void show_dep(struct Node* node);
void show_node(struct List* list);
void find_surname(struct Node* node, const char* surname);

struct Node* GetNode(struct List* list, const int index);
void free_list(struct List* list);
void sort(struct Node* node);