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
	// input: "n"
	// input in "n" line(s): 
	// vector[[],[],...,[]] => ["n" vectors in one]
	
	int n;
	cin >> n;
	
	vector<vector<int>> v(n);

	for (int i = 0; i < n; i++)
		v[i] = get_line();

	// print 0:
	// if v[i][0] < v[i][4] - v[i][3] +
	//				v[i][6] - v[i][5] + ...
	//	==>	if v[i][0] < sum
	// if v[i][1] < v[i][4] - v[i][3] or < v[i][6] - v[i][5] or ...
	// if v[i][1] < temp[j]

	vector<int> out(n, 1);
	vector<int> diff;

	for (int i = 0; i < n; i++)
	{
		int sum = 0;
		for (int j = 0; j < v[i][2]; j += 1)
		{
			diff.push_back(0);
			diff[j] = v[i][2 + 2*j + 2] - v[i][2 + 2*j + 1];
			if(v[i][1] < diff[j])
				out[i] = 0;
			sum += diff[j];
		}
		if(v[i][0] < sum)
			out[i] = 0;
	}

	for (auto x : out)
		cout << x;
	cout << endl;

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
