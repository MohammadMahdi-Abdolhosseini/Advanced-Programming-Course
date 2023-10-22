#include <vector>
#include <string>
#include <iostream>
using namespace std;

vector<int> get_line()
{
	vector<int> v;
	int p, q, m, t;
	cin >> p;
	v.push_back(p);
	cin >> q;
	v.push_back(q);
	cin >> m;
	v.push_back(m);
	for(int i = 0; i < m; ++i)
	{
		cin >> t;
		v.push_back(t);
		cin >> t;
		v.push_back(t);
	}
	return v;
}

int main()
{

	int n;
	cin >> n;
	
	vector<vector<int>> v(n);

	for (int i = 0; i < n; i++)
		v[i] = get_line();

	vector<int> diff;

	for (int i = 0; i < n; i++)
	{
		int K = 0, J = 0;
		int sum = 0;
		for (int j = 0; j < v[i][2]; j += 1)
		{
			diff.push_back(0);
			diff[j] = v[i][2 + 2*j + 2] - v[i][2 + 2*j + 1];
			if(J < diff[j] - v[i][1])
				J = diff[j] - v[i][1];
			sum += diff[j];
		}
		if(v[i][0] < sum)
			K = sum - v[i][0];
		cout << K << " " << J << endl;
	}


	// how to print a 2d vector:
	/*
    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < v[i].size(); j++)
        {
            cout << v[i][j] << " ";
        }    
        cout << endl;
    }
	*/
	return 0;
}
