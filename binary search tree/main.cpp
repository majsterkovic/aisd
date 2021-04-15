#include <Windows.h>
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

    void visit(Node* adr)
    {
        if(adr != nullptr)
        {
            visit((*adr).left);
            touch(adr);
            visit((*adr).right);
        }
    }

    void touch(Node* adr)
    {
        cout << (*adr).value << endl;
    }

    void print()
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        if(head == nullptr)
        {
            cout << "!empty!" << endl;
        }
        visit_and_print(head);
        cout << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
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

int main()
{
    BST drzewo;

    drzewo.push(2);

    drzewo.print();

    drzewo.remove(2);

    drzewo.print();

    return 0;
}
