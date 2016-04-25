#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <ctime>
#include <cassert>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <string>
#include <sstream>
#include <unordered_set>
#include <unordered_map>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pii;
typedef vector <int> vi;

#define pb push_back
#define mp make_pair

template <class T> inline T sqr(const T& x) { return x * x; }
template <class T> inline void updMin(T& a, const T& b) { if (b < a) a = b; }
template <class T> inline void updMax(T& a, const T& b) { if (b > a) a = b; }

struct node {
  int k, p, sz;
  node * l, * r; 
  node() { }
  node (int k, int p) : k(k), p(p), l(NULL), r(NULL), sz(1) { }
};

typedef node * pnode; 

inline int getSize(pnode v) {
  if (!v) return 0; 
  return v->sz; 
}

inline void updSize(pnode v) {
  if (!v) return; 
  v->sz = 1 + getSize(v->l) + getSize(v->r); 
}

struct treap {
  pnode root; 
  
  treap() : root(NULL) { }
  
  int lower_bound(int t) {
    pnode a = NULL, b = NULL;
    split(root, t, a, b); 
    int ret = getSize(a); 
    merge(root, a, b); 
    return ret; 
  }
  
  void insert(int t) {
    insert(root, new node(t, rand())); 
  }
           
private:
           
  void insert(pnode & root, pnode v) {
    updSize(root); 
    updSize(v); 
    
    if (!root) {
      root = v;
    } else if (v->p > root->p) {
      split(root, v->k, v->l, v->r),  root = v;
    } else {
      insert(v->k < root->k ? root->l : root->r, v);
    }
      
    updSize(v); 
    updSize(root); 
  }

  void split (pnode root, int key, pnode & l, pnode & r) {
    updSize(root); 
    updSize(l); 
    updSize(r); 
    
    if (!root) {
        l = r = NULL;
    } else if (key < root->k) {
        split(root->l, key, l, root->l),  r = root;
    } else {
        split(root->r, key, root->r, r),  l = root;
    }
    
    updSize(r); 
    updSize(l); 
    updSize(root); 
  }


  void merge(pnode & root, pnode l, pnode r) {
    updSize(root); 
    updSize(l); 
    updSize(r); 
    
    if (!l || !r) {
        root = l ? l : r;
    } else if (l->p > r->p) {
        merge(l->r, l->r, r),  root = l;
    } else {
        merge(r->l, l, r->l),  root = r;
    }
    
    updSize(r); 
    updSize(l); 
    updSize(root); 
  }
}; 

unordered_map<int, treap> pluses; 
unordered_map<int, treap> minuses; 

int a, t, x, n; 

int main()
{
    //freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
	
	  scanf("%d", &n); 
    
    for (int i = 0; i < n; i++) {
      scanf("%d %d %d", &a, &t, &x);
      if (a == 1) {
        if (pluses.find(x) == pluses.end()) {
          pluses[x] = treap(); 
        } 
        pluses[x].insert(t); 
      }
      
      if (a == 2) {
        if (minuses.find(x) == minuses.end()) {
          minuses[x] = treap(); 
        } 
        minuses[x].insert(t);
      }
      
      if (a == 3) {
        if (pluses.find(x) == pluses.end()) {
          printf("0\n"); 
        } else {
          int ans = pluses[x].lower_bound(t); 
          if (minuses.find(x) != minuses.end()) {
            ans -= minuses[x].lower_bound(t); 
          }
          printf("%d\n", ans); 
        }
      }
    }
  

    return 0;
}
