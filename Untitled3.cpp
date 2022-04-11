#include <climits>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

int a, b, d_out, t_out;
int m;

class node{

    friend class bptree;

public:
    bool is_leaf;
    int *key, size;
    node*parent;
    node** ptr;
    node(int);
};

class bptree{


    node* root;

    node* fParent(node*,node*);
public:
    bptree(int, int);
    int d, t;
    int out_d, out_t;
    node* getroot();
    void insert(int);
    void display();
    void split(node*);

};

node::node(int m){
    key = new int[m + 1];
    ptr = new node*[m + 2];
}

bptree::bptree(int a, int b){
    root = nullptr;
    d = a;
    t = b;
    out_d = 0;
    out_t = 0;
}

void bptree::insert(int x)
{
    if(root == nullptr)
    {
        root = new node(2*d);
        //cout << d << t << endl;
        root->key[0] = x;
        root->is_leaf = true;
        root->size = 1;
    }

    node* cursor = root;

    cout << cursor->size <<endl;



    while(1)
    {
        int pos;
        for(pos = 0; pos < cursor->size; pos++)
        {
            if(x < cursor->key[pos]) break;

        }
        cout << pos;
            if(cursor->is_leaf == false)
            {
                cursor = cursor->ptr[pos];
            }
            else
            {
                for(int i = cursor->size; i < pos; i--)
                {
                    cursor->key[i] = cursor->key[i-1];
                }
                cursor->key[pos] = x;
                cursor->size++;
                if(cursor->is_leaf == false)
                {
                if(cursor->size < 2*d+1)
                {
                    return;
                }
                }
                else
                {
                if(cursor->size < 2*t+2)
                {
                    return;
                }
                }

                split(cursor);
                }



    }
}

void bptree::split(node* cursor)
{
    if(cursor->is_leaf == false)
    {
        node* newleaf = new node(2*d);
        newleaf->is_leaf = true;
        out_d++;

        for(int i = d; i < cursor->size; i++)
        {
            newleaf->key[newleaf->size] = cursor->key[i];
            newleaf->size++;
        }

        cursor->size = d;
        int up = newleaf->key[0];

        if(cursor == root)
        {
            root = new node(2*t+1);
            out_t = 1;
            root->key[root->size] = up;
            root->size++;
            root->ptr[0] = cursor;
            root->ptr[1] = newleaf;
            cursor->parent = root;
            newleaf->parent = root;
        }

        node* prnt = cursor->parent;
        int pos;
        for(int pos = 0; pos < prnt->size; pos++)
        {
            if(up < prnt->key[pos]){
                break;
            }
        }
        for(int j=prnt->size;j>pos+1;j--)
        {
            prnt->ptr[j] = prnt->ptr[j-1];
        }

        prnt->ptr[pos+1]=newleaf;

        split(prnt);
    }

    else
    {
        if(cursor == root)
        {
            node* newleaf = new node(2*t+1);

            out_t++;
            int up = cursor->key[t];
            for(int i = t+1; i < cursor->size; i++)
            {
                newleaf->key[newleaf->size] = cursor->key[i];
                newleaf->size++;
            }

            cursor->size = t;
            int k = 0;

            for(int j=t+1;j<=2*t+2;j++)
            {
                newleaf->ptr[k]=cursor->ptr[j];
                cursor->ptr[j]->parent = newleaf;
                k++;
            }

            root = new node(2*t+1);
            out_t++;

            root->key[root->size++]=up;
            root->ptr[0]=cursor;
            root->ptr[1]=newleaf;
            cursor->parent = root;
            newleaf->parent = root;

            return;
        }

        else
        {

            node *newleaf = new node(2*t+1);

            out_t++;

            int up = cursor->key[t];
            for(int i=t+1;i<cursor->size;i++)
            {
                newleaf->key[newleaf->size++] = cursor->key[i];
            }

            cursor->size=t;

            int k=0;
            for(int j=t+1;j<=2*t+2;j++)
            {
                newleaf->ptr[k]=cursor->ptr[j];
                cursor->ptr[j]->parent = newleaf;
                k++;
            }

            node *prnt = cursor->parent;

            int pos;
            for(pos=0;pos<prnt->size;pos++){
                if(up < prnt->key[pos])
                    break;
            }

            for(int j=prnt->size;j>pos;j--)
                    prnt->key[j]=prnt->key[j-1];

            prnt->key[pos] = up;

            prnt->size++;

            for(int j=prnt->size;j>pos+1;j--)
            {
                prnt->key[j] = prnt->key[j-1];
            }

            prnt->ptr[pos + 1]=newleaf;


            split(prnt);

        }
    }
}

node* bptree::fParent(node* cursor, node* child)
{
    node* par;

    if(cursor->is_leaf || (cursor->ptr[0])->is_leaf) return nullptr;

    for(int i = 0; i < cursor->size + 1; i++)
    {
        if(cursor->ptr[i] == child)
        {
            par = cursor;
            return par;
        }
        else
        {
            par = fParent(cursor->ptr[0],child);
            return par;
        }
    }
}


void bptree :: display()
{
    node *cursor = root;

    cout << out_t << " " << out_d << "  ";
    for(int i = 0; i < cursor->size; i++)
    {
        cout << cursor->key[i] << " ";
    }
    cout << endl;
}
int main()
{
    cin >> a >> b;
    bptree Node(a,b);
    int in, val;
    while(1)
    {
        cin >> in;

        if(in == 3)
        {
            break;
        }
        else if(in == 1)
        {
            cin >> val;

            Node.insert(val);
        }

        else if(in == 2)
        {

            Node.display();
        }
    }
}
