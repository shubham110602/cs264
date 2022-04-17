#include <bits/stdc++.h>

using namespace std;

int page_size;

class page
{
public:
    int size;
    int count;
    vector <int> key;
    page* next;
    page* prev;
    int space;
    int capacity;
    page();

};

page::page(){
    count = 0;
    next = nullptr;
    prev = nullptr;
    size = page_size;
    capacity = page_size - 16;
}


class heap_file
{
public:
    heap_file();
    int num_page;
    page* head;
    void insert(int x, int y);
    void search(int x);
    void status();
};

heap_file::heap_file(){
    head = new page;
    num_page = 0;
}

void heap_file::insert(int x, int y)
{
    page* start = head;
    if(start->count == 0){
        start->capacity = start->capacity - (x + 4);
        start->count++;
        start->key.push_back(y);
        num_page++;

    }
    else
    {
        while(start->capacity < x + 4){
            if(start != nullptr){
                num_page++;
                page* newpage = new page;
                start->next = newpage;
                newpage->prev = start;
            }
            start = start->next;
        }

        start->capacity = start->capacity - (x + 4);
        start->count++;
        start->key.push_back(y);
    }
}

void heap_file::status(){
    cout << num_page << "  ";
    page *itr  = head;
    while(itr!= nullptr){
        cout << itr->count << "  ";
        itr = itr->next;
    }
    cout << "\n";
}

void heap_file::search(int x){
    page* itr = head;
    int p_id = 0;
    int found = 0;
    while(itr != nullptr){
        for(int i = 0; i < itr->key.size(); i++){
            if(itr->key[i] == x){
                cout << p_id << " " << i << endl;
                found = 1;
                break;
            }
        }
        if(found == 1) break;

        p_id++;
        itr = itr->next;
    }
    if(found != 1){
         cout << "-1 -1" << endl;
    }

}

int main()
{

    cin >> page_size;
    heap_file node;
    while(1)
    {
        int n;
        cin >> n;

        if(n == 4){
            break;
        }

        else if(n == 1){
            int x, y;
            cin >> x >> y;
            node.insert(x,y);
        }
        else if(n == 2){
            node.status();
        }

        else if(n == 3){
            int x;
            cin >> x;
            node.search(x);
        }
    }
}
