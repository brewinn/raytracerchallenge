#include "LinkedList.h"
#include <stdlib.h>

typedef struct Node{
	void* data;
	struct Node* next;
} Node;

struct LinkedListStruct{
	Node* head;
	int length;
};

LinkedList LinkedList_Create()
{
	LinkedList list = calloc(1, sizeof(struct LinkedListStruct));
	list->head = NULL;
	int length = 0;
	return list;
}

void LinkedList_Destroy(LinkedList* listPtr)
{
	if(listPtr == NULL)
		return;

	LinkedList list = *listPtr;
	Node* node = list->head;
	if(node == NULL)
	{
		free(list);
		*listPtr = NULL;
		return;
	}
	while(node->next != NULL)
	{
		Node* nextNode = node->next;
		free(node);
		node = nextNode;
	}
	free(node);
	free(list);
	*listPtr = NULL;
}

int LinkedList_GetLength(const LinkedList list)
{
	return list->length;
}

void* LinkedList_ValueAt(const LinkedList list, int index)
{
	if(index+1 > list->length)
		return NULL;

	Node* node = list->head;
	for(int i = 0; i < index; i++)
		node = node->next;
	return node->data;
}

void LinkedList_Append(LinkedList list, void* data)
{
	list->length++;
	Node* newNode = malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = NULL;

	if(list->head == NULL)
	{
		list->head = newNode;
		return;
	}
	
	Node* runner = list->head;
	while(runner->next != NULL)
		runner = runner->next;
	runner->next = newNode;
}

void LinkedList_Prepend(LinkedList list, void* data)
{
	list->length++;
	Node* newNode = malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = list->head;
	list->head = newNode;
}

void LinkedList_Insert(LinkedList list, int index, void* data)
{
	if(index <= 0)
	{
		LinkedList_Prepend(list, data);
		return;
	}
	if(index >= list->length)
	{
		LinkedList_Append(list, data);
		return;
	}
	list->length++;
	Node* node = list->head;
	for(int i = 0; i < index-1; i++)
	{
		node = node->next;
	}
	Node* newNode = malloc(sizeof(Node));
	newNode->data = data;
	newNode->next = node->next;
	node->next = newNode;
}

void* LinkedList_RemoveBeginning(LinkedList list)
{
	int length = list->length;
	if(length == 0)
		return NULL;
	list->length--;
	void* nodeValue = list->head->data;
	if(length == 1)
	{
		free(list->head);
		list->head = NULL;
		return nodeValue;
	}
	Node* oldHead = list->head;
	list->head = list->head->next;
	free(oldHead);
	return nodeValue;
}

void* LinkedList_RemoveEnd(LinkedList list)
{
	int length = list->length;
	if(length == 0)
		return NULL;
	list->length--;
	void* nodeValue = list->head->data;
	if(length == 1)
	{
		free(list->head);
		list->head = NULL;
		return nodeValue;
	}
	Node* node = list->head;
	while(node->next->next != NULL)
		node = node->next;
	free(node->next);
	node->next = NULL;
	return nodeValue;
}

void* LinkedList_Remove(LinkedList list, int index)
{
	if(index <= 0)
		return LinkedList_RemoveBeginning(list);
	if(index >= list->length)
		return LinkedList_RemoveEnd(list);
	list->length--;
	Node* node = list->head;
	for(int i = 0; i < index-1; i++)
	{
		node = node->next;
	}
	Node* nodeToDelete = node->next;
	void* nodeValue = nodeToDelete->data;
	node->next = nodeToDelete->next;
	free(nodeToDelete);
	return nodeValue;
}
