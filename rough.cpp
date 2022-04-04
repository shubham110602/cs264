#include <iostream>
#include <string.h>
#include <sstream>
#include <vector>
using namespace std;
#define rep(i, a, b) for(int i = (a); i < (b); i++)
#define ll long long
#define trav(x, k) for(auto& x : k)
int global_dis, buc_size;
int no_buckets = 2;

class bucket{
    public:
    vector<int> vx;
    int id;
    int a;
    bucket(int x, int j){
    id = x;
    a = j;
    }
};

vector<bucket*> table;

int stringtoint(string s){
stringstream ss(s);
int x;
ss >> x;
return x;
}

string itb(int x)
{
    if(x == 0)
        return "";
    else
    {
        string s = itb(x / 2);
        s.push_back(char('0' + x % 2));
        return s;
    }

}
int lastdig(string s, int t){

    int temp = global_dis;
    string s1 = s.substr(s.length() - temp,s.length());

    int n = stoi(s1,0,2);

    return n;
}
int get_last_digits(int x, int n){
	int a = ~(~(0ll) << n);
	return x & a;
}

void split(int k,bucket * nbucket)
{
	no_buckets++;
    vector<bucket*> temp(table.size()*2);

    vector<int>t;
    for(auto i : nbucket->vx)
    {
        t.push_back(i);
    }

    nbucket->vx.clear();

    if(nbucket->id == global_dis)
    {
        table[k ^ (1<<global_dis)] = temp;

        if(global_dis!=0)
        {
         for (int i = 0; i < (1<<global_dis); ++i)
            {

                if(i!=k)
                    table[i ^ (1<<global_dis)] = table[i];
            }
        }
        global_dis++;
        newB->id = ++ nbucket->id;
        for(auto i : temp)
        {
            int h = i & ((1<<global_dis) -1);
            table[h]->vx.push_back(i);
        }
    }
    else
    {
        int li = k & (1<<(nbucket->id) - 1);
        vector<int>indices;
     for (int i = 0; i < (1<<global_dis); ++i)
        {
            int last = i & (1<<(nbucket->id)) - 1;
            if(last==li)
                indices.push_back(i);
        }
        newB->id = ++nbucket->id;

     for (int i = indices.size()/2; i < indices.size(); ++i)
        {
            table[indices[i]] = newB;
        }

        for(auto i : temp)
        {
            int h = i & ((1<<global_dis) -1);
            table[h]->vx.push_back(i);
        }
    }

}




void growTable(vector<bucket*>& table){
	vector<bucket*> temp(table.size() * 2);
	rep(i, 0, table.size()){
		temp[i] = table[i];
		temp[i + table.size()] = table[i];
	}
	table = temp;
	global_dis++;
}

bool isPresent(vector<bucket*>& table, int tgt){
	            string s = itb(tgt);
            int dir_no = lastdig(s, global_dis);
	trav(x, table[dir_no]->vx){
		if(x == tgt) return 1;
	}
	return 0;
}

void mergeBucket(vector<bucket*>& table, int dig){
	if(table[dig]->id == 1 || dig < 2) return;

	bucket* temp = table[dig];
	bucket* changeTo = table[dig - ceil(log2(dig))];

	rep(i, dig, table.size()){
		if(table[i] == temp){
			table[i] = changeTo;
		}
	}
}









void status(vector<bucket*>& table){
    cout << global_dis << "\n";
    int x = 0;
    for(int i = 0; i < table.size(); i++){
        if(i == table[i]->a) x++;
    }
    cout << x <<endl;
    for(int i = 0; i < table.size(); i++){
        if(i != table[i]->a) continue;

		cout << table[i]->vx.size() << " " << table[i]->id << endl;
    }
}


int main(){

    cout << "Enter the global depth and bucket size\n";
    cin >>global_dis >> buc_size;


    for(int i = 0; i < table.size(); i++){
        table[i] = new bucket(global_dis,i);
    }
    while(1){
        cout << "Enter the following digit according to the given information:\n2 for insertion\n3 for searching\n4 for deletion\n5 to show table status\n";
        int t;
        cin >> t;
        cout << "Enter the digit with you want to perform your desired operation\n";
        int x;
        cin >> x;



        if(t == 6) break;
        else if(t == 5) status(table);
        else if(t == 4){
            string s = itb(x);
            int dir_no = lastdig(s, global_dis);
            vector <int> v1 = table[dir_no]->vx;
             bool done = 0;

            for(auto itr = table[dir_no]->vx.begin(); itr != table[dir_no]->vx.end(); itr++){
            if(*itr == x){
                bool done = 1;
                table[dir_no]->vx.erase(itr);
                break;
                }

            }
        }

        else if(t == 3){
            string s = itb(x);
            int dir_no = lastdig(s, global_dis);
            vector <int> v1 = table[dir_no]->vx;
             bool done = 0;

            for(auto itr = table[dir_no]->vx.begin(); itr != table[dir_no]->vx.end(); itr++){
            if(*itr == x){
                bool done = 1;
                cout << "Element is there\n";
                break;
                }
            else cout << "Element is not there\n";
            }

        }

        else if(t == 2){
            string s = itb(x);
            int dir_no = lastdig(s, global_dis);
            vector <int> v1 = table[dir_no]->vx;
            ll size__ = table[dir_no]->vx.size();
	if(size__ < buc_size)
	{
		table[dir_no]->vx.push_back(x);
	}
	else
	{
		split(dir_no,table[dir_no]);
	}
        }

    }
}
