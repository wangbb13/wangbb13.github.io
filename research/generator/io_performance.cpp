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

std::string filename = "test.txt";
const char* file_name = "test.txt";

std::vector<uint64_t> GenerateData(std::size_t bytes)
{
    assert(bytes % sizeof(uint64_t) == 0);
    std::vector<uint64_t> data(bytes / sizeof(uint64_t));
    std::iota(data.begin(), data.end(), 0);
    std::shuffle(data.begin(), data.end(), std::mt19937{ std::random_device{}() });
    return data;
}

long long option_1(std::size_t bytes)
{
    std::vector<uint64_t> data = GenerateData(bytes);

    auto startTime = std::chrono::high_resolution_clock::now();
    auto myfile = std::fstream(filename, std::ios::out | std::ios::binary);
    myfile.write((char*)&data[0], bytes);
    myfile.close();
    auto endTime = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
}

long long option_2(std::size_t bytes)
{
    std::vector<uint64_t> data = GenerateData(bytes);

    auto startTime = std::chrono::high_resolution_clock::now();
    FILE* file = fopen(file_name, "wb");
    fwrite(&data[0], 1, bytes, file);
    fclose(file);
    auto endTime = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
}

long long option_3(std::size_t bytes)
{
    std::vector<uint64_t> data = GenerateData(bytes);

    std::ios_base::sync_with_stdio(false);
    auto startTime = std::chrono::high_resolution_clock::now();
    auto myfile = std::fstream(filename, std::ios::out | std::ios::binary);
    myfile.write((char*)&data[0], bytes);
    myfile.close();
    auto endTime = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
}

long long option_4(std::size_t size) {
    std::vector<uint64_t> data(size);
    for (std::size_t i = 0; i < size; ++i) {
        data[i] = i;
    }
    
    std::ios_base::sync_with_stdio(false);
    auto startTime = std::chrono::high_resolution_clock::now();
    auto myfile = std::fstream(filename, std::ios::out);
    myfile.write((char*)&data[0], size);
    myfile.close();
    auto endTime = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
}

template<typename T>
std::string to_str(T n) {
    std::ostringstream oss;
    oss << n;
    return oss.str();
}

long long option_5(std::size_t size) {
    std::vector<std::string> data(size);
    for (std::size_t i = 0; i < size; ++i) {
        data[i] = std::to_string(i) + " " + std::to_string(size - i);
    }

    std::ios_base::sync_with_stdio(false);
    auto startTime = std::chrono::high_resolution_clock::now();
    auto myfile = std::fstream(filename, std::ios::out);
    // myfile.write((char*)&data[0], size);
    std::ostream_iterator<std::string> oi(myfile, "\n");
    std::copy(data.begin(), data.end(), oi);
    myfile.close();
    auto endTime = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
}

void test() {
    // std::string str = std::to_string(100000) + " " + std::to_string(int(1 << 27) - 100000) + "\n";
    std::string s = "123456789";
    std::vector<std::string> vs;
    vs.push_back(s);
    std::ofstream fout(filename);
    // fout.write(s.c_str(), sizeof(char) * s.size());
    // fout.write((char*)&vs[0], sizeof(char) * s.size());
    std::ostream_iterator<std::string> oi(fout, "\n");
    std::copy(vs.begin(), vs.end(), oi);
    fout.close();

    std::ifstream fin(filename);
    fin.seekg(0, fin.end);
    long size = fin.tellg();
    fin.seekg(0);
    char* buffer = new char[size];
    fin.read(buffer, size);
    std::cout << buffer << std::endl;
}

int main()
{
    const std::size_t kB = 1024;
    const std::size_t MB = 1024 * kB;
    const std::size_t GB = 1024 * MB;

    const std::size_t size = 1 << 27;

    test();

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