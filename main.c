#include <stdio.h>
#include <stdlib.h>

/*
    Node is structure for individual data containers (that holds data)
    that it points to other nodes using next.
*/

/*
    Used this definition which helps us to write things like this
    Node* node;
    instead of redundant writing 
    struct Node* node;
    for simplicity, you can say that typedef replaces all instances
    of "Node" in the code to "struct Node"
*/

typedef struct Node Node;

struct Node {
    int data;
    struct Node* next;
};

/*
    A linked list is collection of nodes, and each node conatins data, 
    as well as a pointer to another node
    LinkedList structure stores the current status of a linked list
*/

typedef struct {
    Node* start;
    Node* end;
    unsigned int size;
} LinkedList;

/*
    Creates a Node and fills it with the data provided
    Return a pointer to the memory where the Node instance
    is stored
*/

Node* createNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

/*
    safe construction of LinkedList instead of simple declaration.
    Assigns valid value to the data member for safe working of the
    program
*/

LinkedList createList() {
    LinkedList list;
    list.start = NULL;
    list.end = NULL;
    list.size = 0;
    return list;
}

/*
    adds a node at the end of linked list with the data provided
    Also changes the end pointer of linkedlist to the newly added node
    Increases the size of linked list
    Linked list before this operation
      Start                        End
    *********     *********     *********
    * Node1 * ==> * Node2 * ==> * Node3 *
    *********     *********     *********
    Linked list after this oepration
      Start                                      End
    *********     *********     *********     *********
    * Node1 * ==> * Node2 * ==> * Node3 * ==> * Node4 *
    *********     *********     *********     *********
*/

void push_back(LinkedList* const list, int data) {

    if(list->start == NULL) {
        list->start = createNode(data);
        list->end = list->start;
    } else {
        list->end->next = createNode(data);
        list->end = list->end->next;
    }

    ++list->size;
}

/*
    removes a node from the linked list
    if index == 0, changes start pointer of linkedlist to next node
    index can be any value between 0 to list.size
    if pop is used as pop(&list, 0), then below is the representation
    Before the operation
      Start                        End
    *********     *********     *********
    * Node1 * ==> * Node2 * ==> * Node3 *
    *********     *********     *********
    After the operation
     deleted        Start         End
    ---------     *********     *********
    | Node1 |     * Node2 * ==> * Node3 *
    ---------     *********     *********
    if pop is used as pop(&list, 1), then below is the representation
    Before the operation
      Start                        End
    *********     *********     *********
    * Node1 * ==> * Node2 * ==> * Node3 *
    *********     *********     *********
    After the operation
      Start        deleted         End
    *********     ---------     *********
    * Node1 *     | Node2 |     * Node3 *
    *********     ---------     *********
        |                           ^
        |===========================|
       points to next node's next node
*/

void pop(LinkedList* const list, const unsigned int index) {
    if(index >= list->size) {
        printf("Error: out of range");
        exit(1);
    }

    Node* cur = list->start;

    if(index == 0) {
        list->start = cur->next;
        free(cur);
    } else {
        for(int i=0; i<index-1; ++i, cur = cur->next) {}

        Node* tmp = cur->next;
        cur->next = tmp->next;
        free(tmp);
    }

    --list->size;
}

/*
    returns the data stored in the linkedlist as index "index"
    index can be any value between 0 to list->size else an error 
    is thrown
*/

int get(LinkedList* const list, const unsigned int index) {

    if(index >= list->size) {
        printf("Error: out of range");
        exit(1);
    }

    Node* cur = list->start;

    for(int i=0; i<index; ++i, cur = cur->next) {}

    return cur->data;
}

/*
    Safely destroys all the nodes present in linkedlist
*/

void destroyList(LinkedList* list) {

    for(Node* cur = list->start; cur != NULL; ) {
        Node* tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    list->start = NULL;
    list->end = NULL;
    list->size = 0;

    list = NULL;
}

/*
    Self explanatory
*/

void print(LinkedList* const list) {
    for(int i=0; i<list->size; ++i) {
        printf("%d ", get(list, i));
    }
}

int main() {

    LinkedList list = createList();

    push_back(&list, 1);
    push_back(&list, 2);
    push_back(&list, 3);
    push_back(&list, 4);
    push_back(&list, 5);
    push_back(&list, 6);
    push_back(&list, 7);

    print(&list);   // should print 1 2 3 4 5 6 7

    pop(&list, 0);
    pop(&list, 3);

    printf("\n");
    print(&list);   // should print 2 3 4 6 7   

    destroyList(&list);
}
