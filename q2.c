#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
	int value;
	struct node* next;
	struct node* prev;
};

struct node* createNode(int val)
{
	struct node* newNode = (struct node*)malloc(sizeof(struct node));
	newNode->value = val;
	newNode->next = NULL;
	newNode->prev = NULL;
	return newNode;
}

typedef struct list
{
	struct node* head;
	struct node* tail;
	struct node* left;
	struct node* right;
	int size;
}list;

struct list* createList()
{
	struct list* myList = (struct list*)malloc(sizeof(struct list));
	myList = (struct list*)malloc(sizeof(struct list));
	myList->head = myList->left = createNode(0);
	myList->tail = myList->right = createNode(0);
	myList->left->next = myList->right;
	myList->right->prev = myList->left;
	myList->size = 0;
	return myList;
}

struct list* myList;

void printList()
{
	if (myList != NULL)
	{
		struct node* tmp = myList->head;
		printf("[");
		while (tmp != NULL)
		{
			if (tmp == myList->tail) {
				printf("%d", tmp->value);
				printf("]\n");
				return;
			}
			else
				printf("%d, ", tmp->value);
			tmp = tmp->next;
		}
		if (tmp != myList->tail)
		{
			tmp = myList->right;
			while (tmp != NULL)
			{
				if (tmp == myList->tail)
					printf("%d", tmp->value);
				else
					printf("%d, ", tmp->value);
				tmp = tmp->next;
			}
		}
		printf("]\n");
	}
}

void nExtra(int n)
{
	if (myList != NULL)
	{
		for (int i = 0; i < n; i++)
		{
			struct node* newNode = createNode(-1);
			if (myList != NULL)
			{
				myList->right->prev = newNode;
				newNode->next = myList->right;
				myList->right = newNode;
				myList->size++;
			}
		}
		myList->left->next = myList->right;
		myList->right->prev = myList->left;
		struct node* tmp = myList->tail;
		while (tmp->value != -1)
		{
			tmp = tmp->prev;
		}
		myList->right = tmp->next;
	}
}

void freeList()
{
	if (myList != NULL)
	{
		struct node* tmp = myList->head;
		while (tmp != NULL)
		{
			struct node* ttmp = tmp;
			tmp = tmp->next;
			ttmp->prev = ttmp->next = NULL;
			free(ttmp);
		}
		myList->head = myList->left = NULL;
		myList->tail = myList->right = NULL;
		myList->size = 0;
		free(myList);
		myList = NULL;
	}
}

int getfreeSpaceSize()
{
	if (myList != NULL)
	{
		int count = 0;
		if (myList->left != NULL)
		{
			struct node* tmp = myList->left->next;
			while (tmp != NULL && tmp->value == -1)
			{
				count++;
				tmp = tmp->next;
			}
			return count;
		}
		if (myList->right != NULL)
		{
			struct node* tmp = myList->right->prev;
			while (tmp != NULL && tmp->value == -1)
			{
				count++;
				tmp = tmp->prev;
			}
			return count;
		}
		return count;
	}
	return 0;
}

void pullRight()
{
	struct node* tmp = myList->right;
	struct node* next = myList->right->next;
	myList->left->next = next;
	next->prev = myList->left;
	myList->right = next;
	tmp->prev = tmp->next = NULL;
	free(tmp);
	tmp = NULL;
}

void pullLeft()
{
	struct node* tmp = myList->left;
	struct node* prev = tmp->prev;
	myList->right->prev = prev;
	prev->next = myList->right;
	myList->left = prev;
	tmp->prev = tmp->next = NULL;
	free(tmp);
	tmp = NULL;
}

void freeNExtra(int n)
{
	if (myList != NULL)
	{		
		for (int i = 0; i < n; i++)
		{
			struct node* prev = myList->right->prev;
			struct node* tprev = prev->prev;
			tprev->next = myList->right;
			myList->right->prev = tprev;
			prev->next = prev->prev = NULL;
			free(prev);
			prev = NULL;
		}
	}
}

void push(int val)
{
	if (myList->left->next == myList->right)
	{
		nExtra(5);
	}
	if (getfreeSpaceSize() > 5)
	{
		freeNExtra(5);
	}
	if (val % 2 == 0)
	{
		struct node* prev = myList->right->prev;
		prev->value = val;
		myList->right = prev;
	}
	else
	{
		struct node* next = myList->left->next;
		next->value = val;
		myList->left = next;
	}
	myList->size++;
}

void pull(const char* side)
{
	if (myList->head == myList->left && myList->tail == myList->right)
	{
		printf("warning: no nodes to delete!\n");
		return;
	}
	if (myList->left->next == myList->right)
	{
		nExtra(5);
	}
	if ((strcmp(side, "L") == 0) || (strcmp(side, "l") == 0) || (strcmp(side, "S") == 0) || (strcmp(side, "s") == 0))
	{
		if (myList->head == myList->left)
		{
			if (myList->tail->prev == myList->tail)
			{
				printf("warning: no nodes to delete!\n");
				return;
			}
			myList->right->value = -1;
			myList->right = myList->right->next;
		}
		else
		{
			myList->left->value = -1;
			myList->left = myList->left->prev;
		}
	}
	else if ((strcmp(side, "R") == 0) || (strcmp(side, "r") == 0) || (strcmp(side, "H") == 0) || (strcmp(side, "h") == 0))
	{
		if (myList->tail == myList->right)
		{
			if (myList->head->next == myList->head)
			{
				printf("warning: no nodes to delete!\n");
				return;
			}
			myList->left->value = -1;
			myList->left = myList->left->prev;
		}
		else
		{
			myList->right->value = -1;
			myList->right = myList->right->next;
		}
	}
	if (getfreeSpaceSize() > 5)
	{
		freeNExtra(5);
	}
}

int main()
{
	myList = createList();
	printList();
	push(1);
	printList();
	push(12);
	printList();
	push(23);
	printList();
	push(34);
	printList();
	push(45);
	printList();
	push(56);
	printList();
	push(78);
	printList();
	pull("r");
	printList();
	pull("l");
	printList();
	pull("r");
	printList();
	pull("l");
	printList();	
	pull("l");
	printList();
	pull("l");
	printList();
	pull("r");
	printList();
	pull("r");
	printList();
}
