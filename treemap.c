#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap* map = (TreeMap*) malloc(sizeof(TreeMap));
    map->root = NULL;
    map->current = NULL;
    map->lower_than = lower_than;
    return map;
    //new->lower_than = lower_than;
   
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
    
    TreeNode* nuevoNodo = createTreeNode(key, value);

    if (tree->root == NULL) {
        tree->root = nuevoNodo;
        tree->current = nuevoNodo;
        return;
    }
    
    TreeNode* current = tree->root;
    TreeNode* parent = NULL;
    
    while(current != NULL) {
    
        if(is_equal(tree, key, current->pair->key) == 1) {
        return;
    }
    
    parent = current;
        
    if(tree->lower_than(key,current->pair->key) == 0) {
        current = current->right;
        
    } else current = current->left;
    }
    
        nuevoNodo->parent = parent;
        if (tree->lower_than(key, parent->pair->key) == 0) {
            
            parent->right = nuevoNodo;
            
        } else {
            parent->left = nuevoNodo;
    }

    tree->current = nuevoNodo;
    
}

TreeNode * minimum(TreeNode * x){
    if(x==NULL)return NULL;
    while(x->left!=NULL){
        x=x->left;
    }
    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {

}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {

    if(tree->root == NULL || tree==NULL) {

        return NULL;
        
    }else{

        tree->current=tree->root;
        while(tree->current!=NULL){

            if(tree->lower_than(key,tree->current->pair->key)){
                tree->current=tree->current->left;
            }else{
                if(is_equal(tree, tree->current->pair->key, key)){
                    return tree->current->pair;
                }
                tree->current=tree->current->right;
            }
            
        }
    }
    return NULL;

}


Pair * upperBound(TreeMap * tree, void* key) {

    TreeNode *current=tree->root;
    TreeNode *aux=NULL;

    while(current!=NULL){

        if(is_equal(tree, key,current->pair->key) == 1){
            
            return  current->pair;
        
        }else{

            if(tree->lower_than(key,current->pair->key)==0){
                current=current->right;
            }else{
                aux=current;
                current=current->left;
            }
        }
        if(aux==NULL){
            return NULL;
        }
    }
    return aux->pair;
}

Pair * firstTreeMap(TreeMap * tree) {
    TreeNode *current=tree->root;
    current=minimum(current);
    tree->current=current;
    return current->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
    
    if(tree->current->right!=NULL){
        tree->current = tree->current->right;
        tree->current = minimum(tree->current);
        return tree->current->pair;
    }else{
        TreeNode* parent= tree->current->parent;
    
        while(parent != NULL && tree->current == parent->right){
            tree->current=parent;
            parent=parent->parent;
    }
        if(parent != NULL){
            tree->current = parent;
            return  tree->current->pair;
        }
    }
    
    
    
    return NULL;
}
