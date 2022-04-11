#include <bits/stdc++.h>
using namespace std;

class node
{
    friend class bptree;
public:

    bool is_leaf;
    int *key;
    int size;
    node* parent;
    node** ptr;
    node(int a);

};

node::node(int a)
{
    key = new int[a+1];
    ptr = new node*[a+2];
    size = 0;
    is_leaf = false;
    parent = nullptr;
    for(int i = 0; i < a+2;i++){
        ptr[i] = nullptr;
    }
}

class bptree
{
    int d, t, d_out, t_out;

    public:
        bptree(int a, int b);
        void insert(int);
        void display();
        node* root;
        void split(node*);
        bool overflow(node*);
        node* fParent(node*);

};


bptree::bptree(int a, int b)
{
    d = a;
    t = b;
    d_out = 0;
    t_out = 0;
    root = nullptr;
}


bool bptree::overflow(node* cursor)
{
    if(cursor->is_leaf == true)
    {
        if(cursor->size < 2*d+1)
        return 0;
        else
            return 1;
    }
    else
    {
        if(cursor->size < 2*t+2)
        {
            return 0;
        }
        else
            return 1;
    }

}



void bptree::split(node* cursor)
{

    if(cursor->is_leaf == true)
    {
        //cout<<"0000";
        node* newleaf = new node(2*d);
        newleaf->is_leaf = true;
        d_out++;

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
            t_out = 1;
            root->key[root->size] = up;
            root->size++;
            root->ptr[0] = cursor;
            root->ptr[1] = newleaf;
            //cout<<"000000000";
            cursor->parent = root;
            newleaf->parent = root;
            return;
        }

        node* prnt = fParent(cursor);

        int pos = 0;
        //cout << prnt->size;
        for(pos = 0; pos < prnt->size; pos++)
        {
            if(up < prnt->key[pos]) break;
        }

        for(int j=prnt->size;j>pos+1;j--)
        {
            prnt->key[j] = prnt->key[j-1];
        }
        prnt->key[pos] = up;
        prnt->size++;

        for(int j=prnt->size;j>pos+1;j--)
        {
            prnt->key[j] = prnt->key[j-1];
        }
        prnt->ptr[pos+1]=newleaf;

        split(prnt);
    }
    else
    {
        if(cursor == root)
        {
            node* newleaf = new node(2*t+1);

            t_out++;
            int up = cursor->key[t];
            for(int i = t+1; i < cursor->size; i++)
            {
                newleaf->key[newleaf->size] = cursor->key[i];
                newleaf->size++;
            }

            cursor->size = t;
            int b = 0;

            for(int j=t+1;j<=2*t+2;j++)
            {
                newleaf->ptr[b]=cursor->ptr[j];
                cursor->ptr[j]->parent = newleaf;
                b++;
            }

            root = new node(2*t+1);
            t_out++;

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

            t_out++;

            int up = cursor->key[t];
            for(int i=t+1;i<cursor->size;i++)
            {
                newleaf->key[newleaf->size++] = cursor->key[i];
            }

            cursor->size=t;

            int b=0;
            for(int j=t+1;j<=2*t+2;j++)
            {
                newleaf->ptr[b]=cursor->ptr[j];
                cursor->ptr[j]->parent = newleaf;
                b++;
            }

            node *prnt = fParent(cursor);

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

node* bptree::fParent(node* cursor)
{
    return cursor->parent;
}

void bptree::insert(int x)
{
    if(root == nullptr)
    {
        root = new node(2*d);
        root->key[0] = x;
        root->size = 1;
        root->is_leaf = true;
        d_out++;
        return;
    }

    node* cursor = root;

    while(1)
    {
        int pos;
        //cout << cursor->size;
        for(pos = 0; pos < cursor->size; pos++)
        {
            if(x < cursor->key[pos]) break;
        }
        //cout << pos;
        //return;
        if(cursor->is_leaf == false)
        {
            cursor = cursor->ptr[pos];
        }
        else
        {
            for(int j = cursor->size; j > pos; j--)
            {
                cursor->key[j] = cursor->key[j-1];
            }
            cursor->key[pos] = x;
            cursor->size++;
            if(overflow(cursor))
                split(cursor);

        else
            return;
        }
        return;


    }
}




void bptree :: display()
{
    node *cursor = root;

    cout << t_out << " " << d_out << "  ";
    for(int i = 0; i < cursor->size; i++)
    {
        cout << cursor->key[i] << " ";
    }
    cout << endl;
}

int main()
{
    int a, b;
    cin >> a >> b;

    bptree Node(a,b);

    while(1)
    {
        int in;
        cin >> in;

        if(in == 3)
        {
            break;
        }
        else if(in == 1)
        {
            int val;
            cin >> val;
            Node.insert(val);
        }
        else if(in == 2)
        {
            Node.display();
        }
    }
}
