//
// Created by Mariusz on 14.05.2021.
//

#ifndef UNTITLED99_GENERATOR_H
#define UNTITLED99_GENERATOR_H

#pragma once

#include <utility>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <string>
#include <array>

class generator
{
public:
    constexpr static std::array<int, 10>SIZES_SMALL = {30, 60, 90, 120, 150, 180, 210, 240, 270, 300};
    constexpr static std::array<int, 0>SIZES_BIG = {};
    static void edges(std::string &name, int n)
    {
        std::ofstream file;
        std::vector<int>v(n*(n-1)/2, 0);

        for(int i = 0; i < 0.5*n*(n-1)/2; i++)
        {
            v[i] = 1;
        }

        auto rng = std::default_random_engine{};
        std::shuffle(v.begin(), v.end(), rng);

        int counter = 0;

        file.open(name);

        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < i; j++)
            {
                if(v[counter++])
                {
                    file << i+1 << " " << j+1 << "\n";
                }
            }
        }
        file.close();
    }

    static void start()
    {
        std::string name;
        std::ofstream myfile;

        for (int i : SIZES_SMALL)
        {
            name = std::to_string(i) + ".txt";
            edges(name, i);
        }

        for (int i : SIZES_BIG)
        {
            name = std::to_string(i) + ".txt";
            edges(name, i);
        }
        std::cout << "Koniec" << std::endl;

    }
};

#endif //UNTITLED99_GENERATOR_H
