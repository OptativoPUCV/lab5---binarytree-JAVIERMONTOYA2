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
  Pair * pair = malloc(sizeof(Pair));
  pair->key = key;
  pair->value = value;
  
  TreeNode * nodo = createTreeNode(pair->key, pair->value);

  if(tree->root==NULL){
    tree->root=nodo;
    tree->current=nodo;
    return;
  }
  
  TreeNode* aux= tree->root;
  TreeNode* parent = NULL;
  while(aux!=NULL){
    parent=aux;
    if(tree->lower_than(key,aux->pair->key)==0){
      return;
    }
    if(tree->lower_than(key,aux->pair->key)>0){
      aux=aux->left;
    }else{
      aux=aux->right;
    }
  }
  if(tree->lower_than(key,parent->pair->key)>0){
    parent->left=nodo;
  }else{
    parent->right=nodo;
  }
  nodo->parent=parent;
  tree->current=nodo;
}


TreeNode * minimum(TreeNode * x){
  if(x==NULL){
    return NULL;
  }

  TreeNode* min = x;
  TreeNode* aux = x->left;
  
  while(aux!=NULL){
    min=aux;
    aux=aux->left;
  }
  return min;
}


void removeNode(TreeMap * tree, TreeNode* node) {
  if(node==NULL){
    return;
  }

  if(node->left==NULL && node->right==NULL){
    if(node==tree->root){
      tree->root=NULL;
    }else if (node==node->parent->left){
      node->parent->left=NULL;
    }else if (node==node->parent->right){
      node->parent->right=NULL;
    }
    free(node);
  }else if(node->left==NULL||node->right==NULL){
    TreeNode* child;
    if(node->left!=NULL){
      child=node->left;
    }else if(node->right!=NULL){
      child=node->right;
    }
    if(node==tree->root){
      tree->root=child;
      child->parent=NULL;
    }else if(node==node->parent->left){
      node->parent->left=child;
      child->parent=node->parent;
    }else if (node==node->parent->right){
      node->parent->right=child;
      child->parent=node->parent;
    }
    free(node);
  }else{
    TreeNode* min = minimum(node->right);
    node->pair=min->pair;
    removeNode(tree, min);
  }
  
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
  TreeNode* nodo = NULL;
  TreeNode* aux = tree->root;
  TreeNode* parent= NULL;
  while(aux!=NULL){
    parent=aux;
    int cmp=tree->lower_than(key,aux->pair->key);
    if(cmp==0){
      nodo=aux;
      return nodo->pair;
    }
    if(cmp<0){
      aux=aux->left;
      nodo=parent;
    }else{
      aux=aux->right;
      nodo=aux;
    }
  }
  if(nodo!=NULL){
    return nodo->pair;
  }else{
    return NULL;
  }
}

Pair * firstTreeMap(TreeMap * tree) {
  TreeNode* minimo=minimum(tree->root);
  tree->current=minimo;
  return minimo->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
  if(tree->current->right!=NULL){
    TreeNode* minimo = minimum(tree->current->right);
    tree->current = minimo;
    return minimo->pair;
  }
  else{
    TreeNode* ancestor = tree->current->parent;
    while(ancestor!=NULL && tree->lower_than(ancestor->pair->key,tree->current->pair->key)){
      ancestor = ancestor->parent;
    }
    tree->current=ancestor;
    if(ancestor!=NULL){
      return ancestor->pair;
    }else{
      return NULL;
    }
  }
}
