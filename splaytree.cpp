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

struct node{
    node *left, *right, *par;
    ull key;

    node(ull key, node *par = NULL){
        left = NULL;
        right = NULL;
        this->par = par;

        this->key = key;
    }
};

class splayTree{
    private:
        node *root;

        node *search(ull val){
            node *cur = root;
            while(cur != NULL && cur->key != val){
                if(val < cur->key) cur = cur->left;
                else cur = cur->right;
            }

            return cur;
        }

        node *rotate_left(node *x){
            node *p = x->par, *r = x->right, *rl = r->left;

            x->right = rl;
            if(rl != NULL) rl->par = x;

            r->left = x;
            x->par = r;
            r->par = p;

            if(p != NULL){
                if(p->left == x) p->left = r;
                else p->right = r;
            }

            return r;
        }

        node *rotate_right (node *x) {
            auto p = x->par, l = x->left, lr = l->right;
            x->left = lr;
            if (lr) {
                lr->par = x;
            }
            l->right = x;
            x->par = l;
            l->par = p;
            if (p) {
                if(x == p->right) p->right = l;
                else p->left = l;
            }

            return x;
        }

        node *zig(node *x){
            node *p =x->par;

            if(x == p->left) return rotate_right(p);
            else return rotate_left(p);
        }

        node *zigzag(node *x){
            node *p = x->par, *g = p->par;

            if(p == g->left){
                if(x == p->left){
                    rotate_right(g);
                    return rotate_right(p);
                }

                else{
                    rotate_left(p);
                    return rotate_right(g);
                }
            }

            else{
                if(x == p->right){
                    rotate_left(g);
                    return rotate_left(p);
                }

                else{
                    rotate_right(p);
                    return rotate_left(g);
                }
            }

        }

        node *splay(node *x){
            while(x->par != NULL){
                node *g = x->par->par;

                if(g == NULL) zig(x);
                else zigzag(x);
            }

            return x;
        }

    public:
        splayTree(){
            root = NULL;
        }

        void push(ull val, bool print){
            if(root == NULL){
                root = new node(val);
                if(print) cout << "I " << val << " " << "0\n";
                return;
            }

            node *aux = search(val);

            if(aux != NULL){
                if(print) cout << "I " << val << " " << "-1\n";
                return;
            }

            aux = new node(val);
            node *cur = root;

            while(cur != aux){
                if(aux->key < cur->key){
                    if(cur->left == NULL){
                        cur->left = aux;
                        aux->par = cur;
                    }

                    cur = cur->left;
                }

                else{
                    if(cur->right == NULL){
                        cur->right = aux;
                        aux->par = cur;
                    }

                    cur = cur->right;
                }
            }

            if(print){
                int cnt = 0;
                while(cur->par != NULL){
                    cnt++;
                    cur = cur->par;
                }

                cout << "I " << val << " " << cnt << "\n";
            }
        }
        
        node *find(ull val, bool print){
            node *x = search(val);

            if(x == NULL && print) cout << "Q " << val << " " << "-1\n";
            if(x != NULL){
                if(print){
                    node *aux = x;
                    int cnt = 0;

                    while(aux != NULL){
                        cnt++;
                        aux = aux->par;
                    }

                    cout << "Q " << val << " " << cnt-1 << endl;
                }
                root = splay(x);
            }

            return x;
        }
};

int main(){
    ull S, U, B, N, I, Q, P;

    cin >> S >> U >> B >> N >> I >> Q >> P;

    rng gen(S);
    splayTree tree;

    for(ull i = 0; i < B; i++)
        tree.push(gen.next() % U, 0);
    

    for(ull i = 0; i < N; i++){
        bool print = !(i%P);
        ull x = gen.next() % (I+Q);
        ull k = gen.next() % U;
        // cout << x << " ";

        if((x % (I + Q)) < I) tree.push(k, print);
        else tree.find(k, print);
        
    }

    return 0; 
}