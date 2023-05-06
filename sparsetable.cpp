#include <bits/stdc++.h>

using namespace std;
#define ull unsigned long long

class rng{
    private:
        ull x, S, A, C, R;
    public:
        rng(ull s){
            this->S = s;

            x = s;
            A = 1664525;
            C = 1013904223;
            R = (1ULL<<32);
        }

        ull next(){
            ull ans = x;
            x = (A * x + C) % R;

            return ans;
        }
};

class sparse_table{
    private:
        ull n, m;

    public:
        vector <vector <ull>> table;
        sparse_table(vector <ull> &v, ull cmd){
            n = v.size();
            m = floor(log2(n)) + 1;
            table.assign(n, vector <ull> (m, 0));

            for(int j = 0; j < m; j++){
                for(int i = 0; i < n; i++){
                    if(j){
                        if(i + 1 == n) table[i][j] = table[i][j-1];
                        else{
                            switch (cmd){
                            case 1: // SUM
                                table[i][j] = table[i][j-1] + table[min((ull)i+(1 << (j-1)), n-1)][j-1];
                                break;
                            case 2: // MIN
                                table[i][j] = min(table[i][j-1], table[min((ull)i+(1 << (j-1)), n-1)][j-1]);
                                break;
                            case 3: // MAX
                                table[i][j] = max(table[i][j-1], table[min((ull)i+(1 << (j-1)), n-1)][j-1]);
                                break;
                            
                            
                            }
                        }
                    }
                    else table[i][j] = v[i];
                }
            }

        }

        ull query(int l, int r, int cmd){
            ull ans;
            if(cmd == 1) ans = 0;
            else if(cmd == 2) ans = (1ULL<<32);
            else ans = 0;

            for(int i = 30; i >= 0; i--){
                if(l + (1 << i) <= r){
                    // cout << (1<<i) << " ";
                    if(cmd == 1){
                        ans += table[l][i];
                    }
                    else if(cmd == 2){
                        ans = min(ans, table[l][i]);
                    }
                    else{
                        ans = max(ans, table[l][i]);
                    }
                    l+=(1<<i);
                }

                if(i == 0) break;
            }

            return ans;
        }

        void update(ull v, int cmd, int l, int r, int y = 0){
            if(y == m) return;
            if(!y){
                table[l][y] = v;
                update(v, cmd, max(l-1, 0), r, y+1);
                return;
            }

            for(int i = l; i < r; i++){
                if(i + 1 == n) table[i][y] = table[i][y-1];
                else{
                    switch (cmd){
                    case 1: // SUM
                        table[i][y] = table[i][y-1] + table[min((ull)i+(1 << (y-1)), n-1)][y-1];
                        break;
                    case 2: // MIN
                        table[i][y] = min(table[i][y-1], table[min((ull)i+(1 << (y-1)), n-1)][y-1]);
                        break;
                    case 3: // MAX
                        table[i][y] = max(table[i][y-1], table[min((ull)i+(1 << (y-1)), n-1)][y-1]);
                        break;  
                    }
                }
            }

            update(v, cmd, max(l - (1 << y), 0), r, y+1);
        }

        void print(){
            for(auto i:table){
                for(auto j:i){
                    cout << j << " ";
                }
                cout << "\n";
            }
        }
};

int main(){
    ull cnt = 0, s;

    while(cin >> s){
        ull n, o, q, u, cmd;
        string f;

        cin >> n >> f >> o >> q >> u;
        if(f == "SUM") cmd = 1;
        else if(f == "MIN") cmd = 2;
        else cmd = 3;

        rng g(s);
        vector <ull> v(n);
        for(int i = 0; i < n; i++){
            v[i] = g.next() % (4 * n);
        }

        sparse_table st(v, cmd);
        // st.print();
        cout << "caso " << cnt++ << "\n";

        for(ull a = 0; a < o; a++){
            ull x = g.next();

            if(x % (q+u) < q){
                // cout << a << " ";
                ull l = g.next() % n;
                ull r = l + (g.next() % (n - l));
                // cout << l << " " << r << "\n";

                cout << st.query(l, r+1, cmd) << endl;
            }
            else{
                // cout << "test" << endl;
                ull i = g.next() % n, v = g.next() % (4 * n);
                st.update(v, cmd, i, i+1);
                cout << st.query(i, n, cmd) << "\n";
            }
        }
        cout << "\n";
    }

    return 0; 
}