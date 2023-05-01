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
bool compairSides(struct TreeNode* left, struct TreeNode* right);

int main(){

    TreeNode *root;
    
    /*root = insertTree(1);
    root->left = insertTree(2);
    root->right = insertTree(2);
    root->left->left = insertTree(3);
    root->left->right = insertTree(4);
    root->right->left = insertTree(4);
    root->right->right = insertTree(3);*/
    
   
    root = insertTree(1);
    root->left = insertTree(2);
    root->right = insertTree(2);
    root->left->right = insertTree(3);
    root->right->right = insertTree(3);

    isSymmetric(root);

    return 0;
}

bool isSymmetric(struct TreeNode* root){
    bool symmetry = true;
    if(root)
        symmetry = compairSides(root->left, root->right);

    return symmetry;
}

bool compairSides(struct TreeNode* leftTree, struct TreeNode* rightTree){
    if(!leftTree && !rightTree)
        return true;
    if(!leftTree || !rightTree)
        return false;
    if(leftTree->val == rightTree->val){
        if(compairSides(leftTree->left, rightTree->right)){
            if(compairSides(leftTree->right, rightTree->left))
                return true;
        }
    }

    return false;
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
