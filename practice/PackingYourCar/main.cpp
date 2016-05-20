#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define N 100

struct Object{
	int imp;
	int w;
	int v;
	bool marked;
};

struct ObjectW{
	int id;
	int imp;
	int w;
};

struct ObjectV{
	int id;
	int imp;
	int v;
};

int numItems, maxWeight, maxVolume;
int bestImp; //saves the best importance acquired with the objects that is possible to pack
Object objects[N]; //saves the importance, weight and volume of each object
ObjectW objectsW[N]; //objects ordered by imp/w
ObjectV objectsV[N]; //objects ordered by imp/v

double boundW(int W){
	int w = 0;
	double imp = 0;
	for(int i = 0; i < numItems; i++){
		if(objects[objectsW[i].id].marked == false){
			if((w = objectsW[i].w + w) < W){
				imp += objectsW[i].imp;
			}
			else{
				w = w-objectsW[i].w;
				imp += objectsW[i].imp * ((W-w)/(double)objectsW[i].w);
				return imp;
			}
		}
	}
	return imp;
}

double boundV(int V){
	int v = 0;
	double imp = 0;
	for(int i = 0; i < numItems; i++){
		if(objects[objectsV[i].id].marked == false){
			if((v = objectsV[i].v + v) < V){
				imp += objectsV[i].imp;
			}
			else{
				v = v-objectsV[i].v;
				imp += objectsV[i].imp * ((V-v)/(double)objectsV[i].v);
				return imp;
			}
		}
	}
	return imp;
}

void maxImp(int itemId, int W, int V, int imp){
	if (imp > bestImp)
		bestImp = imp;

	if (imp + std::min(boundW(W), boundV(V)) <= bestImp)
		return;

	for(int j = itemId+1; j < numItems; j++){
		if(objects[j].w <= W && objects[j].v <= V){
			objects[j].marked=true;
			maxImp(j, W-objects[j].w, V-objects[j].v, imp+objects[j].imp);
			objects[j].marked=false;
		}
	}
}

//sorts in non increasing order

bool sortW (ObjectW i,ObjectW j) { return (i.imp/(double)i.w > j.imp/(double)j.w); }

bool sortV (ObjectV i,ObjectV j) { return (i.imp/(double)i.v > j.imp/(double)j.v); }

int main(){
	int numTests;
	scanf("%d", &numTests);
	while (numTests--){
		scanf("%d %d %d", &numItems, &maxWeight, &maxVolume);
		bestImp = 0;
		for (int i = 0; i < numItems; i++){
			scanf("%d %d %d", &objects[i].imp, &objects[i].w, &objects[i].v);
			objectsW[i].id = i;
			objectsW[i].imp = objects[i].imp;
			objectsW[i].w = objects[i].w;
			objectsV[i].id = i;
			objectsV[i].imp = objects[i].imp;
			objectsV[i].v = objects[i].v;
		}

		std::sort(objectsW, objectsW+numItems, sortW);
		std::sort(objectsV, objectsV+numItems, sortV);

		for(int i = 0; i < numItems; i++){
			if(objects[i].w <= maxWeight && objects[i].v <= maxVolume){
				objects[i].marked = true;
				maxImp(i, maxWeight-objects[i].w, maxVolume-objects[i].v, objects[i].imp);
				objects[i].marked = false;
			}
		}

		printf("%d\n", bestImp);

	}
	return 0;
}
