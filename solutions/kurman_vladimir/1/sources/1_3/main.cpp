#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

struct Node
{
	Node(){}
	explicit Node(size_t i, size_t j, char t): posI(i), posJ(j), type(t){}
	size_t posI, posJ;
	char type;
	bool processed = false;
};

size_t n, m;
vector<vector<Node>> nodes;
int islandCount = 0;

vector<pair<size_t, size_t>> getNeighbours(size_t i, size_t j)
{
	vector<pair<size_t, size_t>> ans;
	if (i != 0)
		ans.emplace_back(i - 1, j);
	if (i != n - 1)
		ans.emplace_back(i + 1, j);
	if (j != 0)
		ans.emplace_back(i, j - 1);
	if (j != m - 1)
		ans.emplace_back(i, j + 1);
	return ans;
}

int main(int argc, char* argv[])
{
	ifstream fin(BINARY_DIR "/input.txt");
	ofstream fout(BINARY_DIR "/output.txt");
	if (!fin.is_open())
	{
		cout << "Something is wrong with in/out files\n";
		return 1;
	}
	size_t curStr = 0;
	while (!fin.eof())
	{
		string str;
		getline(fin, str);
		nodes.push_back(vector<Node>(str.length()));
		for (size_t i = 0; i < str.length(); ++i)
			nodes[curStr][i] = Node(curStr, i, str[i]);
		++curStr;
	}
	n = nodes.size();
	m = nodes[0].size();
	queue<Node> curIsland;
	for (size_t i = 0; i < n; ++i)
	{
		for (size_t j = 0; j < m; ++j)
		{
			Node & curNode = nodes[i][j];
			if (curNode.type == '~' || curNode.processed)
				continue;
			curNode.processed = true;
			curIsland.push(curNode);
			while (!curIsland.empty())
			{
				auto neighbours = getNeighbours(curIsland.front().posI, curIsland.front().posJ);
				curIsland.pop();
				for (auto neighbour : neighbours)
				{
					Node & curNeighbour = nodes[neighbour.first][neighbour.second];
					if (curNeighbour.type == '~' || curNeighbour.processed)
						continue;
					curIsland.push(curNeighbour);
					curNeighbour.processed = true;
				}
			}
			++islandCount;
		}
	}
	fout << islandCount;
	fin.close();
	fout.close();
	return 0;
}
