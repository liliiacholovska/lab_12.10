#include <iostream>
#include <fstream>
#include <string>

using namespace std;

typedef string Info;

struct Node {
    Node* left, * right;
    Info info;
};

struct Elem {
    Elem* link;
    Node* info;
};

Node* createNode(Info info);
void printTree(Node* root, int level);
void saveToFile(ofstream& f, Node* root);
Node* loadFromFile(ifstream& file);
void addNode(Node*& root, Info value);
bool findNode(Node* root, Info value);
bool deleteNode(Node*& root, Info value);
bool areEqual(Node* root1, Node* root2);
int countNodes(Node* root);
int treeDepth(Node* root);
void destroyTree(Node*& root);
Node* copyTree(Node* root);

int main() {
    Node* root1 = nullptr, * root2 = nullptr;
    ifstream file1("tree1.txt"), file2("tree2.txt");
    ofstream fileOut;
    int option;
    Info value;

    root1 = loadFromFile(file1);
    root2 = loadFromFile(file2);

    file1.close();
    file2.close();

    cout << "Binary Tree Operations:" << endl;
    cout << "1. Print Tree 1" << endl;
    cout << "2. Print Tree 2" << endl;
    cout << "3. Add Node to Tree 1" << endl;
    cout << "4. Find Node in Tree 1" << endl;
    cout << "5. Delete Node from Tree 1" << endl;
    cout << "6. Save Tree 1 to File" << endl;
    cout << "7. Compare Trees" << endl;
    cout << "8. Exit" << endl;

    do {
        cout << "Choose an option: ";
        cin >> option;
        switch (option) {
        case 1:
            printTree(root1, 0);
            break;
        case 2:
            printTree(root2, 0);
            break;
        case 3:
            cout << "Enter value to add: ";
            cin >> value;
            addNode(root1, value);
            break;
        case 4:
            cout << "Enter value to find: ";
            cin >> value;
            if (findNode(root1, value)) {
                cout << "Node found." << endl;
            }
            else {
                cout << "Node not found." << endl;
            }
            break;
        case 5:
            cout << "Enter value to delete: ";
            cin >> value;
            if (deleteNode(root1, value)) {
                cout << "Node deleted." << endl;
            }
            else {
                cout << "Node not found." << endl;
            }
            break;
        case 6:
            fileOut.open("tree1_out.txt");
            saveToFile(fileOut, root1);
            fileOut.close();
            cout << "Tree saved to file." << endl;
            break;
        case 7:
            if (areEqual(root1, root2)) {
                cout << "Trees are equal." << endl;
                cout << "Tree 1 has " << countNodes(root1) << " nodes and depth of " << treeDepth(root1) << "." << endl;
            }
            else {
                cout << "Trees are not equal." << endl;
                cout << "Select which tree to copy:" << endl;
                cout << "1. Copy Tree 1" << endl;
                cout << "2. Copy Tree 2" << endl;
                int choice;
                cin >> choice;
                if (choice == 1) {
                    destroyTree(root2);
                    root2 = copyTree(root1);
                    cout << "Tree 1 copied to Tree 2." << endl;
                }
                else if (choice == 2) {
                    destroyTree(root1);
                    root1 = copyTree(root2);
                    cout << "Tree 2 copied to Tree 1." << endl;
                }
                else {
                    cout << "Invalid choice." << endl;
                }
            }
            break;
        case 8:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid option." << endl;
            break;
        }
    } while (option != 8);

    destroyTree(root1);
    destroyTree(root2);
    return 0;
}

Node* createNode(Info info) {
    Node* newNode = new Node;
    newNode->info = info;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

void addNode(Node*& root, Info value) {
    if (root == nullptr) {
        root = createNode(value);
    }
    else if (value < root->info) {
        addNode(root->left, value);
    }
    else if (value > root->info) {
        addNode(root->right, value);
    }
}

bool findNode(Node* root, Info value) {
    if (root == nullptr) {
        return false;
    }
    else if (value == root->info) {
        return true;
    }
    else if (value < root->info) {
        return findNode(root->left, value);
    }
    else {
        return findNode(root->right, value);
    }
}

bool deleteNode(Node*& root, Info value) {
    if (root == nullptr) return false;
    if (value < root->info) {
        return deleteNode(root->left, value);
    }
    else if (value > root->info) {
        return deleteNode(root->right, value);
    }
    else {
        if (root->left == nullptr) {
            Node* tmp = root->right;
            delete root;
            root = tmp;
        }
        else if (root->right == nullptr) {
            Node* tmp = root->left;
            delete root;
            root = tmp;
        }
        else {
            Node* succParent = root;
            Node* succ = root->right;
            while (succ->left != nullptr) {
                succParent = succ;
                succ = succ->left;
            }
            root->info = succ->info;
            if (succParent != root)
                succParent->left = succ->right;
            else
                succParent->right = succ->right;

            delete succ;
        }
        return true;
    }
}

bool areEqual(Node* root1, Node* root2) {
    if (root1 == nullptr && root2 == nullptr) return true;
    if (root1 != nullptr && root2 != nullptr) {
        return (root1->info == root2->info) && areEqual(root1->left, root2->left) && areEqual(root1->right, root2->right);
    }
    return false;
}

int countNodes(Node* root) {
    if (root == nullptr) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int treeDepth(Node* root) {
    if (root == nullptr) return 0;
    return 1 + max(treeDepth(root->left), treeDepth(root->right));
}

void printTree(Node* root, int level) {
    if (root != nullptr) {
        printTree(root->right, level + 1);
        for (int i = 0; i < level; i++) cout << "  ";
        cout << root->info << endl;
        printTree(root->left, level + 1);
    }
}

void destroyTree(Node*& root) {
    if (root != nullptr) {
        destroyTree(root->left);
        destroyTree(root->right);
        delete root;
        root = nullptr;
    }
}

Node* loadFromFile(ifstream& file) {
    Node* root = nullptr;
    Info info;
    while (file >> info) {
        addNode(root, info);
    }
    return root;
}

void saveToFile(ofstream& f, Node* root) {
    if (root != nullptr) {
        f << root->info << endl;
        saveToFile(f, root->left);
        saveToFile(f, root->right);
    }
}

Node* copyTree(Node* root) {
    if (root == nullptr) return nullptr;

    Node* newNode = createNode(root->info);
    newNode->left = copyTree(root->left);
    newNode->right = copyTree(root->right);

    return newNode;
}