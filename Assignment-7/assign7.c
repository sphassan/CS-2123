#include <stdlib.h>
#include <stdio.h>

struct node
{
	int visited; //boolean, 0 no, 1 yes
	struct node **edge; //array of pointers to other vertices
};
typedef struct node node;

node **createGraph(int verts);
node **addEdge(node **graph, int e1, int e2);
node **traverse(node **graph, int index, int verts);
int connected(node **graph, int verts);
void freeGraph(node **graph, int verts);

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Improper arguments. Must include filename and only one filename.\n");
		return(1);
	}
	
	FILE *fp;
	fp = fopen(argv[1], "r");
	
	int verts;
	int edges;
	
	fscanf(fp, "%d %d", &verts, &edges);
	
	if (edges != verts - 1)
	{
		printf("The graph does not belong to a tree.\n");
		fclose(fp);
		return(0);
	}
	
	node **graph = createGraph(verts);
	
	int e1, e2;
	while (feof(fp) == 0)
	{
		fscanf(fp, "%d %d", &e1, &e2);
		graph = addEdge(graph, e1, e2);
	}	
	fclose(fp);
	
	graph = traverse(graph, 0, verts);
	
	int connect = connected(graph, verts);
	
	if (connect == 1)
		printf("The graph does belong to a tree.\n");
	else
		printf("The graph does not belong to a tree.\n");
	
	freeGraph(graph, verts);
	
	return(0);
}

node **createGraph(int verts)
{
	node **graph = malloc(sizeof(node*) * verts);
	
	int x;
	for (x = 0; x < verts; x++)
	{
		node *newNode = malloc(sizeof(node));
		newNode -> visited = 0;
		newNode -> edge = calloc(verts, sizeof(node*));
		
		graph[x] = newNode;
	}
	
	return(graph);
}

node **addEdge(node **graph, int e1, int e2)
{
	node *temp = graph[e1-1];
	temp -> edge[e2-1] = graph[e2-1];
	temp = graph[e2-1];
	temp -> edge[e1-1] = graph[e1-1];
	
	return(graph);
}

node **traverse(node **graph, int index, int verts)
{
	graph[index] -> visited = 1;
	
	int x;
	for (x = 0; x < verts; x++)
		if (graph[index] -> edge[x] != NULL && graph[index] -> edge[x] -> visited == 0)
			traverse(graph, x, verts);
	
	return(graph);
}

int connected(node **graph, int verts)
{
	int x;
	for (x = 0; x < verts; x++)
		if (graph[x] -> visited == 0)
			return(0);
	
	return(1);
}

void freeGraph(node **graph, int verts)
{
	int x;
	for (x = 0; x < verts; x++)
	{
		free(graph[x] -> edge);
		free(graph[x]);
	}
	
	free(graph);
}
