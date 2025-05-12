#include <iostream>
using namespace std;

struct DNode {
    int info;
    DNode* prev;
    DNode* next;
};

void pushBackRec(DNode*& head, DNode*& tail, int* arr, int size, int index = 0) {
    if (index == size) return;

    DNode* newNode = new DNode{ arr[index], tail, nullptr };
    if (!head) head = newNode;
    else tail->next = newNode;
    tail = newNode;

    pushBackRec(head, tail, arr, size, index + 1);
}

void printListRec(DNode* node) {
    if (!node) {
        cout << endl;
        return;
    }
    cout << node->info << " ";
    printListRec(node->next);
}

bool matchFromHere(DNode* L1, DNode* L2) {
    if (!L1) return true;           // Увесь L1 пройдено → знайдено
    if (!L2) return false;          // L2 закінчився раніше → не збігається
    if (L1->info != L2->info) return false;
    return matchFromHere(L1->next, L2->next);
}

bool isSublistRec(DNode* L1, DNode* L2) {
    if (!L1) return true;
    if (!L2) return false;

    if (L1->info == L2->info && matchFromHere(L1, L2))
        return true;

    return isSublistRec(L1, L2->next);
}

void freeListRec(DNode* node) {
    if (!node) return;
    freeListRec(node->next);
    delete node;
}


int main() {
    DNode* L1_head = nullptr, * L1_tail = nullptr;
    DNode* L2_head = nullptr, * L2_tail = nullptr;

    int arr1[] = { 2, 3 };           // L1
    int arr2[] = { 1, 2, 3, 4 };     // L2

    pushBackRec(L1_head, L1_tail, arr1, 2);
    pushBackRec(L2_head, L2_tail, arr2, 4);

    cout << "L1: "; printListRec(L1_head);
    cout << "L2: "; printListRec(L2_head);

    if (isSublistRec(L1_head, L2_head))
        cout << "L1 входить у L2" << endl;
    else
        cout << "L1 НЕ входить у L2" << endl;

    // Рекурсивне звільнення
    freeListRec(L1_head); L1_head = nullptr;
    freeListRec(L2_head); L2_head = nullptr;

    return 0;
}

