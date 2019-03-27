#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>

class StoreRelation
{
private:
    std::ofstream fout;

public:
    StoreRelation(const char *filename) {
        fout = std::ofstream(filename);
    }

    ~StoreRelation() {
        if (fout) 
            fout.close();
    }

    void writeln(std::vector<int>& a_line) {
        int length = a_line.size();
        if (length)
            fout << a_line[0];
        for (int i = 1; i < length; ++ i) 
            fout << " " << a_line[i];
        fout << std::endl;
    }

    void writeln(int i, std::unordered_set<int> adj) {
        if (adj.size()) {
            fout << i;
            for (auto &e : adj) 
                fout << " " << e;
            fout << std::endl;
        }
    }
};