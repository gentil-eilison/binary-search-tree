#include <iostream>
#include <vector>
#include <queue>

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

void getLeavesCount(Node* rootNode, int* count) {
    if (rootNode->leftChild == nullptr && rootNode->rightChild == nullptr) {
        *count += 1;
    } else {
        if (rootNode->leftChild != nullptr) {
            getLeavesCount(rootNode->leftChild, count);
        }
        if (rootNode->rightChild != nullptr) {
            getLeavesCount(rootNode->rightChild, count);
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

void preOrderTraversal(Node* root) {
    std::cout << root->value << ' ';
    
    if (root->leftChild != nullptr) {
        preOrderTraversal(root->leftChild);
    }

    if (root->rightChild != nullptr) {
        preOrderTraversal(root->rightChild);
    }
}

void symmetricalTraversal(Node* root) {
    if (root->leftChild != nullptr) {
        symmetricalTraversal(root->leftChild);
    }

    std::cout << root->value << ' ';

    if (root->rightChild != nullptr) {
        symmetricalTraversal(root->rightChild);
    }
}

void postOrderTraversal(Node* root) {
    if (root->leftChild != nullptr) {
        postOrderTraversal(root->leftChild);
    }

    if (root->rightChild != nullptr) {
        postOrderTraversal(root->rightChild);
    }

    std::cout << root->value << ' ';
}

void levelTraversal(Node* root) {
    std::queue<Node*> nodes;
    nodes.push(root);

    while (nodes.size() != 0) {
        Node* currentNode = nodes.front();
        std::cout << currentNode->value << ' ';

        if (currentNode->leftChild) {
            nodes.push(currentNode->leftChild);
        }

        if (currentNode->rightChild) {
            nodes.push(currentNode->rightChild);
        }

        nodes.pop();
    }
}

Node* locateMin(Node* root) {
    std::queue<Node*> nodes;
    nodes.push(root);
    Node* min = root;

    while(nodes.size() != 0) {
        Node* currentNode = nodes.front();
        if (currentNode->value < min->value) {
            min = currentNode;
        }

        if (currentNode->leftChild != nullptr) {
            nodes.push(currentNode->leftChild);
        }

        if (currentNode->rightChild != nullptr) {
            nodes.push(currentNode->rightChild);
        }

        nodes.pop();
    }
    
    return min;
}

void removeBST(int value, Node*& node) {
    Node* auxiliaryPointer = nullptr;

    if (node == nullptr) {
        return;
    }

    if (value < node->value) {
        removeBST(value, node->leftChild);
    } else if (value > node->value) {
        removeBST(value, node->rightChild);
    } else if (node->rightChild != nullptr && node->leftChild != nullptr) {
        auxiliaryPointer = locateMin(node->rightChild);
        node->value = auxiliaryPointer->value;
        removeBST(node->value, node->rightChild);
    } else {
        auxiliaryPointer = node;

        if (node->leftChild != nullptr) {
            node = node->leftChild;
        } else {
            node = node->rightChild;
        }
    }
}

std::vector<int> getTreeValues(int valuesCount) {
    std::vector<int> values;

    int currentValue;
    for (int count = 0; count < valuesCount; count++) {
        std::cout << "Type the number: " << std::endl;
        std::cin >> currentValue;
        values.push_back(currentValue);
    }
    
    return values;
}

int main() {
    int valuesCount = 0;
    std::cout << "Enter the number of values you want in the tree: " << std::endl;
    std::cin >> valuesCount;
    std::vector<int> values = getTreeValues(valuesCount);

    Node* rootNode = nullptr;

    for (int value: values) {
        insertBST(rootNode, value);
    }

    std::cout << "Done inserting" << std::endl;

    std::cout << "Removing element of key 11, new tree state" << std::endl;
    removeBST(11, rootNode);

    int option = 1;

    while (option != 0) {
        std::cout << "What do you wish to do?" << std::endl;
        std::cout << "[1] Display tree" << std::endl;
        std::cout << "[2] Nodes count" << std::endl;
        std::cout << "[3] Leaves count" << std::endl;
        std::cout << "[4] Pre Order Traversal" << std::endl;
        std::cout << "[5] Symmetrical Traversal" << std::endl;
        std::cout << "[6] Post Order Traversal" << std::endl;
        std::cout << "[7] Level Traversal" << std::endl;
        std::cout << "[0] Exit" << std::endl;
        std::cin >> option;

        int nodesCount = 0;
        int leavesCount = 0;

        switch (option) {
            case 1:
                displayBST(rootNode);
                break;
            case 2:
                getNodesCount(rootNode, &nodesCount);
                std::cout << nodesCount << std::endl;
                break;
            case 3:
                getLeavesCount(rootNode, &leavesCount);
                std::cout << leavesCount << std::endl;
                break;
            case 4:
                preOrderTraversal(rootNode);
                std::cout << std::endl;
                break;
            case 5:
                symmetricalTraversal(rootNode);
                std::cout << std::endl;
                break;
            case 6:
                postOrderTraversal(rootNode);
                std::cout << std::endl;
                break;
            case 7:
                levelTraversal(rootNode);
                std::cout << std::endl;
                break;
            case 0:
                break;
            default:
                break;
        }
    }
    return 1;
}