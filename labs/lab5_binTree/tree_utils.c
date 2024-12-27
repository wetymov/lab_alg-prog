#include "tree_utils.h"
#include <stdio.h>

void RecursiveInorder(Node* root) {
    if (root == NULL) return;
    RecursiveInorder(root->left);
    printf("%d ", root->value);
    RecursiveInorder(root->right);
}

void MorrisInorder(Node* root) {
    Node* current = root;
    while (current != NULL) {
        if (current->left == NULL) {
            printf("%d ", current->value);
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
                printf("%d ", current->value);
                current = current->right;
            }
        }
    }
}

void printTreeRecursive(Node* root, int level, int indent) {
    if (root == NULL) return;
    printTreeRecursive(root->right, level + 1, indent);
    for (int i = 0; i < indent * level; i++) printf(" ");
    printf("%d\n", root->value);
    printTreeRecursive(root->left, level + 1, indent);
}

void printTree(Node* root) {
    if (root == NULL) {
        printf("Дерево пусто.\n");
        return;
    }
    printTreeRecursive(root, 0, 4);
}
