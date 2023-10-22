#include <iostream>
#include <vector>
using namespace std;

int findMin (int a, int b)
{
    int min = a;
    if (a > b)
    {
        min = b;
    }
    return min;
}

int findMax (int a, int b)
{
    int max = a;
    if (a < b)
    {
        max = b;
    }
    return max;
}

int findMinOrMax (int a, int b, bool isMaxTurn)
{
    if (isMaxTurn)
    {
        return findMax(a, b);
    }
    else
    {
        return findMin(a, b);
    }
}

void recursiveMisaghiNavigation (vector<int> v, int n, int index = 0, int oldStep = 0, bool isMaxTurn = true)
{
    cout << v[index];

    int newStep = findMinOrMax(v[index], v[index-oldStep], isMaxTurn);    
    isMaxTurn = !isMaxTurn;

    bool reachedTheEnd = (index+newStep >= n);
    bool isSameIndexAgain = (newStep == 0 & oldStep == 0);
    if (reachedTheEnd | isSameIndexAgain)
    {
        cout << endl;
        return;
    }
    else
    {
        cout << ' ';
        recursiveMisaghiNavigation(v, n, index+newStep, newStep, isMaxTurn);
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> v[i];
    }
    recursiveMisaghiNavigation(v, n);
    
    return 0;
}
