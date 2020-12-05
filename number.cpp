#include <fstream>
#include <algorithm>

typedef long long ll;

ll a[1005][1005] = {};
ll f[1005][1005] = {};

int main(int argc, char** argv)
{
    std::ifstream cin("number.in");
    std::ofstream cout("number.out");

    ll n, m;
    cin >> n >> m;
    for(ll i = 1; i <= n; i++)
    {
        for(ll j = 1; j <= m; j++)
        {
            cin >> a[i][j];
            f[i][j] = -1e12;
        }
    }
    ll res;
    f[1][1] = a[1][1];
    for(ll j = 1; j <= m; j++)
    {
        if(j != 1)
        {
            for(ll i = 1; i <= n; i++)
            {
                f[i][j] = f[i][j - 1] + a[i][j];
            }
        }
        res = f[1][j - 1] + a[1][j];
        for(ll i = 2; i <= n; i++)
        {
            f[i][j] = std::max(f[i][j], res + a[i][j]);
            if(j != 1)
            {
                res = std::max(f[i][j - 1], res) + a[i][j];
            }
            else
            {
                res = f[i][j];
            }
            
        }
        if(j != 1)
        {
            res = f[n][j - 1] + a[n][j];
            for(ll i = n - 1; i >= 1; i--)
            {
                f[i][j] = std::max(f[i][j], res + a[i][j]);
                res = std::max(f[i][j - 1], res) + a[i][j];
            }
        }
        
    }
    cout << f[n][m];

    cin.close();
    cout.close();
    return 0;
}