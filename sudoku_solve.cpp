#include <iostream>

using namespace std;

const int maxn = 15, n = 9;
int a[maxn][maxn];
int cnt[4][maxn][maxn];
int needFindX[maxn * maxn], needFindY[maxn * maxn], numFind = 0;
bool isFound = false;

int getBlock(int x, int y)
{
    x = (x - 1) / 3;
    y = (y - 1) / 3;
    return (x - 1) * 3 + y;
}

void EnterInput()
{
    memset(cnt, 0, sizeof(cnt));

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
        {
            cin >> a[i][j];

            if (a[i][j] == 0)
            {
                numFind++;
                needFindX[numFind] = i;
                needFindY[numFind] = j;
                continue;
            }

            cnt[1][i][a[i][j]]++;
            cnt[2][j][a[i][j]]++;
            cnt[3][getBlock(i, j)][a[i][j]]++;
        }
}

bool CheckInput()
{
    for (int tp = 1; tp <= 3; tp++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (cnt[tp][i][j] > 1)
                    return false;

    return true;
}

void PrintResult()
{
    isFound = true;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
            cout << a[i][j] << " ";
        cout << endl;
    }
}

void FindValue(int num)
{
    if (isFound)
        return;

    if (num > numFind)
    {
        PrintResult();
        return;
    }

    for (int value = 1; value <= 9; value++)
    {
        int x = needFindX[num];
        int y = needFindY[num];

        a[x][y] = value;

        cnt[1][x][value]++;
        cnt[2][y][value]++;
        cnt[3][getBlock(x, y)][value]++;

        if (cnt[1][x][value] < 2 && cnt[2][y][value]<2 &&
            cnt[3][getBlock(x, y)][value]<2)
            FindValue(num + 1);

        cnt[1][x][value]--;
        cnt[2][y][value]--;
        cnt[3][getBlock(x, y)][value]--;

        a[x][y] = 0;
    }
}

int main()
{
    freopen("input.inp", "r", stdin);

    EnterInput();
    if (!CheckInput())
    {
        cout << -1 << endl;
        return 0;
    }
    FindValue(1);

    return 0;
}