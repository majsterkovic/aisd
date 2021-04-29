#include <Windows.h>
#include <iostream>
#include <algorithm>
#include <vector>

using std::cout, std::endl, std::max;

class AVL {

private:
    struct Node {
        int value;
        int bf;
        Node *left;
        Node *right;
    };

public:
    Node *head = nullptr;

    void push(int x) {
        Node **wskadr = &head;

        std::vector<Node **> path;
        path.push_back(wskadr);

        while ((*wskadr != nullptr)) {

            if (((*wskadr)->value) < x) {
                wskadr = &(*wskadr)->right;

            } else if (((*wskadr)->value) > x) {
                wskadr = &(*wskadr)->left;
            }
            path.push_back(wskadr);
        }

        *wskadr = new Node{x, 0, *wskadr, *wskadr};

        // propagacja współczynnika
        for (int i = path.size() - 2; i >= 0; i--) {
            int dir = 0;
            if (*path[i + 1] == (**path[i]).left) {
                dir = -1;
            } else if (*path[i + 1] == (**path[i]).right) {
                dir = 1;
            }
            (**path[i]).bf += dir;

            if ((**path[i]).bf == 0) {
                break;
            }
            if ((**path[i]).bf / 2 != 0) {
                //drzewo niewyważone - rotacje
                if ((**path[i]).bf == -2 && (**path[i + 1]).bf <= 0) {
                    cout << "rotuje R" << endl;
                    right(path[i]);
                    break;
                } else if ((**path[i]).bf == -2 && (**path[i + 1]).bf > 0) {
                    cout << "rotuje LR" << endl;
                    left(path[i + 1]);
                    right(path[i]);
                    break;
                } else if ((**path[i]).bf == 2 && (**path[i + 1]).bf >= 0) {
                    cout << "rotuje L" << endl;
                    left(path[i]);
                    break;
                } else if ((**path[i]).bf == 2 && (**path[i + 1]).bf < 0) {
                    cout << "rotuje RL" << endl;
                    right(path[i + 1]);
                    left(path[i]);
                    break;
                }

            }
        }
    }

    void right(Node **wskadr) {
        int ch, p;

        Node *parent = *wskadr;
        Node *child = parent->left;

        if ((*parent).bf == -2 && (*child).bf == 0) {
            p = 1;
            ch = -1;
        }
        if ((*parent).bf == -2 && (*child).bf == -1) {
            p = 0;
            ch = 0;
        }
        if ((*parent).bf == -2 && (*child).bf == -2) {
            p = 0;
            ch = 1;
        }
        if ((*parent).bf == -1 && (*child).bf == -1) {
            p = 1;
            ch = 1;
        }
        if ((*parent).bf == -1 && (*child).bf == 0) {
            p = 1;
            ch = 0;
        }
        if ((*parent).bf == -1 && (*child).bf == 1) {
            p = 2;
            ch = 0;
        }

        parent->left = child->right;
        parent->bf = ch;
        child->right = parent;
        child->bf = p;
        *wskadr = child;

    }

    void left(Node **wskadr) {

        int ch, p;

        Node *parent = *wskadr;
        Node *child = parent->right;

        if ((*parent).bf == 2 && (*child).bf == 0) {
            p = -1;
            ch = 1;
        }
        if ((*parent).bf == 2 && (*child).bf == 1) {
            p = 0;
            ch = 0;
        }
        if ((*parent).bf == 2 && (*child).bf == 2) {
            p = 0;
            ch = -1;
        }
        if ((*parent).bf == 1 && (*child).bf == 1) {
            p = -1;
            ch = -1;
        }
        if ((*parent).bf == 1 && (*child).bf == 0) {
            p = -1;
            ch = 0;
        }
        if ((*parent).bf == 1 && (*child).bf == -1) {
            p = -2;
            ch = 0;
        }

        parent->right = child->left;
        parent->bf = ch;
        child->left = parent;
        child->bf = p;
        *wskadr = child;

    }

    void remove(int x) {
        Node **cur = &head;

        cout << "usuwam" << x << endl;

        std::vector<Node **> path;
        path.push_back(cur);

        while (*cur && (**cur).value != x) {
            if (x > (**cur).value) {
                cur = &(**cur).right;
            } else if (x < (**cur).value) {
                cur = &(**cur).left;
            }
            path.push_back(cur);
        }
        //path.pop_back();

        Node *tmp;
        int dir = 0;


        if ((**cur).left == nullptr) {
            tmp = *cur;

            if (path.size() > 1) {
                if ((**path[path.size() - 2]).right == *cur) {
                    dir = 1;
                } else {
                    dir = -1;
                }
            }


            *cur = (**cur).right;
            delete tmp;

            int y = path.size();
            if (path.size() > 1) {

                for (int i = path.size() - 3; i >= 0; i--) {
                    (**path[i]).bf -= dir;

                    //drzewo niewyważone

                    if ((**path[i]).bf == -2 && (**path[i + 1]).bf <= 0) {
                        right(path[i]);
                    } else if ((**path[i]).bf == -2 && (**path[i + 1]).bf > 0) {
                        left(path[i + 1]);
                        right(path[i]);
                    } else if ((**path[i]).bf == 2 && (**path[i + 1]).bf >= 0) {
                        left(path[i]);
                    } else if ((**path[i]).bf == 2 && (**path[i + 1]).bf < 0) {
                        right(path[i + 1]);
                        left(path[i]);
                    }


                    if (i == 0) {
                        break;
                    }
                    if ((**path[i - 1]).right == *path[i]) {
                        dir = 1;
                    } else {
                        dir = -1;
                    }
                }
            }


        }
        else if ((**cur).right == nullptr) {
            tmp = *cur;

            if (path.size() > 1) {
                if ((**path[path.size() - 2]).right == *cur) {
                    dir = 1;
                } else {
                    dir = -1;
                }
            }

            *cur = (**cur).left;
            delete tmp;


            if (path.size() > 1) {
                for (int i = path.size() - 3; i >= 0; i--) {
                    (**path[i]).bf -= dir;

                    //drzewo niewyważone

                    if ((**path[i]).bf == -2 && (**path[i + 1]).bf <= 0) {
                        right(path[i]);

                    } else if ((**path[i]).bf == -2 && (**path[i + 1]).bf > 0) {
                        left(path[i + 1]);
                        right(path[i]);
                    } else if ((**path[i]).bf == 2 && (**path[i + 1]).bf >= 0) {
                        left(path[i]);
                    } else if ((**path[i]).bf == 2 && (**path[i + 1]).bf < 0) {
                        right(path[i + 1]);
                        left(path[i]);
                    }


                    if (i == 0) {
                        break;
                    }
                    if ((**path[i - 1]).right == *path[i]) {
                        dir = 1;
                    } else {
                        dir = -1;
                    }

                }
            }
        } else if ((**cur).right != nullptr && (**cur).right != nullptr) {
            int left_max = local_max((**cur).left);
            remove(left_max);
            (**cur).value = left_max;
        }
    }

    void visit_and_print(Node *adr) {
        if (adr != nullptr) {
            visit_and_print((*adr).left);
            touch(adr);
            visit_and_print((*adr).right);
        }
    }

    void touch(Node *adr) {
        cout << (*adr).value << " " << (*adr).bf << endl;
    }

    void print() {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        if (head == nullptr) {
            cout << "!empty!" << endl;
        }
        visit_and_print(head);
        cout << endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }

    bool contains(int x) {
        Node *adr = head;
        while (adr != nullptr) {
            if (adr->value < x) {
                adr = adr->right;
            } else if (adr->value > x) {
                adr = adr->left;
            } else if (adr->value == x) {
                return true;
            }
        }
        return false;
    }

    int local_max(Node *adr) {
        int m;
        while (adr != nullptr) {
            m = adr->value;
            adr = adr->right;
        }
        return m;
    }

    int max() {
        return local_max(head);
    }

};

int main() {
    AVL drzewo;

    int mn = 7;

    for (int i = 0; i <= 22; i++) {
        drzewo.push(i);
    }


    for (int i = 0; i <= 22; i++) {
        drzewo.remove(i);
    }


    return 0;
}