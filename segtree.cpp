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

class segtree{
    private:
        int N, cmd;
        vector <ull> tree;

        void build(vector <ull> &v, int n, int l, int r){
            if(l == r){
                tree[n] = v[l];
                return;
            }

            int mid = (l+r)/2;
            build(v, 2*n, l, mid);
            build(v, 2*n + 1, mid + 1, r);

            switch (cmd)
            {
            case 1:
                tree[n] = tree[2*n] + tree[2*n + 1];
                break;
            case 2:
                tree[n] = min(tree[2*n], tree[2*n + 1]);
                break;
            case 3:
                tree[n] = max(tree[2*n], tree[2*n + 1]);
                break;
            }
        }

        ull queryAux(int n, int l, int r, int lI, int rI){
            if(lI > r || rI < l){
                switch (cmd)
                {
                case 1:
                    return 0;
                case 2:
                    return ULLONG_MAX;
                case 3:
                    return 0;
                }
            }
            if(lI <= l && r <= rI) return tree[n];

            int mid = (l + r)/2;
            
            switch (cmd)
            {
            case 1:
                return queryAux(2*n, l, mid, lI, rI) + queryAux(2*n+1, mid+1, r, lI, rI);
            case 2:
                return min(queryAux(2*n, l, mid, lI, rI), queryAux(2*n+1, mid+1, r, lI, rI));
            case 3:
                return max(queryAux(2*n, l, mid, lI, rI), queryAux(2*n+1, mid+1, r, lI, rI));
            }
        }

        void updateAux(int pos, ull val, int n, int l, int r){
            if(l == r){
                tree[n] = val;
                return;
            }

            int mid = (l+r)/2;
            if(pos <= mid) updateAux(pos, val, 2*n, l, mid);
            else updateAux(pos, val, 2*n + 1, mid + 1, r);

            switch (cmd)
            {
            case 1:
                tree[n] = tree[2*n] + tree[2*n + 1];
                break;
            case 2:
                tree[n] = min(tree[2*n], tree[2*n + 1]);
                break;
            case 3:
                tree[n] = max(tree[2*n], tree[2*n + 1]);
                break;
            }
        }

    public:
        segtree(int n, int cmd, vector <ull> &v){
            this->N = n;
            this->cmd = cmd;

            tree.resize(4*N);
            build(v, 1, 0, n-1);
        }

        ull query(int l, int r){
            return queryAux(1, 0, N-1, l, r);
        }

        void update(ull val, int pos){
            updateAux(pos, val, 1, 0, N-1);
        }
};

int main(){
    ull cnt = 0, s;

    while(cin >> s){
        ull n, w, q, u, cmd, p;
        string f;

        cin >> n >> f >> w >> q >> u >> p;
        if(f == "SUM") cmd = 1;
        else if(f == "MIN") cmd = 2;
        else cmd = 3;


        rng g(s);
        // cout << n << endl;
        vector <ull> v(n);
        for(int i = 0; i < n; i++){
            v[i] = g.next() % (4 * n);
        }

        segtree seg(n, cmd, v);
        cout << "caso " << cnt++ << "\n";

        for(ull a = 0; a < w; a++){
            ull x = g.next();

            if(x % (q+u) < q){
                ull l = g.next() % n;
                ull r = l + (g.next() % (n - l));

                if(!(a%p)) cout << seg.query(l, r) << "\n";
            }
            else{
                ull i = g.next() % n, v = g.next() % (4 * n);
                seg.update(v, i);
                if(!(a%p)) cout << seg.query(i, n) << "\n";
            }
        }
        cout << "\n";
    }

    return 0;
}