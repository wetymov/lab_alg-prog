#include "balance.h"
#include <stdlib.h>

Node* MorrisCollect(Node* root) {
    Node dummy = { 0, NULL, NULL };
    Node* tail = &dummy;
    Node* current = root;
    while (current != NULL) {
        if (current->left == NULL) {
            tail->right = current;
            tail = current;
            current = current->right;
        }
        else {
            Node* pre = current->left;
            while (pre->right != NULL && pre->right != current) {
                pre = pre->right;
            }
            if (pre->right == NULL) {
                pre->right = current;
                current = current->left;
            }
            else {
                pre->right = NULL;
                tail->right = current;
                tail = current;
                current = current->right;
            }
        }
    }
    return dummy.right;
}

int CountNodes(Node* head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->right;
    }
    return count;
}

Node* BuildBalancedTreeFromListIterative(Node* sortedList) {
    if (sortedList == NULL) return NULL;
    int count = CountNodes(sortedList);
    Node** nodeArray = (Node**)malloc(count * sizeof(Node*));
    Node* current = sortedList;
    for (int i = 0; i < count; i++) {
        nodeArray[i] = current;
        current = current->right;
        nodeArray[i]->left = nodeArray[i]->right = NULL;
    }
    Node* root = NULL;
    Node** stack = (Node**)malloc(count * sizeof(Node*));
    int* stackLeft = (int*)malloc(count * sizeof(int));
    int* stackRight = (int*)malloc(count * sizeof(int));
    int top = -1;
    stack[++top] = NULL;
    stackLeft[top] = 0;
    stackRight[top] = count - 1;
    while (top >= 0) {
        Node* parent = stack[top];
        int left = stackLeft[top];
        int right = stackRight[top];
        top--;
        if (left > right) continue;
        int mid = left + (right - left) / 2;
        Node* newNode = nodeArray[mid];
        if (parent == NULL) {
            root = newNode;
        }
        else if (newNode->value < parent->value) {
            parent->left = newNode;
        }
        else {
            parent->right = newNode;
        }
        stack[++top] = newNode;
        stackLeft[top] = mid + 1;
        stackRight[top] = right;
        stack[++top] = newNode;
        stackLeft[top] = left;
        stackRight[top] = mid - 1;
    }
    free(nodeArray);
    free(stack);
    free(stackLeft);
    free(stackRight);
    return root;
}

Node* BalanceBTreeIterative(Node* root) {
    if (root == NULL) return NULL;
    Node* sortedList = MorrisCollect(root);
    return BuildBalancedTreeFromListIterative(sortedList);
}
