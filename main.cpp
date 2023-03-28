#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

ifstream fin("dfa.txt");

int main() {
    int nrFinal, x, nrTranz, qfrom, qto;
    char val;
    vector<int> final;
    fin>>nrFinal;
    for (int i = 0; i < nrFinal; ++i) {
        fin>>x;
        final.push_back(x);
    }
    fin>>nrTranz;
    vector<vector<pair<char, int>>> tranz(nrTranz);
    for (int i = 0; i < nrTranz; ++i) {
        fin>>qfrom>>val>>qto;
        tranz[qfrom].push_back(make_pair(val, qto));
    }
    int current, ok;
    string test;
    while(fin>>test){
        current = 1;
        for (int i = 0; i < test.length(); ++i) {
            ok = 0;
            for (int j = 0; j < tranz[current].size(); ++j) {
                if (tranz[current][j].first == test[i]) {
                    current = tranz[current][j].second;
                    ok = 1;
                    break;
                }
            }
            if (ok == 0){
                break;
            }
        }
        if (ok == 0){
            cout<<"Cuvantul "<<test<<" nu este acceptat"<<endl;
        }
        else {
            ok = 0;
            for (int i = 0; i < nrFinal; ++i) {
                if (final[i] == current) {
                    ok = 1;
                    break;
                }
            }
            if (ok == 0){
                cout<<"Cuvantul "<<test<<" nu este acceptat"<<endl;
            }
            else{
                cout << "Cuvantul " << test << " este acceptat"<<endl;
                current = 1;
                cout<<0;
                for (int i = 0; i < test.length(); ++i) {
                    for (int j = 0; j < tranz[current].size(); ++j) {
                        if (tranz[current][j].first == test[i]) {
                            cout<<" ->("<<tranz[current][j].first<<") ";
                            current = tranz[current][j].second;
                            cout<<current;
                        }
                    }
                }
                cout<<endl;
            }
        }
        cout<<endl;
    }

    return 0;
}
