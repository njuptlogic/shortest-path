#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <string>

using namespace std;

// 边的结构体
struct Edge {
    int length;
    int point_1;
    int point_2;

    Edge(int len, int p1, int p2) : length(len), point_1(p1), point_2(p2) {}
};

// 用于计算所有城市旅行的最短路径长度及路径
pair<int, string> calculateShortestPath(int start, vector<vector<int>>& distanceMatrix, vector<int>& cities) {
    int n = cities.size();
    sort(cities.begin(), cities.end());

    int shortestPathLength = numeric_limits<int>::max();
    string shortestPath;

    do {
        int currentPathLength = 0;
        int currentCity = start;
        string path = to_string(start);

        // 计算这种排列的总距离
        for (int city : cities) {
            currentPathLength += distanceMatrix[currentCity][city];
            currentCity = city;
            path += "->" + to_string(city);
        }
        // 回到起点
        currentPathLength += distanceMatrix[currentCity][start];
        path += "->" + to_string(start);

        // 更新最短路径长度和路径
        if (currentPathLength < shortestPathLength) {
            shortestPathLength = currentPathLength;
            shortestPath = path;
        }
    } while (next_permutation(cities.begin(), cities.end()));  // 生成下一个排列

    return { shortestPathLength, shortestPath };
}

int main() {
    int n, e;
    cout << "输入城市数量和边的数量：";
    cin >> n >> e;
    

    vector<Edge> edges;
    vector<vector<int>> distanceMatrix(n + 1, vector<int>(n + 1, numeric_limits<int>::max()));

    if (n < 2)
    {
        cout << "您输入的城市数目是非法的";
    }
    else
    {
        for (int i = 0; i < e; ++i) {
            int length, p1, p2;
            cout << "输入第 " << i + 1 << " 条边的长度和连接的两个城市编号：";
            cin >> length >> p1 >> p2;
            edges.emplace_back(length, p1, p2);
            distanceMatrix[p1][p2] = length;
            distanceMatrix[p2][p1] = length;
        }
        int start;
        cout << "输入起始城市编号：";
        cin >> start;

        vector<int> cities;
        for (int i = 1; i <= n; ++i) {
            if (i != start) {
                cities.push_back(i);
            }
        }

        pair<int, string> result = calculateShortestPath(start, distanceMatrix, cities);
        int shortestPathLength = result.first;
        string shortestPath = result.second;

        cout << "需要的最短路程是：" << shortestPathLength << endl;
        cout << "最短路径是：" << shortestPath << endl;
        system("pause");
        return 0;
    }
}