#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <numeric>  // ������ͷ�ļ���ʹ�� std::iota

class Edge {
public:
    int length;
    int point1;
    int point2;

    Edge(int len, int p1, int p2) : length(len), point1(p1), point2(p2) {}
};

// ���㻷��·������
int calculateCyclicPathLength(const std::vector<int>& path, const std::vector<std::vector<int>>& adjMatrix) {
    int totalLength = 0;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        totalLength += adjMatrix[path[i]][path[i + 1]];
    }
    // ���ϴ����һ�����з��ص����ľ���
    totalLength += adjMatrix[path.back()][path[0]];
    return totalLength;
}

// �Ŵ��㷨��⻷��TSP
void geneticAlgorithmCyclicTSP(int n, int k, std::vector<Edge>& edges) {
    int populationSize = 50;
    int generations = 1000;
    double mutationRate = 0.05;
    srand(time(nullptr));

    std::vector<std::vector<int>> adjMatrix(n + 1, std::vector<int>(n + 1, INT_MAX));
    for (auto& edge : edges) {
        adjMatrix[edge.point1][edge.point2] = edge.length;
        adjMatrix[edge.point2][edge.point1] = edge.length;
    }

    // ��ʼ����Ⱥ
    std::vector<std::vector<int>> population(populationSize);
    for (int i = 0; i < populationSize; ++i) {
        population[i] = std::vector<int>(n);
        std::iota(population[i].begin(), population[i].end(), 1);  // ��ȷ����1��n
        std::random_shuffle(population[i].begin(), population[i].end());
        // ȷ����ʼ������k
        if (population[i][0] != k) {
            std::swap(population[i][0], *std::find(population[i].begin(), population[i].end(), k));
        }
    }

    std::vector<int> bestPath;
    int bestLength = INT_MAX;

    // ��ʼ�Ŵ��㷨�ĵ���
    for (int gen = 0; gen < generations; ++gen) {
        // ������Ӧ��
        std::vector<std::pair<int, int>> fitness;
        for (int i = 0; i < populationSize; ++i) {
            int len = calculateCyclicPathLength(population[i], adjMatrix);
            fitness.emplace_back(len, i);
            if (len < bestLength) {
                bestLength = len;
                bestPath = population[i];
            }
        }
        std::sort(fitness.begin(), fitness.end());

        // ѡ��
        std::vector<std::vector<int>> newPopulation;
        for (int i = 0; i < populationSize / 2; ++i) {
            newPopulation.push_back(population[fitness[i].second]);
        }

        // ����ͱ���
        while (newPopulation.size() < populationSize) {
            int p1 = rand() % (populationSize / 2);
            int p2 = rand() % (populationSize / 2);
            std::vector<int> child = newPopulation[p1];

            // ���棺�򵥽���һ�λ���
            if (p1 != p2) {
                for (size_t j = 1; j < n / 2; ++j) {
                    std::swap(child[j], *std::find(child.begin(), child.end(), newPopulation[p2][j]));
                }
            }

            // ����
            if ((rand() % 100) < mutationRate * 100) {
                int idx1 = rand() % n;
                int idx2 = rand() % n;
                std::swap(child[idx1], child[idx2]);
            }

            newPopulation.push_back(child);
        }

        population = newPopulation;
    }

    std::cout << "Best cyclic travel length: " << bestLength << std::endl;
    std::cout << "Best cyclic path: ";
    for (int city : bestPath) {
        std::cout << city << "->";
    }
    std::cout << bestPath[0];
    std::cout << std::endl;
}

int main() {
    int n, k;
    std::cout << "Enter the number of cities: ";
    std::cin >> n;

    if (n < 2)
    {
        std::cout<< "wrong city numbers";
    }
    else
    {
        std::cout << "Enter the starting city: ";
        std::cin >> k;

        std::vector<Edge> edges;
        for (int i = 1; i <= n * (n - 1) / 2; i++) {
            int len, p1, p2;
            std::cout << "Enter length and endpoints of edge " << i << ": ";
            std::cin >> len >> p1 >> p2;
            edges.emplace_back(len, p1, p2);
        }

        geneticAlgorithmCyclicTSP(n, k, edges);
        system("pause");
        return 0;
    }
   
}
