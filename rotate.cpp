#include <iostream>
#include <cmath>
#include <cassert>

using namespace std;

/* 
 * Rotations. Each of the following functions takes an input point, three angles
 * and an output point. Angle a is about the x axis, angle b is about the y axis
 * and angle c is about the z axis
 */


//{{Cos[b] Cos[c], Cos[b] Sin[c], -Sin[b]}, 
// {Cos[c] Sin[a] Sin[b] - Cos[a] Sin[c], Cos[a] Cos[c] + Sin[a] Sin[b] Sin[c], Cos[b] Sin[a]},
// {Cos[a] Cos[c] Sin[b] + Sin[a] Sin[c], -(Cos[c] Sin[a]) + Cos[a] Sin[b] Sin[c], Cos[a] Cos[b]}}
int rotate(double in[3], double a, double b, double c, double out[3])
{
	assert(in != out);

	out[0] = 	in[0]*cos(b)*cos(c) + 
				in[1]*cos(b)*sin(c) -
				in[2]*sin(b);
	out[1] = 	in[0]*(cos(c)*sin(a)*sin(b)-cos(a)*sin(c))+
				in[1]*(cos(a)*cos(c)+sin(a)*sin(b)*sin(c))+
				in[2]*cos(b)*sin(a);
	out[2] =	in[0]*(cos(a)*cos(c)*sin(b)+sin(a)*sin(c))+
				in[1]*(cos(a)*sin(b)*sin(c)-cos(c)*sin(a))+
				in[2]*cos(a)*cos(b);
	return 0;
}

// D[{{1, 0, 0}, {0, Cos[a], Sin[a]}, {0, -Sin[a], Cos[a]}} . 
// {{Cos[b], 0, -Sin[b]}, {0, 1, 0}, {Sin[b], 0, Cos[b]}} . 
// {{Cos[c], Sin[c], 0}, {-Sin[c], Cos[c], 0}, {0, 0, 1}}, a]
int dXRotate(double in[3], double a, double b, double c, double out[3])
{
	assert(in != out);
	
	out[0] = 	0;
	out[1] = 	in[0]*(cos(a)*cos(c)*sin(b)+sin(a)*sin(c)) + 
				in[1]*(cos(a)*sin(b)*sin(c)-cos(c)*sin(a)) + 
				in[2]*(cos(a)*cos(b));
	out[2] = 	in[0]*(cos(a)*sin(c)-cos(c)*sin(a)*sin(b)) + 
				in[1]*(-cos(a)*cos(c)-sin(a)*sin(b)*sin(c)) + 
				in[2]*(-cos(b)*sin(a));
	return 0;
}

// D[{{1, 0, 0}, {0, Cos[a], Sin[a]}, {0, -Sin[a], Cos[a]}} . 
// {{Cos[b], 0, -Sin[b]}, {0, 1, 0}, {Sin[b], 0, Cos[b]}} . 
// {{Cos[c], Sin[c], 0}, {-Sin[c], Cos[c], 0}, {0, 0, 1}}, b]
int dYRotate(double in[3], double a, double b, double c, double out[3])
{
	assert(in != out);
	
	out[0] = 	in[0]*(-cos(c)*sin(b)) +
				in[1]*(-sin(b)*sin(c)) + 
				in[2]*(-cos(b));
	out[1] =	in[0]*(cos(b)*cos(c)*sin(a)) + 
				in[1]*(cos(b)*sin(a)*sin(c)) + 
				in[2]*(-sin(a)*sin(b));
	out[2] =	in[0]*(cos(a)*cos(b)*cos(c)) +
				in[1]*(cos(a)*cos(b)*sin(c)) + 
				in[2]*(-cos(a)*sin(b));
	return 0;
}

// D[{{1, 0, 0}, {0, Cos[a], Sin[a]}, {0, -Sin[a], Cos[a]}}.
// {{Cos[b], 0, -Sin[b]}, {0, 1, 0}, {Sin[b], 0, Cos[b]}} . 
// {{Cos[c], Sin[c], 0}, {-Sin[c], Cos[c], 0}, {0, 0, 1}}, c]
int dZRotate(double in[3], double a, double b, double c, double out[3])
{
	assert(in != out);
	
	out[0] =	in[0]*sin(c) +
				in[1]*cos(b)*cos(c);
	out[1] = 	in[0]*(-cos(a)*cos(c)-sin(a)*sin(b)*sin(c)) +
				in[1]*(cos(c)*sin(a)*sin(b)-cos(a)*sin(c));
	out[2] =	in[0]*(cos(c)*sin(a)-cos(a)*sin(b)*sin(c)) + 
				in[1]*(cos(a)*cos(c)*sin(b)+sin(a)*sin(c));
	return 0;
}

void swap(double a[3], double b[3])
{
	for(size_t ii=0; ii<3; ii++)
		std::swap(a[0],b[0]);
}

int main()
{
	const double PI = acos(-1);
	double pos1[3] = {1.2, 91, 12};
	double pos2[3];
	double pos3[3];
	
	rotate(pos1, PI/4, PI/2, PI, pos2); swap(pos1, pos2);
	cerr << "(" << pos1[0] << "," << pos1[1] << "," << pos1[2] << ")" << endl;
	rotate(pos1, PI/4, PI/2, PI, pos2); swap(pos1, pos2);
	cerr << "(" << pos1[0] << "," << pos1[1] << "," << pos1[2] << ")" << endl;
	rotate(pos1, PI/4, PI/2, PI, pos2); swap(pos1, pos2);
	cerr << "(" << pos1[0] << "," << pos1[1] << "," << pos1[2] << ")" << endl;
	rotate(pos1, PI/4, PI/2, PI, pos2); swap(pos1, pos2);
	cerr << "(" << pos1[0] << "," << pos1[1] << "," << pos1[2] << ")" << endl;
	rotate(pos1, PI/4, PI/2, PI, pos2); swap(pos1, pos2);
	cerr << "(" << pos1[0] << "," << pos1[1] << "," << pos1[2] << ")" << endl;
	rotate(pos1, PI/4, PI/2, PI, pos2); swap(pos1, pos2);
	cerr << "(" << pos1[0] << "," << pos1[1] << "," << pos1[2] << ")" << endl;
	rotate(pos1, PI/4, PI/2, PI, pos2); swap(pos1, pos2);
	cerr << "(" << pos1[0] << "," << pos1[1] << "," << pos1[2] << ")" << endl;
	rotate(pos1, PI/4, PI/2, PI, pos2); swap(pos1, pos2);
	cerr << "(" << pos1[0] << "," << pos1[1] << "," << pos1[2] << ")" << endl;

	// test dP/d a
	double da = 0.000001;
	double a = 1.2;
	double b = 3.1;
	double c = .1;
	rotate(pos1, a, b, c, pos2);
	rotate(pos1, a+da, b, c, pos3);
	cerr << "d/da = ( " << (pos3[0]-pos2[0])/da << "," << (pos3[1]-pos2[1])/da 
		<< "," << (pos3[2]-pos2[2])/da << ")" << endl;
	dXRotate(pos1, a, b, c, pos2);
	cerr << "d/da = ( " << pos2[0] << "," << pos2[1] << "," << pos2[2] 
		<< ")" << endl;
	
	rotate(pos1, a, b, c, pos2);
	rotate(pos1, a, b+da, c, pos3);
	cerr << "d/db = ( " << (pos3[0]-pos2[0])/da << "," << (pos3[1]-pos2[1])/da 
		<< "," << (pos3[2]-pos2[2])/da << ")" << endl;
	dYRotate(pos1, a, b, c, pos2);
	cerr << "d/db = ( " << pos2[0] << "," << pos2[1] << "," << pos2[2] 
		<< ")" << endl;
	
	rotate(pos1, a, b, c, pos2);
	rotate(pos1, a, b, c+da, pos3);
	cerr << "d/dc = ( " << (pos3[0]-pos2[0])/da << "," << (pos3[1]-pos2[1])/da 
		<< "," << (pos3[2]-pos2[2])/da << ")" << endl;
	dZRotate(pos1, a, b, c, pos2);
	cerr << "d/dc = ( " << pos2[0] << "," << pos2[1] << "," << pos2[2] 
		<< ")" << endl;
}

//Sx[a_,b_]:={{1,a,b},{0,1,0},{0,0,1}}
//Sy[c_,d_]:={{1,0,0},{c,1,d},{0,0,1}}
//Sz[e_,f_]:={{1,0,0},{0,1,0},{e,f,1}} 
// Solve For 1 Rotation
// Rotate About X
// In[119]:= FullSimplify[Solve[Sy[0,b].Sz[0,d].Sy[0,f]==R[\[Phi],0,0],{b,d,f}]]
// Out[119]= {{b->(-1+Cos[\[Phi]]) Csc[\[Phi]],d->Sin[\[Phi]],f->-Tan[\[Phi]/2]}}
// In[120]:= FullSimplify[Solve[Sz[0,b].Sy[0,d].Sz[0,f]==R[\[Phi],0,0],{b,d,f}]]
// Out[120]= {{b->Tan[\[Phi]/2],d->-Sin[\[Phi]],f->Tan[\[Phi]/2]}}
// Rotate About Y
// In[121]:= FullSimplify[Solve[Sx[0,b].Sz[c,0].Sx[0,f]==R[0,\[Theta],0],{b,c,f}]]
// Out[121]= {{b->Tan[\[Theta]/2],c->-Sin[\[Theta]],f->Tan[\[Theta]/2]}}
// In[122]:= FullSimplify[Solve[Sz[a,0].Sx[0,d].Sz[e,0]==R[0,\[Theta],0],{a,d,e}]]
// Out[122]= {{a->-Tan[\[Theta]/2],d->Sin[\[Theta]],e->(-1+Cos[\[Theta]]) Csc[\[Theta]]}}
// Rotate About Z
// In[123]:= FullSimplify[Solve[Sx[a,0].Sy[c,0].Sx[e,0]==R[0,0,\[Alpha]],{a,c,e}]]
// Out[123]= {{a->(-1+Cos[\[Alpha]]) Csc[\[Alpha]],c->Sin[\[Alpha]],e->-Tan[\[Alpha]/2]}}
// In[124]:= FullSimplify[Solve[Sy[a,0].Sx[c,0].Sy[e,0]==R[0,0,\[Alpha]],{a,c,e}]]
// Out[124]= {{a->Tan[\[Alpha]/2],c->-Sin[\[Alpha]],e->Tan[\[Alpha]/2]}}
