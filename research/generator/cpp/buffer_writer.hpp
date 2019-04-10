#pragma once

#include <stdio.h>
// #include <fcntl.h>

#include <iostream>
// #include <fstream>
// #include <chrono>
// #include <vector>
// #include <unordered_set>

// #if defined(__unix__) || defined (__CYGWIN__)
//     #include <unistd.h>
// #else
//     #include <io.h>
// #endif

// #ifndef O_BINARY
//     #define O_BINARY 0
// #endif

class BufferWriter {
private:
    FILE *fout;
    int chunk;
    char *buffer;

    int cur_size;   // current size of buffer

public:
    BufferWriter() {
        fout = nullptr;
        buffer = nullptr;
        chunk = cur_size = 0;
    }

    BufferWriter(const char *filename, int buffer_size) {
        fout = fopen(filename, "w");
        if (!fout) {
            std::cout << "Cannot open file: " << filename << std::endl;
            return;
        }
        chunk = buffer_size;
        buffer = new char[chunk + 1];
        cur_size = 0;
    }

    ~BufferWriter() {
        if (buffer) {
            delete [] buffer;
        }
        if (fout) {
            close();
        }
    }

    void write(int n) {
        do {
            buffer[cur_size++] = '0' + (n % 10);
            if (cur_size == chunk) {
                flush();
                cur_size = 0;
            }
            n /= 10;
        } while (n > 0);
    }

    void write(char ch) {
        buffer[cur_size++] = ch;
        if (cur_size == chunk) {
            flush();
            cur_size = 0;
        }
    }

    void space() {
        buffer[cur_size++] = ' ';
        if (cur_size == chunk) {
            flush();
            cur_size = 0;
        }
    }

    void new_line() {
        buffer[cur_size++] = '\n';
        if (cur_size == chunk) {
            flush();
            cur_size = 0;
        }
    }

    void flush() {
        fwrite(buffer, sizeof(char), cur_size, fout);
    }

    void close() {
        flush();
        fclose(fout);
        fout = nullptr;
    }
};
