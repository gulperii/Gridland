#include <string>
#include <sstream>
#include <regex>
#include <fstream>
#include <iostream>
#include <list>
#include <queue>

using namespace std;
typedef pair<int, int> coordinate;
typedef pair<coordinate, int> triplet;
vector<list<coordinate>> adjList;
int numVertex;
int sourceIndex;
int destIndex;
pair<int, int> source;
pair<int, int> destination;
# define INF 0x3f3f3f3f

template<class Container>
void split(const string &str, Container &cont) {
    istringstream iss(str);
    copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(cont));
}

void addEdge(vector<coordinate> &neighbors) {
    int sourceIndex = neighbors[0].first;
    int sourceHeight = neighbors[0].second;

    for (int i = 1; i < neighbors.size(); i++) {
        int neighborIndex = neighbors[i].first;
        int neighborHeight = neighbors[i].second;
        adjList[sourceIndex].push_back(make_pair(abs(sourceHeight - neighborHeight), neighborIndex));
    }


}

int prims() {
    priority_queue<coordinate, vector<coordinate>, greater<coordinate>> pq;
    int src = 1;
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
            int v = (*i).first;
            int weight = (*i).second;

            if (inMST[v] == false && key[v] > weight) {
                key[v] = weight;
                pq.push(make_pair(key[v], v));
                parent[v] = u;

            }
        }
    }

    int parentOfDest=parent[destIndex];
    int ladderHeight=key[destIndex];

    while(parentOfDest!=sourceIndex){
        ladderHeight=max(ladderHeight,parentOfDest);
        parentOfDest=parent[parentOfDest];
    }
    return ladderHeight;
}

int main(int argc, char *argv[]) {

    ios_base::sync_with_stdio(false);
    ifstream infile(argv[1]);
    string line;
    //  vector<string> firstLine;
    getline(infile, line);
    vector<string> words;
    split(line, words);
    int numRows = stoi(words[0]);
    int numCols = stoi(words[1]);
    numVertex = numCols * numRows;
    int matrix[numRows + 2][numCols + 2];

    for (int i = 0; i < numRows; i++) {
        getline(infile, line);
        vector<string> words;
        split(line, words);
        for (int a = 0; a < numCols; a++) {
            matrix[i + 1][a + 1] = stoi(words[a]);
        }
    }

    getline(infile, line);
    vector<string> word;
    split(line, word);
    int query = stoi(word[0]);
    getline(infile, line);
    vector<string> wordl;
    split(line, wordl);

    source = make_pair(stoi(wordl[0]), stoi(wordl[1]));
    sourceIndex = (source.first - 1) * numCols + source.second;
    destination = make_pair(stoi(wordl[2]), stoi(wordl[3]));
    destIndex = (destination.first - 1) * numCols + destination.second;


    //  (y-1).n + x

    for (int i = 1; i < numRows; i++) {
        for (int j = 1; j < numCols; j++) {
            vector<coordinate> neighbors;
            pair<coordinate, int> source = make_pair(make_pair(i, j), matrix[i][j]);
            int index = (source.first.first - 1) * numCols + source.first.second;
            neighbors.push_back(make_pair(index, source.second));
            if (j - 1 != 0) {
                pair<coordinate, int> left = make_pair(make_pair(i - 1, j), matrix[i][j - 1]);
                index = (left.first.first - 1) * numCols + left.first.second;
                neighbors.push_back(make_pair(index, left.second));
            }


            if (i - 1 != 0) {
                pair<coordinate, int> up = make_pair(make_pair(i, j - 1), matrix[i - 1][j]);
                index = (up.first.first - 1) * numCols + up.first.second;
                neighbors.push_back(make_pair(index, up.second));
            }

            if (i + 1 != numRows + 1) {
                pair<coordinate, int> down = make_pair(make_pair(i, j + 1), matrix[i + 1][j]);
                index = (down.first.first - 1) * numCols + down.first.second;
                neighbors.push_back(make_pair(index, down.second));
            }
            if (j + 1 != numCols + 1) {
                pair<coordinate, int> right = make_pair(make_pair(i + 1, j), matrix[i][j + 1]);
                index = (right.first.first - 1) * numCols + right.first.second;
                neighbors.push_back(make_pair(index, right.second));
            }
            addEdge(neighbors);
        }
    }

    ofstream myfile;
    myfile.open(argv[2]);


}
