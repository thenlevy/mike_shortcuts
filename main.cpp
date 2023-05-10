#include <iostream>
#include<vector>
#include<unordered_set>

using namespace std;

int main() {

    // parse input
    long long n;
    cin >> n;

    vector<long long> a(n, 0);
    vector<long long> dist_to_1(n, 0);

    for (size_t i = 0; i < n ; i++) {
        cin >> a[i];
        a[i]--; // because we shift from [1, n] to [0, n-1]
        dist_to_1[i] = i;
    }

    // solve.
    //
    // The idea is to construt the set dist_i that contains all vertices at distance i of vertex 0.
    // dist_1 = {1, a[0]} and dist_{i+1} = 
    // {j +- 1, j in dist_i, j \notin dist_1, U ...  U dist_i} 
    // U 
    // {a[j], j in dist_i, j \notin dist_1, U ... U dist_i}
    //
    // Actually, we are performing Dijkstra's algorithm on the graph without storing the graph,
    // simply by relying on the fact that we do not need to store the edges since we know what
    // they are: the neighbor of i are i-1 i+1 and a[i].
    long long i = 0;
    unordered_set<long long> at_dist_i = {};
    at_dist_i.emplace(0);

    while (i < n) {
        unordered_set<long long> at_dist_i_plus_one = {};

        for (auto x: at_dist_i) {

            // try to add x - 1. 
            if (x > 0) {
                if (dist_to_1[x-1] >= i + 1) { // This test ensures that x-1 \notin dist_1,...dist_i
                    dist_to_1[x-1] = i + 1;
                    at_dist_i_plus_one.emplace(x-1);
                }
            }

            // try to add x + 1
            if (x < n - 1) {
                if (dist_to_1[x+1] >= i + 1) { // This test ensures that x+1 \notin dist_1,...,dist_i
                    dist_to_1[x+1] = i + 1;
                    at_dist_i_plus_one.emplace(x+1);
                }
            }

            if (dist_to_1[a[x]] >= i + 1) { // This test ensures that a[x] \notin dist_1,..,dist_i
                dist_to_1[a[x]] = i + 1;
                at_dist_i_plus_one.emplace(a[x]);
            }
        }

        i++;
        at_dist_i = std::move(at_dist_i_plus_one);
    }

    // output.
    for (size_t i = 0; i < n ; i ++) {
        cout << dist_to_1[i] << " ";
    }
    cout << endl;
}
