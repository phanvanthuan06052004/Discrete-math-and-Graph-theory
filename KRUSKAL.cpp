#include <bits/stdc++.h>
#include <fstream>
#include <algorithm>
#include <vector>
#include <graphics.h>
using namespace std;
const int MAX = 100;
int edgeThickness = 3;  
int edgeLineStyle = 0; 
struct Edge 
{
    int d,c,k,X,Y;
};
void drawEdge(int xi,int yi,int xj, int yj,Edge H) ;
void drawEdge1(int xi,int yi,int xj, int yj,Edge H) ;
bool sortEdges(const Edge &a, const Edge &b)
{
    return a.k < b.k;
}

int findRoot(int parent[], int i)
{
    if(parent[i]==i)
    	return i;
    return findRoot(parent,parent[i]);
}

void unionTrees(int parent[], int rank[], int x, int y)
{
    int rootX = findRoot(parent, x);
    int rootY = findRoot(parent, y);

    if (rootX != rootY) 
	{
        if (rank[rootX] < rank[rootY]) 
            {
			parent[rootX] = rootY;
			rank[rootY]+=rank[rootX];
			}
         else 
            {
			parent[rootY] = rootX;
         	rank[rootX]+=rank[rootY];
         	}
    }
    return ;
}


void kruskalMST(int G[][MAX], int V,int X[],int Y[])
{
    vector<Edge> edges;
    for (int i = 0; i < V; ++i) 
	{
        for (int j = i + 1; j < V; ++j)
		{
            if (G[i][j] != 0)
			{
                Edge edge = {i, j, G[i][j],i,j};
                edges.push_back(edge);
            }
        }
    }

    sort(edges.begin(), edges.end(), sortEdges);

    int parent[MAX], rank[MAX];
    for (int v = 0; v < V; ++v) 
	{
        parent[v] = v;
        rank[v] = 1;
    }

    for (int i = 0; i < edges.size(); ++i) 
	{
    int rootX = findRoot(parent, edges[i].d);
    int rootY = findRoot(parent, edges[i].c);

    if (rootX != rootY) 
		{
		drawEdge(X[edges[i].d],Y[edges[i].d],X[edges[i].c],Y[edges[i].c],edges[i]) ;
        unionTrees(parent, rank, rootX, rootY);
   		}
   	else 
   		drawEdge1(X[edges[i].d],Y[edges[i].d],X[edges[i].c],Y[edges[i].c],edges[i]) ;
	}

}
void drawNode(int x[], int y[],int V)
{
	
    int gd = DETECT, gm;
    initgraph(&gd, &gm, NULL);
	setbkcolor(WHITE); 
    int centerX = getmaxx() / 2;
    int centerY = getmaxy() / 2;
    int radius = 210;
    float angleIncrement = 360.0 / V;

    // Ve dinh
    for (int i = 0; i < V; ++i) 
	{
        float angle = i * angleIncrement;
        x[i] = centerX + radius * cos(angle * 3.14159 / 180.0);
        y[i] = centerY + radius * sin(angle * 3.14159 / 180.0);

        setcolor(RED);
        circle(x[i], y[i], 25);
        floodfill(x[i], y[i], RED);
        setcolor(WHITE);
        setbkcolor(RED);
        char buffer[10];
        sprintf(buffer, "%d", i );
        outtextxy(x[i] - 5, y[i] - 5, buffer);
    }

}
void drawNode1(int x[], int y[],int V)
{
	for (int i = 0; i < V; ++i) 
	{
	    setcolor(RED);
        circle(x[i], y[i], 25);
        floodfill(x[i], y[i], RED);
        setcolor(WHITE);
        setbkcolor(RED);
        char buffer[10];
        sprintf(buffer, "%d", i );
        outtextxy(x[i] - 5, y[i] - 5, buffer);
    }
}
void drawEdge1(int xi,int yi,int xj, int yj,Edge H) 
 {
 	setlinestyle(edgeLineStyle, 0, edgeThickness);
    setcolor(WHITE);
    line(xi, yi, xj, yj);
    setcolor(YELLOW);
    char weight[10];
    sprintf(weight, "%d", H.k);
    outtextxy((xi + xj) / 2, (yi + yj) / 2, weight);
    setlinestyle(0, 0, 1);
}
void drawEdge(int xi,int yi,int xj, int yj,Edge H) 
 {
 	setlinestyle(edgeLineStyle, 0, edgeThickness);
    setcolor(BLUE);
    line(xi, yi, xj, yj);
    setcolor(YELLOW);
    char weight[10];
    sprintf(weight, "%d", H.k);
    outtextxy((xi + xj) / 2, (yi + yj) / 2, weight);
    setlinestyle(0, 0, 1);
}
int main()
{
	fstream f;
	f.open("Kruskal.txt", ios::in);
	if (f.fail()) 
		cout<<"Open Fail \n";
    int V; f >> V;
    int X[V],Y[V];
    
    drawNode(X,Y,V);
    int G[MAX][MAX];
    for (int i = 0; i < V; ++i)
        for (int j = 0; j < V; ++j)
            f >> G[i][j];
  
    kruskalMST(G, V,X,Y);
    drawNode1(X,Y,V);
    delay(500000);
    closegraph();
    f.close();
    return 0;
}
