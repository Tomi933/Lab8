#include <iostream>
#include <Windows.h>
using namespace std;

struct Elem {
    int info;
    Elem* link;
};

// Додавання вузла на початок списку
void push(Elem*& top, int value) {
    Elem* tmp = new Elem;
    tmp->info = value;
    tmp->link = top;
    top = tmp;
}

// Видалення вузла з початку списку
int pop(Elem*& top) {
    if (!top) return -1;
    Elem* tmp = top->link;
    int value = top->info;
    delete top;
    top = tmp;
    return value;
}

// Рекурсивне створення списку з масиву
void createListRecursive(Elem*& head, const int arr[], int size, int index = 0) {
    if (index >= size) return;
    push(head, arr[index]); // спочатку додай, потім — далі
    createListRecursive(head, arr, size, index + 1);
}


// Рекурсивне виведення списку
void printListRecursive(Elem* head) {
    if (!head) {
        cout << endl;
        return;
    }
    cout << head->info << " ";
    printListRecursive(head->link);
}

// Рекурсивна вставка V2 після кожного V1
int insertAfterValueRecursive(Elem*& node, int V1, int V2, int& k) {
    if (!node) return k;

    if (node->info == V1) {
        Elem* newNode = new Elem;
        newNode->info = V2;
        newNode->link = node->link;
        node->link = newNode;
        k++;
        insertAfterValueRecursive(newNode->link, V1, V2, k);
    }
    else {
        insertAfterValueRecursive(node->link, V1, V2, k);
    }

    return k;
}


// Рекурсивне очищення списку з використанням pop
void freeListRecursive(Elem*& head) {
    if (!head) return;
    pop(head);  // видаляє верхній елемент
    freeListRecursive(head);
}

// --- MAIN ---
int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Elem* list = nullptr;
    int arr[] = { 1, 2, 3, 2, 4, 2, 5 };
    int size = sizeof(arr) / sizeof(arr[0]);
    int V1 = 2, V2 = 99;

    createListRecursive(list, arr, size);
    cout << "Початковий список: ";
    printListRecursive(list);

    int k = 0;
    insertAfterValueRecursive(list, V1, V2, k);

    cout << "Після вставки " << V2 << " після кожного " << V1 << ": ";
    printListRecursive(list);

    freeListRecursive(list);
    return 0;
}
