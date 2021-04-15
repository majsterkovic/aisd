#include <Windows.h>
#include <iostream>

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
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
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
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

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


    bool remove(int x)
    {
        if(contains(x))
        {
            
            Node **cur = &head;
            while(*cur && (**cur).value != x)
            {
                cur = &(**cur).next;
            }
            //(**cur).value == x;
            Node *tmp = *cur;
            *cur = (**cur).next;
            delete tmp;
        }
    }

};

int main()
{
    LinkedList lista;
    lista.print();

    lista.push(2);
    lista.push(1);
    lista.push(3);
    lista.push(4);

    lista.print();

    lista.remove(1);
    lista.remove(4);

    lista.print();

    return 0;
}
