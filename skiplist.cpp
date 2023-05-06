#include <bits/stdc++.h>

using namespace std;
#define ull unsigned long long
#define endl "\n"
ull cnt;

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

struct node{
    ull val;
    ull height;
    vector <node*> next;
};

class skiplist{
    private:
        node head;

        ull random_height(rng &gen){
            ull l = 1;
            while(gen.next() % 100 < 50 && l <= head.height) l++;
            return l;
        }


    public:
        skiplist(ull L){
            head.height = L;
            head.next.assign(L, nullptr);
        }

        vector <node *> precursor(ull val){
            vector <node *> p(head.height, nullptr);
            node *cur = &head;
            for(int i = head.height - 1; i >= 0; i--){
                while(cur->next[i] != nullptr && cur->next[i]->val < val){
                    cur = cur->next[i];
                    cnt++;
                }

                p[i] = cur;
            }

            return p;
        }

        node* search(ull val, bool print){
            cnt = 1;
            vector <node *> p = precursor(val);

            if(p[0]->next[0] != nullptr && p[0]->next[0]->val == val){
                if(print) cout << "F " << cnt << " " << p[0]->next[0]->height << endl;
                return p[0]->next[0];
            }
            else{
                if(print) cout << "F " << cnt << " " << 0 << endl;
                return nullptr;
            }
        }

        void insert(ull val, rng &gen, bool print){
            vector <node *> p = precursor(val);

            if(p[0]->next[0] != nullptr && p[0]->next[0]->val == val){
                if(print) cout << "I 0" << endl;
                return;
            }

            ull h = random_height(gen);
            if(h > head.height){
                while(head.next.size() < h){
                    head.next.push_back(nullptr);
                    head.height++;
                }
                while(p.size() < h) p.push_back(&head);
            }

            node *n = new node();
            n->height = h;
            n->next.assign(h, nullptr);
            n->val = val;

            for(ull i = 0; i < h; i++){
                n->next[i] = p[i]->next[i];
                p[i]->next[i] = n;
            }

            if(print) cout << "I 1" << endl;
        }

        void remove(ull val, bool print){
            vector <node *> p = precursor(val);
            // cout << val << " " << p[0]->next[0]->val << " ";
            if(p[0]->next[0] != nullptr && p[0]->next[0]->val == val){
                node *n = p[0]->next[0];
                for(int i = 0; i < n->height; i++){
                    p[i]->next[i] = n->next[i];
                }

                while(head.height > 1 && head.next.back() == nullptr){
                    head.height--;
                    head.next.pop_back();
                    // cout << "HERE" << endl;
                }

                if(print){
                    cout << "D 1" << endl;
                }
            }

            else if(print) cout << "D 0" << endl;
        }


};

int main(){
    ull S, U, B, N, F, I, D, P;

    cin >> S >> U >> B >> N >> F >> I >> D >> P;
    rng gen(S);
    skiplist list(1);

    for(int i = 0; i < B; i++){
        ull x = gen.next() % U;
        list.insert(x, gen, 0);
    }

    for(int i = 0; i < N; i++){
        int x = gen.next() % (F+I+D);
        // cout << x << endl;

        if(x < F){
            // if(!(i % P)) cout << x << " ";
            x = gen.next() % U;
            list.search(x, !(i % P));
        }

        else if(F <= x && x < F + I){
            x = gen.next() % U;
            list.insert(x, gen, !(i % P));
        }

        else{
            x = gen.next() % U;
            list.remove(x, !(i% P));
        }
    }

    return 0;
}