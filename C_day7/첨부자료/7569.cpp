#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

struct XYZ
{
    int x;
    int y;
    int z;
    int day;
};

int map[110][110][110]; // k, j, i

queue<XYZ> q;


int main()
{
    int i, j ,k, n, m, h, x, y, z, day;

    scanf("%d %d %d", &n, &m, &h);

    for(i = 0; i < h; i++) {
        for(j = 0; j < m; j++) {
            for(k = 0; k < n; k++) {
                scanf("%d", &map[k][j][i]); //xyz
                if(map[k][j][i] == 1)
                    q.push({k, j, i, 0});
            }
        }
    }

    while(!q.empty()) {
        x = q.front().x;
        y = q.front().y;
        z = q.front().z;
        day = q.front().day;
        q.pop();

        if(map[x+1][y][z] == 0 && x+1 != n)
        {
            q.push({x+1, y, z, day + 1});
            map[x+1][y][z] = 1;
        }
        if(map[x-1][y][z] == 0 && x-1 != -1)
        {
            q.push({x-1, y, z, day + 1});
            map[x-1][y][z] = 1;
        }
        if(map[x][y+1][z] == 0 && y+1 != m)
        {
            q.push({x, y+1, z, day + 1});
            map[x][y+1][z] = 1;
        }
        if(map[x][y-1][z] == 0 && y-1 != -1)
        {
            q.push({x, y-1, z, day + 1});
            map[x][y-1][z] = 1;
        }
        if(map[x][y][z+1] == 0 && z+1 != h)
        {
            q.push({x, y, z+1, day + 1});
            map[x][y][z+1] = 1;
        }
        if(map[x][y][z-1] == 0 && z-1 != -1)
        {
            q.push({x, y, z-1, day + 1});
            map[x][y][z-1] = 1;
        }
    }

    for(i = 0; i < h; i++) {
        for(j = 0; j < m; j++) {
            for(k = 0; k < n; k++) {
                if(map[k][j][i] == 0)
                {
                    printf("%d", -1);
                    return 0;
                }
            }
        }
    }
    printf("%d", day);

    return 0;
}
