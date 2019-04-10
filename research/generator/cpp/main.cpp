#include "pwl.hpp"
#include "store.hpp"
#include <sstream>
#include <chrono>
using namespace std;
using namespace std::chrono;

template <typename T>
T string2num(string& str) {
    T ans;
    istringstream iss(str);
    iss >> ans;
    return ans;
}

int main(int argc, char const *argv[])
{
    // parameters: 
    // lambda, dmin, dmax, nodes, edges, filename
    if (argc != 10) {
        cout << "usage: ./main ilambda idmin idmax olambda odmin odmax nodes edges filename" << endl;
        return 0;
    }
    string s_ilambda = argv[1];
    string s_idmin = argv[2];
    string s_idmax = argv[3];
    string s_olambda = argv[4];
    string s_odmin = argv[5];
    string s_odmax = argv[6];
    string s_nodes = argv[7];
    string s_edges = argv[8];
    const char *filename = argv[9];

    double ilambda = string2num<double>(s_ilambda);
    int idmin = string2num<int>(s_idmin);
    int idmax = string2num<int>(s_idmax);
    double olambda = string2num<double>(s_olambda);
    int odmin = string2num<int>(s_odmin);
    int odmax = string2num<int>(s_odmax);
    int nodes = string2num<int>(s_nodes);
    ullint edges = string2num<ullint>(s_edges);

    NGPowerLow ipwl(ilambda, idmin, idmax, nodes, edges);
    NGPowerLow opwl(olambda, odmin, odmax, nodes, edges);
    StoreRelation store(filename);
    int all_e = 0;

    auto start = high_resolution_clock::now();

    for (int i = 0; i < nodes; ++ i) {
        unordered_set<int> adj;
        int d_out = opwl.get_d(i);
        all_e += d_out;
        for (int k = 0; k < d_out; ++ k) {
            int j = ipwl.get_j();
            while (adj.find(j) != adj.end()) 
                j = ipwl.get_j();
            adj.insert(j);
        }
        store.writeln(i, adj);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    
    cout << "actual edges = " << all_e << endl;
    cout << "elapsed time = " << duration.count() << " us" << endl << endl;
    return 0;
}