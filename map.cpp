#include <iostream>
#include <vector>
#include <queue>
#define MAX 100
using namespace std;
struct node
{
    int x, y; //坐标
    int dis;  //距离
} nd;
vector<struct node> vec_node;
queue<node> que;

int map[MAX][MAX], value[MAX][MAX];
int n, m, k, d;
long long num;
void BFS() //广度优先搜索
{
    int x, y, dis;
    while (!que.empty())
    {
        nd = que.front(); //取队列的第一个元素
        que.pop();        //出队列
        x = nd.x;
        y = nd.y;
        dis = nd.dis;
        if (value[x][y] > 0)
        {
            k--;
            num += dis * value[x][y];
        }
        if (k == 0) //客户找完了
        {
            return;
        }
        int dx[] = {0, 1, 0, -1};
        int dy[] = {-1, 0, 1, 0};
        for (int i = 0; i < 4; i++)
        {
            //cout << dx[i] << dy[i];
            // if (x > 1 && x < n && y > 1 && y < n && map[x + dx[i]][y + dy[i]] != 2 && map[x + dx[i]][y + dy[i]] != 1)
            // {
            //     nd.x = x + dx[i];
            //     nd.y = y + dy[i];
            //     nd.dis = dis + 1;
            //     que.push(nd);
            //     map[x + dx[i]][y + dy[i]] = 2;
            // }
            if (x > 1 && map[x - 1][y] != 2 && map[x - 1][y] != 1)
            {
                nd.x = x - 1;
                nd.y = y;
                nd.dis = dis + 1;
                que.push(nd);
                map[x - 1][y] = 2; //
            }
            if (x < n && map[x + 1][y] != 2 && map[x + 1][y] != 1)
            {
                nd.x = x + 1;
                nd.y = y;
                nd.dis = dis + 1;
                que.push(nd);
                map[x + 1][y] = 2;
            }
            if (y > 1 && map[x][y - 1] != 2 && map[x][y - 1] != 1)
            {
                nd.x = x;
                nd.y = y - 1;
                nd.dis = dis + 1;
                que.push(nd);
                map[x][y - 1] = 2; //
            }
            if (y < n && map[x][y + 1] != 2 && map[x][y + 1] != 1)
            {
                nd.x = x;
                nd.y = y + 1;
                nd.dis = dis + 1;
                que.push(nd);
                //		cout << "??"<<x<<" "<<y<<endl;
                map[x][y + 1] = 2; //
            }
        }
    }
}
int main()
{
    int x, y, c;
    cin >> n >> m >> k >> d;
    for (int i = 0; i < m; i++)
    {
        cin >> x >> y;
        map[x][y] = 1; // 表示该点为奶茶分店
        nd.x = x;
        nd.y = y;
        que.push(nd); //将分店加入队列
    }
    int k1 = k;
    for (int i = 0; i < k; i++)
    {
        cin >> x >> y >> c;
        if (value[x][y] > 0)
        {
            k1--;
        }
        value[x][y] += c;
    }
    k = k1;
    for (int i = 0; i < d; i++)
    {
        cin >> x >> y;
        map[x][y] = 2;
    }
    BFS();
    cout << num;
    return 0;
}