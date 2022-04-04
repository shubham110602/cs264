#include <iostream>
#include <string.h>
#include <sstream>
#include <vector>
using namespace std;

int global_dis, buc_size;
int no_buckets = 2;

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
int lastdig(string s){

    int temp = global_dis;
    string s1 = s.substr(s.length() - temp,s.length());

    int n = stoi(s1,0,2);

    return n;
}


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
            int dir_no = lastdig(s);
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
            int dir_no = lastdig(s);
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
            int dir_no = lastdig(s);
            vector <int> v1 = table[dir_no]->vx;

            long long si_ze = table[dir_no]->vx.size();
            if(si_ze < buc_size){
                table[dir_no]->vx.push_back(x);
            }
            //else split(dir_no, table[dir_no]);
        }

    }
}
