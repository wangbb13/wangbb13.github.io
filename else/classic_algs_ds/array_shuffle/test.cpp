// test shuffle a vector
#include <iostream>
#include "array_shuffle.hpp"
#include "other_impl.hpp"

using namespace std;

int main() {
    int length = 10;
    vector<int> test_vec(length);
    for (int i = 0; i < length; ++i)
        test_vec[i] = i;
    cout << "original vector: ";
    for (int i = 0; i < length; ++i)
        cout << test_vec[i] << " ";
    cout << endl;
    
    cout << "my shuffled vector: ";
    algds::shuffle<int>(test_vec);
    for (int i = 0; i < length; ++i)
        cout << test_vec[i] << " ";
    cout << endl;

    cout << "other shuffled vector: ";
    int *list = new int[length];
    for (int i = 0; i < length; ++i)
        list[i] = i;
    alg::shuffle<int>(list, length);
    for (int i = 0; i < length; ++i)
        cout << list[i] << " ";
    cout << endl;

    system("pause");
    return 0;
}