#include <iostream>
#include <limits>
using namespace std;

typedef int Info;

struct Node {
    Node* left;
    Node* right;
    Info info;
};

// Функція створення дерева
Node* CreateTree(int nodeCount);

// Функція друку дерева
void PrintTree(Node* root, int level);

// Функція додавання вузла
void InsertNode(Node*& root, Info value);

// Функція видалення вузла
bool DeleteNode(Node*& root, Info value);

// Функція пошуку вузла
bool FindNode(Node* root, Info value);

// Функція для пошуку найбільшого елемента і рівня
void FindMaxValue(Node* root, int level, Info& maxVal, int& maxLevel);


int main() {
    Node* root = nullptr;
    int choice, count;
    Info value;
    do {
        cout << "\nMenu:\n";
        cout << "1. Create Tree\n";
        cout << "2. Add Node\n";
        cout << "3. Delete Node\n";
        cout << "4. Find Node\n";
        cout << "5. Print Tree\n";
        cout << "6. Find Max Value and Level\n";
        cout << "0. Exit\n";
        cout << "Your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter number of nodes: ";
            cin >> count;
            root = CreateTree(count);
            break;
        case 2:
            cout << "Enter value to add: ";
            cin >> value;
            InsertNode(root, value);
            break;
        case 3:
            cout << "Enter value to delete: ";
            cin >> value;
            if (!DeleteNode(root, value))
                cout << "Node not found.\n";
            break;
        case 4:
            cout << "Enter value to find: ";
            cin >> value;
            if (FindNode(root, value))
                cout << "Node found.\n";
            else
                cout << "Node not found.\n";
            break;
        case 5:
            PrintTree(root, 0);
            break;
        case 6: {
            Info maxVal = numeric_limits<Info>::min();
            int maxLevel = -1;
            FindMaxValue(root, 0, maxVal, maxLevel);
            cout << "Max value: " << maxVal << " on level " << maxLevel << endl;
            break;
        }
        }
    } while (choice != 0);
    return 0;
}


Node* CreateTree(int nodeCount) {
    if (nodeCount == 0)
        return nullptr;

    Info value;
    cout << "Enter node value: ";
    cin >> value;

    Node* newNode = new Node{ nullptr, nullptr, value };
    int leftCount = nodeCount / 2;
    int rightCount = nodeCount - leftCount - 1;
    newNode->left = CreateTree(leftCount);
    newNode->right = CreateTree(rightCount);
    return newNode;
}

void PrintTree(Node* root, int level) {
    if (root != nullptr) {
        PrintTree(root->right, level + 1);
        for (int i = 0; i < level; i++) cout << "   ";
        cout << root->info << endl;
        PrintTree(root->left, level + 1);
    }
}

void InsertNode(Node*& root, Info value) {
    if (root == nullptr) {
        root = new Node{ nullptr, nullptr, value };
    }
    else if (value < root->info) {
        InsertNode(root->left, value);
    }
    else {
        InsertNode(root->right, value);
    }
}

bool DeleteNode(Node*& root, Info value) {
    if (root == nullptr)
        return false;

    if (value < root->info)
        return DeleteNode(root->left, value);
    else if (value > root->info)
        return DeleteNode(root->right, value);
    else {
        Node* temp = root;
        if (root->left == nullptr) {
            root = root->right;
        }
        else if (root->right == nullptr) {
            root = root->left;
        }
        else {
            Node* parent = root;
            Node* succ = root->right;
            while (succ->left != nullptr) {
                parent = succ;
                succ = succ->left;
            }
            root->info = succ->info;
            if (parent->left == succ)
                parent->left = succ->right;
            else
                parent->right = succ->right;
            temp = succ;
        }
        delete temp;
        return true;
    }
}

bool FindNode(Node* root, Info value) {
    if (root == nullptr)
        return false;
    if (value == root->info)
        return true;
    else if (value < root->info)
        return FindNode(root->left, value);
    else
        return FindNode(root->right, value);
}

void FindMaxValue(Node* root, int level, Info& maxVal, int& maxLevel) {
    if (root != nullptr) {
        if (root->info > maxVal) {
            maxVal = root->info;
            maxLevel = level;
        }
        FindMaxValue(root->left, level + 1, maxVal, maxLevel);
        FindMaxValue(root->right, level + 1, maxVal, maxLevel);
    }
}
