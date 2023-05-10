#include <iostream>
#include<vector>
#include<unordered_set>

using namespace std;

int main() {

    long long n;
    cin >> n;

    vector<long long> a(n, 0);
    vector<long long> dist_to_1(n, 0);

    for (size_t i = 0; i < n ; i++) {
        cin >> a[i];
        a[i]--; // because we shift from [1, n] to [0, n-1]
        dist_to_1[i] = i;
    }

    long long nb_shortcuts_seen = 0;

    long long i = 0;
    unordered_set<long long> at_dist_i;
    unordered_set<long long> at_dist_i_plus_one;
    at_dist_i.emplace(0);

    while (i < n) {
        at_dist_i_plus_one.clear();

        for (auto x: at_dist_i) {
            if (x > 0) {
                if (dist_to_1[x-1] > i + 1) {
                    dist_to_1[x-1] = i + 1;
                    at_dist_i_plus_one.emplace(x-1);
                }
            }
            if (x < n) {
                if (dist_to_1[x+1] > i + 1) {
                    dist_to_1[x+1] = i + 1;
                    at_dist_i_plus_one.emplace(x+1);
                }
            }

            if (dist_to_1[a[x]] > i + 1) {
                dist_to_1[a[x]] = i + 1;
                at_dist_i_plus_one.emplace(a[x]);
            }
        }

        i++;
        at_dist_i = at_dist_i_plus_one;
    }

    for (size_t i = 0; i < n ; i ++) {
        cout << dist_to_1[i] << " ";
    }
    cout << endl;



}
