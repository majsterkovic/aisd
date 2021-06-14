#ifndef UUUU_GENERATOR_H
#define UUUU_GENERATOR_H

#pragma once

#include <utility>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <numeric>
#include <string>
#include <array>

class generator
{
public:

    constexpr static std::array<int, 2>SIZES_BIG = {190, 200};
    constexpr static std::array<int, 10>SIZES_SMALL = {6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    constexpr static std::array<int, 3>DENSITY = {30, 50,70};


    static void edges(std::string &name, int n, int wsp)
    {
        std::ofstream file;
        std::vector<int>v(n*(n-1)/2, 0);

        for(int i = 0; i < wsp*n*(n-1)/200; i++)
        {
            v[i] = 1;
        }
        std::random_device r;

        std::random_device myRandomDevice;
        unsigned seed2 = myRandomDevice();
        unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
        unsigned seed3 = myRandomDevice();
        unsigned seed4 = std::chrono::steady_clock::now().time_since_epoch().count();
        unsigned sd = (seed3 + seed)*seed2+seed4;

        std::default_random_engine rng(sd);
        std::shuffle(v.begin(), v.end(), rng);

        int counter = 0;

        file.open(name, std::ofstream::out | std::ofstream::trunc);

        std::vector<int>first_path(n);
        std::iota(first_path.begin(), first_path.end(), 1);
        std::shuffle(first_path.begin(), first_path.end(), rng);

        for(int i = 0; i < n; i++)
        {
            file << first_path[i] << " " << first_path[(i + 1)%n] << "\n";
        }

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

        for (int d : DENSITY)
        {
            for (int s : SIZES_BIG)
            {
                name = std::to_string(s) + "_" + std::to_string(d) + "_Hamilton.txt";
                edges(name, s, d);
            }
        }
        std::cout << "Koniec" << std::endl;
    }
};


#endif //UNTITLED_GENERATOR_H
