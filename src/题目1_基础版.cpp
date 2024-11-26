#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <string>

using namespace std;

// �ߵĽṹ��
struct Edge {
    int length;
    int point_1;
    int point_2;

    Edge(int len, int p1, int p2) : length(len), point_1(p1), point_2(p2) {}
};

// ���ڼ������г������е����·�����ȼ�·��
pair<int, string> calculateShortestPath(int start, vector<vector<int>>& distanceMatrix, vector<int>& cities) {
    int n = cities.size();
    sort(cities.begin(), cities.end());

    int shortestPathLength = numeric_limits<int>::max();
    string shortestPath;

    do {
        int currentPathLength = 0;
        int currentCity = start;
        string path = to_string(start);

        // �����������е��ܾ���
        for (int city : cities) {
            currentPathLength += distanceMatrix[currentCity][city];
            currentCity = city;
            path += "->" + to_string(city);
        }
        // �ص����
        currentPathLength += distanceMatrix[currentCity][start];
        path += "->" + to_string(start);

        // �������·�����Ⱥ�·��
        if (currentPathLength < shortestPathLength) {
            shortestPathLength = currentPathLength;
            shortestPath = path;
        }
    } while (next_permutation(cities.begin(), cities.end()));  // ������һ������

    return { shortestPathLength, shortestPath };
}

int main() {
    int n, e;
    cout << "������������ͱߵ�������";
    cin >> n >> e;
    

    vector<Edge> edges;
    vector<vector<int>> distanceMatrix(n + 1, vector<int>(n + 1, numeric_limits<int>::max()));

    if (n < 2)
    {
        cout << "������ĳ�����Ŀ�ǷǷ���";
    }
    else
    {
        for (int i = 0; i < e; ++i) {
            int length, p1, p2;
            cout << "����� " << i + 1 << " ���ߵĳ��Ⱥ����ӵ��������б�ţ�";
            cin >> length >> p1 >> p2;
            edges.emplace_back(length, p1, p2);
            distanceMatrix[p1][p2] = length;
            distanceMatrix[p2][p1] = length;
        }
        int start;
        cout << "������ʼ���б�ţ�";
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

        cout << "��Ҫ�����·���ǣ�" << shortestPathLength << endl;
        cout << "���·���ǣ�" << shortestPath << endl;
        system("pause");
        return 0;
    }
}