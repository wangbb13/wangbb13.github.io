#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <unordered_set>
#include "buffer_writer.hpp"

class StoreRelation
{
private:
    // std::ofstream fout;
    
    BufferWriter writer;

public:
    StoreRelation(const char *filename) {
        // fout = std::ofstream(filename);

        int buffer_size = 1 << 20;
        writer = BufferWriter(filename, buffer_size);
    }

    ~StoreRelation() {
        // if (fout) 
        //     fout.close();

        writer.close();
    }

    void writeln(std::vector<int>& a_line) {
        int length = a_line.size();
        
        // version 1
        // if (length)
        //     fout << a_line[0];
        // for (int i = 1; i < length; ++ i) 
        //     fout << " " << a_line[i];
        // fout << std::endl;
        
        // version 2
        // if (length) {
        //     std::string ans = std::to_string(a_line[0]);
        //     for (int i = 1; i < length; ++i) {
        //         ans = ans + " " + std::to_string(a_line[i]);
        //     }
        //     ans = ans + "\n";
        //     fout.write(ans.c_str(), sizeof(char) * ans.size());
        // }

        // version 3
        if (length) {
            writer.write(a_line[0]);
            for (int i = 1; i < length; ++i) {
                writer.space();
                writer.write(a_line[i]);
            }
            writer.new_line();
        }
    }

    void writeln(int i, std::unordered_set<int> adj) {
        if (adj.size()) {
            // version 1
            // fout << i;
            // for (auto &e : adj) 
            //     fout << " " << e;
            // fout << std::endl;
            
            // version 2
            // std::string ans = std::to_string(i);
            // for (auto &e : adj) 
            //     ans = ans + " " + std::to_string(e);
            // ans = ans + "\n";
            // fout.write(ans.c_str(), sizeof(char) * ans.size());

            // version 3
            writer.write(i);
            for (auto& e: adj) {
                writer.space();
                writer.write(e);
            }
            writer.new_line();
        }
    }
};