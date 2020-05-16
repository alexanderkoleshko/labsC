#include "List.h"
#include "PriorSource.h"
#include "PriorBank.h"
#define NULL 0


struct Deposit* deposit_creation(char* deposit_category, int balance) 
{
	struct Deposit* dep = (struct Deposit*)calloc(1, sizeof(struct Deposit));
	dep->dep_next = NULL;
	dep->deposit_category = deposit_category;
	dep->balance = balance;
	if (strcmp(deposit_category, "Savings contribution") == 0)
		dep->is_lock = 0;
	else if (strcmp(deposit_category, "Cumulative contribution") == 0)
		dep->is_lock = 1;
	else
		dep->is_lock = 3;
	return dep;
}

struct Node* node_creation(char* deposit_category,
							char* name, char* surname, char* issuing_authority,
							char* time_in, char* time_expired, char* passport_series,
							int balance, struct Node* prev, struct Node* next)
{
	struct Node* node = (struct Node*)calloc(1, sizeof(struct Node));
	node->next = next;
	node->prev = prev;
	node->account_number = hashing(passport_series);
	printf("account id: %lld\n", node->account_number);
	node->name = name;
	node->surname = surname;
	node->issuing_authority = issuing_authority;
	node->time_in = time_in;
	node->time_expired =  time_expired;
	node->passport_series = passport_series;
	node->dep_head = deposit_creation(deposit_category, balance);
	node->dep_size++;

	return node;
}

void list_creation(struct List* list)
{
	if (list == NULL)
	{
		printf("No information. Error list is NULL\n");
		return;
	}
	list->size = 0;
	list->head = NULL;
}

void show_node(struct List* list)
{
	if (list == NULL)
	{
		printf("No information. Error list is NULL\n");
		return;
	}
	struct Node* node = list->head;
	for (int i = 0; i < list->size; i++)
	{
		printf("%d: %s %s %lld\n", i + 1, node->surname, node->name, node->account_number);
		node = node->next;
	}
}

void show_dep(struct Node* node)
{
	if (node == NULL)
	{
		printf("No information. Error node is NULL\n");
		return;
	}
	struct Deposit* dep = node->dep_head;
	for (int i = 0; i < node->dep_size; i++)
	{
		printf("%d: %s.\n", i + 1, dep->deposit_category);
		dep = dep->dep_next;
	}
}

void add_deposit_(struct Deposit* dep, char* deposit_category, int balance)
{
	if (dep == NULL)
	{
		printf("No information. Error deposit is NULL\n");
		return;
	}
	struct Deposit* temp = dep;
	while (temp->dep_next != NULL)
	{
		temp = temp->dep_next;
	}
	temp->dep_next = deposit_creation(deposit_category, balance);
}

struct Deposit* find_deposit(struct Node* node, const int index)
{
	if (node == NULL)
	{
		printf("No information. Error node is NULL\n");
		return NULL;
	}
	int count = 0;
	struct Deposit* temp = node->dep_head;
	if (index > node->dep_size)
		return NULL;

	while (index != count)
	{
		temp = temp->dep_next;
		count++;
	}
	return temp;
}

struct Node* find_account(struct Node* node, unsigned long long int account_number)
{
	if (node == NULL)
	{
		printf("No information. Error node is NULL\n");
		return NULL;
	}
	struct Node* temp = node;
	while (temp->next != NULL)
	{
		if (temp->account_number == account_number)
		{
			break;
		}

		temp = temp->next;
	}
	if (temp->account_number == account_number)
	{
		return temp;
	}
	return NULL;
}

void find_surname(struct Node* node,const char* surname)
{
	if (node == NULL)
	{
		printf("No information. Error node is NULL\n");
		return NULL;
	}
	struct Node* temp = node;
	if (temp == NULL)
		return;
	do
	{
		if (strcmp(temp->surname, surname) == 0)
		{
			printf("%s %s %lld\n", node->surname, node->name, node->account_number);
		}

		temp = temp->next;
	} while (temp != NULL);
}

struct Node* find_dep(struct Node* node, char* passport_series)
{
	if (node == NULL)
	{
		printf("No information. Error node is NULL\n");
		return NULL;
	}
	struct Node* temp = node;
	while (temp->next != NULL)
	{
		if (temp->passport_series == passport_series)
		{
			break;
		}

		temp = temp->next;
	}
	if (temp->passport_series == passport_series)
	{
		return temp;
	}
	return NULL;
}

struct Node* add_deposit(struct Node* node, char* passport_series, char* deposit_category, int balance)
{
	if (node == NULL)
	{
		printf("No information. Error node is NULL\n");
		return NULL;
	}
	struct Node* temp = node;
	while (temp->next != NULL)
	{
		if (temp->passport_series == passport_series)
		{
			break;
		}

		temp = temp->next;
	}
	if (temp->passport_series == passport_series)
	{
		add_deposit_(temp->dep_head, deposit_category, balance);
		temp->dep_size++;
		return NULL;
	}
	return temp;
}

void push_back(char* deposit_category,
				char* name, char* surname, char* issuing_authority,
				char* time_in, char* time_expired, char* passport_series,
				int balance, struct List* list)
{
	if (list->head == NULL) {
		list->head = node_creation(deposit_category,
									name, surname, issuing_authority,
									time_in, time_expired, passport_series,
									balance, NULL, NULL);
	}
	else
	{
		struct Node* temp = add_deposit(list->head, passport_series, deposit_category, balance);
		if (temp == NULL)
			return;
		temp->next = node_creation(deposit_category,
									name, surname, issuing_authority,
									time_in, time_expired, passport_series,
									balance, temp, NULL);
	}
	list->size++;
}

int GetSize(struct List* list)
{
	if (list == NULL)
	{
		printf("No information. Error list is NULL\n");
		return 0;
	}
	return list->size;
}


struct Deposit* pop_dep(struct Node* node, const int index)
{
	if (node == NULL)
	{
		printf("No information. Error node is NULL\n");
		return NULL;
	}
	int counter = 0;
	struct Deposit* temp = node->dep_head;
	if (node->dep_size < index) {
		return node->dep_head;
	}
	else if (index == 0)
	{
		node->dep_head = node->dep_head->dep_next;
		free(temp->deposit_category);
		free(temp);
		node->dep_size--;
		return node->dep_head;
	}
	else
	{
		while (node->dep_size != counter)
		{
			if (counter == index - 1) {
				break;
			}
			temp = temp->dep_next;
			counter++;
		}
		struct Deposit* del = temp->dep_next;
		temp = temp->dep_next->dep_next;
		free(del->deposit_category);
		free(del);
		node->dep_size--;
		return node->dep_head;
	}

}

void free_pop(struct List* list, struct Node* temp, int index)
{
	temp->dep_head = pop_dep(temp, index);
	if (temp->dep_size == 0)
	{
		if (temp->next != NULL)
		{
			temp->next->prev = temp->prev;
		}
		if (temp->prev != NULL)
		{
			temp->prev->next = temp->next;
		}
		else
		{
			list->head = temp->next;
		}
		char* txt = to_string_txt(temp->account_number);
		remove(txt);
		free(txt);
		free(temp->issuing_authority);
		free(temp->name);
		free(temp->surname);
		free(temp->time_expired);
		free(temp->time_in);
		free(temp->passport_series);
		free(temp);
		list->size--;
		return 0;
	}
}

int pop(struct List* list, const char* passport_series, const int index)
{
	if (list == NULL)
	{
		printf("No information. Error list is NULL\n");
		return 0;
	}
	int counter = 0;
	struct Node* temp = list->head;
	while (list->size != counter)
	{
		if (strcmp(temp->passport_series, passport_series) == 0) 
		{
			break;
		}
		temp = temp->next;
		counter++;
	}
	if (temp == NULL)
		return 0;
	free_pop(list, temp, index);
	printf("successfull\n");
	return 1;

}

void clear(struct List* list, const char* passport_series)
{
	if (list == NULL)
	{
		printf("No information. Error list is NULL\n");
		return;
	}
	while (list->size)
	{
		pop(list, passport_series, 0);
	}
}

struct Node* GetNode(struct List* list, const int index)
{
	if (list == NULL)
	{
		printf("No information. Error list is NULL\n");
		return NULL;
	}
	int counter = 0;
	struct Node* temp = list->head;
	if (index > list->size) {
		return NULL;
	}
	while (list->size != counter)
	{
		if (counter == index)
		{
			return temp;
		}
		temp = temp->next;
		counter++;
	}
	return NULL;
}

void sort(struct Node* node)
{
	if (node == NULL)
	{
		printf("No information. Error node is NULL\n");
		return;
	}
	struct Deposit* result = NULL;
	struct Deposit* result_end = NULL;
	int size = node->dep_size;
	for(int i = 0; i < node->dep_size; i++)
	{
		struct Deposit* dep = node->dep_head;
		struct Deposit* max = node->dep_head;
		for (int j = 0; j < size - 1; j++)
		{
			if (dep->dep_next->balance > max->dep_next->balance)
			{
				max = dep;
			}
			dep = dep->dep_next;
		}
		struct Deposit* temp;
		if (max == node->dep_head)
		{
			temp = max;
			node->dep_head = max->dep_next;
		}
		else
		{
			temp = max->dep_next;
			max->dep_next = max->dep_next->dep_next;
		}

		if (result == NULL)
		{
			result = temp;
			result_end = result;
		}
		result_end->dep_next = temp;
		result_end = result_end->dep_next;
		size--;
	}
	node->dep_head = result;
	printf("successfull\n");
	return;
}

void free_list(struct List* list)
{
	if (list == NULL)
	{
		printf("No information. Error list is NULL\n");
		return;
	}
	do
	{
		int counter = 0;
		struct Node* temp = list->head;
		if (temp == NULL)
			return;
		int size = temp->dep_size;
		for (int i = 0; i < size; i++)
		{
			free_pop(list, temp, 0);
		}
	} while (list->size);
}

