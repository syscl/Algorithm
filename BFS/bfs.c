//
//  bfs.c
//  bfs
//
//  Created by Yating Zhou(aka syscl) on 06/04/2017.
//  Copyright (c) 2017 Yating Zhou(aka syscl). All rights reserved.
//
//  This work is licensed under the Creative Commons Attribution-NonCommercial
//  4.0 Unported License => http://creativecommons.org/licenses/by-nc/4.0
//
#include "syscl_lib.h"

//============================start=============================================

int main(int argc, char **argv)
{
	printHeader();

	// init Graph and jugs with volume now
	graph_t *Graph = calloc(1, sizeof(graph_t));
	Graph->vertex  = calloc(kMAXBUF, sizeof(vtx));
	initGraph(Graph);

	vol targetVolume = getUsrInt("Type in target volume you want: ");
	int nr_jug       = getUsrInt("Type in number of jugs you want: ");

	for (int i = 0; i < nr_jug; i++)
	{
		char *msg = (char *)calloc(kMAXBUF, sizeof(char));
		sprintf(msg, "Type in %d-th jug's capacity: ", i);
		Graph->vertex->jug[i].capacity = getUsrInt(msg);
		free(msg);
	}

	fillWater(Graph->vertex, nr_jug);

	DBG("BFS start\n");
	//
	// for i-th Graph[i] status => get vertex
	//
	for (int i = 0; i <= gMin(kMAXBUF-1, Graph->length); i++)
	{
		//
		// for j-th jug => Graph[i]->jug[j]
		//
		for (int j = 0; j < nr_jug; j++)
		{
			//
			// for k-th jug => Graph[i]->jug[k] which jug[j] will pour it's water to jug[k]
			//
			for (int k = 0; k < nr_jug; k++)
			{
				if (k == j) continue; 
				// copy current state from Graph[i] to tmp_vtx
				vtx* tmp_vtx = calloc(1, sizeof(vtx));
				initVtx(tmp_vtx);
				vtxcp(Graph->vertex + i, tmp_vtx);
				// now let's pour the water
				bool ret = pour(&(tmp_vtx->jug[j]), &(tmp_vtx->jug[k]));
				if (ret)
				{
					// pour success assign parent then add to list(w/ distance) if there's none
					if (!isInGraph(tmp_vtx, Graph))
					{
						Graph->length++;
						(Graph->vertex + Graph->length)->parent = (Graph->vertex + i);
						//insert vertex now
						insertVtx(tmp_vtx, Graph, Graph->length);
					}

					if (findVolume(Graph->vertex + Graph->length, targetVolume))
					{
						// yes we found, print the method
						print(Graph->vertex + Graph->length);
						puts("Done.");
						DBG("Yes we found.\n");
						// now we end the loop
						// notice to free the heap 
						// to avoid potential memory leak
						vtxfree(tmp_vtx);
						graphfree(Graph);
						return kRETSUCCESS;
					}
				}
				//
				// free tmp_vtx
				//
				vtxfree(tmp_vtx);
			}
		}
	}

	DBG("BFS end\n");

	puts("Impossible to find.");
	// avoid potential memory leak
	graphfree(Graph);
	return kRETFAILURE;
}

//==============================================================================
// initilize vertex v: return false if unable to init jug[]
//==============================================================================

bool initVtx(vtx *v)
{
	DBG("%s() ===>\n", __func__);
	v->parent = NULL;
	for (jug_t *jug = v->jug; jug < &kMAXJUG[v->jug]; jug++)
	{
		if (!initJug(jug, 0, INF))
		{
			DBG("%s() <===false\n", __func__);
			return false;
		}
	}
	DBG("%s() <===true\n", __func__);
	return true;
}

//==============================================================================
// initGraph(...) init a graph(V, E)
//==============================================================================

bool initGraph(graph_t *Graph)
{
	DBG("initGraph() ===>\n");
	for (vtx *v = Graph->vertex; v < &kMAXBUF[Graph->vertex]; v++)
	{
		if (!initVtx(v))
		{
			DBG("initGraph() <===false\n");
			return false;
		}
	}
	Graph->length = 0;  // init length of a graph
	DBG("initGraph() <===true\n");
	return true;
}

//==============================================================================
// print out vertex's current status 
//==============================================================================

void printVtx(vtx *v)
{
	putchar('(');
	for (int i = 0; i < kMAXJUG; i++)
	{
		if (v->jug[i].capacity == INF) break;
		printf("%d%s", v->jug[i].water, (v->jug[i+1].capacity==INF || i==kMAXJUG-1)?")":", ");
	}
	return;
}

//==============================================================================
//
// print: recursive version of printVtx(...) use stack property(FILO)
//
// to print out the path we want to pour water
//
//==============================================================================

void print(vtx *v)
{
	if (v->parent != NULL)
	{
		print(v->parent);
	}
	printVtx(v);
	printf(" -> ");
}

//==============================================================================
// vtxcp(...): copy properties from source(src) to target(tar)
//==============================================================================

bool vtxcp(vtx *src, vtx *tar)
{
	DBG("vtxcp() ===>\n");
	for (jug_t *s = src->jug, *t = tar->jug; t < &kMAXJUG[t]; s++, t++)
	{
		if (s->capacity == INF) break;

		t->water    = s->water;
		t->capacity = s->capacity;
	}
	DBG("vtxcp() <===true\n");
	return true;
}

//==============================================================================
// pour(...) pour water to another jug
//==============================================================================

bool pour(jug_t *from, jug_t *to)
{
	DBG("pour() ===>\n");
	vol v1   = from->water;
	vol v2   = to->water;
	vol c2   = to->capacity;
	bool ret = true;

	DBG("from (%d, %d)\n", from->water, to->water);

	if (v1 == 0 || v2 == c2)
	{
		// no water or target is full, do nothing
		ret = false;
	}
	else if (v1 + v2 > c2)
	{
		// (v1, v2) -> (v1 - (c2 - v2), c2)
		to->water   = c2;
		from->water = v1 + v2 - c2;
	}
	else
	{
		// (v1, v2) -> (0, v1 + v2)
		from->water = 0;
		to->water   = v1 + v2;
	}

	DBG("to   (%d, %d)\n", from->water, to->water);
	DBG("pour() <===\n");
	return ret;
}

//==============================================================================
// findVolume(...) find if targetVolume is matched
//==============================================================================

bool findVolume(vtx *v, vol targetVolume)
{
	DBG("%s() ===>\n", __func__);
	for (jug_t *jug = &kMAXJUG[v->jug]; jug >= v->jug; jug--)
	{
		if (jug->water == targetVolume)
		{
			DBG("%s() <===true\n", __func__);
			return true;
		}
	}
	DBG("%s() <===false\n", __func__);
	return false;
}

//==============================================================================
// vtxcmp(...) compare vertex v and g, return true if matched, otherwise false
//==============================================================================

bool vtxcmp(vtx *v, vtx *g)
{
	for (jug_t *t = &kMAXJUG[v->jug], *s = &kMAXJUG[g->jug]; t >= v->jug; t--, s--)
		if (t->water != s->water) return false;
	return true;
}

//==============================================================================
// isInGraph(...) find a status vertex is in a Graph
//==============================================================================

bool isInGraph(vtx *v, graph_t *G)
{
	//DBG("isInGraph() ===>\n");
	for (vtx *p = &(G->length[G->vertex]); p >= G->vertex; p--)
		if (vtxcmp(v, p)) return true;
	return false;
}

//==============================================================================
// getUsrInt: get int from userspace
//==============================================================================

int getUsrInt(const char *prompt)
{
	int v;
	printf("%s", prompt);
	scanf("%d", &v);
	DBG("user type in %d\n", v);
	return v;
}

//==============================================================================
// fillWater: fill water to the maximum capacity jug
//==============================================================================

void fillWater(vtx *s, int n)
{
	jug_t *max = &n[s->jug];
	for (jug_t *p = max - 1; p >= s->jug; p--) 
		max = (max->capacity > p->capacity) ? max : p;
	max->water = max->capacity;
	DBG("The %ld-th jug is the largest one, fill with %d pint water\n", max-s->jug, max->water);
	return;
}

//==============================================================================
// vtxfree(...) free vertex from heap
//==============================================================================

void vtxfree(vtx *v)
{
	DBG("vtxfree() ===>\n"); 
	// prevent weird pointer
	v->parent = NULL;
	free(v);
	DBG("vtxfree() <===\n");
	return;
}

//==============================================================================
// graphfree(...) free Grahp from heap
//==============================================================================

void graphfree(graph_t *g)
{
	DBG("graphfree() ===>\n");
	free(g->vertex);
	g->vertex = NULL;
	free(g);
	DBG("%s() <===\n", __func__);
	return;
}

//==============================================================================
// insertVtx(...) insert vertex to graph if there's no same vertex exist
//==============================================================================

bool insertVtx(vtx *v, graph_t *G, int distance)
{
	DBG("insertVtx() ===>\n");
	v->distance = distance;
	DBG("distance: %d\n", v->distance);
	DBG("insertVtx() <===\n");
	return vtxcp(v, &distance[G->vertex]);
}

//==============================================================================
