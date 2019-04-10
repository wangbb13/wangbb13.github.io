#include <fstream>
#include <chrono>
#include <vector>
#include <cstdint>
#include <numeric>
#include <random>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <string>
#include <sstream>
#include <iterator>

#include "buffer_writer.hpp"

// std::string filename = "test.txt";
// const char* file_name = "test.txt";

// std::vector<uint64_t> GenerateData(std::size_t bytes)
// {
//     assert(bytes % sizeof(uint64_t) == 0);
//     std::vector<uint64_t> data(bytes / sizeof(uint64_t));
//     std::iota(data.begin(), data.end(), 0);
//     std::shuffle(data.begin(), data.end(), std::mt19937{ std::random_device{}() });
//     return data;
// }

// long long option_1(std::size_t bytes)
// {
//     std::vector<uint64_t> data = GenerateData(bytes);

//     auto startTime = std::chrono::high_resolution_clock::now();
//     auto myfile = std::fstream(filename, std::ios::out | std::ios::binary);
//     myfile.write((char*)&data[0], bytes);
//     myfile.close();
//     auto endTime = std::chrono::high_resolution_clock::now();

//     return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
// }

// long long option_2(std::size_t bytes)
// {
//     std::vector<uint64_t> data = GenerateData(bytes);

//     auto startTime = std::chrono::high_resolution_clock::now();
//     FILE* file = fopen(file_name, "wb");
//     fwrite(&data[0], 1, bytes, file);
//     fclose(file);
//     auto endTime = std::chrono::high_resolution_clock::now();

//     return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
// }

// long long option_3(std::size_t bytes)
// {
//     std::vector<uint64_t> data = GenerateData(bytes);

//     std::ios_base::sync_with_stdio(false);
//     auto startTime = std::chrono::high_resolution_clock::now();
//     auto myfile = std::fstream(filename, std::ios::out | std::ios::binary);
//     myfile.write((char*)&data[0], bytes);
//     myfile.close();
//     auto endTime = std::chrono::high_resolution_clock::now();

//     return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
// }

// long long option_4(std::size_t size) {
//     std::vector<uint64_t> data(size);
//     for (std::size_t i = 0; i < size; ++i) {
//         data[i] = i;
//     }
    
//     std::ios_base::sync_with_stdio(false);
//     auto startTime = std::chrono::high_resolution_clock::now();
//     auto myfile = std::fstream(filename, std::ios::out);
//     myfile.write((char*)&data[0], size);
//     myfile.close();
//     auto endTime = std::chrono::high_resolution_clock::now();

//     return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
// }

// template<typename T>
// std::string to_str(T n) {
//     std::ostringstream oss;
//     oss << n;
//     return oss.str();
// }

// long long option_5(std::size_t size) {
//     std::vector<std::string> data(size);
//     for (std::size_t i = 0; i < size; ++i) {
//         data[i] = std::to_string(i) + " " + std::to_string(size - i);
//     }

//     std::ios_base::sync_with_stdio(false);
//     auto startTime = std::chrono::high_resolution_clock::now();
//     auto myfile = std::fstream(filename, std::ios::out);
//     // myfile.write((char*)&data[0], size);
//     std::ostream_iterator<std::string> oi(myfile, "\n");
//     std::copy(data.begin(), data.end(), oi);
//     myfile.close();
//     auto endTime = std::chrono::high_resolution_clock::now();

//     return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
// }

void bench0(int n) {
    // naive method
    auto start = std::chrono::high_resolution_clock::now();
    
    std::ofstream fout("test_0.txt");
    int row = 233;
    std::vector<int> data(255);
    std::fill(data.begin(), data.end(), 233);
    
    for (int i = 0; i < n; ++i) {
        fout << row;
        for (int j = 0; j < data.size(); ++j) {
            fout << " " << data[j];
        }
        fout << std::endl;
    }
    fout.close();

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms." << std::endl;
}

void bench1(int n) {
    // std::copy
    std::ios_base::sync_with_stdio(false);
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<int> data(256);
    std::fill(data.begin(), data.end(), 233);

    std::ofstream fout("test_1.txt");
    std::ostream_iterator<int> oi(fout, " ");
    for (int i = 0; i < n; ++i) {
        std::copy(data.begin(), data.end(), oi);
        fout << std::endl;
    }
    fout.close();

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms." << std::endl;
}

void bench2(int n) {
    // std::copy
    std::ios_base::sync_with_stdio(false);
    auto start = std::chrono::high_resolution_clock::now();

    int row = 233;
    std::vector<int> data(255);
    std::fill(data.begin(), data.end(), 233);

    int buffer_size = 1 << 24;
    BufferWriter bw("test_2.txt", buffer_size);
    for (int i = 0; i < n; ++i) {
        bw.write(row);
        for (auto& x : data) {
            bw.space();
            bw.write(x);
        }
        bw.new_line();
    }
    bw.close();

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms." << std::endl;
}

void bench_C(int n) {
    // 
}

void bench_Cpp(int n) {
    // 
}

void bench_posix(int n) {
    auto start = std::chrono::high_resolution_clock::now();



    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms." << std::endl;
}

int main()
{
    const std::size_t kB = 1024;
    const std::size_t MB = 1024 * kB;
    const std::size_t GB = 1024 * MB;

    int n = 1 << 20;

    bench0(n);
    bench1(n);
    bench2(n);

    // std::cout << "option1, " << size / MB << "MB: " << option_1(size) << "ms" << std::endl;
    // std::cout << "option2, " << size / MB << "MB: " << option_2(size) << "ms" << std::endl;
    // std::cout << "option3, " << size / MB << "MB: " << option_3(size) << "ms" << std::endl;
    // std::cout << "option4, " << size / MB << "MB: " << option_4(size) << "ms" << std::endl;
    // std::cout << "option5, " << size / MB << "MB: " << option_5(size) << "ms" << std::endl;


    // for (std::size_t size = 1 * MB; size <= 4 * GB; size *= 2) std::cout << "option1, " << size / MB << "MB: " << option_1(size) << "ms" << std::endl;
    // for (std::size_t size = 1 * MB; size <= 4 * GB; size *= 2) std::cout << "option2, " << size / MB << "MB: " << option_2(size) << "ms" << std::endl;
    // for (std::size_t size = 1 * MB; size <= 4 * GB; size *= 2) std::cout << "option3, " << size / MB << "MB: " << option_3(size) << "ms" << std::endl;

    return 0;
}