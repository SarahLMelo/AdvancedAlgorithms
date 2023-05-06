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

class hashtable{
    private:
        ull sz;
        const ull P = (1ULL<<31) - 1;
        vector <vector <ull>> table;
        vector <ull> a, b;

        ull hashing(ull k, ull int i){
            return ((a[i] * k + b[i]) % P) % sz;
        }

    public:
        hashtable(ull N, rng &gen){
            bool createTable = true;
            while(createTable){
                table.assign(2 * (N/2) + 1, {});

                a[0] = 1 + gen.next() % (P - 1);
                b[0] = gen.next() % P;

                for(int i = 0; i < N; i++){
                    ull k = gen.next();
                    table[hashing(k, 0)].push_back(k);
                }

                ull sum = 0;
                for(auto i:table){
                    sum += i.size()*i.size();
                }

                if(sum <= 4*N) createTable = false;
            }

            

            
        }


};

int main(){
    ull S, U, M, I, Q, Pi, Pq;

    return 0; 
}