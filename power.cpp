#include <fstream>

int res[101] = {};

int main(int argc, char** argv)
{
	std::ifstream cin("power.in");
	std::ofstream cout("power.out");
	
	int n;
	cin >> n;
	if(n & 1)
	{
		cout << -1;
	}
	else
	{
		int cnt = 0;
		int p = 0;
		while(n != 0)
		{
			int num = n & 1;
			n >>= 1;
			if(num & 1)
			{
				cnt++;
				res[cnt] = num << p;
			}
			p++;
		}
		while(cnt != 0)
		{
			cout << res[cnt] << " ";
			cnt--;
		}
	}
	
	cin.close();
	cout.close();
	return 0;
}
