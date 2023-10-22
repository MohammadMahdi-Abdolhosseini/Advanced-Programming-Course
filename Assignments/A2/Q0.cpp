#include <iostream>
#include <string>
using namespace std;

string to_upper(string line, int index = 0)
{
	if (index == line.size())
	{
		return line;
    }
    else
    {
        line[index] = toupper(line[index]);
        return to_upper(line, index+1);
    }
}

int main()
{
	string line;
	while (getline(cin, line))
	{
		cout << to_upper(line) << endl;
	}

	return 0;
}