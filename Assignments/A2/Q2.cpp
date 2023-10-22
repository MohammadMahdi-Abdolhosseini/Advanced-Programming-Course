#include <iostream>
#include <vector>
using namespace std;

const int WALKABLE = 1;
const int OBSTACLE = 0;

bool isSafe(vector<vector<int>> matrix, int n, int x, int y)
{
    if (x >= 0 && x < n && y >= 0 && y < n)
    {
        return (matrix[x][y] == WALKABLE);
    }
    else
    {
        return false;
    }
}

int countPaths(vector<vector<int>> matrix, int n, int x = 0, int y = 0)
{
    if (x == n-1 & y == n-1)
    {
        // Base case: reached the bottom-right corner
        return 1;
    }

    int paths = 0;

    if (isSafe(matrix, n, x, y))
    {
        // Recursive case: move right and down
        paths += countPaths(matrix, n, x+1, y);
        paths += countPaths(matrix, n, x, y+1);
    }

    return paths;
}

vector<vector<int>> makeMatrix(int n)
{
    vector<vector<int>> matrix(n, vector<int>(n, WALKABLE));

    // Set the elements above the main diagonal to OBSTACLE
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            matrix[i][j] = OBSTACLE;
        }
    }

    return matrix;
}

int main()
{
    int n;
    cin >> n;
    n += 1;
    vector<vector<int>> matrix = makeMatrix(n);
    cout << countPaths(matrix, n) << endl;
    return 0;
}
