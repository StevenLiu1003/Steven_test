#include <iostream>
#include <fstream>

using namespace std;

//Designated file path
#define FILEPATH "C:\\Users\\Wei Chih Liu\\Documents\\Visual Studio 2015\\Projects\\Dijkstra_Algorithm\\Dijkstra_Algorithm_2.txt"
#define MAX 20

class Edge{
private:
	//Assign Dijkstra class as Edge's friend class
	friend class Dijkstra;
	int vertex_1, vertex_2;
	float weight;
public:
	Edge(int v1, int v2, int w) : vertex_1(v1), vertex_2(v2), weight(w) {}
};

class Dijkstra{
private:
	int nodeNumber;
	int count;
	int initialNode;
	int endNode;
	int *V_array_ptr;
	float *cost_array_ptr;
	int *path_array_ptr;
	Edge* E[MAX];
public:
	Dijkstra();//Default constructor
	void Read_Data();
	void message();
	float mini_func(float, float, int, int);
	void Dijkstra_algorithm();
	void print_cost();
	void print_path();
	void reverse_arr(int *, int);
};

Dijkstra::Dijkstra() : count(0) {
	Read_Data();
	V_array_ptr = new int[nodeNumber];
	cost_array_ptr = new float[nodeNumber];
	path_array_ptr = new int[nodeNumber];
	for (int i = 0; i < nodeNumber; i++) {
		V_array_ptr[i] = -1;
	}
	for (int i = 0; i < nodeNumber; i++) {
		cost_array_ptr[i] = INFINITY;
	}
}

void Dijkstra::Read_Data()
{
	int vi, vj, weight;
	int **Data;
	fstream File;

	File.open(FILEPATH, ios::in);
	if (!File.is_open())
	{
		cerr << "Fail to open file..." << endl;
		system("PAUSE");
		exit(1);
	}

	File >> nodeNumber;//Read the total node number
	Data = new int*[nodeNumber];

	//Read data from txt file
	for (vi = 0; vi < nodeNumber; vi++)
	{
		Data[vi] = new int[nodeNumber];
		for (vj = 0; vj < nodeNumber; vj++)
			File >> Data[vi][vj];
	}

	//Obtain the edge weight
	for (vi = 0; vi < nodeNumber; vi++)
	{
		for (vj = 0; vj < nodeNumber; vj++)
		{
			weight = Data[vi][vj];
			if (weight)
			{
				E[count] = new Edge(vi, vj, weight);
				count++;
			}
		}
	}
}

void Dijkstra::message() {
	cout << "Please enter the initial node..." << endl;
	cin >> initialNode;
	cout << "Please enter the end node..." << endl;
	cin >> endNode;
}

void Dijkstra::Dijkstra_algorithm() {
	int costMiniNode = initialNode;
	//Initialize the path array
	for (int i = 0; i < nodeNumber; i++) {
		path_array_ptr[i] = initialNode;
	}
	//Let cost of starting node be zero
	cost_array_ptr[initialNode] = 0;

	//Obtain the optimal cost and path
	for (int i = 0; i < nodeNumber; i++) {
		int tag = 0, k = -1;
		//-2 represents this position has been used
		V_array_ptr[costMiniNode] = -2;
		for (int j = 0; j < count; j++) {
			if (E[j]->vertex_1 == costMiniNode) {
				cost_array_ptr[E[j]->vertex_2] = mini_func(cost_array_ptr[E[j]->vertex_2],
					cost_array_ptr[E[j]->vertex_1] + E[j]->weight, j, costMiniNode);
			}
		}
		//Move V_array_ptr[k] until it is unused...
		while (tag == 0) {
			k++;
			//Set a condition for avoiding k constantly increases
			if (V_array_ptr[k] == -1 || k == nodeNumber) {
				tag = 1;
			}
		}
		//Find the minimum cost and unused node
		for (int l = k + 1; l < nodeNumber; l++) {
			if ((cost_array_ptr[k] > cost_array_ptr[l]) && V_array_ptr[l] != -2) {
				k = l;
			}
		}
		costMiniNode = k;
	}
}

float Dijkstra::mini_func(float originalCost, float changedCost, int j, int costMiniNode) {
	//If return value is changedCost, then walking through this costMiniNode costs less!!
	//Therefore, we should replace value in path_array_ptr[E[j]->vertex_2] with costMiniNode...
	if (originalCost == INFINITY) {
		path_array_ptr[E[j]->vertex_2] = costMiniNode;
		return changedCost;
	}
	else if (originalCost > changedCost) {
		path_array_ptr[E[j]->vertex_2] = costMiniNode;
		return changedCost;
	}
	else {
		return originalCost;
	}
}

void Dijkstra::print_cost() {
	cout << "The minimum cost from '" << initialNode << "' to each node is..." << endl;
	for (int i = 0; i < nodeNumber; i++) {
		cout << i << " | ";
	} cout << endl;
	for (int i = 0; i < nodeNumber; i++) {
		cout << cost_array_ptr[i] << " | ";
	} cout << endl;
}

void Dijkstra::print_path() {
	int node = endNode, count = 0, tag = 0;
	int *temp_ptr = new int[nodeNumber];
	cout << "The minimum cost path from '" << initialNode << "' to each node is..." << endl;
	for (int i = 0; i < nodeNumber; i++) {
		cout << i << " | ";
	} cout << endl;
	for (int i = 0; i < nodeNumber; i++) {
		cout << path_array_ptr[i] << " | ";
	} cout << endl << endl;

	//Obtain the path(order is inversed!!)
	while (tag == 0) {
		if (path_array_ptr[node] == node) {
			tag = 1;
		}
		temp_ptr[count] = node;
		node = path_array_ptr[node];
		count++;
	}
	//Reverse the path array
	reverse_arr(temp_ptr, count);
	cout << "The path from " << initialNode << " to " << endNode << " is " << endl;
	for (int i = 0; i < count; i++) {
		cout << "V" << temp_ptr[i] << " ";
	} cout << endl;
}

void Dijkstra::reverse_arr(int *arr_ptr, int count) {
	for (int i = 0; i < (count / 2); i++) {
		//Swap using bit operation
		arr_ptr[i] = arr_ptr[i] ^ arr_ptr[count - i - 1];
		arr_ptr[count - i - 1] = arr_ptr[i] ^ arr_ptr[count - i - 1];
		arr_ptr[i] = arr_ptr[i] ^ arr_ptr[count - i - 1];
	}
}

int main(){
	Dijkstra A_Dijkstra;

	A_Dijkstra.message();
	A_Dijkstra.Dijkstra_algorithm();
	cout << endl;
	A_Dijkstra.print_cost();
	cout << endl;
	A_Dijkstra.print_path();

	system("PAUSE");
	return 0;
}