#include <string>
#include <sstream>
#include <regex>
#include <fstream>
#include <iostream>
#include <list>
#include <queue>
# define INF 0x3f3f3f3f

using namespace std;
typedef pair<int, int> coordinate;
//typedef pair<coordinate, int> triplet;
int numVertex;
int sourceIndex;
int destIndex;
pair<int, int> source;
pair<int, int> destination;

class myComparator
{
public:
    int operator() (const coordinate& p1, const coordinate& p2)
    {
        return p1.first > p2.first;
    }
};

template<class Container>
void split(const string &str, Container &cont) {
    istringstream iss(str);
    copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(cont));
}

void addEdge(vector<coordinate> &neighbors,vector<list<coordinate>> &adjList) {
    int sourceIndex = neighbors[0].first;
    int sourceHeight = neighbors[0].second;

    for (int i = 1; i < neighbors.size(); i++) {
        int neighborIndex = neighbors[i].first;
        int neighborHeight = neighbors[i].second;
        adjList[sourceIndex].push_back(make_pair(abs(sourceHeight - neighborHeight), neighborIndex));
    }
}

int prims(vector<list<coordinate>> &adjList) {
    priority_queue<coordinate, vector<coordinate>, myComparator> pq;
    vector<int> key(numVertex, INF);
    vector<int> parent(numVertex, -1);
    vector<bool> inMST(numVertex, false);

    pq.push(make_pair(0, sourceIndex));
    key[sourceIndex] = 0;
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        inMST[u] = true;
        list<pair<int, int >>::iterator i;

        for (i = adjList[u].begin(); i != adjList[u].end(); ++i) {
            int weight = (*i).first;
            int v = (*i).second;

            if (inMST[v] == false && key[v] > weight) {
                key[v] = weight;
                pq.push(make_pair(key[v], v));
                parent[v] = u;

            }
        }
    }
/*
    for (int i = 0; i < adjList.size(); i++) {
        cout << i << endl;
        list<pair<int, int >>::iterator a;
        for (a = adjList[i].begin(); a != adjList[i].end(); ++a) {
            cout << (*a).first << "-" << (*a).second << " ";
        }
        cout << "" << endl;
    }

*/
    int parentOf = parent[destIndex];
    int ladderHeight = key[destIndex];

    while (parentOf != sourceIndex) {
        destIndex = parentOf;
        parentOf = parent[destIndex];
        ladderHeight = max(ladderHeight, key[destIndex]);
    }

    return ladderHeight;
 //   return 0;
}

int main(int argc, char *argv[]) {

    ios_base::sync_with_stdio(false);
    ifstream infile(argv[1]);
    string line;
    getline(infile, line);
    vector<string> words;
    split(line, words);
    int numRows = stoi(words[0]);
    int numCols = stoi(words[1]);
    numVertex = numCols * numRows;
    int matrix[numRows][numCols];
    for (int i = 0; i < numRows; i++) {
        getline(infile, line);
        vector<string> words;
        split(line, words);
        for (int a = 0; a < numCols; a++) {
            matrix[i][a] = stoi(words[a]);
         //   cout << matrix[i][a] << " ";
        }
    }

    getline(infile, line);
    vector<string> word;
    split(line, word);
    int query = stoi(word[0]);
    getline(infile, line);
    vector<string> wordl;
    split(line, wordl);

    source = make_pair(stoi(wordl[0]) - 1, stoi(wordl[1]) - 1);
   // cout << source.first << " " << source.second << endl;
    sourceIndex = (source.first) * numCols + source.second;
 //   cout << sourceIndex << endl;

    destination = make_pair(stoi(wordl[2]) - 1, stoi(wordl[3]) - 1);
  //  cout << destination.first << " " << destination.second << endl;

    destIndex = (destination.first) * numCols + destination.second ;
  //  cout << destIndex << endl;
    vector<list<coordinate>> adjList;
    adjList.resize(numVertex);


    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            vector<coordinate> neighbors;
            pair<coordinate, int> source = make_pair(make_pair(i, j), matrix[i][j]);
            int index = (source.first.first) * numCols + source.first.second ;
            neighbors.push_back(make_pair(index, source.second));

            if (j != 0) {
                pair<coordinate, int> left = make_pair(make_pair(i, j - 1), matrix[i][j - 1]);
                index = (left.first.first) * numCols + left.first.second ;
                neighbors.push_back(make_pair(index, left.second));
            }

            if (i != 0) {
                pair<coordinate, int> up = make_pair(make_pair(i - 1, j), matrix[i - 1][j]);
                index = (up.first.first) * numCols + up.first.second ;
                neighbors.push_back(make_pair(index, up.second));
            }

            if (i != numRows - 1) {
                pair<coordinate, int> down = make_pair(make_pair(i + 1, j), matrix[i + 1][j]);
                index = (down.first.first) * numCols + down.first.second ;
                neighbors.push_back(make_pair(index, down.second));
            }
            if (j != numCols - 1) {
                pair<coordinate, int> right = make_pair(make_pair(i, j + 1), matrix[i][j + 1]);
                index = (right.first.first) * numCols + right.first.second ;
                neighbors.push_back(make_pair(index, right.second));
            }

            addEdge(neighbors,adjList);
        }
    }

    ofstream myfile;
    myfile.open(argv[2]);
    myfile <<prims(adjList)<< endl;

    myfile.close();

    return 5;


}
