//written with Ashley Abernathy and Luke Holbrook
//I am not nearly sorry enough for the runtime

#include <stdlib.h>
#include <stdio.h>

struct node
{
	int label, level;
	struct node **edge;
};
typedef struct node node;

node **createGraph(int verts);
node **addEdge(node **graph, int e1, int e2);
node **traverse(node **graph, int source, int verts);
void freeGraph(node **graph, int verts);

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("Improper arguments. Must include only one filename for graph.\n");
		exit(1);
	}
	
	FILE *fp = fopen(argv[1], "r");
	
	int verts, edges;
	fscanf(fp, "%d %d", &verts, &edges);
	
	node **graph = createGraph(verts);
	
	int e1, e2;
	while (feof(fp) == 0)
	{
		fscanf(fp, "%d %d", &e1, &e2);
		graph = addEdge(graph, e1, e2);
	}
	fclose(fp);
	
	node **bft = NULL;
	bft = traverse(graph, 0, verts);
	
	printf("Shortest paths to outside\n");
	int x;
	node *temp;
	for (x = 1; x < verts; x++)
	{
		temp = bft[x];
		printf("%d: %d", x+1, x+1);
		while (temp != NULL)
		{
			temp = temp -> edge[0];
			if (temp != NULL)
				printf(" -> %d", (temp -> label +1));
		}
		printf("\n");
	}
	
	freeGraph(graph, verts);
	freeGraph(bft, verts);
	
	return 0;
}

node **createGraph(int verts)
{
	node **graph = malloc(sizeof(node*) * verts);
	
	int x;
	for (x = 0; x < verts; x++)
	{
		node *newNode = malloc(sizeof(node));
		newNode -> label = x;
		newNode -> level = -1;
		newNode -> edge = calloc(verts, sizeof(node*));
		
		graph[x] = newNode;
	}
	
	return(graph);
}

node **addEdge(node **graph, int e1, int e2)
{
	graph[e1-1] -> edge[e2-1] = graph[e2-1];
	graph[e2-1] -> edge[e1-1] = graph[e1-1];
	
	return(graph);
}

node **traverse(node **graph, int source, int verts)
{
	node **bft = createGraph(verts); //[0] will always be parent
	graph[source] -> level = 0;
	
	int lev, x, y;
	for (lev = 0; lev < verts; lev++)
	{
		for (x = 0; x < verts; x++)
		{
			if (graph[x] -> level == lev)
			{
				for (y = 0; y < verts; y++)
				{
					if (graph[x] -> edge[y] != NULL && bft[y] -> edge[0] == NULL)
					{
						graph[y] -> level = graph[x] -> level + 1;
						bft[y] -> edge[0] = graph[x];
					}
				}
			}
		}
	}
	
	return(bft);
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
