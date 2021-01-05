#include <stdio.h>
#include <stdlib.h>

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
	myList->size = 2;
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
			if (tmp == myList->tail)
				printf("%d", tmp->value);
			else
				printf("%d, ", tmp->value);
			tmp = tmp->next;
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
		myList->right = myList->tail;
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

int main()
{	
	myList = createList();
	printList();
	nExtra(5);
	printList();
	freeList();
}
