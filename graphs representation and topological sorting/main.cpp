#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <list>
#include <unordered_set>
#include <unordered_map>
#include <chrono>
#include <deque>
#include <string>
#include <fstream>

#include "generator.h"

class adjacency_matrix {

public:

    std::vector<std::vector<int>> M{{0, 0},
                                    {0, 0}};

    void add_edge(int &From, int &To) {
        int greatest = std::max(From, To);
        if (greatest > (int)M.size()) {
            int missing = greatest - (int)M.size();

            for (auto &row : M) {
                for (int i = 0; i < missing; i++) {
                    row.push_back(0);
                }
            }
            for (int i = 0; i < missing; i++) {
                M.emplace_back(greatest, 0);
            }
        }

        M[From - 1][To - 1] = 1;
        M[To - 1][From - 1] = -1;
    }

    void print() {
        for (auto &row : M) {
            for (auto &value : row) {
                std::cout << value << "\t";
            }
            std::cout << "\n";
        }
    }

    void delete_vertex(int V) {
        V--;
        for (auto &row : M) {
            row[V] = 0;
        }
        std::fill(M[V].begin(), M[V].end(), 0);
    }

    bool check_exist(int From, int To) {
        if (M[From - 1][To - 1] == 1) {
            return true;
        } else {
            return false;
        }

    }

    int order() {
        return (int)M.size();
    }

    std::set<int> successors(int &V) {
        V--;
        std::set<int> S;
        for (int i = 0; i < M[V].size(); i++) {
            if (M[V][i] == 1) {
                S.insert(i + 1);
            }
        }
        return S;
    }

};

class predecessor_list {
public:

    std::unordered_map<int, std::set<int>> L;

    void add_edge(int &From, int &To) {
        L[To].insert(From);
    }

    void delete_vertex(int V) {
        L.erase(V);
        for (auto &list : L) {
            list.second.erase(V);
        }

    }

    bool check_exist(int From, int To) {
        return L[To].find(From) != L[To].end();

    }

    void print() {
        for (auto &list : L) {
            std::cout << list.first << " : ";
            for (auto &el : list.second) {
                std::cout << el << " ";
            }
            std::cout << std::endl;
        }
    }

    int order() {
        std::set<int> verticles;
        for (auto &list : L) {
            verticles.insert(list.first);
            for (auto &el : list.second) {
                verticles.insert(el);
            }
        }
        return (int) verticles.size();

    }

    std::set<int> successors(int &V) {
        std::set<int> S;
        for (auto &el : L) {
            if (el.second.find(V) != el.second.end()) {
                S.insert(el.first);
            }
        }
        return S;
    }
};

class successor_list {
public:

    std::unordered_map<int, std::set<int>> L;

    void add_edge(int &From, int &To) {
        L[From].insert(To);
    }

    void delete_vertex(int V) {
        L.erase(V);
        for (auto &list : L) {
            list.second.erase(V);
        }

    }

    bool check_exist(int From, int To) {
        return L[From].find(To) != L[From].end();

    }

    void print() {
        for (auto &list : L) {
            std::cout << list.first << " : ";
            for (auto &el : list.second) {
                std::cout << el << " ";
            }
            std::cout << std::endl;
        }
    }

    int order() {
        std::set<int> verticles;
        for (auto &list : L) {
            verticles.insert(list.first);
            for (auto &el : list.second) {
                verticles.insert(el);
            }
        }
        return (int) verticles.size();

    }

    std::set<int> successors(int &V) {
        return L[V];
    }
};

class edge_list {
public:

    struct edge {
    public:

        int from;
        int to;

        bool operator==(const edge &e) const {
            return (from == e.from) && (to == e.to);
        }

        bool operator<(const edge &e) const {
            if (from != e.from)
            {
                return from < e.from;
            }
            else
            {
                return to < e.to;
            }

        }

    };

//    struct edge_hash {
//    public:
//        std::size_t operator()(const edge &e) const {
//            auto h1 = std::hash<int>{}(e.from);
//            auto h2 = std::hash<int>{}(e.to);
//            return h1 ^ (h2 << 1);
//        }
//    };

    std::set<edge> edges;

    void add_edge(int &From, int &To) {
        edges.insert(edge{From, To});
    }

    bool check_exist(int From, int To) {
        return edges.find(edge{From, To}) != edges.end();
    }

    void delete_vertex(int V) {
        std::erase_if(edges, [V](edge E) { return (E.to == V || E.from == V); });
    }

    int order() {
        std::set<int> verticles;
        for (auto &edge : edges) {
            verticles.insert(edge.from);
            verticles.insert(edge.to);
        }
        return (int)verticles.size();
    }

    std::set<int> successors(int &V) {

        std::set<int> S;

        auto it = edges.begin();

        while(it != edges.end() && it->from != V)
        {
            it++;
        }

        while(it->from == V && it != edges.end())
        {
            S.insert(it->to);
            it++;
        }
        return S;
    }

};


template<class GraphType>
void visit(int vertex, std::map<int, int> &visited, GraphType &G, std::deque<int> &sorted) {
    if (visited[vertex] == 2) {
        return;
    }
    visited[vertex] = 1;
    for (auto &successor : G.successors(vertex)) {
        visit<GraphType>(successor, visited, G, sorted);
    }
    visited[vertex] = 2;
    sorted.push_front(vertex);

}

template<class GraphType>
std::deque<int> DFS_sorting(GraphType G) {
    std::deque<int> sorted;
    std::map<int, int> visited;

    int N = G.order();
    for (int vertex = 1; vertex <= N; vertex++) {
        visited[vertex] = 0;
    }

    while (std::count_if(visited.begin(), visited.end(), [](auto p) { return p.second == 2; }) != N) {
        for (auto &vertex : visited) {
            if (vertex.second != 2) {
                visit<GraphType>(vertex.first, visited, G, sorted);
            }
        }
    }
    return sorted;
}

template<class GraphType>
int degree(int V, GraphType &G) {
    std::set<int> successors;

    std::vector<int> temp(G.order());
    std::iota(temp.begin(), temp.end(), 1);

    std::unordered_set<int> verticles(temp.begin(), temp.end());

    for (auto &vertex : verticles) {
        if (G.check_exist(vertex, V)) {
            return 1;
        }
    }
    return 0;
}

template<class GraphType>
std::deque<int> Kahn_sorting(GraphType G) {
    std::deque<int> sorted;
    std::unordered_set<int> verticles;

    int N = G.order();

    for (int vertex = 1; vertex <= N; vertex++) {
        verticles.insert(vertex);
    }
    while (!verticles.empty()) {
        auto V = verticles.begin();

        while (V != verticles.end()) {
            if (degree<GraphType>(*V, G) == 0) {
                sorted.push_back(*V);
                G.delete_vertex(*V);
                V = verticles.erase(V);
            } else {
                ++V;
            }
        }
    }
    return sorted;
}


int main()
{

    generator::start();
    std::ifstream file;
    std::ofstream result;

    auto start = std::chrono::steady_clock::now();
    auto stop = std::chrono::steady_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    long long sum;
    int x, y;

    int proby = 10;

    result.open("res.csv", std::ofstream::out | std::ofstream::trunc);
    result.close();

    for(auto & s : generator::SIZES_SMALL)
    {

        result.open("res.csv", std::ios::app);

        sum = 0;

        for(int i = 0; i < proby; i++)
        {

            file.open(std::to_string(s) + ".txt");

            edge_list graf;

            while (file >> x >> y)
            {
                graf.add_edge(x, y);
            }

            file.close();

            std::deque<int>sorted;

            start = std::chrono::steady_clock::now();

            sorted = Kahn_sorting<edge_list>(graf);

            for(auto el : sorted)
            {
                std::cout << el << std::endl;
            }

            stop = std::chrono::steady_clock::now();
            duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
            sum = sum + duration.count();
        }

        std::cout << "WPISSSSSSSSSSSSSSSSSSSS";
        result << "edge_list" << ";" << "Kahn" << ";" << s << ";" << sum/proby << std::endl;

        ///// 2
        sum = 0;

        for(int i = 0; i < proby; i++)
        {

            file.open(std::to_string(s) + ".txt");

            std::cout << s << std::endl;

            successor_list graf;

            while (file >> x >> y)
            {
                graf.add_edge(x, y);
            }

            file.close();

            std::deque<int>sorted;

            start = std::chrono::steady_clock::now();

            sorted = Kahn_sorting<successor_list>(graf);

            for(auto el : sorted)
            {
                std::cout << el << std::endl;
            }

            stop = std::chrono::steady_clock::now();
            duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
            sum = sum + duration.count();
        }

        result << "successor_list" << ";" << "Kahn" << ";" << s << ";" << sum/proby << std::endl;

        ///// 3

        sum = 0;

        for(int i = 0; i < proby; i++)
        {

            file.open(std::to_string(s) + ".txt");

            std::cout << s << std::endl;

            predecessor_list graf;


            while (file >> x >> y)
            {
                graf.add_edge(x, y);
            }

            file.close();

            std::deque<int>sorted;

            start = std::chrono::steady_clock::now();

            sorted = Kahn_sorting<predecessor_list>(graf);

            for(auto el : sorted)
            {
                std::cout << el << std::endl;
            }

            stop = std::chrono::steady_clock::now();
            duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
            sum = sum + duration.count();
        }

        result << "predecessor_list" << ";" << "Kahn" << ";" << s << ";" << sum/proby << std::endl;

        ////// 4

        sum = 0;

        for(int i = 0; i < proby; i++)
        {

            file.open(std::to_string(s) + ".txt");

            std::cout << s << std::endl;

            adjacency_matrix graf;

            while (file >> x >> y)
            {
                graf.add_edge(x, y);
            }

            file.close();

            std::deque<int>sorted;

            start = std::chrono::steady_clock::now();

            sorted = Kahn_sorting<adjacency_matrix>(graf);

            for(auto el : sorted)
            {
                std::cout << el << std::endl;
            }

            stop = std::chrono::steady_clock::now();
            duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
            sum = sum + duration.count();
        }

        result << "adjacency_matrix" << ";" << "Kahn" << ";" << s << ";" << sum/proby << std::endl;

        result.close();

    }

    for(auto & s : generator::SIZES_BIG)
    {

        result.open("res.csv", std::ios::app);

        sum = 0;

        for(int i = 0; i < proby; i++)
        {

            file.open(std::to_string(s) + ".txt");

            std::cout << s << std::endl;

            edge_list graf;


            while (file >> x >> y)
            {
                graf.add_edge(x, y);
            }

            file.close();

            std::deque<int>sorted;

            start = std::chrono::steady_clock::now();
            sorted = DFS_sorting<edge_list>(graf);

            for(auto el : sorted)
            {
                std::cout << el << std::endl;
            }
            stop = std::chrono::steady_clock::now();
            duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
            sum = sum + duration.count();

        }

        result << "edge_list" << ";" << "DFS" << ";" << s << ";" << sum/proby << std::endl;

        ///// 2

        sum = 0;

        for(int i = 0; i < proby; i++)
        {

            file.open(std::to_string(s) + ".txt");

            std::cout << s << std::endl;

            successor_list graf;

            while (file >> x >> y)
            {
                graf.add_edge(x, y);
            }

            file.close();


            std::deque<int>sorted;

            start = std::chrono::steady_clock::now();
            sorted = DFS_sorting<successor_list>(graf);

            for(auto el : sorted)
            {
                std::cout << el << std::endl;
            }
            stop = std::chrono::steady_clock::now();
            duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
            sum = sum + duration.count();

        }

        result << "successor_list" << ";" << "DFS" << ";" << s << ";" << sum/proby << std::endl;

        ///// 3

        sum = 0;

        for(int i = 0; i < proby; i++)
        {

            file.open(std::to_string(s) + ".txt");

            std::cout << s << std::endl;

            predecessor_list graf;

            while (file >> x >> y)
            {
                graf.add_edge(x, y);
            }

            file.close();

            std::deque<int>sorted;

            start = std::chrono::steady_clock::now();
            sorted = DFS_sorting<predecessor_list>(graf);

            for(auto el : sorted)
            {
                std::cout << el << std::endl;
            }
            stop = std::chrono::steady_clock::now();
            duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
            sum = sum + duration.count();

        }

        result << "predecessor_list" << ";" << "DFS" << ";" << s << ";" << sum/proby << std::endl;

        ////// 4

        sum = 0;

        for(int i = 0; i < proby; i++)
        {

            file.open(std::to_string(s) + ".txt");

            std::cout << s << std::endl;

            adjacency_matrix graf;

            while (file >> x >> y)
            {
                graf.add_edge(x, y);
            }

            file.close();

            std::deque<int>sorted;

            start = std::chrono::steady_clock::now();
            sorted = DFS_sorting<adjacency_matrix>(graf);

            for(auto el : sorted)
            {
                std::cout << el << std::endl;
            }
            stop = std::chrono::steady_clock::now();
            duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
            sum = sum + duration.count();

        }

        result << "adjacency_matrix" << ";" << "DFS" << ";" << s << ";" << sum/proby << std::endl;

        result.close();

    }


}
