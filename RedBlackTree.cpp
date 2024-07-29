// Implementing Red-Black Tree in C++
#include <iostream>
#include <queue>
#include <algorithm>
#include <string>
#include <Windows.h>
using namespace std;


struct Node {
    int data;  //��� �������� ����-�����
    Node* parent;  //��������� �� ��������
    Node* left;  //��������� �� ������ �������
    Node* right;  //��������� �� ������� �������
    int color;   //����������-���� (1-�������, 0-������)
};

typedef Node* NodePtr;  //��������� ��� NodePtr - ��������� �� ���� ������

class RedBlackTree {
private:
    NodePtr root;   //������ ������
    NodePtr TNULL;  //������ ���� ������
    
    // ������������ �����

    void inOrderHelper(NodePtr node) {
        if (node != TNULL) {   //������ ��������
            inOrderHelper(node->left);  //���������� ������� ����� ���������
            cout << node->data << " ";   //������� �������� ����
            inOrderHelper(node->right);   //���������� ������� ������ ���������
        }
    }
   
    // ������� ��� ������������ ������ ����� �������
    void insertFix(NodePtr k) {
        NodePtr u;
        while (k->parent->color == 1) {  //���� ���� �������� ������������ ���� - �������

            //���� �������� ������������ ���� ��� ������ ������� ������� ������������ ����
            if (k->parent == k->parent->parent->right) {  
                u = k->parent->parent->left;  //���� �� ����� ������ � ��������� ������������ ����
                if (u->color == 1) {
                    u->color = 0;   //������ ���� �� ������
                    k->parent->color = 0;    //�������� ������������ ���� ������ ���� �� ������
                    k->parent->parent->color = 1;  //  ������� ������������ ���� - �������� �����
                    k = k->parent->parent;   //����������� �� ������ �� 2 ������ ����
                }
                else {
                    if (k == k->parent->left) {   //���� ����������� ���� - ����� �������
                        k = k->parent;   
                        rightRotate(k); //������ ������� ������ �������� 
                    }
                    k->parent->color = 0;   //���� �������� ������������ ���� ������ ������
                    k->parent->parent->color = 1;  //���� ������� - �������
                    leftRotate(k->parent->parent);   //����� ������� ������ �������
                }
            }
            else {
                u = k->parent->parent->right;

                if (u->color == 1) {   //���� ���� �� ����� ������ � ��������� ������������ ���� - �������
                    u->color = 0;  //������ �� ������
                    k->parent->color = 0;  //���� �������� ������ �� ������
                    k->parent->parent->color = 1;  //���� ������� ������ �� �������
                    k = k->parent->parent;    //����������� �� ������ �� 2 ������ ����
                }
                else {
                    if (k == k->parent->right) {  //���� ����������� ���� - ������ �������
                        k = k->parent;
                        leftRotate(k);  //����� ������� ������ ��������
                    }
                    k->parent->color = 0;   
                    k->parent->parent->color = 1;  
                    rightRotate(k->parent->parent);   //������ ������� ������ �������
                }
            }
            if (k == root) {  //����� �� ����� - ����� �� �����
                break;
            }
        }
        root->color = 0;  //������ ������� �����
    }


public:
    RedBlackTree() {
        TNULL = new Node;
        TNULL->color = 0;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
    }

    NodePtr getRoot() {
        return this->root;
    }

    void inorder() {
        inOrderHelper(this->root);
    }

    /*  void printTreeFirst() {
        if (root) {
            printHelper(this->root, "", true);
        }
    }*/

    void leftRotate(NodePtr x) {
        NodePtr y = x->right;  //y - ������ ��������� ����, ��������� �� ����
        x->right = y->left;   //������ ��������� �������� ���� ���������� ����� ���������� y
        if (y->left != TNULL) {  //���� ����� ��������� y ��� �� ����
            y->left->parent = x;  //������ �������� ������ ��������� y � ����� � �������
        }

        y->parent = x->parent;  //�������� y ������������� �������� �������� �������� ����
        if (x->parent == nullptr) {  //���� ������� ���� ��� ������
            this->root = y;    //������ ������ y
        }

        else if (x == x->parent->left) { //���� ������� ���� - ����� �������
            x->parent->left = y;   //������ y ����� ��������
        }   
        else {   //���� ������� ���� - ������ �������
            x->parent->right = y;  //������ y ������ ��������
        } 
        
        //������ ������� ���� ����� �������� y
        y->left = x;  
        x->parent = y; 
    }

    void rightRotate(NodePtr x) {
        NodePtr y = x->left;          //y - ����� ��������� ����, ��������� �� ����
        x->left = y->right;   //����� ��������� �������� ���� ���������� ������ ���������� y
        if (y->right != TNULL) {   //���� y ��� �� ����
            y->right->parent = x;  //������ ������� ���� ��������� ������� ��������� y
        }

        y->parent = x->parent;   //�������� y ������������� �������� �������� �������� ����
        if (x->parent == nullptr) {   //���� ������� ���� ��� ������
            this->root = y;           //������ ������ y
        }

        else if (x == x->parent->right) {   //���� ������� ���� - ������ �������
            x->parent->right = y;            //������ y ������ ��������
        }
        else {     //���� ������� ���� - ����� �������
            x->parent->left = y;    //������ y ����� ��������
        }

        //������ ������� ���� ������ �������� y
        y->right = x;   
        x->parent = y;   
    }

    void insert(int key) {
        NodePtr node = new Node;
        node->parent = nullptr;
        node->data = key;
        node->left = TNULL;
        node->right = TNULL;
        node->color = 1;  //��������� ���� ���� - �������

        NodePtr y = nullptr;  
        NodePtr x = this->root;  //� - ������ ������

        //������� ���� � �������� ����� ������
        while (x != TNULL) {  //���� �� ��������� �� ����� ������
            y = x;                        //y �� ��������� �������� ���������� ��������� �����
            if (node->data < x->data) {  //���� ������� �������� ������ �������� ��������� ����
                x = x->left;  //���� ���������� ����� ��������
            }
            else {
                x = x->right;  //���� ���������� ������ ��������
            }
        }

        node->parent = y;   //�������� ����� ���������� ��������� ���� ��� �������

        if (y == nullptr) {  //���� y ������� nullptr
            root = node;   //������ ������ �����
        }
        //������ ���� ����� ��� ������ �������� � ����������� �� ��� ��������
        else if (node->data < y->data) {  
            y->left = node;    
        }
        else {
            y->right = node;
        }
        //���� ���� ��� ������
        if (node->parent == nullptr) {
            node->color = 0;   //��� ����-������
            return;
        }

        if (node->parent->parent == nullptr) {
            return;
        }
        //����� ������� ��� �������������� ������� ������ � ��� ������������
        insertFix(node);
    }
    //�����, ������������ ����� �������
    int sumLeafValues(NodePtr node) {
        if (node == nullptr) {  //���� ������ ������, ���������� 0
            return 0;
        } 
        //�������� �� ��, �������� �� ���� ������
        if (node->left == TNULL && node->right == TNULL) {  
            return node->data;  //���������� �������� �����
        }
    //����������� ����� ������� ��� ������ � ������� ���������
        int leftSum = sumLeafValues(node->left); 
        int rightSum = sumLeafValues(node->right);
        //����� ������ ���� ����� ������������ ����� �������
        return leftSum + rightSum;
    }

    //������� �������� ���������� ����� ������
    int countNodes(NodePtr node) {
        if (node == TNULL) { //���� ������ ������, ���������� 0
            return 0;
        }   //����� ���������� 1(������� �������� ����) +
       // +���������� ����������� ������� � ������� � ������ �����������
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    //������� �������� ����� �������� ����� ������
    int sumAllValues(NodePtr node) {
        if (node == TNULL) {    //���� ������ ������, ���������� 0
            return 0;
        }    //����� ���������� �������� �������� ���� +
       // +���������� ����������� ������� � ������� � ������ �����������
        return node->data + sumAllValues(node->left) + sumAllValues(node->right);
    }

    double averageValue() { 
        //������ � ���������� ����������� ������� �������� ����� � ���������� ����� ������
        int totalNodes = countNodes(root);  
        int totalValue = sumAllValues(root);

        if (totalNodes == 0) {
            return 0.0; // ����� �������� ������� �� ����, ������ 0.0, ���� ������ ������
        }
        //���������� ������� �������������� ���� �����
        return static_cast<double>(totalValue) / totalNodes;
    }

    //�������-����� � ������
    void breadthFirstTraversal() { 
        if (root == TNULL) {   //�������� �� ������ ������
            cout << "������ ������" << endl;
            return;
        }
        //��������� ������� � ����������� �������� ����
        queue<NodePtr> q;  
        q.push(root);

        while (!q.empty()) {   //���� ������� �� �����
            NodePtr current = q.front();  
            q.pop();   //������� ���� �� ������
            cout << current->data << " ";  //����� �������� ���� 

            //���� � ���� ���� �������, �� ��������� �� � �������
            if (current->left != TNULL) {  
                q.push(current->left);
            }

            if (current->right != TNULL) {
                q.push(current->right);
            }
        }
        cout << endl;
    }

    int height(NodePtr root) {
        if (root == NULL)
            return 0;
        return max(height(root->left), height(root->right)) + 1;
    }

    int getcol(int h) {
        if (h == 1)
            return 1;
        return getcol(h - 1) + getcol(h - 1) + 1;
    }

    void printTree(string** M, NodePtr root, int col, int row, int height) {
        if (root == NULL)
            return;

        string sColor = root->color ? "R" : "B";
        M[row][col] = to_string(root->data) + sColor;

        // ������������ �������� ��� ���������� ������
        int offset = pow(2, height - 2);

        if (root->left != TNULL)
            printTree(M, root->left, col - offset, row + 1, height - 1);

        if (root->right != TNULL)
            printTree(M, root->right, col + offset, row + 1, height - 1);
    }

    void TreePrinter(RedBlackTree tree) {
        int h = height(tree.root);
        int col = getcol(h);
        string** M = new string* [h];
        for (int i = 0; i < h; i++) {
            M[i] = new string[col];
            // �������������� ��� �������� ������� ������
            for (int j = 0; j < col; j++) {
                M[i][j] = "";
            }
        }
        printTree(M, tree.root, col / 2, 0, h);
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < col; j++) {
                if (M[i][j] == "")
                    cout << " " << " ";
                else
                    cout << M[i][j] << " ";
            }
            cout << endl << endl << endl;
        }
    }
};

int main() {
    RedBlackTree bst;
    int choice, item;
    SetConsoleOutputCP(1251);
    cout << "1. �������� �������" << endl;
    cout << "2. ������������ �����" << endl;
    cout << "3. ����� � ������" << endl;
    cout << "4. ����� ����� �������� �������" << endl;
    cout << "5. ����� ������� �������������� ���� �����" << endl;
    cout << "6. ����� ������" << endl;
    cout << "7. ����� �� ���������" << endl;
    do {
        cout << "������� ��� �����: ";
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "������� �������� �������� ��� �������: ";
            cin >> item;
            bst.insert(item);
            break;
        case 2:
            cout << "������������ �����: ";
            bst.inorder();
            cout << endl;
            break;
        case 3:
            cout << "����� � ������: ";
            bst.breadthFirstTraversal();
            break;
        case 4:
            cout << "����� �������� �������: ";
            cout << bst.sumLeafValues(bst.getRoot());
            cout << endl;
            break;
        case 5:
            cout << "������� �������������� ���� �����: ";
            cout << bst.averageValue();
            cout << endl;
            break;
        case 6:
            cout << endl << endl << endl;
            bst.TreePrinter(bst);
            break;
        case 7:
            cout << "�����." << endl;
            break;
        default:
            cout << "������������ �����. ���������� �����." << endl;
        }
    } while (choice != 7);

    return 0;
}

