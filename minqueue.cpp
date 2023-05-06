#include <bits/stdc++.h>

using namespace std;
#define ull unsigned long long

ull S, B, N, P;

class min_queue{
    private:
        vector <ull> qs;
        ull cur;
    public:
        vector <pair <ull, ull>> qm;
        min_queue(){
            cur = 0;
        }

        void push(ull x){
            qs.push_back(x);

            // cout << "HERE" << endl;
            while(!qm.empty() && x <= qm.back().first){
                qm.pop_back();
            }
            qm.emplace_back(x, qs.size() - 1);
        }

        void pop(){
            if(cur == qs.size() - 1) return;

            if(!qm.empty() && qm.front().second == cur){
                qm.erase(qm.begin());
            }

            cur++;
        }

        ull n_min_elem(){ return qm.size(); }
        long long pos_min_elem() {
            return qm[0].second - cur;
        }

};

void solve(){
    const ull A = 1664525, C = 1013904223, R = (1ULL<<32);

    min_queue q;
    cin >> S >> B >> N >> P;

    for(int i = 0; i < B; i++){
        // cout << S << endl;
        q.push(S);
        S = (A * S + C) % R;
    }

    for(int i = 0; i < N; i++){
        // cout << S << endl;
        if(S % 10 < P){
            S = (A * S + C) % R;
            q.push(S);
            // cout << S << endl;
        }

        else q.pop();
        

        cout << q.n_min_elem() << " " << q.pos_min_elem() << endl;
        S = (A * S + C) % R;
    }

}

int32_t main(){
    solve();

    return 0;
}