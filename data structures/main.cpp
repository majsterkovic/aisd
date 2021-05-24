#include <iostream>
#include <chrono>
#include <string>

#include "generator.h"
#include "LinkedList.h"
#include "BST.h"
#include "AVL.h"

int main() {
    generator::start();

    auto start = chrono::steady_clock::now();
    auto stop = chrono::steady_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    long long sum, x, avg;
    string op, structure;

    ifstream myfile;
    ofstream result;

    result.open("res.csv", ofstream::out | ofstream::trunc);
    result.close();


    op = "remove";
    structure = "linkedlist";

//    for (int t = 0; t < size(generator::TYPES); t++) {
//        for (int n = 0; n < size(generator::N); n++) {
//            sum = 0;
//            string source = (string) (generator::TYPES[t]) + "_" + to_string(generator::N[n]) + ".txt";
//
//            result.open("res.csv", ios::app);
//
//            for (int i = 0; i < 4; i++) {
//
//                LinkedList obj;
//
//                ifstream file;
//                file.open("random_" + to_string(generator::N[n]) + ".txt");
//                while (file >> x) {
//                    obj.push(x);
//                }
//                file.close();
//                myfile.open(source);
//                start = chrono::steady_clock::now();
//                while (myfile >> x) {
//                    obj.remove(x);
//                }
//                stop = chrono::steady_clock::now();
//                duration = chrono::duration_cast<chrono::microseconds>(stop - start);
//                sum = sum + duration.count();
//                myfile.close();
//            }
//            avg = sum / 4;
//
//            result << structure << ";" << op << ";" << (string) (generator::TYPES[t]) << ";" << generator::N[n] << ";"
//                   << avg << endl;
//            result.close();
//        }
//    }
//
//    op = "remove";
//    structure = "bst";
//
//    for (int t = 0; t < size(generator::TYPES); t++) {
//        for (int n = 0; n < size(generator::N); n++) {
//            sum = 0;
//            string source = (string) (generator::TYPES[t]) + "_" + to_string(generator::N[n]) + ".txt";
//
//            result.open("res.csv", ios::app);
//
//            for (int i = 0; i < 4; i++) {
//
//                BST obj;
//
//                ifstream file;
//                file.open("random_" + to_string(generator::N[n]) + ".txt");
//                while (file >> x) {
//                    obj.push(x);
//                }
//                file.close();
//                myfile.open(source);
//                start = chrono::steady_clock::now();
//                while (myfile >> x) {
//                    obj.remove(x);
//                }
//                stop = chrono::steady_clock::now();
//                myfile.close();
//                duration = chrono::duration_cast<chrono::microseconds>(stop - start);
//                sum = sum + duration.count();
//            }
//            avg = sum / 4;
//            myfile.close();
//            result << structure << ";" << op << ";" << (string) (generator::TYPES[t]) << ";" << generator::N[n] << ";"
//                   << avg << endl;
//            result.close();
//        }
//    }
//
//    op = "remove";
//    structure = "avl";
//    for (int t = 0; t < size(generator::TYPES); t++) {
//        for (int n = 0; n < size(generator::N); n++) {
//            sum = 0;
//            string source = (string) (generator::TYPES[t]) + "_" + to_string(generator::N[n]) + ".txt";
//            result.open("res.csv", ios::app);
//            for (int i = 0; i < 4; i++) {
//
//                AVL<int> obj;
//
//                ifstream file;
//                file.open("random_" + to_string(generator::N[n]) + ".txt");
//                while (file >> x) {
//                    obj.push(x);
//                }
//                file.close();
//                myfile.open(source);
//                start = chrono::steady_clock::now();
//                while (myfile >> x) {
//                    obj.remove(x);
//                }
//                stop = chrono::steady_clock::now();
//                duration = chrono::duration_cast<chrono::microseconds>(stop - start);
//                sum = sum + duration.count();
//                myfile.close();
//            }
//            avg = sum / 4;
//            result << structure << ";" << op << ";" << (string) (generator::TYPES[t]) << ";" << generator::N[n] << ";"
//                   << avg << endl;
//            result.close();
//        }
//    }

//    op = "contains";
//    structure = "linkedlist";
//    for (int t = 0; t < size(generator::TYPES); t++) {
//        for (int n = 0; n < size(generator::N); n++) {
//            sum = 0;
//            string source = (string) (generator::TYPES[t]) + "_" + to_string(generator::N[n]) + ".txt";
//            result.open("res.csv", ios::app);
//            for (int i = 0; i < 4; i++) {
//                LinkedList obj;
//                ifstream file;
//                myfile.open(source);
//                file.open("random_" + to_string(generator::N[n]) + ".txt");
//                while (file >> x) {
//                    obj.push(x);
//                }
//                myfile.open(source);
//                start = chrono::steady_clock::now();
//                while (myfile >> x) {
//                    obj.contains(x);
//                }
//                stop = chrono::steady_clock::now();
//                myfile.close();
//                duration = chrono::duration_cast<chrono::microseconds>(stop - start);
//                sum = sum + duration.count();
//            }
//            avg = sum / 4;
//            result << structure << ";" << op << ";" << (string) (generator::TYPES[t]) << ";" << generator::N[n] << ";"
//                   << avg << endl;
//            result.close();
//        }
//    }
//
//    op = "contains";
//    structure = "bst";
//    for (int t = 0; t < size(generator::TYPES); t++) {
//        for (int n = 0; n < size(generator::N); n++) {
//            sum = 0;
//            string source = (string) (generator::TYPES[t]) + "_" + to_string(generator::N[n]) + ".txt";
//
//            result.open("res.csv", ios::app);
//            for (int i = 0; i < 4; i++) {
//                BST obj;
//                myfile.open(source);
//                while (myfile >> x) {
//                    obj.push(x);
//                }
//                myfile.close();
//                myfile.open(source);
//                start = chrono::steady_clock::now();
//                while (myfile >> x) {
//                    obj.contains(x);
//                }
//                stop = chrono::steady_clock::now();
//                myfile.close();
//                duration = chrono::duration_cast<chrono::microseconds>(stop - start);
//                sum = sum + duration.count();
//            }
//            avg = sum / 4;
//            result << structure << ";" << op << ";" << (string) (generator::TYPES[t]) << ";" << generator::N[n] << ";"
//                   << avg << endl;
//            result.close();
//        }
//    }
//
//    op = "contains";
//    structure = "avl";
//    for (int t = 0; t < size(generator::TYPES); t++) {
//        for (int n = 0; n < size(generator::N); n++) {
//            sum = 0;
//            string source = (string) (generator::TYPES[t]) + "_" + to_string(generator::N[n]) + ".txt";
//            myfile.open(source);
//            result.open("res.csv", ios::app);
//            for (int i = 0; i < 4; i++) {
//                AVL<int> obj;
//                myfile.open(source);
//                while (myfile >> x) {
//                    obj.push(x);
//                }
//                myfile.close();
//                myfile.open(source);
//                start = chrono::steady_clock::now();
//                while (myfile >> x) {
//                    obj.contains(x);
//                }
//                stop = chrono::steady_clock::now();
//                myfile.close();
//                duration = chrono::duration_cast<chrono::microseconds>(stop - start);
//                sum = sum + duration.count();
//            }
//            avg = sum / 4;
//            result << structure << ";" << op << ";" << (string) (generator::TYPES[t]) << ";" << generator::N[n] << ";"
//                   << avg << endl;
//            result.close();
//        }
//    }

//    op = "push";
//    structure = "linkedlist";
//    for (int t = 0; t < size(generator::TYPES); t++) {
//        for (int n = 0; n < size(generator::N); n++) {
//            sum = 0;
//            string source = (string) (generator::TYPES[t]) + "_" + to_string(generator::N[n]) + ".txt";
//
//            result.open("res.csv", ios::app);
//
//            for (int i = 0; i < 4; i++) {
//                LinkedList obj;
//                myfile.open(source);
//                start = chrono::steady_clock::now();
//                while (myfile >> x) {
//                    obj.push(x);
//                }
//                stop = chrono::steady_clock::now();
//                duration = chrono::duration_cast<chrono::microseconds>(stop - start);
//                sum = sum + duration.count();
//                myfile.close();
//            }
//            avg = sum / 4;
//
//            result << structure << ";" << op << ";" << (string) (generator::TYPES[t]) << ";" << generator::N[n] << ";"
//                   << avg << endl;
//            result.close();
//        }
//    }
//
//    op = "push";
//    structure = "bst";
//    for (int t = 0; t < size(generator::TYPES); t++) {
//        for (int n = 0; n < size(generator::N); n++) {
//            sum = 0;
//            string source = (string) (generator::TYPES[t]) + "_" + to_string(generator::N[n]) + ".txt";
//            result.open("res.csv", ios::app);
//
//            for (int i = 0; i < 4; i++) {
//                BST obj;
//                myfile.open(source);
//                start = chrono::steady_clock::now();
//                while (myfile >> x) {
//                    obj.push(x);
//                }
//                stop = chrono::steady_clock::now();
//                myfile.close();
//                duration = chrono::duration_cast<chrono::microseconds>(stop - start);
//                sum = sum + duration.count();
//            }
//            avg = sum / 4;
//
//            result << structure << ";" << op << ";" << (string) (generator::TYPES[t]) << ";" << generator::N[n] << ";"
//                   << avg << endl;
//            result.close();
//        }
//    }
//
//    op = "push";
//    structure = "avl";
//    for (int t = 0; t < size(generator::TYPES); t++) {
//        for (int n = 0; n < size(generator::N); n++) {
//            sum = 0;
//            string source = (string) (generator::TYPES[t]) + "_" + to_string(generator::N[n]) + ".txt";
//
//            result.open("res.csv", ios::app);
//
//            for (int i = 0; i < 4; i++) {
//                AVL<int> obj;
//                myfile.open(source);
//                start = chrono::steady_clock::now();
//                while (myfile >> x) {
//                    obj.push(x);
//                }
//                stop = chrono::steady_clock::now();
//                duration = chrono::duration_cast<chrono::microseconds>(stop - start);
//                sum = sum + duration.count();
//                myfile.close();
//            }
//            avg = sum / 4;
//
//            result << structure << ";" << op << ";" << (string) (generator::TYPES[t]) << ";" << generator::N[n] << ";"
//                   << avg << endl;
//            result.close();
//        }
//    }



    op = "print";
    structure = "bst";
    for (int t = 0; t < size(generator::TYPES); t++) {
        for (int n = 0; n < size(generator::N)-2; n++) {
            sum = 0;
            string source = (string) (generator::TYPES[t]) + "_" + to_string(generator::N[n]) + ".txt";
            result.open("res.csv", ios::app);
            for (int i = 0; i < 4; i++) {
                BST obj;
                myfile.open(source);
                while (myfile >> x) {
                    obj.push(x);
                }
                start = chrono::steady_clock::now();
                obj.print();
                stop = chrono::steady_clock::now();
                duration = chrono::duration_cast<chrono::microseconds>(stop - start);
                sum = sum + duration.count();
                myfile.close();
            }
            avg = sum / 4;
            result << structure << ";" << op << ";" << (string) (generator::TYPES[t]) << ";" << generator::N[n] << ";"
                   << avg << endl;
            result.close();
        }
    }
//
//    op = "print";
//    structure = "avl";
//    for (int t = 0; t < size(generator::TYPES); t++) {
//        for (int n = 0; n < size(generator::N); n++) {
//            sum = 0;
//            string source = (string) (generator::TYPES[t]) + "_" + to_string(generator::N[n]) + ".txt";
//            result.open("res.csv", ios::app);
//            for (int i = 0; i < 4; i++) {
//                AVL<int> obj;
//                myfile.open(source);
//                while (myfile >> x) {
//                    obj.push(x);
//                }
//                start = chrono::steady_clock::now();
//                obj.print();
//                stop = chrono::steady_clock::now();
//                myfile.close();
//                duration = chrono::duration_cast<chrono::microseconds>(stop - start);
//                sum = sum + duration.count();
//            }
//            avg = sum / 4;
//            result << structure << ";" << op << ";" << (string) (generator::TYPES[t]) << ";" << generator::N[n] << ";"
//                   << avg << endl;
//            result.close();
//        }
//    }
//
//    op = "print";
//    structure = "linkedlist";
//    for (int t = 0; t < size(generator::TYPES); t++) {
//        for (int n = 0; n < size(generator::N); n++) {
//            sum = 0;
//            string source = (string) (generator::TYPES[t]) + "_" + to_string(generator::N[n]) + ".txt";
//            result.open("res.csv", ios::app);
//            for (int i = 0; i < 4; i++) {
//                LinkedList obj;
//                myfile.open(source);
//                while (myfile >> x) {
//                    obj.push(x);
//                }
//                start = chrono::steady_clock::now();
//                obj.print();
//                stop = chrono::steady_clock::now();
//                duration = chrono::duration_cast<chrono::microseconds>(stop - start);
//                sum = sum + duration.count();
//                myfile.close();
//            }
//            avg = sum / 4;
//            result << structure << ";" << op << ";" << (string) (generator::TYPES[t]) << ";" << generator::N[n] << ";"
//                   << avg << endl;
//            result.close();
//        }
//    }

}
