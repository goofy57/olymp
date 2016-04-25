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

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll, ll> pii;
typedef vector <int> vi;

#define pb push_back
#define mp make_pair

template <class T> inline T sqr(const T& x) { return x * x; }
template <class T> inline void updMin(T& a, const T& b) { if (b < a) a = b; }
template <class T> inline void updMax(T& a, const T& b) { if (b > a) a = b; }

typedef
tree<
  int,
  null_type,
  less<int>,
  rb_tree_tag,
  tree_order_statistics_node_update>
set_t;

// Usage: 
// 
// set_t.order_of_key(key); 
// *set_t.find_by_order(index); 
// 

unordered_map<int, set_t> pluses; 
unordered_map<int, set_t> minuses; 

int a, t, x, n; 

int main()
{
    //freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
	
	  scanf("%d", &n); 
    
    for (int i = 0; i < n; i++) {
      scanf("%d %d %d", &a, &t, &x);
      if (a == 1) {
        pluses[x].insert(t); 
      }
      if (a == 2) {
        minuses[x].insert(t);
      }
      if (a == 3) {
        if (pluses.find(x) == pluses.end()) {
          printf("0\n"); 
        } else {
          int ans = pluses[x].order_of_key(t); 
          if (minuses.find(x) != minuses.end()) {
            ans -= minuses[x].order_of_key(t); 
          }
          printf("%d\n", ans); 
        }
      }
      
    }
  

    return 0;
}
