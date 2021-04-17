#include <Windows.h>
#include <iostream>
#include <algorithm>
#include <vector>

using std::cout, std::endl, std::max;

class BST
{

private:

    struct Node
    {
        int value;
        int bf;
        Node *left;
        Node *right;
    };

public:
    Node *head = nullptr;

    void push(int x)
    {
        Node **wskadr = &head;
        std::vector<Node**>path;

        path.push_back(wskadr);

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
            path.push_back(wskadr);
        }

        *wskadr = new Node{x, 0, *wskadr, *wskadr};

        std::vector<Node**>::iterator it;
        for(it=path.begin(); it!=path.end(); ++it)
        {
            set_bf(*it);
        }

    }


    int height(Node** wskadr)
    {
        if(*wskadr == nullptr)
        {
            return 0;
        }
        else return 1 + std::max(height(&(*wskadr)->left), height(&(*wskadr)->right));
    }

    void set_bf(Node **wskadr)
    {
        (*wskadr)->bf = height(&(*wskadr)->right) - height(&(*wskadr)->left);
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
        cout << (*adr).value << " " << (*adr).bf << endl;
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
    drzewo.push(5);
    drzewo.push(8);
    drzewo.push(11);

    drzewo.print();

    cout << drzewo.height(&(drzewo.head->right->left));

    return 0;
}
