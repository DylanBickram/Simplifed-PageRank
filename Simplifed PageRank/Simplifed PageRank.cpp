#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <map>
#include <iterator>
#include <iomanip>
using namespace std;

struct Vertex
{
    double outDegree; 
    double rank;
    double sum;
    int ID;
    string URL;

    //=== Constructors ===//
    Vertex();

    Vertex(string name);

};

// Default Constructor
Vertex::Vertex()
{
    this->URL = "";
    outDegree = 0.0;
    rank = 0.0;
    sum = 0.0;
    ID = 0;
    
}

// Constructor 
Vertex::Vertex(string name)
{
    this->URL = name;
    outDegree = 0.0;
    rank = 0.0;
    sum = 0.0;
    ID = 0;
}

class AdjacencyList
{

private:

    unordered_map <string, pair<Vertex, vector<Vertex>>> adjList;
    int totalVertices; // Represents |V| of the graph

public:

    // Default Constructor
    AdjacencyList()
    {
        totalVertices = 0;
    }

    // Destructor 
    ~AdjacencyList() {}

    //=== Behaviors ==// 

    void InsertEdge(string from, string to);

    void pageRank(int p);

    void vertexRanker(Vertex vertex, vector<Vertex>& vertices, vector<double>& matrix);

    void printPageRank();

};

// Function sorts and prints the page ranks of the adjancency list
void AdjacencyList::printPageRank()
{
    // Convert unordered adjList to map data type in order to sort the adjancency list
    map<string, pair<Vertex, vector<Vertex>>> pageRanks(adjList.begin(), adjList.end());

    // Iterate through the sorted map and print out the string and the rank of the vertex
    for (auto iter2 = pageRanks.begin(); iter2 != pageRanks.end(); iter2++)
        cout << iter2->first << setprecision(2) << fixed << " " << iter2->second.first.rank << endl;
}

// Function inserts edge from one webpage to another 
void AdjacencyList::InsertEdge(string from, string to)
{

    // Create vertices for the from webpage to the to webpage
    Vertex start = Vertex(from);
    Vertex end = Vertex(to);

    // If 'from' vertex does not exist in the list, add one to the list
    if (adjList.find(from) == adjList.end())
    {
        adjList[from].first = start;
        adjList[from].first.ID = totalVertices; // Vertices directed to from is equal to the total vertices 
        totalVertices++; // Vertices in the graph increase by 1
    }

    // If the 'to' vertex does not exist, add one
    if (adjList.find(to) == adjList.end())
    {
        adjList[to].first = end;
        adjList[to].first.ID = totalVertices;
        totalVertices++;
    }

    // Push back 'to' vector of directed vertices
    adjList[from].second.push_back(end);

    adjList[from].first.outDegree += 1.0;
}

// Assigns the power iterated ranked values to the sum of a 
void AdjacencyList::vertexRanker(Vertex vertex, vector<Vertex>& vertices, vector<double>& matrix)
{
    // nodeValues in the matrix are 1 divided by a vertex's outDegree
    double nodeValue = 1.0 / vertex.outDegree;

    // Search for the name of URL of vertex i and assign its sum value it's converted pageRank
    for (auto& i : vertices)
        adjList.find(i.URL)->second.first.sum += nodeValue * matrix[vertex.ID];
    
}

void AdjacencyList::pageRank(int p)
{
    int pow_Iterations = p;
    vector<double> iter_Matrix;

    // Initialize iteration matrix
    for (auto& i : adjList)
    {
        iter_Matrix.push_back(1.0 / totalVertices);
        i.second.first.rank = 1.0 / totalVertices;
    }

    // Calculate page ranks
    for (int i = 1; i < pow_Iterations; i++)
    {
        
        for (auto& j : adjList)
            vertexRanker(j.second.first, j.second.second, iter_Matrix);
           
        // Update the rank values and the iteration matrix
        for (auto& j : adjList)
        {
            j.second.first.rank = j.second.first.sum;
            iter_Matrix[j.second.first.ID] = j.second.first.rank;
            j.second.first.sum = 0.0; // Reset sum value
        }

    }

    printPageRank();
}




int main()
{
    // Initialize adjacency list object
    AdjacencyList Graph;

    // Initialize user inputs
    int no_of_lines, power_iterations;
    string from, to;

    // Parse the number of lines and power iterations
    cin >> no_of_lines;
    cin >> power_iterations;

    // Iterate through the number of lines and parse from and to 
    for (int i = 0; i < no_of_lines; i++)
    {
        cin >> from;
        cin >> to;

        // Insert edges to the directed graph
        Graph.InsertEdge(from, to);
    }

    // Assign and print page ranks
    Graph.pageRank(power_iterations);
}



