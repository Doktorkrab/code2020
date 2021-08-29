#include <iostream>
#include <vector>
#include <cryptominisat5/cryptominisat.h>
#include <unordered_map>

using namespace std;

int main() {
    CMSat::SATSolver solver;
    solver.set_num_threads(8);
    int n;
    cin >> n;
    solver.new_vars(n * n);

    unordered_map<int, vector<int>> have, have1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            have[i + j].push_back(i * n + j);
            have1[i - j].push_back(i * n + j);
        }
    }
    for (auto[x, v] : have) {
        for (int i = 0; i < v.size(); i++)
            for (int j = i + 1; j < v.size(); j++) {
                int y = v[i];
                int z = v[j];
                vector<CMSat::Lit> clause;
                clause.emplace_back(y, true);
                clause.emplace_back(z, true);
//                cout << y << ' ' << z << '\n';
                solver.add_clause(clause);
            }
    }
    for (auto[x, v] : have1) {
        for (int i = 0; i < v.size(); i++)
            for (int j = i + 1; j < v.size(); j++) {
                int y = v[i];
                int z = v[j];
                if (y != z) {
                    vector<CMSat::Lit> clause;
                    clause.emplace_back(y, true);
                    clause.emplace_back(z, true);
//                    cout << y << ' ' << z << "!\n";
                    solver.add_clause(clause);
                }
            }

    }
    cout.flush();
    CMSat::lbool res = solver.solve();
    assert(res == CMSat::l_True);
    vector<int> ans(n, -1);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            if (solver.get_model()[i * n + j] == CMSat::l_True)
                ans[i] = j;
    for (int i = 0; i < n; i++)
        cout << ans[i] + 1 << " \n"[i + 1 == n];
    return 0;
}
