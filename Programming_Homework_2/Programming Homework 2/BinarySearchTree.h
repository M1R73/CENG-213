#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <cmath>
#include <functional>
#include <algorithm>

#include "Node.h"
#include "NoSuchItemException.h"

template<class T>
class DefaultBalanceCondition {
public:
    bool operator()(int current, int ideal) const {
        return true;
    }
};

template<class T,
         typename BalanceCondition = DefaultBalanceCondition<T>,
         typename Comparator = std::less<T> >
class BinarySearchTree {
public:
    BinarySearchTree();
    BinarySearchTree(const std::list<T> &sortedList);
    BinarySearchTree(const BinarySearchTree &obj);
    ~BinarySearchTree();

    BinarySearchTree &operator=(const BinarySearchTree &rhs);

    bool insert(const T &element);
    bool remove(const T &element);
    void removeAllNodes();

    bool isEmpty() const;
    int getHeight() const;
    int getSize() const;

    const T &get(const T &element) const;
    const T &getMin() const;
    const T &getMax() const;
    const T &getNext(const T &element) const;
    const T &getCeiling(const T &element) const;
    const T &getFloor(const T &element) const;

    std::list<Node<T> *> find(const T &low, const T &high) const;

    void toCompleteBST();

    void printPreorder() const;
    void printInorder() const;
    void printPostorder() const;
    void printPretty() const;
    void print(std::ostream &out) const;

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void printPretty(Node<T> *node, int indentLevel, bool isLeftChild) const;
    void print(Node<T> *t, std::ostream &out) const;
    void printTraversal(Node<T> *node, int type) const;

    // Helper functions declarations
    int getLog2(int n) const;
    int leftSizeCalculator(int n);
    void updateMetadata(Node<T>* node);
    void checkBalance(Node<T>* &node);
    
    Node<T>* SortedHelper(const std::vector<T> &vec, int start, int end);
    Node<T>* copyHelper(Node<T>* root) const;
    void destruct(Node<T>* node);
    
    bool insertHelper(Node<T> *&p, const T &element);
    bool removeHelper(Node<T>* &p, const T &element);
    
    void findHelper(Node<T>* p, const T &low, const T &high, std::list<Node<T> *> &result) const;
    
    void vecMaker(Node<T> *p, std::vector<Node<T>*> &vec);
    Node<T>* SortedHelper(const std::vector<Node<T>*> &vec, int start, int end);
    void toCompleteBST(Node<T>* &node);

private:
    Node<T> *root;
    int numNodes;
    Comparator isLessThan;
    BalanceCondition isBalancedFunctor;

private:


};

/////////////////////////////////////////////////////////////
///////////  CONSTRUCTORS / DESTRUCTOR  /////////////////////
/////////////////////////////////////////////////////////////

template<class T, typename B, typename C>
BinarySearchTree<T,B,C>::BinarySearchTree() {
    root = NULL;
    numNodes = 0;
}

template<class T, typename B, typename C>
int BinarySearchTree<T,B,C>::getLog2(int n) const {
    if (n <= 0) return 0;
    int h = 0;
    while (n > 1) {
        n /=2;
        h++;
    }
    return h;
}

template<class T, typename B, typename C>
int BinarySearchTree<T,B,C>::leftSizeCalculator(int n) {
    if (n <= 1) return 0;
    int h = getLog2(n);
    int maxNodes = pow(2,h) - 1;
    int low_left = n - maxNodes;
    int maxLeftLast = pow(2,h-1);
    return (maxNodes / 2) + std::min(low_left, maxLeftLast);
}

template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::updateMetadata(Node<T>* node) {
    if (node == NULL) return;
    int hLeft = (node->left != NULL) ? (int)node->left->height : -1;
    int hRight = (node->right != NULL) ? (int)node->right->height : -1;
    node->height = 1 + std::max(hLeft, hRight);

    int sLeft = (node->left != NULL) ? (int)node->left->subsize : 0;
    int sRight = (node->right != NULL) ? (int)node->right->subsize : 0;
    node->subsize = 1 + sLeft + sRight;
}

template<class T, typename B, typename C>
Node<T>* BinarySearchTree<T,B,C>::SortedHelper(const std::vector<T> &vec, int start, int end) {
    if (start > end) return NULL;
    int n = end - start + 1;
    int rootIndex = start + leftSizeCalculator(n);

    Node<T> *newNode = new Node<T>(vec[rootIndex], NULL, NULL, 0, 1);
    newNode->left = SortedHelper(vec, start, rootIndex - 1);
    newNode->right = SortedHelper(vec, rootIndex + 1, end);
    updateMetadata(newNode);
    return newNode;
}

template<class T, typename B, typename C>
BinarySearchTree<T,B,C>::BinarySearchTree(const std::list<T> &sortedList)
{
    std::vector<T> vec(sortedList.begin(), sortedList.end());
    numNodes = vec.size();
    root = SortedHelper(vec, 0, numNodes - 1);
}

template<class T, typename B, typename C>
Node<T>* BinarySearchTree<T,B,C>::copyHelper(Node<T>* root) const {
    if (root == NULL) return NULL;
    Node<T>* newNode = new Node<T>(root->element, NULL, NULL, root->height, root->subsize);
    newNode->left = copyHelper(root->left);
    newNode->right = copyHelper(root->right);
    return newNode;
}

template<class T, typename B, typename C>
BinarySearchTree<T,B,C>::BinarySearchTree(const BinarySearchTree &obj)
{
    numNodes = obj.numNodes;
    if (obj.root == NULL) root = NULL;
    else root = copyHelper(obj.root);
}


template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::destruct(Node<T>* node) {
    if (node == NULL) return;
    destruct(node->left);
    destruct(node->right);
    delete node;
}

template<class T, typename B, typename C>
BinarySearchTree<T,B,C>::~BinarySearchTree() {
    removeAllNodes();
}

template<class T, typename B, typename C>
BinarySearchTree<T,B,C> &
BinarySearchTree<T,B,C>::operator=(const BinarySearchTree &rhs)
{
    removeAllNodes();
    if (rhs.root == NULL) root = NULL;
    else {
        root = copyHelper(rhs.root);
        numNodes = rhs.numNodes;
    }
    return *this;
}

template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::removeAllNodes()
{
    if (root != NULL) {
        destruct(root);
        root = NULL;
        numNodes = 0;
    }
}

/////////////////////////////////////////////////////////////
//////////////////// GETTERS ////////////////////////////////
/////////////////////////////////////////////////////////////

template<class T, typename B, typename C>
bool BinarySearchTree<T,B,C>::isEmpty() const {
    return root == NULL;
 }

template<class T, typename B, typename C>
int BinarySearchTree<T,B,C>::getHeight() const {
    if (root == NULL) return -1;
    return root->height;
}

template<class T, typename B, typename C>
int BinarySearchTree<T,B,C>::getSize() const {
    return numNodes;
 }


/////////////////////////////////////////////////////////////
////////////////////// FIND NODE ////////////////////////////
/////////////////////////////////////////////////////////////

template<class T, typename B, typename C>
const T &BinarySearchTree<T,B,C>::get(const T &element) const
{
    Node<T>* p = root;
    if (p == NULL) throw NoSuchItemException();
    
    while (p) {
        if (isLessThan(element, p->element)) {
            p = p->left;
        } else if (isLessThan(p->element, element)) {
            p = p->right;
        } else {
            return p->element;
        }
    }
    throw NoSuchItemException();
}

/////////////////////////////////////////////////////////////
//////////////////// INSERT / REMOVE ////////////////////////
/////////////////////////////////////////////////////////////

template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::checkBalance(Node<T>* &node) {
    if (node == NULL) return;
    int idealHeight = getLog2(node->subsize);
    if (!isBalancedFunctor((int)node->height, idealHeight)) {
        toCompleteBST(node);
    }
}

template<class T, typename B, typename C>
bool BinarySearchTree<T,B,C>::insertHelper(Node<T> *&p, const T &element) {
    if (p == NULL) {
        p = new Node<T>(element, NULL, NULL, 0, 1);
        numNodes++;
        return true;
    }

    bool result = false;
    if (isLessThan(element, p->element)) {
        result = insertHelper(p->left, element);
    } else if (isLessThan(p->element, element)) {
        result = insertHelper(p->right, element);
    } else {
        p->element = element;
        return false;
    }

    if (result) {
        updateMetadata(p);
        checkBalance(p);
    }
    return result;
}

template<class T, typename B, typename C>
bool BinarySearchTree<T,B,C>::insert(const T &element)
{
    return insertHelper(root, element);
}

template<class T, typename B, typename C>
bool BinarySearchTree<T,B,C>::removeHelper(Node<T>* &p, const T &element) {
    if (p == NULL) return false;

    bool result = false;
    if (isLessThan(element, p->element)) {
        result = removeHelper(p->left, element);
    } else if (isLessThan(p->element, element)) {
        result = removeHelper(p->right, element);
    } else {
        result = true;
        if (p->left == NULL || p->right == NULL) {
            Node<T> *temp = p;
            p = (p->left != NULL) ? p->left : p->right;
            delete temp;
            numNodes--;
        } else {
            Node<T>* successor = p->right;
            while (successor->left != NULL) successor = successor->left;
            p->element = successor->element;
            result = removeHelper(p->right, p->element);
        }
    }

    if (result) {
        updateMetadata(p);
        checkBalance(p);
    }
    return result;
}

template<class T, typename B, typename C>
bool BinarySearchTree<T,B,C>::remove(const T &element) {
    return removeHelper(root, element);
}

/////////////////////////////////////////////////////////////
//////////////////// MIN/MAX/NEXT ///////////////////////////
/////////////////////////////////////////////////////////////

template<class T, typename B, typename C>
const T &BinarySearchTree<T,B,C>::getMin() const {
    if (root == NULL) throw NoSuchItemException();
    Node<T>* p = root;
    while (p->left) p = p->left;
    return p->element;
}

template<class T, typename B, typename C>
const T &BinarySearchTree<T,B,C>::getMax() const {
    if (root == NULL) throw NoSuchItemException();
    Node<T>* p = root;
    while (p->right) p = p->right;
    return p->element;
}

template<class T, typename B, typename C>
const T &BinarySearchTree<T,B,C>::getNext(const T &key) const {
    if (root == NULL) throw NoSuchItemException();
    Node<T>* p = root;
    Node<T> *successor = NULL;
    while (p) {
        if (isLessThan(key, p->element)) {
            successor = p;
            p = p->left;
        } else {
            p = p->right;
        }
    }
    if (!successor) throw NoSuchItemException();
    return successor->element;
}

/////////////////////////////////////////////////////////////
//////////////// CEILING & FLOOR ////////////////////////////
/////////////////////////////////////////////////////////////

template<class T, typename B, typename C>
const T &BinarySearchTree<T,B,C>::getFloor(const T &key) const {
    if (root == NULL) throw NoSuchItemException();
    Node<T>* p = root;
    Node<T>* suc = NULL;
    while (p) {
        if (isLessThan(p->element, key)) {
            suc = p;
            p = p->right;
        } else if (isLessThan(key, p->element)) {
            p = p->left;
        } else {
            return p->element;
        }
    }
    if (!suc) throw NoSuchItemException();
    return suc->element;
}

template<class T, typename B, typename C>
const T &BinarySearchTree<T,B,C>::getCeiling(const T &key) const {
    if (root == NULL) throw NoSuchItemException();
    Node<T>* p = root;
    Node<T>* suc = NULL;
    while (p) {
        if (isLessThan(key, p->element)) {
            suc = p;
            p = p->left;
        } else if (isLessThan(p->element, key)) {
            p = p->right;
        } else {
            return p->element;
        }
    }
    if (!suc) throw NoSuchItemException();
    return suc->element;
}

/////////////////////////////////////////////////////////////
/////////////////////// RANGE FIND //////////////////////////
/////////////////////////////////////////////////////////////

template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::findHelper(Node<T>* p, const T &low, const T &high, std::list<Node<T> *> &result) const {
    if (p == NULL) return;
    if (isLessThan(low, p->element)) findHelper(p->left, low, high, result);
    if (!isLessThan(p->element, low) && !isLessThan(high, p->element)) result.push_back(p);
    if (isLessThan(p->element, high)) findHelper(p->right, low, high, result);
}

template<class T, typename B, typename C>
std::list<Node<T> *> BinarySearchTree<T,B,C>::find(const T &low, const T &high) const
{
    std::list<Node<T> *> result;
    findHelper(root, low, high, result);
    return result;
}

/////////////////////////////////////////////////////////////
//////////////////// COMPLETE BST ///////////////////////////
/////////////////////////////////////////////////////////////

template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::vecMaker(Node<T> *p, std::vector<Node<T>*> &vec) {
    if (p == NULL) return;
    vecMaker(p->left, vec);
    vec.push_back(p);
    vecMaker(p->right, vec);
}

template<class T, typename B, typename C>
Node<T>* BinarySearchTree<T,B,C>::SortedHelper(const std::vector<Node<T>*> &vec, int start, int end) {
    if (start > end) return NULL;
    int n = end - start + 1;
    int rootIndex = start + leftSizeCalculator(n);
    Node<T> *newNode = vec[rootIndex];
    newNode->left = SortedHelper(vec, start, rootIndex - 1);
    newNode->right = SortedHelper(vec, rootIndex + 1, end);
    updateMetadata(newNode);
    return newNode;
}

template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::toCompleteBST(Node<T>* &node) {
    std::vector<Node<T>*> vec;
    vecMaker(node, vec);
    node = SortedHelper(vec, 0, vec.size() - 1);
}

template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::toCompleteBST()
{
    toCompleteBST(root);
}

/////////////////////////////////////////////////////////////
//////////////////////// PRINTS /////////////////////////////
/////////////////////////////////////////////////////////////

// === PREORDER ===
template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::printPreorder() const {
    std::cout << "BST_preorder{" << std::endl;
    printTraversal(root, 0);
    std::cout << std::endl << "}" << std::endl;
}

// === INORDER ===
template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::printInorder() const {
    std::cout << "BST_inorder{" << std::endl;
    printTraversal(root, 1);
    std::cout << std::endl << "}" << std::endl;
}

// === POSTORDER ===
template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::printPostorder() const {
    std::cout << "BST_postorder{" << std::endl;
    printTraversal(root, 2);
    std::cout << std::endl << "}" << std::endl;
}


template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::printTraversal(Node<T> *node, int type) const
{
    std::vector<T> arr;
    if (node == NULL) return;

    if (type == 1) { // Inorder
        std::stack<Node<T>*> s;
        Node<T>* curr = node;
        while (curr != NULL || !s.empty()) {
            while (curr != NULL) {
                s.push(curr);
                curr = curr->left;
            }
            curr = s.top(); s.pop();
            arr.push_back(curr->element);
            curr = curr->right;
        
        }
    } else if (type == 0) { // Preorder
        std::stack<Node<T>*> s;
        s.push(node);
        while (!s.empty()) {
            Node<T>* curr = s.top(); s.pop();
            arr.push_back(curr->element);
            if (curr->right) s.push(curr->right);
            if (curr->left) s.push(curr->left);
        }
    } else { // Postorder
        std::stack<Node<T>*> s1, s2;
        s1.push(node);
        while (!s1.empty()) {
            Node<T>* curr = s1.top(); s1.pop();
            s2.push(curr);
            if (curr->left) s1.push(curr->left);
            if (curr->right) s1.push(curr->right);
        }
        while (!s2.empty()) {
            arr.push_back(s2.top()->element);
            s2.pop();
        }
    }

    for (size_t i = 0; i < arr.size(); i++) {
        std::cout << "\t" << arr[i];
        if (i + 1 < arr.size()) std::cout << ",";
        std::cout << std::endl;
    }
}


/////////////////////////////////////////////////////////////
/////////////////////// PRETTY PRINT ////////////////////////
/////////////////////////////////////////////////////////////

template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::printPretty() const
{
        // check if the tree is empty?
    if (isEmpty()) {
        // the tree is empty.
        std::cout << "BST_pretty{}" << std::endl;
        return;
    }

    // the tree is not empty.

    // recursively output the tree.
    std::cout << "BST_pretty{" << std::endl;
    printPretty(root, 0, false);
    std::cout << "}" << std::endl;
}

template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::printPretty(Node<T> *node,
                                                int indentLevel,
                                                bool isLeftChild) const
{
    // check if the node is NULL?
    if (node == NULL)
        return;

    // output the indentation and the node.
    std::cout << "\t";
    for (int i = 0; i < indentLevel; ++i) {
        std::cout << "---";
    }
    std::cout << (indentLevel == 0 ? "root:" : (isLeftChild ? "l:" : "r:")) << node->element << std::endl;

    // first, output left subtree with one more indentation level.
    printPretty(node->left, indentLevel + 1, true);

    // then, output right subtree with one more indentation level.
    printPretty(node->right, indentLevel + 1, false);
}


template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::print(std::ostream &out) const {
    print(root, out);
    out << "\n";
}
// Print pair<int,float> or any std::pair<K,V>
template<typename A, typename B>
std::ostream& operator<<(std::ostream& os, const std::pair<A,B>& p) {
    os << p.first;   // ONLY print the key
    return os;
}

template<class T, typename B, typename C>
void BinarySearchTree<T,B,C>::print(Node<T> *t, std::ostream &out) const
{
    if (!t) return;

    bool hasLeft  = (t->left  != NULL);
    bool hasRight = (t->right != NULL);

    // LEFT subtree
    if (hasLeft)
    {
        out << '[';
        print(t->left, out);
    }
    else if (hasRight)
    {
        out << '[';
    }

    // CURRENT node
    if (!hasLeft && !hasRight)
    {
        out << '(' << t->element << ')';
    }
    else
    {
        out << '{' << t->element
            << ",H" << t->height
            << ",S" << t->subsize
            << '}';
    }

    // RIGHT subtree
    if (hasRight)
    {
        print(t->right, out);
        out << ']';
    }
    else if (hasLeft)
    {
        out << ']';
    }
}

#endif // BINARY_SEARCH_TREE_H