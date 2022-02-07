#include <iostream>
using namespace std;

class stackNode {
    //class for stack element which is SLL
public:
    int data; //data
    stackNode* next; //next pointer
    stackNode(int a) { //constructor
        data = a;
        next = NULL;
    }
};

stackNode* top = NULL; //top of stack initialized to NULL
int stackSize = 0;// size of stack initialized to 0


void push(int x) { //push operation

    stackNode* node = (stackNode*)(malloc(sizeof(stackNode)));
    node->data = x;
    node->next = top;
    top = node;
    cout << x << " is pushed\n";
    stackSize++;
}

bool isEmpty() { //isEmpty function
    if (top == NULL && stackSize == 0)
        return true;
    else
        return false;
}

int pop() { //pop operation

    if (isEmpty()) {
        cout << "stack is empty\n";
        return INT_MIN;
    }
    else {
        stackSize--;
        int temp = top->data;
        stackNode* tempNode = top;
        top = top->next;
        free(tempNode);
        return temp;
    }
}

int top_stack() { //top() operation
    if (isEmpty()) {
        cout << "stack is empty\n";
        return INT_MIN;
    }
    else {
        return top->data;
    }

}

void print(Node* node)
{
    while (node != NULL) {
        cout << node->data << " ";
        node = node->next;
    }
}

int main()
{
    /* Start with the empty list */
    Node* res = NULL;
    Node* head = NULL;

    /* Let us create a unsorted linked lists to test the functions
Created lists shall be a: 2->3->20->5->10->15 */
    push(15);
    push(10);
    push(5);
    push(20);
    push(3);
    push(2);

    /* Sort the above created Linked List */
   // MergeSort(&head);

    cout << "Sorted Linked List is: \n";
    printList(head);

    return 0;
}
