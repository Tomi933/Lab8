#include <iostream>

struct Elem
{
    Elem* link1,
        * link2;
    int info;
};


int main() {
    
    Elem* p;
    p = new Elem;

    p->info = 1;
    p->link1 = new Elem;
    p->link1->info = 2;
    p->link1->link2 = new Elem;
    p->link1->link2->info = 3;
    p->link1->link2->link1 = p->link1;
    p->link1->link2->link2 = NULL;
    p->link1->link1 = new Elem;
    p->link1->link1->info = 4;
    p->link1->link1->link1 = NULL;
    p->link1->link1->link2 = p;

    //Перевірка:
    std::cout << "p->info = " << p->info << "\n";                     // 1
    std::cout << "p->link1->info = " << p->link1->info << "\n";       // 2
    std::cout << "p->link1->link2->info = " << p->link1->link2->info << "\n"; // 3
    std::cout << "p->link1->link1->info = " << p->link1->link1->info << "\n"; // 4

    //Перевіримо зв’язки:
    std::cout << "p->link1->link2->link1->info = " << p->link1->link2->link1->info << "\n"; // ->2
    std::cout << "p->link1->link1->link2->info = " << p->link1->link1->link2->info << "\n"; // ->1 (p)

    // Звільнення пам'яті
    delete p->link1->link2;
    delete p->link1->link1;
    delete p->link1;
    delete p;

    return 0;
}
