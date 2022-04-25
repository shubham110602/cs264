#include <bits/stdc++.h>
using namespace std;

int main()
{
    int buff, numr, tot;
    cin >> buff >> numr >> tot;

    vector<vector<int>> ve;

    vector<int> tdata;

    for (int i = 0; i < tot; i++)
    {
        int x;
        cin >> x;

        tdata.push_back(x);
    }

    for (int i = 0; i < tot; i = i + numr)
    {
        vector<int> te;

        for (int j = i; j < min(tot, i + numr); j++)
            te.push_back(tdata[j]);

        ve.push_back(te);
    }

    int x = ve.size();

    vector<vector<int>> q;
    for (int i = 0; i < x; i = i + buff)
    {
        vector<int> qq;

        for (int j = i; j < min(i + buff, x); j++)
        {
            for (int k = 0; k < ve[j].size(); k++)
            {
                qq.push_back(ve[j][k]);
            }
        }

        sort(qq.begin(), qq.end());
        q.push_back(qq);
    }

    ve = q;

    while (ve.size() > 1)
    {
        q.clear();
        int y=ve.size();

        for (int i = 0; i < y; i = i + buff-1)
        {
            vector<int> qq;

            for (int j = i; j < min(i + buff-1, y); j++)
            {
                for (int k = 0; k < ve[j].size(); k++)
                {
                    qq.push_back(ve[j][k]);
                }
            }

            sort(qq.begin(), qq.end());
            q.push_back(qq);
        }

        ve = q;
    }
    cout << "asddf\n";
    for(int i=0;i<ve[0].size();i++){

        cout << ve[0][i] << " ";
    }

}
