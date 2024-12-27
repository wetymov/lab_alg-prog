#include "node.h"
#include <stdlib.h>

Node* Create(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return NULL;
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void Destroy(Node* node) {
    if (node) {
        Destroy(node->left);
        Destroy(node->right);
        free(node);
    }
}

Node* Insert(Node* root, Node* newNode) {
    if (root == NULL) return newNode;
    if (newNode->value < root->value) {
        root->left = Insert(root->left, newNode);
    }
    else {
        root->right = Insert(root->right, newNode);
    }
    return root;
}

int getHeight(Node* root) {
    if (root == NULL) return 0;
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}
