#include <iostream>
using namespace std;

struct DNode {
    int info;
    DNode* prev;
    DNode* next;
};

void pushBack(DNode*& head, DNode*& tail, int value) {
    DNode* newNode = new DNode{ value, nullptr, nullptr };
    if (!head) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

void printList(DNode* head) {
    for (DNode* p = head; p; p = p->next)
        cout << p->info << " ";
    cout << endl;
}

bool isSublist(DNode* L1, DNode* L2) {
    if (!L1) return true;  // ������� L1 ������ �������
    if (!L2) return false; // L2 �������, � L1 � �

    for (DNode* start = L2; start; start = start->next) {
        DNode* p1 = L1;
        DNode* p2 = start;

        while (p1 && p2 && p1->info == p2->info) {
            p1 = p1->next;
            p2 = p2->next;
        }

        if (!p1) return true; // ���� p1 ����� �� ���� � L1 ��������
    }

    return false;
}

void freeListIter(DNode*& head) {
    while (head) {
        DNode* tmp = head;
        head = head->next;
        delete tmp;
    }
}


int main() {
    DNode* L1_head = nullptr, * L1_tail = nullptr;
    DNode* L2_head = nullptr, * L2_tail = nullptr;

    // ������ L1: 2 3
    pushBack(L1_head, L1_tail, 2);
    pushBack(L1_head, L1_tail, 3);

    // ������ L2: 1 2 3 4
    pushBack(L2_head, L2_tail, 1);
    pushBack(L2_head, L2_tail, 2);
    pushBack(L2_head, L2_tail, 3);
    pushBack(L2_head, L2_tail, 4);

    cout << "L1: "; printList(L1_head);
    cout << "L2: "; printList(L2_head);

    if (isSublist(L1_head, L2_head))
        cout << "L1 ������� � L2" << endl;
    else
        cout << "L1 �� ������� � L2" << endl;

    freeListIter(L1_head); L1_head = nullptr;
    freeListIter(L2_head); L2_head = nullptr;
    return 0;
}
