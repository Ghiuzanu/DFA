#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

ifstream fin("nfa.txt");

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
    int ok;
    queue<int> current;
    queue<int> currentNew;
    string test;
    while(fin>>test){
        current.push(0);
        for (int i = 0; i < test.length(); ++i) {
            ok = 0;
            int n = current.size();
            for (int k = 0; k < n; ++k) {
                for (int j = 0; j < tranz[current.front()].size(); ++j) {
                    if (tranz[current.front()][j].first == test[i]) {
                        ok = 1;
                        currentNew.push(tranz[current.front()][j].second);
                    }
                }
                current.pop();
            }
            if (ok == 0){
                break;
            }
            else{
                current = currentNew;
                while(currentNew.size()){
                    currentNew.pop();
                }
            }
        }
        if (ok == 0){
            cout<<"Cuvantul "<<test<<" nu este acceptat"<<endl;
        }
        else {
            ok = 0;
            queue<int> aux;
            for (int i = 0; i < nrFinal; ++i) {
                aux = current;
                while(aux.size()){
                    if (final[i] == aux.front()) {
                        ok = 1;
                        break;
                    }
                    aux.pop();
                }
            }
            if (ok == 0){
                cout<<"Cuvantul "<<test<<" nu este acceptat"<<endl;
            }
            else{
                cout << "Cuvantul " << test << " este acceptat"<<endl;
                while(current.size()){
                    current.pop();
                }
                current.push(0);
                cout<<0;
                for (int i = 0; i < test.length(); ++i) {
                    cout<<" -> ";
                    int n = current.size();
                    for (int k = 0; k < n; ++k) {
                        for (int j = 0; j < tranz[current.front()].size(); ++j) {
                            if (tranz[current.front()][j].first == test[i]) {
                                cout<<tranz[current.front()][j].second<<" / ";
                                currentNew.push(tranz[current.front()][j].second);
                            }
                        }
                        current.pop();
                    }
                    current = currentNew;
                    while(currentNew.size()){
                        currentNew.pop();
                    }
                }
                cout<<endl;
            }
        }
        cout<<endl;
    }
    return 0;
}
