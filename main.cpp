#include <iostream>

struct Node {
    int value;
    Node* rightChild;
    Node* leftChild;
};

int searchBST(int value, Node*& rootNode) {
    int found = 0;

    if (rootNode != nullptr) {
        if (value == rootNode->value) {
            found = 1;
        } else if (value < rootNode->value) {
            if (rootNode->leftChild == nullptr) {
                found = 2;
            } else {
                rootNode = rootNode->leftChild;
                found = searchBST(value, rootNode);
            }
        } else {
            if (rootNode->rightChild == nullptr) {
                found = 3;
            } else {
                rootNode = rootNode->rightChild;
                found = searchBST(value, rootNode);
            }
        }
    }
    return found;
}

bool insertBST(Node*& rootNode, int value) {
    bool insertOK = true;
    Node* auxiliaryPointer = rootNode;
    int found = searchBST(value, auxiliaryPointer);

    if (found == 1) {
        insertOK = false;
    } else {
        Node* newNode = new Node;
        newNode->value = value;
        newNode->leftChild = nullptr;
        newNode->rightChild = nullptr;

        if (found == 0) {
            rootNode = newNode;
        } else if (found == 2) {
            auxiliaryPointer->leftChild = newNode;
        } else {
            auxiliaryPointer->rightChild = newNode;
        }
    }
    return insertOK;
}

void displayBST(Node* rootNode, int level = 0) {
    if (rootNode != nullptr) {
        std::string spaces(level * 4, ' ');
        displayBST(rootNode->rightChild, level + 1);
        std::cout << spaces << "-> " << rootNode->value << std::endl;
        displayBST(rootNode->leftChild, level + 1);
    }
}

void getLeafCount(Node* rootNode, int* count) {
    if (rootNode->leftChild == nullptr && rootNode->rightChild == nullptr) {
        *count += 1;
    } else {
        if (rootNode->leftChild != nullptr) {
            getLeafCount(rootNode->leftChild, count);
        }
        if (rootNode->rightChild != nullptr) {
            getLeafCount(rootNode->rightChild, count);
        }
    }
}

void getNodesCount(Node* rootNode, int* count) {
    if (rootNode != nullptr) {
        *count += 1;
        getNodesCount(rootNode->leftChild, count);
        getNodesCount(rootNode->rightChild, count);
    }
}

int main() {
    const int values[12] = {100, 50, 200, 70, 140, 30, 350, 117, 400, 42, 80, 65};

    Node* rootNode = nullptr;

    for (int value: values) {
        insertBST(rootNode, value);
    }

    std::cout << "Done inserting" << std::endl;
    displayBST(rootNode);

    int leafCount = 0;
    getLeafCount(rootNode, &leafCount);
    std::cout << "Leaf count: " << leafCount << std::endl;

    int nodesCount = 0;
    getNodesCount(rootNode, &nodesCount);
    std::cout << "Nodes count: " << nodesCount << std::endl;

    return 1;
}