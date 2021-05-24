//
// Created by Mariusz on 15.04.2021.
//

#ifndef AISD_DATA_BST_H
#define AISD_DATA_BST_H

#include <iostream>

using std::cout, std::endl;

class BST
{

private:

    struct Node
    {
        int value;
        Node *left;
        Node *right;
    };

public:
    Node *head = nullptr;

    void push(int x)
    {
        Node **wskadr = &head;

        while( (*wskadr != nullptr) )
        {

            if( ((*wskadr)->value) < x )
            {
                wskadr = &(*wskadr)->right;

            }
            else if( ((*wskadr)->value) > x )
            {
                wskadr = &(*wskadr)->left;
            }
        }

        *wskadr = new Node{x, *wskadr, *wskadr};
    }

    void visit_and_print(Node* adr)
    {
        if(adr != nullptr)
        {
            visit_and_print((*adr).left);
            touch(adr);
            visit_and_print((*adr).right);
        }
    }

    void touch(Node* adr)
    {
        printf("%d\n", (*adr).value);
    }

    void print()
    {
        if(head == nullptr)
        {
            printf("!empty!\n");
        }
        visit_and_print(head);
        printf("\n");
    }

    bool contains(int x)
    {
        Node* adr = head;
        while(adr != nullptr)
        {
            if(adr->value < x)
            {
                adr = adr->right;
            }
            else if(adr->value > x)
            {
                adr = adr->left;
            }
            else if(adr->value == x)
            {
                return true;
            }
        }
        return false;
    }

    int local_max(Node* adr)
    {
        int m;
        while(adr != nullptr)
        {
            m = adr->value;
            adr = adr->right;
        }
        return m;
    }

    int max()
    {
        return local_max(head);
    }

    void remove(int x)
    {
        Node** cur = &head;
        while(*cur && (**cur).value != x)
        {
            if(x > (**cur).value)
            {
                cur = &(**cur).right;
            }
            else if(x < (**cur).value)
            {
                cur = &(**cur).left;
            }
        }

        Node *tmp;
        if( (**cur).left == nullptr)
        {
            tmp = *cur;
            *cur = (**cur).right;
            delete tmp;
        }
        else if( (**cur).right == nullptr)
        {
            tmp = *cur;
            *cur = (**cur).left;
            delete tmp;
        }
        else if( (**cur).right != nullptr && (**cur).right != nullptr )
        {
            int left_max = local_max((**cur).left);
            remove(left_max);
            (**cur).value = left_max;
        }

    }

};


#endif //AISD_DATA_BST_H
