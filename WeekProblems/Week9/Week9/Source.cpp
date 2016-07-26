/*APL's course Week 9 Problem (Convex Hull)
**Author: Artur Pedroso
**Date: 25.05.2016
**University of Coimbra
**License: wtfpl
**/

#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <math.h>
#include <algorithm>
#include <string.h>

#define N 20

struct Vertex {
	int id; //number of vertex
	int x;
	int y;
};

Vertex vertices[N];
Vertex verticesCopy[N];//this copy mantains the order of vertices given in input

//return crossProduct of vector (p1-p0 and p2-p0)
int crossProduct(Vertex p0, Vertex p1, Vertex p2) {
	return (p1.x - p0.x) * (p2.y - p0.y) - (p1.y - p0.y) * (p2.x - p0.x);
}

//return euclidian distance between p0 and p1
double euclidDistance(Vertex p0, Vertex p1) {
	return sqrt(pow(p1.x - p0.x, 2) + pow(p1.y - p0.y, 2));
}

//comparer to sort vertices in ccw order relative to vertices[0] (lowest point)
bool comparerCCW(Vertex p1, Vertex p2) {
	int cpVal = crossProduct(vertices[0], p1, p2);
	
	if (cpVal > 0) 
		return true;//CCW
	
	if (cpVal < 0)
		return false;//CW

	if (euclidDistance(vertices[0], p1) < euclidDistance(vertices[0], p2))
		return true;//colinear
	
	return false;
}

//calculate area of polygon constituted by the vertices between [pini and pFin]
double calcArea(int pIni, int pFin) {
	double area = 0;
	int j = pFin;
	pFin++;
	for (int i = pIni; i < pFin; i++) {
		area += (verticesCopy[j].x + verticesCopy[i].x)*(verticesCopy[j].y - verticesCopy[i].y);
		j = i;
	}
	return area / 2.0;
}

//calculate area of polygon from p to p0(index == 0)
double calcArea2(int p, int totalVertices) {
	double area = 0;
	int j = 0;
	for (int i = p; i <= totalVertices; i++) {
		area += (verticesCopy[j].x + verticesCopy[i%totalVertices].x)*(verticesCopy[j].y - verticesCopy[i%totalVertices].y);
		j = i;
	}
	return area / 2.0;
}

//O(n*log(n))
void solveProblem(int n) {
	if (n < 3)
		return;//we can't construct a convex hull with less than 3 vertices
	
	std::sort(vertices+1, vertices+n, comparerCCW);//sort vertices in CCW in relation to vertices[0](lowest vertex)
	std::stack<Vertex> S;
	
	S.push(vertices[0]);
	S.push(vertices[1]);
	Vertex stackTop;
	for (int i = 2; i < n; i++) {
		stackTop = S.top();
		S.pop();
		while (crossProduct(S.top(), stackTop, vertices[i]) < 0) {
			stackTop = S.top();
			S.pop();
		}
		S.push(stackTop); //insert again the element that didn't passed the test
		S.push(vertices[i]);
	}
	//From this moment on the convex hull is in the stack...

	//Now we mark the id's that are present in convex hull
	char marked[N];
	memset(marked, 0, n * sizeof(char));
	while (!S.empty()) {
		marked[S.top().id] = 1;
		S.pop();
	}

	//Now it's time to calculate areas of poligons inside convex hull
	int firstVertex; //index of first vertex of polygon INSIDE conevex hull
	bool startPol = false; //make true starting a new polygon
	double area;
	int polysDetected = 0;
	for (int i = 0; i < n; i++) {
		if (marked[i] == 0) {
			if (!startPol) {
				startPol = true;
				firstVertex = i-1; //id of first vertex INSIDE convex hull
			}
		}
		else {
			if (startPol) {
				startPol = false; //close the polygon
				//calc area of polygon
				area = calcArea(firstVertex, i);
				printf("%d %.1f\n", polysDetected++, area);
			}
		}
	}

	if (startPol) {
		//in this case the polygon isn't closed
		//calc area of polygon
		area = calcArea2(firstVertex, n); //this is a variation of calcArea
		printf("%d %.1f\n", polysDetected, area);
	}
}

//get vertices from input saving the one with lowest y in vertices[0]
void getVertices(int n) {
	Vertex tmpV;
	scanf("%d %d", &vertices[0].x, &vertices[0].y);
	vertices[0].id = 0;
	memcpy(&verticesCopy[0], &vertices[0], sizeof(Vertex));
	for (int i = 1; i < n; i++) {
		scanf("%d %d", &vertices[i].x, &vertices[i].y);
		vertices[i].id = i;
		memcpy(&verticesCopy[i], &vertices[i], sizeof(Vertex));
		if ((vertices[i].y < vertices[0].y) ||
			(vertices[i].y == vertices[0].y && vertices[i].x < vertices[0].x)) {
			//save the point with lowest y in vertices[0] or lower x if two vertex have same y (lowest)
			tmpV = vertices[0];
			vertices[0] = vertices[i];
			vertices[i] = tmpV;
		}
	}
}

int main(){
	//freopen("test.txt", "r", stdin);
	int numVertices;
	while (scanf("%d", &numVertices) != EOF) {
		getVertices(numVertices);
		solveProblem(numVertices);
	}
	return 0;
}
