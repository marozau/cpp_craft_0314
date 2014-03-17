#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <vector>

using namespace std;

int main()
{
	ifstream filein;
	filein.open(BINARY_DIR "/input.txt");
	if (filein.is_open()){
		pair<int, int> datapoint;
		set<pair<int, int>> coordinates;
		string line;
		int row = 0;
		int column;
		int strLength;
		while (getline(filein, line)){
			row++;
			strLength = line.length();
			for (column = 1; column <= strLength; ++column){
				if (line[column - 1] == 'o'){
					datapoint = make_pair(row, column);
					coordinates.insert(datapoint);
				}
				else if (line[column - 1] == '~'){ 
					continue;
				}
				else { cout << "Error! Unknown symbol in input.txt!" << endl; }
			}
		}
		filein.close();

		pair<int, int> currentPoint;
		vector<pair<int, int>> neighbours(4);
		vector<vector<pair<int, int>>> islands;
		while (!coordinates.empty()){
			vector<pair<int, int>> connectedComponent;
			set<pair<int, int>>::iterator iter = coordinates.begin();
			datapoint = *iter;
			connectedComponent.push_back(datapoint);
			coordinates.erase(iter);
			for (size_t i = 0; i < connectedComponent.size(); ++i){
				currentPoint = connectedComponent[i];
				neighbours.clear();
				neighbours.push_back(make_pair(connectedComponent[i].first - 1, connectedComponent[i].second));
				neighbours.push_back(make_pair(connectedComponent[i].first + 1, connectedComponent[i].second));
				neighbours.push_back(make_pair(connectedComponent[i].first, connectedComponent[i].second - 1));
				neighbours.push_back(make_pair(connectedComponent[i].first, connectedComponent[i].second + 1));
				for (vector<pair<int, int>>::iterator iter = neighbours.begin(); iter != neighbours.end(); ++iter){
					if (coordinates.count(*iter)){
						connectedComponent.push_back(*iter);				
						coordinates.erase(*iter);
					}
				}
			}
			islands.push_back(connectedComponent);
		}

		ofstream fileout;
		fileout.open(BINARY_DIR "/output.txt");
		fileout << islands.size() << endl;
		fileout.close();
	}
	else {
		cout << "Unable to open file input.txt!" << endl;
		return 1;
	}

	return 0;
}
