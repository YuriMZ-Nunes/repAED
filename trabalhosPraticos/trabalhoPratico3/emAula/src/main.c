#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
}TreeNode;

bool isSymmetric(struct TreeNode* root);
struct TreeNode* insertTree(int num);
void totalTree(struct TreeNode* root, int *total);
void getLeft(struct TreeNode* root, int* leftVector, int* i);
void getRight(struct TreeNode* root, int* rightVector, int *i);

int main(){

    TreeNode *root;
    /*
    root = insertTree(1);
    root->left = insertTree(2);
    root->right = insertTree(2);
    root->left->left = insertTree(3);
    root->left->right = insertTree(4);
    root->right->left = insertTree(4);
    root->right->right = insertTree(3);
    */
   
    root = insertTree(1);
    root->left = insertTree(2);
    root->right = insertTree(2);
    root->left->right = insertTree(3);
    root->right->right = insertTree(3);

    isSymmetric(root);

    return 0;
}

bool isSymmetric(struct TreeNode* root){
    int total = 0;

    totalTree(root, &total);

    if(total%2 == 0)
        return false;

    int leftVector[total/2];
    int rightVector[total/2];
    int i = 0, j = 0;

    getLeft(root->left, leftVector, &i);
    getRight(root->right, rightVector, &j);
    
    bool compair = true;
    for(int i = 0; i < total/2; i++){
        if(leftVector[i] != rightVector[i])
            compair = false;
    }

    return compair;
}

void getLeft(struct TreeNode* root, int* leftVector, int* i){
    if(root){
        leftVector[*i] = root->val;
        *i+=1;
        getLeft(root->left, leftVector, i);
        *i+=1;
        getLeft(root->right, leftVector, i);
    }else{
        leftVector[*i] = -101;
    }
}

void getRight(struct TreeNode* root, int* rightVector, int *i){
    if(root){
        rightVector[*i] = root->val;
        *i+=1;
        getRight(root->right, rightVector, i);
        *i+=1;
        getRight(root->left, rightVector, i);
    }

    rightVector[*i] = -101;
}

void totalTree(struct TreeNode* root, int *total){
    if(root){
        *total += 1;
        totalTree(root->left, total);
        totalTree(root->right, total);
    }
}

struct TreeNode* insertTree(int num){
    TreeNode* node = malloc(sizeof(TreeNode));
    TreeNode* left = NULL;
    TreeNode* right = NULL;

    node->val = num;
    node->left = left;
    node->right = right;

    return node;
}
