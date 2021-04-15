//
// Created by Mariusz on 15.04.2021.
//

#ifndef AISD_DATA_LINKEDLIST_H
#define AISD_DATA_LINKEDLIST_H

#include <fstream>
#include <iostream>
#include <string>

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
        // &head to adres wskaźnika zawierającego adres głowy
        // *pnode to adres głowy
        // **pnode to wskaźnik na wskaźnik

        // dopóki wskaźnik wskazuje na pusty adres (czyli początkowo head) oraz wartość pod tym adresem jest mniejsza niż x
        while( (*wskadr != nullptr) && ((*wskadr)->value) < x)
        {
            //zwiększaj adres
            wskadr = &(*wskadr)->next;
        }
        // np. pod wskaźnik *head wrzuć adres nowego węzła z wartościami {x, 0}
        *wskadr = new Node{x, *wskadr};
    }

    void print()
    {
        // ustawianie koloru konsoli

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
        Node **cur = &head;
        while(*cur && (**cur).value != x)
        {
            cur = &(**cur).next;
        }
        Node *tmp = *cur;
        *cur = (**cur).next;
        delete tmp;
    }

};

#endif //AISD_DATA_LINKEDLIST_H
