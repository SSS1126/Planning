#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

/*
    实现逻辑：
    ->  vector track 存储搜索的最短路径,最后遍历即可
    ->  HashMap存储从源节点到当前节点的权重和，以及来判断是否已经遍历
        ->  key值为节点，value为当前节点到各个节点的权重
    ->  graph的行数表示节点个数，每一行表示当前节点到其余节点的距离；
*/

class dijkstra {
    public:
        unordered_map <int, vector<int>> weight;
        vector<int> track;
        int curNode;
        // trackWeight表示路径权重和,起点为0
        int trackWeight = 0;

        vector<int> source (int graph[5][5], int firstNode, int endNode) {
            track.push_back(firstNode);
            // 将起点存入weight
            weight[firstNode];
            // graph的列数
            int col = 5;
            int row = firstNode;
            curNode = firstNode;
            while(curNode != endNode) {  // 当weight的最后一个元素为终点时，循环停止，表示找到最短路径
                int oldWeight = 100000;
                int Node;
                for (int j = 0; j < col; j++) {
                    // 如果权重等于0，将其设置为无限大
                    if (graph[row][j] == 0) {
                        weight[curNode].push_back(100000);
                        continue;
                    } else if (graph[row][j] == 100000) {
                        weight[curNode].push_back(100000);
                        continue;
                    }

                    weight[curNode].push_back(trackWeight + graph[row][j]);
                    if (trackWeight + graph[row][j] < oldWeight && weight.find(j) == weight.end()) {
                        oldWeight = trackWeight + graph[row][j];
                        Node = j;
                    }
                }

                for (auto w = weight.begin(); w != weight.end(); ++w) {
                    vector<int>& pace = w->second;
                    // 将从当前节点取得的最小路径与之前节点的路径权重进行比较
                    for (auto p = 0; p < pace.size(); p++) {
                        if (pace[p] < oldWeight && weight.find(p) == weight.end()) {
                            oldWeight = pace[p];
                            auto it = find(pace.begin(), pace.end(), oldWeight);
                            Node = distance(pace.begin(), it);
                            curNode = w->first;
                        }
                    }
                }
                weight[curNode][Node] = 100000;
                curNode = Node;
                trackWeight = oldWeight;
                row = Node;
                track.push_back(Node);
            }
            return track;
        }
};
