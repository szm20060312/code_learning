#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct BTreeNode
{
    ElementType Element;
    struct BTreeNode *Left;
    struct BTreeNode *Right;
} BTNode;

BTNode* createNode(ElementType value)
{
    BTNode *node = (BTNode *)malloc(sizeof(BTNode));
    node->Element = value;
    node->Left = NULL;
    node->Right = NULL;
    return node;
}

int leaf(BTNode *t)
{
    if (t == NULL)
        return 0;

    if (t->Left == NULL && t->Right == NULL)
        return 1;

    return leaf(t->Left) + leaf(t->Right);
}
int main()
{
    /*
            1
           / \
          2   3
         /   / \
        4   5   6

    */

    BTNode *root = createNode(1);
    root->Left = createNode(2);
    root->Right = createNode(3);
    root->Left->Left = createNode(4);
    root->Right->Left = createNode(5);
    root->Right->Right = createNode(6);

    int result = leaf(root);

    printf("Number of leaf nodes: %d\n", result);

    return 0;
}
