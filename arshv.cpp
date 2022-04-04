#include<bits/stdc++.h>
using namespace std;
#define ll long long int


string to_bin(ll x)
{
    if(x == 0)
        return "";
    else
    {
        string s = to_bin(x / 2);
        s.push_back(char('0' + x % 2));
        return s;
    }
}

ll global_d,Bucket_s;
ll current_s=2;
ll no_of_buckets=2;
ll time_=0;


struct Bucket
{
	vector<ll> v;
	ll local_d = 1;
	ll creation_time = 0;

	int size_()
	{
		return v.size();
	}

	void into(ll n)
	{
		v.push_back(n);
	}
};


map<ll,Bucket *> dir;


void split(int k,Bucket * nbucket)
{
	no_of_buckets++;
    Bucket * newB = new Bucket;
    vector<int>temp;
    for(auto i : nbucket->v)
    {
        temp.push_back(i);
    }

    nbucket->v.clear();

    if(nbucket->local_d == global_d)
    {
        dir[k ^ (1<<global_d)] = newB;
		dir[k ^ (1<<global_d)]->creation_time = time_++;
        if(global_d!=0)
        {
         for (int i = 0; i < (1<<global_d); ++i)
            {

                if(i!=k)
                    dir[i ^ (1<<global_d)] = dir[i];
            }
        }
        global_d++;
        newB->local_d = ++ nbucket->local_d;
        for(auto i : temp)
        {
            int h = i & ((1<<global_d) -1);
            dir[h]->v.push_back(i);
        }
    }
    else
    {
        int li = k & (1<<(nbucket->local_d) - 1);
        vector<int>indices;
     for (int i = 0; i < (1<<global_d); ++i)
        {
            int last = i & (1<<(nbucket->local_d)) - 1;
            if(last==li)
                indices.push_back(i);
        }
        newB->local_d = ++nbucket->local_d;
		newB->creation_time = time_++;
     for (int i = indices.size()/2; i < indices.size(); ++i)
        {
            dir[indices[i]] = newB;
        }

        for(auto i : temp)
        {
            int h = i & ((1<<global_d) -1);
            dir[h]->v.push_back(i);
        }
    }

}

void insert(ll n)
{
	string s = to_bin(n);
	ll temp = global_d;
	ll dir_n0 = 0;
	ll t1 = 1;
	for(ll t = s.length()-1 ; temp>0 && t>=0;t--,temp--)
	{
		dir_n0 += t1*(s[t]-'0');
		t1*=2;
	}
	// dir_n0--;
	ll size__ = dir[dir_n0]->v.size();
	if(size__ < Bucket_s)
	{
		dir[dir_n0]->v.push_back(n);
	}
	else
	{
		split(dir_n0,dir[dir_n0]);
		// if(dir[dir_n0]->local_d==global_d)
		// {
		// 	dir[dir_n0]->local_d++;
		// 	split_dir(dir[dir_n0]->local_d,dir_n0,n);
		// 	no_of_buckets++;
		// }
		// else
		// {
		// 	dir[dir_n0]->local_d++;
		// 	make_new_dir(dir[dir_n0]->local_d,dir_n0,n);
		// 	no_of_buckets++;
		// }
	}

}


int main()
{
	cin>>global_d>>Bucket_s;
	current_s = pow(2,global_d);

	// Bucket * bc = new Bucket;
	// Bucket * bc1 = new Bucket;

	for(ll i=0;i<current_s;i++)
	{
		Bucket * bc = new Bucket;
		dir[i] = bc;
		dir[i]->local_d = global_d;
		dir[i]->creation_time = time_;
		time_++;

	}

	ll x = 0;
	cin>>x;

	while(x!=6)
	{
		// cout<<global_d<<" "<<Bucket_s<<"\n";
		// cout<<"\n";
		// cout<<"2: Insert a new Element!\n";
		// cout<<"3: Search a Element!\n";
		// cout<<"4: Delete a value!\n";
		// cout<<"5: Display the Hash Table!\n";
		// cout<<"6: Quit!\n";
		// cin>>x;
		switch(x)
		{
			case 2:{
						ll num;
						cin>>num;
						insert(num);
						break;
				   }

			case 3:{
						ll x;
						cin>>x;
						string s = to_bin(x);
						ll temp = global_d;
						ll dir_n0 = 0;
						ll t1=1;

						for(ll i=s.length()-1;i>=0 && temp>0;i--,temp--)
						{
							dir_n0 += t1*(s[i]-'0');
							t1 *= 2;
						}

						// dir_n0--;

						vector<ll> v1 = dir[dir_n0]->v;

						bool ok = false;

						for(auto it : v1)
						{
							if(it==x)
							{
								ok = true;
								break;
							}
						}

						if(ok)
						{
							cout<<"Yes Element is there!\n";
						}
						else
						{
							cout<<"#searchElement does not exist!\n";
						}

						break;
				   }
			case 4:{
						ll x;
						cin>>x;
						string s = to_bin(x);
						ll temp = global_d;
						ll dir_n0 = 0;
						ll t1=1;

						for(ll i=s.length()-1;i>=0 && temp>0;i--,temp--)
						{
							dir_n0 += t1*(s[i]-'0');
							t1 *= 2;
						}

						// dir_n0--;

						vector<ll> v1 = dir[dir_n0]->v;

						bool ok = false;

						for(auto it = v1.begin();it!=v1.end();it++)
						{
							if(*it==x)
							{
								ok = true;
								v1.erase(it);
								break;
							}
						}

						if(ok)
						{
							cout<<"Yes Element is Deleteed!\n";
						}
						else
						{
							cout<<"# delete Element does not exist!\n";
						}
						break;
			       }
			case 5:{
						cout<<global_d<<" \n"<<no_of_buckets<<"\n";
						ll x = (1<<global_d);
						set<pair<ll, pair < vector<ll>,ll >>> s;

						vector<pair<ll, pair < vector<ll>,ll >>> final;
						for(ll i=0; i<x; i++)
						{
							vector<ll> temp = dir[i]->v;

							ll ld = dir[i]->local_d;
							ll ct = dir[i]->creation_time;
							s.insert({ct,{temp,ld}});

							// cout<<temp.size()<<" "<<ld<<"\n";
						}

						for(auto t: s)
						{
							vector<ll> t1 = t.second.first;
							// cout<<t1.size()<<" "<<t.second.second<<"\n";
							final.push_back({t.first,{t1,t.second.second}});
						}

						sort(final.begin(),final.end());

						for(auto t: final)
						{
							// cout<<t.first<<" ";
							cout<<t.second.first.size()<<" "<<t.second.second<<"\n";
						}
						break;
				   }

			default:{

				cout<<"Enter the correct choice between 2 to 6 :";
				break;
			}

		}

		cin>>x;
	}


}
