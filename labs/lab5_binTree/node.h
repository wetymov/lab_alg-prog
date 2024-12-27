#pragma once
#ifndef NODE_H
#define NODE_H

struct node {
    int value;
    struct node* left;
    struct node* right;
};
typedef struct node Node;

Node* Create(int value);
void Destroy(Node* node);
Node* Insert(Node* root, Node* newNode);
int getHeight(Node* root);

#endif
