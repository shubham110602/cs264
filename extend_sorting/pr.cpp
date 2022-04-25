#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <bits/stdc++.h>
#include <algorithm>

using namespace std;

typedef pair<int, pair<int, int> > ppi;

vector<int> mergeKArrays(vector<vector<int> > arr){
    vector<int> output;
    priority_queue<ppi, vector<ppi>, greater<ppi> > pq;
    for (int i = 0; i < arr.size(); i++){
        pq.push({ arr[i][0], { i, 0 } });
    }
    while (pq.empty() == false) {
        ppi curr = pq.top();
        pq.pop();
        int i = curr.second.first;
        int j = curr.second.second;
        output.push_back(curr.first);
        if (j + 1 < arr[i].size()){
            pq.push({ arr[i][j + 1], { i, j + 1 } });
        }
    }
    return output;
}

int main(){
    int num_buffer_pages;
    cin>>num_buffer_pages;

    int record_per_page;
    cin>>record_per_page;

    int total_records;
    cin>>total_records;

    int num_pages = int(ceil(double(total_records) / double(record_per_page)));
    int run_Size = num_buffer_pages * record_per_page;
    int num_runs = int(ceil(double(num_pages)/double(num_buffer_pages)));

    int num_records_in_last_run =total_records - run_Size * int( floor(double(total_records)/double(run_Size)) ) ;
    int temp2 = num_runs;
    int pass=0;

    vector <vector <int>> arr2;

    while(temp2 > 0){
        vector <int> temp3;
        int y;
        if(temp2==1){
            for(int i=0;i<num_records_in_last_run;i++){
                cin>>y;
                temp3.push_back(y);
            }
        }
        else{
            for(int i=0;i<run_Size;i++){
                cin>>y;
                temp3.push_back(y);
            }
        }
        temp2--;
        sort(temp3.begin(),temp3.end());
        arr2.push_back(temp3);
    }


    while(num_runs > 1){
        int g = int(ceil(double(num_runs) / double(num_buffer_pages-1)));
        pass++;
        int h =0;
        int f = int(ceil(double(num_runs) / double(num_buffer_pages)));
        vector <vector <int>> out_from_pass;
        for(int i=0;i<g;i++){
            vector <vector <int>> temp;
            if(h<num_buffer_pages-1){
                for(int v=0;v<num_buffer_pages-1 && h<arr2.size();h++,v++){
                    temp.push_back(arr2[h]);
                }
            }
            else{
                for(int v=0;v<f && h<arr2.size();h++,v++){
                    temp.push_back(arr2[h]);
                }
            }
            vector<int> output = mergeKArrays(temp);
            out_from_pass.push_back(output);
        }
        num_runs = int(ceil(double(num_runs) / double(num_buffer_pages-1)));
        arr2.clear();

        for(int i=0;i<out_from_pass.size();i++){
            arr2.push_back(out_from_pass[i]);
        }

    }

    for(int i=0;i<arr2[0].size();i++){
        cout<<arr2[0][i]<<" ";
    }

}
