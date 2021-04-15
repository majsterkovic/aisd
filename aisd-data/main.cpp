#include <iostream>
#include <chrono>
#include <string>

#include "generator.h"
#include "LinkedList.h"
#include "BST.h"

int main()
{
    generator::start();

    auto start = chrono::steady_clock::now();
    auto stop = chrono::steady_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
    long long sum, x, avg;
    string op, structure;

    ifstream myfile;
    ofstream result;

    op = "push";
    structure = "linkedlist";
    for(int t = 0; t < size(generator::TYPES); t++)
    {
        for(int n = 0; n < size(generator::N); n++)
        {
            sum = 0;
            string source = (string)(generator::TYPES[t]) + "_" + to_string(generator::N[n]) + ".txt";
            myfile.open(source);
            result.open("res.txt", ios::app);
            x;

            for(int i = 0; i < 5; i++)
            {
                LinkedList obj;

                start = chrono::steady_clock::now();
                while(myfile >> x)
                {
                    obj.push(x);
                }
                stop = chrono::steady_clock::now();
                duration = chrono::duration_cast<chrono::microseconds>(stop - start);
                sum = sum + duration.count();
            }
            avg = sum/5;
            myfile.close();
            result << structure << ";" << op << ";" << (string)(generator::TYPES[t]) << ";" << generator::N[n] << ";" << avg << endl;
            result.close();
        }
    }

    op = "push";
    structure = "bst";
    for(int t = 0; t < size(generator::TYPES); t++)
    {
        for(int n = 0; n < size(generator::N); n++)
        {
            sum = 0;
            string source = (string)(generator::TYPES[t]) + "_" + to_string(generator::N[n]) + ".txt";
            myfile.open(source);
            result.open("res.txt", ios::app);
            x;

            for(int i = 0; i < 5; i++)
            {
                BST obj;

                start = chrono::steady_clock::now();
                while(myfile >> x)
                {
                    obj.push(x);
                }
                stop = chrono::steady_clock::now();
                duration = chrono::duration_cast<chrono::microseconds>(stop - start);
                sum = sum + duration.count();
            }
            avg = sum/5;
            myfile.close();
            result << structure << ";" << op << ";" << (string)(generator::TYPES[t]) << ";" << generator::N[n] << ";" << avg << endl;
            result.close();
        }
    }

}
