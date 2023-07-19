#include<vector>
#include <iostream>
#include<string>
using namespace std;
class WeightedQuickUnionUF
{
private:
    vector<int> parent;
    vector<int> size;
    int count;

public:
    WeightedQuickUnionUF(int n) : count(n)
    {
        parent.resize(n);
        size.resize(n);

        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int getCount()
    {
        return count;
    }

    int find(int p)
    {
        validate(p);

        while (p != parent[p])
        {
            parent[p] = parent[parent[p]]; // Path compression
            p = parent[p];
        }
        return p;
    }

    bool connected(int p, int q)
    {
        return find(p) == find(q);
    }

    void unionOp(int p, int q)
    {
        int rootP = find(p);
        int rootQ = find(q);

        if (rootP == rootQ)
            return;

        if (size[rootP] < size[rootQ])
        {
            parent[rootP] = rootQ;
            size[rootQ] += size[rootP];
        }
        else
        {
            parent[rootQ] = rootP;
            size[rootP] += size[rootQ];
        }

        count--;
    }

    void validate(int p)
    {
        int n = parent.size();
        if (p < 0 || p >= n)
        {
            throw out_of_range("Index " + to_string(p) + " is out of range!");
        }
    }
};