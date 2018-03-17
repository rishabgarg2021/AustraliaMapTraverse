
/* ... */

#include <stdio.h>
#include "traverse.h"
#include "list.h"
#include "queue.h"
#include "stack.h"
#include "graph.h"

#include <limits.h>
//function prototypes.
//struct stores the parent of node,distance from source and visitation of 
//vertex.
typedef struct{
    int distance;
    int source;
    int visited;
}tuple;
void DFS(Graph *graph,int *visited_array, int n);
void print_dfs(Graph* graph, int source_id);
void print_bfs(Graph* graph, int source_id);
void DFS_P(Graph *graph,int *visited_array, int n,int m,int *total,int *flag);
void detailed_path(Graph* graph, int source_id, int destination_id);
void again(int *A,int total,Graph *graph,int source );
void all_paths(Graph* graph, int source_id, int destination_id);
void DFS_ALL_PATHS(Graph *graph,int *visited_array, int source
				  ,int destination,int* A,int total, int current);
int shortest_vertex(Graph *graph,tuple *unvisited_array);
void DIJ_SHORTEST_PATH(Graph *graph,int current,int destination_id,
				       tuple *unvisited_array,int *flag);


//end of function prototypes.
//solution to Part1.


void DFS(Graph *graph,int *visited_array, int n){
    Edge *track_h=graph->vertices[n]->first_edge;
    if(visited_array[n]==0){
        printf("%s\n",graph->vertices[n]->label);
        visited_array[n]=1;
    }
    //track_h tracks the pointer to linked list of each vetex edges.
    //it traverses all vertex edges if its visited before otherwise its\
    //recurssively called if new vertex is found.
    for( n=track_h->v;track_h!=NULL;track_h=track_h->next_edge){
        n=track_h->v;
        //printf("n=%d\n",n);
        if(visited_array[n]==0){
            printf("%s\n",graph->vertices[n]->label);
            visited_array[n]=1;
            DFS(graph,visited_array,n);
            
        }
    }
}

void print_dfs(Graph* graph, int source_id) {
    
    int total_nodes=graph->n;
    int i=0;
    int visited_array[total_nodes];
    //assume each node as index of visited_array and is set to 0.
    for( i=0;i<total_nodes;i++){
        visited_array[i]=0;
    }
    //function dfs is called and its reccurssively made.
    DFS(graph,visited_array,source_id);
    
}

//end of part1.






//solution to Part2 

void print_bfs(Graph* graph, int source_id) {
    int total_nodes=graph->n;
    int visited_array[total_nodes];
    int i=0;
    //assume each node as index of visited_array and is set to 0.
    for( i=0;i<total_nodes;i++){
        visited_array[i]=0;
    }
    int r=0;//r is node number which is getting dequeued
    int n=0;//n is the node number which is traversed of current vertex.
    Queue *queue = new_queue();
    //main idea of this algorithm is to add elements in queue level by level.
    //if one vertex is being pop then its all edges are being queued in
    //queue and once vertex is dequeued it prints the elements.
    queue_enqueue(queue,source_id);
    while(!queue_is_empty(queue)){
        r=queue_dequeue(queue);
        //if vertex is printed its marked as visited.
        //no vertex can be printed more than once even if elements are being add
        //to queue manty times.
        if (visited_array[r]==0){
            printf("%s\n",graph->vertices[r]->label);
            visited_array[r]=1;
        }
        //track_q helps in traversing the edge of vertice.
        Edge *track_q=graph->vertices[r]->first_edge;
        for(n=track_q->v;track_q!=NULL;track_q=track_q->next_edge){
            n=track_q->v;
            //if vertice edges are being add to queue if its not printed.
            if(visited_array[n]==0){
                queue_enqueue(queue,track_q->v);
            }
        }
    }
    // queue is free when every vertice is printed level by level.
    free_queue(queue);
}
//end of part 2.








//Solution to part3.
//DFS_P its the path traversed by dfs function from source to destination vertex
//DFS_P traverse the commulative sum of path and writes the vertices traversed
//from source to destination.
void DFS_P(Graph *graph,int *visited_array, int n,int m,int *total,int *flag){
    Edge *track_h=graph->vertices[n]->first_edge;
    visited_array[n]=1;
    //n is the current vertex number
    //m is the destination vertex number.
    //flag becomes 1 as soon as it gets current vertex equals destination.
    printf("%s (%dkm)\n",graph->vertices[n]->label,*total);
    //if starting and destination vertex are same its need to return from
    //the recursion
    if(m==n){
        *flag=1;
        return;
    }
    //track_h tracks the pointer to linked list of each vetex edges.
    //it traverses all vertex edges if its visited before otherwise its\
    //recurssively called if new vertex is found.
    //function calls each new edge from given vertex till it finds new edge.
    //e.g.if one vertex doesnt have any new edge it goes into for loop
    //and checks for visited vertex but it will find a new vertex going
    //from it .total is a pointer which tracks the total distance travelled
    //till now
    for( n=track_h->v;track_h!=NULL && *flag==0;track_h=track_h->next_edge){
        n=track_h->v;
        
        //printf("n=%d\n",n);
        if(visited_array[n]==0){
            *total=*total+track_h->weight;
            DFS_P(graph,visited_array,n,m,total,flag);
        }
    }
}

void detailed_path(Graph* graph, int source_id, int destination_id) {
    
    int *total,p,*flag,q;
    
    total=&p;
    flag=&q;
    p=0;
    q=0;
    int i=0;
    int total_nodes=graph->n;
    int visited_array[total_nodes];
    //assume each node as index of visited_array and is set to 0.
    for( i=0;i<total_nodes;i++){
        visited_array[i]=0;
    }
    DFS_P(graph,visited_array,source_id,destination_id,total,flag);
   
}

//end of part3.







//solution to part4


//it helps to print the path traversed by all paths from source to destination 
//stored in A array by node number.

void again(int *A,int total,Graph *graph,int source ){
	int i=0;
	printf("%s ",graph->vertices[source]->label);
	for( i=total-1;i>=0;i--){
		printf(" %s",graph->vertices[A[i]]->label);
		
	}
	printf("\n");
	
}


//calculates the total number of possible path between source and destination.
void DFS_ALL_PATHS(Graph *graph,int *visited_array, int source
	,int destination,int* A,int total, int current){
	int p=0;
	//n is source vertex.m is destination vertex.
	//we would return from recursive function if we come back to node which is 
	//visited.
	if (current != destination && visited_array[current] == 1){
		return;
	}
	//if we reach to source vertex we would return from recursive by printing 
	//path travered from array A.
	if (current == source){
		 again( A, total,graph,source );
		 	 return;
	 }
	//it traverse the edge of nodes and call recursively dfs again. 
	//if all neighbours of particular node is visited, its marked as non visited
	//so that it can be counted when we are traversing from other nodes.
	Edge *track_h=graph->vertices[current]->first_edge;
	for( p=track_h->v;track_h!=NULL;track_h=track_h->next_edge){
		p=track_h->v;
		A[total]=current;
		visited_array[current]=1;
		DFS_ALL_PATHS(graph,visited_array,source, destination,A,total+1 , p);
	}
	visited_array[current]=0;
			
}

void all_paths(Graph* graph, int source_id, int destination_id) {
   	int total=0;
   	int i=0;
	int total_nodes=graph->n;
	int A[total_nodes+1];
    int visited_array[total_nodes];
    //assume each node as index of visited_array and is set to 0.
    for( i=0;i<total_nodes;i++){
        visited_array[i]=0;
    }
	DFS_ALL_PATHS(graph,visited_array,source_id,destination_id,A,total
		         ,destination_id);
	
	
}
//end of part 4.











//solution to part5.


//it checks the shortest distance of all unvisited node and return the node 
//number which has the shortest distance on it.
int shortest_vertex(Graph *graph,tuple *unvisited_array){
    int size=graph->n;
    int i;
    int shortest=0;
    int m=0;
   
    for( i=1;i<size;i++){
        if(unvisited_array[i].visited==0){
            shortest=unvisited_array[i].distance;
            m=i;
            break;
        }
    }
    for( i=1;i<size;i++){
        if(shortest>unvisited_array[i].distance && 
		  unvisited_array[i].visited==0){
            shortest=unvisited_array[i].distance;
            m=i;
        }
    }
    
    return m;
}



void DIJ_SHORTEST_PATH(Graph *graph,int current,int destination_id,
				       tuple *unvisited_array,int *flag){
    
    unvisited_array[current].visited=1;
    *flag=*flag+1;
    int u=0;
  
    Edge *track_h=graph->vertices[current]->first_edge;
    //traverse the edges of node and update its distance if its new distance is 
    //smaller than the previous one.
    for( u=track_h->v;track_h!=NULL && (*flag)<graph->n+1;
    	 track_h=track_h->next_edge){
        u=track_h->v;
        if((unvisited_array[current].distance+track_h->weight)
        	<unvisited_array[u].distance && unvisited_array[u].visited==0){
            unvisited_array[u].distance=unvisited_array[current].distance
            +track_h->weight;
            unvisited_array[u].source=track_h->u;
        }
    }
    if(*flag<=graph->n){
    	//returns the shortex distance of unvisited array.
        int shortest=shortest_vertex(graph,unvisited_array);
 
        DIJ_SHORTEST_PATH(graph,shortest, destination_id, unvisited_array
        				  ,flag);
    }
}

void shortest_path(Graph* graph, int source_id, int destination_id) {
   tuple unvisited_array[graph->n];//array of structs of all nodes.
    int *flag;
    int t=0;
    flag=&t;
    int i=0;
    //set the distance on each node to be int max.
    for( i=0;i<graph->n ;i++){
        unvisited_array[i].distance=INT_MAX;
        unvisited_array[i].source=0;
        unvisited_array[i].visited=0;
    }
    unvisited_array[source_id].distance=0;
    unvisited_array[source_id].source=source_id;
    
    DIJ_SHORTEST_PATH(graph,source_id,destination_id,unvisited_array
    	 			 ,flag);
    int m=0;
    int B[20];
    
    
    B[0]=destination_id;
    //stores the vertex number from parent of final vertex followed by
    //parent of parent of final vertex and continues till our parent
    //is source vertex.
    i=1;
    for(m=unvisited_array[destination_id].source;m!=source_id;
    	m=unvisited_array[m].source){
        B[i]=m;
        i=i+1;
    }
    B[i]=source_id;
    //back traverse the path and prints the shortest path.
    int x=i;
    for(x=i;x>0;x=x-1){
        printf("%s, ",graph->vertices[B[x]]->label);
    }
    printf("%s ",graph->vertices[B[0]]->label);
    printf("(%dkm)\n",unvisited_array[destination_id].distance);
    
}

//end of part5.


//ALGORITHMS ARE FUN.



