//
// Created by Mariusz on 15.04.2021.
//

#ifndef AISD_DATA_GENERATOR_H
#define AISD_DATA_GENERATOR_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include <random>
#include <vector>
#include <string>

using namespace std;

class generator
{
public:

    constexpr static int N[10] = {5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000};
    constexpr static const char* TYPES[5] = {"random", "sorted", "rev_sorted", "A", "V"};

    struct sequence
    {
    private:
        int current = 0;
        const int step = 1;
    public:
        explicit sequence(const int start = 0, const int step = 1)
                : current(start), step(step) { }
        int operator()()
        {
            return exchange(current, current + step);
        }
    };

    static void start()
    {


        string name;
        ofstream myfile;
        vector<long long> vec;

        // random
        for (int i = 0; i < size(N); i++) {
            name = (string)(TYPES[0]) + "_" + to_string(N[i]) + ".txt";

            vec.clear();
            vec.resize(N[i]);

            generate(vec.begin(), vec.end(), sequence(0, 2));

            auto rng = default_random_engine{};
            shuffle(vec.begin(), vec.end(), rng);

            myfile.open(name);

            vector<long long>::iterator it;
            for (it = vec.begin(); it != vec.end(); it++) {
                myfile << *it << "\n";
            }

            myfile.close();
        }

        //sorted
        for (int i = 0; i < size(N); i++) {
            name = (string)(TYPES[1]) + "_" + to_string(N[i]) + ".txt";

            vec.clear();
            vec.resize(N[i]);

            generate(vec.begin(), vec.end(), sequence(0, 2));

            myfile.open(name);

            vector<long long>::iterator it;

            for (it = vec.begin(); it != vec.end(); it++) {
                myfile << *it << "\n";
            }

            myfile.close();
        }

        //sorted rev
        for (int i = 0; i < size(N); i++) {
            name = (string)(TYPES[2]) + "_" + to_string(N[i]) + ".txt";

            vec.clear();
            vec.resize(N[i]);

            generate(vec.begin(), vec.end(), sequence(0, 2));
            reverse(vec.begin(), vec.end());

            myfile.open(name);

            vector<long long>::iterator it;
            for (it = vec.begin(); it != vec.end(); it++) {
                myfile << *it << "\n";
            }

            myfile.close();
        }
        //A-shaped
        for (int i = 0; i < size(N); i++) {
            name = (string)(TYPES[3]) + "_" + to_string(N[i]) + ".txt";

            vec.clear();
            vec.resize(N[i]);

            generate(vec.begin(), vec.end(), sequence(0, 2));
            reverse(vec.begin() + vec.size() / 2, vec.end());

            myfile.open(name);

            vector<long long>::iterator it;
            for (it = vec.begin(); it != vec.end(); it++) {
                myfile << *it << "\n";
            }

            myfile.close();
        }

        //A-shaped
        for (int i = 0; i < size(N); i++) {
            name = (string)(TYPES[4]) + "_" + to_string(N[i]) + ".txt";

            vec.clear();
            vec.resize(N[i]);

            generate(vec.begin(), vec.end(), sequence(0, 2));
            reverse(vec.begin(), vec.begin() + vec.size() / 2);

            myfile.open(name);

            vector<long long>::iterator it;
            for (it = vec.begin(); it != vec.end(); it++) {
                myfile << *it << "\n";
            }

            myfile.close();
        }
    }
};

#endif //AISD_DATA_GENERATOR_H
