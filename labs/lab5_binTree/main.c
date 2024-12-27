#include "node.h"
#include "tree_utils.h"
#include "balance.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 20

int main(void) {
    Node* root = NULL;
    srand(time(NULL));
    for (int i = 0; i < SIZE; i++) {
        int n = rand() % 1000;
        printf("%d ", n);
        Node* newNode = Create(n);
        if (newNode == NULL) return -1;
        root = Insert(root, newNode);
    }
    printf("\n");
    printTree(root);
    printf("\nRecursion: ");
    RecursiveInorder(root);
    printf("\nMorris: ");
    MorrisInorder(root);
    root = BalanceBTreeIterative(root);
    printf("\nBalanced tree:\n");
    printTree(root);
    Destroy(root);
    return 0;
}
