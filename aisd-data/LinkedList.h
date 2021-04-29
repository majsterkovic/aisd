//
// Created by Mariusz on 15.04.2021.
//

#ifndef AISD_DATA_LINKEDLIST_H
#define AISD_DATA_LINKEDLIST_H

using namespace std;

class LinkedList
{

private:

    struct Node
    {
        int value;
        Node *next;
    };

    Node *head = nullptr;

public:
    void push(int x)
    {
        Node **wskadr = &head;

        while( (*wskadr != nullptr) && ((*wskadr)->value) < x)
        {
            wskadr = &(*wskadr)->next;
        }
        *wskadr = new Node{x, *wskadr};
    }

    void print()
    {
        Node *wskadr = head;
        if(wskadr == nullptr)
        {
            printf("!empty!\n");
        }
        else
        {
            while(wskadr != nullptr)
            {
                printf("%d\n", wskadr->value);
                wskadr = wskadr->next;
            }
        }
        printf("\n");

    }

    bool contains(int x)
    {
        Node *adr = head;

        while(adr != nullptr)
        {
            if(adr->value == x)
            {
                return true;
            }
            adr = adr->next;
        }
        return false;
    }

    void remove(int x)
    {
        Node **wskadr = &head;
        while(*wskadr && (**wskadr).value != x)
        {
            wskadr = &(**wskadr).next;
        }
        Node *tmp = *wskadr;
        *wskadr = (**wskadr).next;
        delete tmp;
    }

};

#endif //AISD_DATA_LINKEDLIST_H
