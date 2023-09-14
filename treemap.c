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
  TreeMap* map = malloc(sizeof(TreeMap));
  map->lower_than = lower_than;
  map->root = NULL;
  map->current=NULL;
  return map;
  
  //new->lower_than = lower_than;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
  Pair* par = malloc(sizeof(Pair));
  par->key=key;
  par->value=value;
  TreeNode* nodo = createTreeNode(par->key, par->value);
  TreeNode* aux= tree->root;
  TreeNode* parent = NULL;
  while(aux!=NULL){
    parent=aux;
    if(tree->lower_than(key,aux->pair->key)==0){
      return;
    }
    if(tree->lower_than(key,aux->pair->key)<0){
      aux=aux->left;
    }else{
      aux=aux->right;
    }
  }
  if(tree->lower_than(key,parent->pair->key)<0){
    parent->left=nodo;
  }else{
    parent->right=nodo;
  }
  nodo->parent=parent;
  tree->current=nodo;
}


TreeNode * minimum(TreeNode * x){

    return NULL;
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
  TreeNode* node = tree->root;
  while(node!=NULL){
    if(tree->lower_than(key,node->pair->key)){
      node=node->left;
    }else if(tree->lower_than(node->pair->key,key)){
      node=node->right;
    }else{
      tree->current=node;
      return node->pair;
    }
  }
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
