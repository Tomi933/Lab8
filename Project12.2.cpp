#include <iostream>
#include <Windows.h>
using namespace std;

struct Elem {
    int info;
    Elem* link;
};


void push(Elem*& top, int value) {
    Elem* tmp = new Elem;
    tmp->info = value;
    tmp->link = top;
    top = tmp;
}


void createList(Elem*& head, const int arr[], int size) {
    head = 0;
    for (int i = size - 1; i >= 0; --i) {
        push(head, arr[i]);
    }
}


void printList(Elem* head) {
    while (head != 0) { 
        cout << head->info << " ";
        head = head->link;
    }
    cout << endl;
}

int insertAfterValue(Elem*& head, int V1, int V2) {
    
    int k = 0;

    Elem* current = head;
    while (current != 0) {
        if (current->info == V1) {
            Elem* newNode = new Elem;
            newNode->info = V2;
            newNode->link = current->link;
            current->link = newNode;
            current = newNode->link;
            k++;
        }
        else {
            current = current->link;
        }
    }
    return k;
}

void freeList(Elem*& head) {
    while (head != 0) {
        Elem* tmp = head;
        head = head->link;
        delete tmp;
    }
}


int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Elem* list = 0;
    int values[] = { 1, 2, 3, 2, 4, 2, 5 };
    int size = sizeof(values) / sizeof(values[0]);
    int V1 = 2;
    int V2 = 99;

    createList(list, values, size);
    cout << "Початковий список: ";
    printList(list);

    insertAfterValue(list, V1, V2);
    cout << "Список після вставки після " << V1 << " елемента " << V2 << ": ";
    printList(list);

    freeList(list);
    return 0;
}
