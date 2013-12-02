#include <iostream>
#include <cstdio>
#include <vector>
#include <list>
#include <cassert>

using namespace std;

float test[] = {  1.1, 0.1, 0.5, 0, 0, 
					    0,   0.5, 0.1, 1, 2,
					    1,   0.1, 0.05,0 ,1,
					   1.1,    0,   0, 1, 1,
					   5,    8.1,  89, 2, 3};


struct MATRIX
{
	size_t size1;
	size_t size2;
	float* data;
};

#define MATRIX_GET(mat, i, j) mat->data[i*mat->size1 + j]
#define MATRIX_SET(mat, i, j, v) mat->data[i*mat->size1 + j] = v

struct Tie
{
	int node;
	float w;
};

//Size of NodeT = //2*sizeof(size_t) + npar*(sizeof(NodeT**)+sizeof(float*)) + 
//			nchil*(sizeof(NodeT**)+sizeof(float*))
struct NodeT
{
	list<Tie> par; //parent nodes
	list<Tie> chil; //parent nodes
};

void makeGraphT(const MATRIX* in, vector<NodeT>& out)
{
	assert(in->size1 == in->size2);
	size_t n = in->size1;

	// allocate nodes
	out.clear();
	out.resize(n);

	size_t ncon = 0;
	for(int rr = 0 ; rr < n ; rr++) {
		for(int cc = 0 ; cc < n ; cc++) {

			//parent -> child
			//rr     -> cc
			if(MATRIX_GET(in, rr, cc) != 0) {
				//add child
				Tie tmp = {cc, MATRIX_GET(in, rr, cc)};
				out[rr].chil.push_back(tmp);

				//add 
				tmp.node = rr;
				out[cc].par.push_back(tmp);
			}
		}
	}
}

int main()
{
	MATRIX* matrix = new MATRIX;
	matrix->data = test;
	matrix->size1 = 5;
	matrix->size2 = 5;

	vector<NodeT> graph;
	makeGraphT(matrix, graph);

	//random walk for 100 steps
	int pos = 1;
	for(int ii = 0; ii < 100; ii++ ) {
		int trg = rand()%graph[pos].chil.size();
		auto it = graph[pos].chil.begin();
		while(trg > 0) {
			it++;
			trg--;
		}

		fprintf(stderr, "%i %f\n", it->node, it->w);
		pos = it->node;
	}
}
