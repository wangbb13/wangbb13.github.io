/*
 * Name: change classrooms
 * Solution: DP
 */
#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

const int DINF = 0x1fffffff;
const double FINF = DINF * 1.0;

void fw(vector< vector<int> >& sp, int n) {
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                sp[i][j] = std::min(sp[i][j], sp[i][k] + sp[k][j]);
            }
        }
    }
}

int main() {
    int n, m, v, e;
    int a, b, w;
    cin >> n >> m >> v >> e;
    vector<int> ci(n);
    vector<int> di(n);
    vector<double> ki(n);
    for (int i = 0; i < n; ++i) {
        cin >> ci[i];
        ci[i]--;
    }
    for (int i = 0; i < n; ++i) {
        cin >> di[i];
        di[i]--;
    }
    for (int i = 0; i < n; ++i)
        cin >> ki[i];
    vector< vector<int> > graph(v, vector<int>(v, DINF));
    for (int i = 0; i < v; ++i) 
        graph[i][i] = 0;
    for (int i = 0; i < e; ++i) {
        cin >> a >> b >> w;
        a--, b--;
        graph[a][b] = w;
        graph[b][a] = w;
    }
    if (n == 1) {
        cout << std::fixed;
        cout << setprecision(2) << 0.0 << endl;
        return 0;
    }
    fw(graph, v);
    double ***path = new double**[n];
    // initial
    m++;
    for (int i = 0; i < n; ++i) {
        path[i] = new double*[2];
        path[i][0] = new double[m];
        path[i][1] = new double[m];
        for (int j = 0; j < m; ++j) {
            path[i][0][j] = path[i][1][j] = FINF;
        }
    }
    // initial end 
    path[1][0][0] = graph[ci[0]][ci[1]];
    path[1][0][1] = ki[0] * graph[di[0]][ci[1]] + (1.0 - ki[0]) * graph[ci[0]][ci[1]];
    path[1][1][1] = ki[1] * graph[ci[0]][di[1]] + (1.0 - ki[1]) * graph[ci[0]][ci[1]];
    path[1][1][2] = ki[0] * ki[1] * graph[di[0]][di[1]] + \
                    ki[0] * (1 - ki[1]) * graph[di[0]][ci[1]] + \
                    (1 - ki[0]) * ki[1] * graph[ci[0]][di[1]] + \
                    (1 - ki[0]) * (1 - ki[1]) * graph[ci[0]][ci[1]];
    for (int k = 2; k < n; ++k) {
        path[k][0][0] = path[k-1][0][0] + graph[ci[k-1]][ci[k]];
        for (int i = 1; i < std::min(k + 1, m); ++i) {
            // apply
            path[k][1][i] = std::min(path[k][1][i], path[k-1][0][i - 1] + \
                ki[k] * graph[ci[k-1]][di[k]] + (1-ki[k]) * graph[ci[k-1]][ci[k]]);
            if (i > 1) {
                path[k][1][i] = std::min(path[k][1][i], path[k-1][1][i - 1] + \
                ki[k - 1] * ki[k] * graph[di[k-1]][di[k]] + \
                ki[k - 1] * (1 - ki[k]) * graph[di[k-1]][ci[k]] + \
                (1 - ki[k - 1]) * ki[k] * graph[ci[k-1]][di[k]] + \
                (1 - ki[k - 1]) * (1 - ki[k]) * graph[ci[k-1]][ci[k]]);
            }
            // or not
            path[k][0][i] = std::min(path[k][0][i], path[k-1][0][i] + graph[ci[k-1]][ci[k]]);
            if (i > 1) {
                path[k][0][i] = std::min(path[k][0][i], path[k-1][1][i] + \
                ki[k-1] * graph[di[k-1]][ci[k]] + \
                (1 - ki[k-1]) * graph[ci[k-1]][ci[k]]);
            }
        }
    }
    // result
    double ans = FINF;
    for (int i = 0; i < m; ++i) {
        ans = std::min(ans, path[n - 1][0][i]);
        ans = std::min(ans, path[n - 1][1][i]);
    }
    cout << std::fixed;
    cout << setprecision(2) << ans << endl;
}