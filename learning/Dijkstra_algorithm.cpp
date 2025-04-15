#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 2022;

int edges[MAXN][MAXN];
int d[MAXN];

bool visited[MAXN];

int gcd(int u, int v)
{
    int temp = u % v;
    while (temp > 0)
    {
        u = v;
        v = temp;
        temp = u % v;
    }
    return v;
}
int lcm(int u, int v)
{
    return (u * v / gcd(u, v));
}

int main()
{
    memset(edges, 0x3f3f3f, sizeof(edges));
    for (int i = 1; i <= 2021; i++)
    {
        edges[i][i] = 0;
        for (int j = i + 1; j <= 2021; j++)
        {
            if (j - i <= 21)
            {
                edges[i][j] = edges[j][i] = lcm(j, i);
            }
            else
            {
                break;
            }
        }
    }
    memset(d, 0x3f3f3f, sizeof(d));
    memset(visited, false, sizeof(visited));
    d[1] = 0;
    for (int i = 1; i < 2021; i++)
    {
        int x = 0;
        for (int j = 1; j < 2021; j++)
        {
            if (!visited[j] && d[j] < d[x])
            {
                x = j;
            }
        }
        visited[x] = 1;
        for (int j = max(1, x - 21); j <= min(2021, x + 21); j++)
        {
            d[j] = min(d[j], d[x] + edges[x][j]);
        }
    }
    printf("%d\n", d[2021]);
    return 0;
}