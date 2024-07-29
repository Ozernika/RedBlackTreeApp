// Implementing Red-Black Tree in C++
#include <iostream>
#include <queue>
#include <algorithm>
#include <string>
#include <Windows.h>
using namespace std;


struct Node {
    int data;  //тип значения узла-целое
    Node* parent;  //указатель на родителя
    Node* left;  //указатель на левого потомка
    Node* right;  //указатель на правого потомка
    int color;   //переменная-цвет (1-красный, 0-черный)
};

typedef Node* NodePtr;  //объявляем тип NodePtr - указатель на узел дерева

class RedBlackTree {
private:
    NodePtr root;   //корень дерева
    NodePtr TNULL;  //пустой узел дерева
    
    // симметричный поиск

    void inOrderHelper(NodePtr node) {
        if (node != TNULL) {   //дерево непустое
            inOrderHelper(node->left);  //рекурсивно обходим левое поддерево
            cout << node->data << " ";   //выводим значение узла
            inOrderHelper(node->right);   //рекурсивно обходим правое поддерево
        }
    }
   
    // функция для балансировки дерева после вставки
    void insertFix(NodePtr k) {
        NodePtr u;
        while (k->parent->color == 1) {  //пока цвет родителя вставленного узла - красный

            //если родитель вставленного узла это правый ребенок дедушки вставленного узла
            if (k->parent == k->parent->parent->right) {  
                u = k->parent->parent->left;  //узел на одном уровне с родителем вставленного узла
                if (u->color == 1) {
                    u->color = 0;   //меняет цвет на черный
                    k->parent->color = 0;    //родитель вставленного узла меняет цвет на черный
                    k->parent->parent->color = 1;  //  дедушка вставленного узла - красного цвета
                    k = k->parent->parent;   //поднимаемся по дереву на 2 уровня выше
                }
                else {
                    if (k == k->parent->left) {   //если вставленный узел - левый потомок
                        k = k->parent;   
                        rightRotate(k); //правый поворот вокруг родителя 
                    }
                    k->parent->color = 0;   //цвет родителя вставленного узла делаем черным
                    k->parent->parent->color = 1;  //цвет дедушки - красный
                    leftRotate(k->parent->parent);   //левый поворот вокруг дедушки
                }
            }
            else {
                u = k->parent->parent->right;

                if (u->color == 1) {   //если узел на одном уровне с родителем вставленного узла - красный
                    u->color = 0;  //меняем на черный
                    k->parent->color = 0;  //цвет родителя меняем на черный
                    k->parent->parent->color = 1;  //цвет дедушки меняем на красный
                    k = k->parent->parent;    //поднимаемся по дереву на 2 уровня выше
                }
                else {
                    if (k == k->parent->right) {  //если вставленный узел - правый потомок
                        k = k->parent;
                        leftRotate(k);  //левый поворот вокруг родителя
                    }
                    k->parent->color = 0;   
                    k->parent->parent->color = 1;  
                    rightRotate(k->parent->parent);   //правый поворот вокруг дедушки
                }
            }
            if (k == root) {  //дошли до корня - выход из цикла
                break;
            }
        }
        root->color = 0;  //корень черного цвета
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
        NodePtr y = x->right;  //y - правое поддерево узла, поданного на вход
        x->right = y->left;   //правое поддерево входного узла заменяется левым поддеревом y
        if (y->left != TNULL) {  //если левое поддерево y это не лист
            y->left->parent = x;  //меняем родителя левого поддерева y в связи с заменой
        }

        y->parent = x->parent;  //родителю y присваивается значение родителя входного узла
        if (x->parent == nullptr) {  //если входной узел это корень
            this->root = y;    //делаем корнем y
        }

        else if (x == x->parent->left) { //если входной узел - левый потомок
            x->parent->left = y;   //делаем y левым потомком
        }   
        else {   //если входной узел - правый потомок
            x->parent->right = y;  //делаем y правым потомком
        } 
        
        //делаем входной узел левым потомком y
        y->left = x;  
        x->parent = y; 
    }

    void rightRotate(NodePtr x) {
        NodePtr y = x->left;          //y - левое поддерево узла, поданного на вход
        x->left = y->right;   //левое поддерево входного узла заменяется правым поддеревом y
        if (y->right != TNULL) {   //если y это не лист
            y->right->parent = x;  //делаем входной узел родителем правого поддерева y
        }

        y->parent = x->parent;   //родителю y присваивается значение родителя входного узла
        if (x->parent == nullptr) {   //если входной узел это корень
            this->root = y;           //делаем корнем y
        }

        else if (x == x->parent->right) {   //если входной узел - правый потомок
            x->parent->right = y;            //делаем y правым потомком
        }
        else {     //если входной узел - левый потомок
            x->parent->left = y;    //делаем y левым потомком
        }

        //делаем входной узел правым потомком y
        y->right = x;   
        x->parent = y;   
    }

    void insert(int key) {
        NodePtr node = new Node;
        node->parent = nullptr;
        node->data = key;
        node->left = TNULL;
        node->right = TNULL;
        node->color = 1;  //начальный цвет узла - красный

        NodePtr y = nullptr;  
        NodePtr x = this->root;  //х - корень дерева

        //вставка узла в качестве листа дерева
        while (x != TNULL) {  //пока не добрались до листа дерева
            y = x;                        //y на последней итерации становится родителем листа
            if (node->data < x->data) {  //если входное значение меньше значения корневого узла
                x = x->left;  //узел становится левым потомком
            }
            else {
                x = x->right;  //узел становится правым потомком
            }
        }

        node->parent = y;   //родитель листа становится родителем узла для вставки

        if (y == nullptr) {  //если y остался nullptr
            root = node;   //корень делаем узлом
        }
        //делаем узел левым или правым потомком в зависимости от его значения
        else if (node->data < y->data) {  
            y->left = node;    
        }
        else {
            y->right = node;
        }
        //если узел это корень
        if (node->parent == nullptr) {
            node->color = 0;   //его цвет-черный
            return;
        }

        if (node->parent->parent == nullptr) {
            return;
        }
        //вызов функции для восстанавления свойств дерева и его балансировки
        insertFix(node);
    }
    //метод, возвращающий сумму листьев
    int sumLeafValues(NodePtr node) {
        if (node == nullptr) {  //если дерево пустое, возвращаем 0
            return 0;
        } 
        //проверка на то, является ли узел листом
        if (node->left == TNULL && node->right == TNULL) {  
            return node->data;  //возвращаем значение листа
        }
    //рекурсивный вызов функции для левого и правого поддерева
        int leftSum = sumLeafValues(node->left); 
        int rightSum = sumLeafValues(node->right);
        //после обхода всех узлов возвращается сумма листьев
        return leftSum + rightSum;
    }

    //функция подсчета количества узлов дерева
    int countNodes(NodePtr node) {
        if (node == TNULL) { //если дерево пустое, возвращаем 0
            return 0;
        }   //иначе возвращаем 1(подсчет текущего узла) +
       // +результаты рекурсивных вызовов у правого и левого поддеревьев
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    //функция подсчета суммы значений узлов дерева
    int sumAllValues(NodePtr node) {
        if (node == TNULL) {    //если дерево пустое, возвращаем 0
            return 0;
        }    //иначе возвращаем значение текущего узла +
       // +результаты рекурсивных вызовов у правого и левого поддеревьев
        return node->data + sumAllValues(node->left) + sumAllValues(node->right);
    }

    double averageValue() { 
        //запись в переменные результатов функций подсчета суммы и количества узлов дерева
        int totalNodes = countNodes(root);  
        int totalValue = sumAllValues(root);

        if (totalNodes == 0) {
            return 0.0; // Чтобы избежать деления на ноль, вернем 0.0, если дерево пустое
        }
        //возвращаем среднее арифметическое всех узлов
        return static_cast<double>(totalValue) / totalNodes;
    }

    //функция-обход в ширину
    void breadthFirstTraversal() { 
        if (root == TNULL) {   //проверка на пустое дерево
            cout << "Дерево пустое" << endl;
            return;
        }
        //создается очередь и добавляется корневой узел
        queue<NodePtr> q;  
        q.push(root);

        while (!q.empty()) {   //пока очередь не пуста
            NodePtr current = q.front();  
            q.pop();   //удаляем узел из начала
            cout << current->data << " ";  //вывод значения узла 

            //если у узла есть потомки, то добавляем их в очередь
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

        // Рассчитываем смещение для следующего уровня
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
            // Инициализируем все элементы матрицы нулями
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
    cout << "1. Вставить элемент" << endl;
    cout << "2. Симметричный обход" << endl;
    cout << "3. Обход в ширину" << endl;
    cout << "4. Найти сумму значений листьев" << endl;
    cout << "5. Найти среднее арифметическое всех узлов" << endl;
    cout << "6. Вывод дерева" << endl;
    cout << "7. Выход из программы" << endl;
    do {
        cout << "Введите ваш выбор: ";
        cin >> choice;
        switch (choice) {
        case 1:
            cout << "Введите значение элемента для вставки: ";
            cin >> item;
            bst.insert(item);
            break;
        case 2:
            cout << "Симметричный обход: ";
            bst.inorder();
            cout << endl;
            break;
        case 3:
            cout << "Обход в ширину: ";
            bst.breadthFirstTraversal();
            break;
        case 4:
            cout << "Сумма значений листьев: ";
            cout << bst.sumLeafValues(bst.getRoot());
            cout << endl;
            break;
        case 5:
            cout << "Среднее арифметическое всех узлов: ";
            cout << bst.averageValue();
            cout << endl;
            break;
        case 6:
            cout << endl << endl << endl;
            bst.TreePrinter(bst);
            break;
        case 7:
            cout << "Выход." << endl;
            break;
        default:
            cout << "Неправильный выбор. Попробуйте снова." << endl;
        }
    } while (choice != 7);

    return 0;
}

