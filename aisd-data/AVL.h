//
// Created by Mariusz on 24.04.2021.
//

#ifndef AISD_DATA_AVL_H
#define AISD_DATA_AVL_H


#include<iostream>
using namespace std;

template <typename T>
class AVL{
public:
    class node{
    public:
        T key;
        int height;
        node * left;
        node * right;
        node(T k){
            height = 1;
            key = k;
            left = NULL;
            right = NULL;
        }
    };
    node * root = NULL;
    int n;
    void push(T x){
        root=insertUtil(root, x);
    }
    void remove(T x){
        root=removeUtil(root, x);
    }

    void print()
    {
        if(root == nullptr)
        {
            printf("!empty!\n");
        }
        visit_and_print(root);
        printf("\n");
    }

    bool contains(int x)
    {
        node* adr = root;
        while(adr != nullptr)
        {
            if(adr->key < x)
            {
                adr = adr->right;
            }
            else if(adr->key > x)
            {
                adr = adr->left;
            }
            else if(adr->key == x)
            {
                return true;
            }
        }
        return false;
    }



    void visit_and_print(node* adr)
    {
        if(adr != nullptr)
        {
            visit_and_print((*adr).left);
            touch(adr);
            visit_and_print((*adr).right);
        }
    }

    void touch(node* adr)
    {
        cout << (*adr).key << endl;
    }

    int height(node * head){
        if(head==NULL) return 0;
        return head->height;
    }
    node * rightRotation(node * head){
        node * newhead = head->left;
        head->left = newhead->right;
        newhead->right = head;
        head->height = 1+max(height(head->left), height(head->right));
        newhead->height = 1+max(height(newhead->left), height(newhead->right));
        return newhead;
    }

    node * leftRotation(node * head){
        node * newhead = head->right;
        head->right = newhead->left;
        newhead->left = head;
        head->height = 1+max(height(head->left), height(head->right));
        newhead->height = 1+max(height(newhead->left), height(newhead->right));
        return newhead;
    }

    void inorderUtil(node * head){
        if(head==NULL) return ;
        inorderUtil(head->left);
        cout<<head->key<<" "<<endl;
        inorderUtil(head->right);
    }

    node * insertUtil(node * head, T x){
        if(head==NULL){
            n+=1;
            node * temp = new node(x);
            return temp;
        }
        if(x < head->key) head->left = insertUtil(head->left, x);
        else if(x > head->key) head->right = insertUtil(head->right, x);
        head->height = 1 + max(height(head->left), height(head->right));
        int bal = height(head->left) - height(head->right);
        if(bal>1){
            if(x < head->left->key){
                return rightRotation(head);
            }else{
                head->left = leftRotation(head->left);
                return rightRotation(head);
            }
        }else if(bal<-1){
            if(x > head->right->key){
                return leftRotation(head);
            }else{
                head->right = rightRotation(head->right);
                return leftRotation(head);
            }
        }
        return head;
    }
    node * removeUtil(node * head, T x){
        if(head==NULL) return NULL;
        if(x < head->key){
            head->left = removeUtil(head->left, x);
        }else if(x > head->key){
            head->right = removeUtil(head->right, x);
        }else{
            node * r = head->right;
            if(head->right==NULL){
                node * l = head->left;
                delete(head);
                head = l;
            }else if(head->left==NULL){
                delete(head);
                head = r;
            }else{
                while(r->left!=NULL) r = r->left;
                head->key = r->key;
                head->right = removeUtil(head->right, r->key);
            }
        }
        if(head==NULL) return head;
        head->height = 1 + max(height(head->left), height(head->right));
        int bal = height(head->left) - height(head->right);
        if(bal>1){
            if(height(head->left) >= height(head->right)){
                return rightRotation(head);
            }else{
                head->left = leftRotation(head->left);
                return rightRotation(head);
            }
        }else if(bal < -1){
            if(height(head->right) >= height(head->left)){
                return leftRotation(head);
            }else{
                head->right = rightRotation(head->right);
                return leftRotation(head);
            }
        }
        return head;
    }
    int searchUtil(node * head, T x){
        if(head == NULL) return NULL;
        T k = head->key;
        if(k == x) return 1;
        if(k > x) return searchUtil(head->left, x);
        if(k < x) return searchUtil(head->right, x);
    }
};


#endif //AISD_DATA_AVL_H
