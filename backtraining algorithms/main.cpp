#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <chrono>
#include <string>
#include <fstream>

#include "generator.h"

class adjacency_matrix {

public:

    std::vector<std::vector<int>>M;

    adjacency_matrix(int n)
    {
        M = std::vector<std::vector<int>>(n, std::vector<int>(n, 0));
    }

    void add_edge(int From, int To)
    {
        M[From - 1][To - 1] = 1;
        M[To - 1][From - 1] = 1;
    }

    void delete_edge(int From, int To)
    {
        M[From - 1][To - 1] = 0;
        M[To - 1][From - 1] = 0;
    }

    void print() {
        for (auto const & row : M) {
            for (auto const & value : row) {
                std::cout << value << "\t";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    bool check_exist(int From, int To)
    {
        return (bool)M[From - 1][To - 1];
    }

    int order() {
        return (int)M[0].size();
    }

    std::set<int> successors(int V) {
        --V;
        std::set<int> S;
        for (int i = 0; i < M[V].size(); i++) {
            if (M[V][i] == 1) {
                S.insert(i + 1);
            }
        }
        return S;
    }

};

template<class GraphType>
std::vector<int> DFS_Euler(GraphType &G, int v, std::vector<int>&result)
{
    int SIZE = G.order();
    for(int u = 1; u <= SIZE; u++)
    {
        if(G.check_exist(u, v))
        {
            G.delete_edge(v, u);
            DFS_Euler(G, u, result);
        }
    }
    result.push_back(v);
    return result;
}


template<class GraphType>
bool Hamiltonian(int &start, int &v, int &visited, int &k, std::vector<int>&Path, std::vector<bool>&O, GraphType &G)
{
    //std::cout << v << std::endl;
    O[v-1] = true;
    visited++;
    for(auto u : G.successors(v))
    {
        if(u == start && visited == G.order())
        {
            Path[k] = v;
            k++;
            return true;
        }
        if(O[u-1] == false)
        {
            if(Hamiltonian(start, u, visited, k, Path, O, G))
            {
                Path[k] = u;
                k++;
                return true;
            }
        }
    }
    O[v-1] = false;
    visited--;
    return false;
}

template<class GraphType>
bool Hcycle(GraphType &G, std::vector<int>&Path)
{
    std::vector<bool>O(G.order(), false);

    int start = 1;
    int visited = 0;
    int k = 1;
    Path[0] = 1;

    return Hamiltonian(start, start, visited, k, Path, O, G);
}


int main() {

    std::ifstream file;
    std::ofstream result;



    auto start = std::chrono::steady_clock::now();
    auto stop = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    long long sum;
    int x, y;

    int proby = 3;

    result.open("res.csv", std::ofstream::out | std::ofstream::trunc);
    result.close();

//    for(auto & s : generator::SIZES_BIG)
//    {
//        for(auto & d : generator::DENSITY)
//        {
//            generator::start();
//            result.open("res.csv", std::ios::app);
//            sum = 0;
//
//            for(int i = 0; i < proby; i++)
//            {
//                file.open(std::to_string(s) + "_" + std::to_string(d) + "_Euler.txt");
//
//                adjacency_matrix G(s);
//
//                while (file >> x >> y)
//                {
//                    G.add_edge(x, y);
//                }
//
//                file.close();
//
//                std::vector<int>Ecycle_list;
//
//                start = std::chrono::steady_clock::now();
//
//                DFS_Euler<adjacency_matrix>(G, 1, Ecycle_list);
//
//                stop = std::chrono::steady_clock::now();
//
//                for(auto el : Ecycle_list)
//                {
//                    std::cout << el << std::endl;
//                }
//                std::cout << std::endl;
//
//
//                duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
//                sum = sum + duration.count();
//            }
//            result << "Euler" << ";" << s << ";" << d << ";" << sum/proby << std::endl;
//            result.close();
//
//        }
//    }

    for(auto & s : generator::SIZES_BIG)
    {
        for(auto & d : generator::DENSITY)
        {

            result.open("res.csv", std::ios::app);
            sum = 0;

            for(int i = 0; i < proby; i++)
            {

                generator::start();
                file.open(std::to_string(s) + "_" + std::to_string(d) + "_Hamilton.txt");

                adjacency_matrix G(s);

                while (file >> x >> y)
                {
                    G.add_edge(x, y);
                }

                file.close();

                start = std::chrono::steady_clock::now();

                std::vector<int>Hcycle_list(G.order()+1);

                if(Hcycle<adjacency_matrix>(G, Hcycle_list))
                {
                    for(auto el : Hcycle_list)
                    {
                        std::cout << el << std::endl;
                    }
                    std::cout << std::endl;
                }

                stop = std::chrono::steady_clock::now();
                duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
                sum = sum + duration.count();
            }
            result << "Hamilton" << ";" << s << ";" << d << ";" << sum/proby << std::endl;
            result.close();

        }
    }

    for(auto & s : generator::SIZES_BIG)
    {

        for(auto & d : generator::DENSITY)
        {
            result.open("res.csv", std::ios::app);
            sum = 0;

            for(int i = 0; i < proby; i++)
            {
                file.open("w" + std::to_string(s) + "_" + std::to_string(d) + "_Euler.txt");

                adjacency_matrix G(s);

                while (file >> x >> y)
                {
                    G.add_edge(x, y);
                }

                file.close();

                std::vector<int>Ecycle_list;

                start = std::chrono::steady_clock::now();

                DFS_Euler<adjacency_matrix>(G, 1, Ecycle_list);

                stop = std::chrono::steady_clock::now();

                for(auto el : Ecycle_list)
                {
                    std::cout << el << std::endl;
                }
                std::cout << std::endl;

                duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
                sum = sum + duration.count();
            }
            result << "wEuler" << ";" << s << ";" << d << ";" << sum/proby << std::endl;
            result.close();

        }
    }

    for(auto & s : generator::SIZES_SMALL)
    {
        for(auto & d : generator::DENSITY)
        {
            result.open("res.csv", std::ios::app);
            sum = 0;

            for(int i = 0; i < proby; i++)
            {
                file.open("w" + std::to_string(s) + "_" + std::to_string(d) + "_Hamilton.txt");

                adjacency_matrix G(s);

                while (file >> x >> y)
                {
                    G.add_edge(x, y);
                }

                file.close();

                start = std::chrono::steady_clock::now();

                std::vector<int>Hcycle_list(G.order()+1);

                if(Hcycle<adjacency_matrix>(G, Hcycle_list))
                {
                    for(auto el : Hcycle_list)
                    {
                        std::cout << el << std::endl;
                    }
                    std::cout << std::endl;
                }

                stop = std::chrono::steady_clock::now();
                duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
                sum = sum + duration.count();
            }
            result << "wHamilton" << ";" << s << ";" << d << ";" << sum/proby << std::endl;
            result.close();

        }
    }

    return 0;
}