#ifndef __LINKEDLIST__
#define __LINKEDLIST__

typedef struct LinkedListStruct *LinkedList;

LinkedList LinkedList_Create();
int LinkedList_GetLength(const LinkedList list);
void LinkedList_Destroy(LinkedList *listPtr);
void *LinkedList_ValueAt(const LinkedList list, int index);
void LinkedList_Append(LinkedList list, void *data);
void LinkedList_Prepend(LinkedList list, void *data);
void LinkedList_Insert(LinkedList list, int index, void *data);
void *LinkedList_RemoveBeginning(LinkedList list);
void *LinkedList_RemoveEnd(LinkedList list);
void *LinkedList_Remove(LinkedList list, int index);

#endif /* __LINKEDLIST__ */
