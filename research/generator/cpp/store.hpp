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
        // if (length)
        //     fout << a_line[0];
        // for (int i = 1; i < length; ++ i) 
        //     fout << " " << a_line[i];
        // fout << std::endl;
        if (length) {
            std::string ans = std::to_string(a_line[0]);
            for (int i = 1; i < length; ++i) {
                ans = ans + " " + std::to_string(a_line[i]);
            }
            ans = ans + "\n";
            fout.write(ans.c_str(), sizeof(char) * ans.size());
        }
    }

    void writeln(int i, std::unordered_set<int> adj) {
        if (adj.size()) {
            // fout << i;
            // for (auto &e : adj) 
            //     fout << " " << e;
            // fout << std::endl;
            std::string ans = std::to_string(i);
            for (auto &e : adj) 
                ans = ans + " " + std::to_string(e);
            ans = ans + "\n";
            fout.write(ans.c_str(), sizeof(char) * ans.size());
        }
    }
};