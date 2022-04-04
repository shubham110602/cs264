#include<bits/stdc++.h>

using namespace std;

#define ll long long
#define int long long
#define vi vector<int>
#define pii pair<int,int>
#define pll pair<ll,ll>
#define psi pair<string,ll>
#define mii map<int,int>
#define mp make_pair
#define MOD 1000000007
#define mod 1000003
#define pb push_back
#define eb emplace_back
#define lim 100000
#define ff first
#define ss second
#define endl "\n"
#define PI 3.1415926535
#define golden 1.6180339887498
#define pspii pair<string, pair<int, int>>
#define rep(i, a, b) for(int i = (a); i < (b); i++)
#define repl(i,a, b) for(int i = (a); i > (b); i--)
#define MAX 1e16
#define trav(x, k) for(auto& x : k)

// struct hash_pair {
//     template <class T1, class T2>
//     size_t operator()(const pair<T1, T2>& p) const {
//         auto hash1 = hash<T1> {}(p.first);
//         auto hash2 = hash<T2> {}(p.second);
//         return hash1 ^ hash2;
//     }
// };

ll power(ll a, ll b, ll c) { ll ans = 1; ll k = a; while (b > 0) { if (b & 1) { ans *= k; ans %= c; } k = (k * k) % c; b = b >> 1;} return ans;}

// ll ncr(ll n,ll r,ll*arr){
//     if(r==0) return 1;
//     ll res = 1;
//     return (arr[n]*(power(arr[n-r],MOD-2, MOD))%MOD*(power(arr[r],MOD-2, MOD))%MOD)%MOD;
// }

ll gcd(ll a, ll b) { if (a == 0) return b; if (b == 0) return a; return gcd(b, a % b); }
ll add_mod(ll a, ll b, ll m) {return ((a % m) + (b % m)) % m;}
ll sub_mod(ll a, ll b, ll m) {return ((a % m) - (b % m) + m) % m;}
ll mul_mod(ll a, ll b, ll m) {return ((a % m) * (b % m)) % m;}
void print(double val, int k) { cout << fixed << setprecision(k) << val << " ";}
ll toint(string s) {stringstream ss; ss << s; ll x; ss >> x; return x;}


// <------------------------------------------- WRITE CODE HERE ------------------------------------------------>


int gd, bc;

int get_last_digits(int x, int n){
	int a = ~(~(0ll) << n);
	return x & a;
}

class bucket{
public:
	vi arr;
	int ld;
	int actual;

	bucket(int x, int j) {
		ld = x;
		actual = j;
	}
};

void growTable(vector<bucket*>& table){
	vector<bucket*> temp(table.size() * 2);
	rep(i, 0, table.size()){
		temp[i] = table[i];
		temp[i + table.size()] = table[i];
	}
	table = temp;
	gd++;
}

void deleteValue(vector<bucket*>& table, int x, int dig){
	for(auto itr = table[dig]->arr.begin(); itr != table[dig]->arr.end(); itr++){
		if(*itr == x){
			table[dig]->arr.erase(itr);
			return;
		}
	}
}

bool isPresent(vector<bucket*>& table, int tgt){
	int dig = get_last_digits(tgt, gd);
	trav(x, table[dig]->arr){
		if(x == tgt) return 1;
	}
	return 0;
}

void printTable(vector<bucket*>& table){
	rep(i, 0, table.size()){
		if(i != table[i]->actual) continue;
		cout << i << " : ";

		trav(x, table[i]->arr){
			cout << x << " ";
		}

		cout << endl;
	}
	cout << endl;
}

void mergeBucket(vector<bucket*>& table, int dig){
	if(table[dig]->ld == 1 || dig < 2) return;

	bucket* temp = table[dig];
	bucket* changeTo = table[dig - ceil(log2(dig))];

	rep(i, dig, table.size()){
		if(table[i] == temp){
			table[i] = changeTo;
		}
	}
}

void printTableStatus(vector<bucket*>& table){
	cout << endl << gd << endl;
	int x = 0;

	rep(i, 0, table.size()){
		if(i == table[i]->actual) x++;
	}
	cout << x << endl;
	rep(i, 0, table.size()){
		if(i != table[i]->actual) continue;
		//cout << "#" << i << " : " ;
		cout << table[i]->arr.size() << " " << table[i]->ld << endl;
	}
	cout << endl;
}

void solve(){
	cin >> gd >> bc;
	vector<bucket*> table ((1ll) << (gd));

	rep(i, 0, table.size()) table[i] = new bucket(gd, i);

	while(1){
		int x; cin >> x;

		if(x == 6) {

			break;

		} else if(x == 5) {

			// printTable(table);

			printTableStatus(table);

		} else if(x == 2) {

			cin >> x;

			if(isPresent(table, x)) continue;

			bool canInsert = 1;
			int dig = get_last_digits(x, gd);
			dig = get_last_digits(x, table[dig]->ld);

			while(table[dig]->arr.size() == bc){

				if(gd > 20){
					cout << "\nError : Cannot expand directory further\n\n";
					canInsert = 0;
					break;
				}

				if(table[dig]->ld == gd){
					if(gd == 20){
						cout << "\nError : Cannot expand directory further\n\n";
						canInsert = 0;
						break;
					}
					growTable(table);
				}

				int split_dig;

				table[dig]->ld++;
				int new_dig = get_last_digits(x, table[dig]->ld);
				if(new_dig == dig)
					split_dig = dig + ((1ll) << (table[dig]->ld-1));
				else
					split_dig = new_dig;


				table[split_dig] = new bucket(table[dig]->ld, split_dig);


				rep(j,0,table[dig]->arr.size()){
					int abc = table[dig]->arr[j];

					if(dig != get_last_digits(abc, table[dig]->ld)){
						deleteValue(table, abc, dig);
						table[get_last_digits(abc, table[dig]->ld)]->arr.pb(abc);
						j--;
					}
				}

				if(table[dig]->arr.size() == 0){
					mergeBucket(table, dig);
				}

				if(split_dig != new_dig) {
					if(table[split_dig]->arr.size() == 0) {
						table[split_dig] = table[dig];
					}
				}

				if(table[new_dig]->arr.size() == bc) {
					dig = new_dig;
					continue;
				} else {
					dig = new_dig;
					break;
				}

			}

			if(canInsert)
				table[dig]->arr.pb(x);

		} else if(x == 3) {

			cin >> x;
			if(isPresent(table, x)) {
				cout << "YES\n\n";
			}
			else {
				cout << "NO\n\n";
			}

		} else if(x == 4) {

			cin >> x;
			if(isPresent(table, x)) {
				int dig = get_last_digits(x, gd);
				deleteValue(table, x, dig);

				if(table[dig]->arr.size() == 0 && table[dig]->ld > 1) {
					mergeBucket(table, dig);
				}
			}

		}
	}

}

int32_t main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

#ifndef ONLINE_JUDGE

    freopen("input1.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

#endif

    int t = 1;
    // cin >> t;
    while(t--) solve();
    return 0;
}
