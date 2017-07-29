#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Structs.h"
#include "Algorithms.h"

void readEdges(Tree * courses, Tree * tracks, List * list);
void createCourseNodes(Tree * courses);
void createTrackNodes(Tree * tracks);
Node * getNodeByTrackName(Tree * tracks, char * c);
Node * getNodeByCourse(Tree * courses, int num);

int main(int argc, char ** argv){
	printf("Inputs are CSE, CGV, SoftEngr, MI, DBIS, Systems, Security, FCS, PL\n"); 
	//prepares an array of the tracks that are inputs
	int size = 0;
	//determines if inputs are valid and counts number of valid arguments
	for (int i = 1; i < argc; i++){
		printf("%d\n", getTrackNumber(argv[i]));
		if (getTrackNumber(argv[i]) == -1){
			return -1;
		}
		++size;
	}

	//creates a separate array with the enumerated types for tracks and uses them to transfer information to algorithm later
	int colors[size];
	for (int i = 1; i < size+1; i++){
		colors[i-1] = getTrackNumber(argv[i]);

	}

	//Initiates original edge list, as well as the hash trees
	List * list = new List();
	Tree * courses = new Tree();
	Tree * tracks = new Tree();
	courses->side = COURSE;
	tracks->side = TRACK;

	//Creates Vertices of Bipartite Graph
	createCourseNodes(courses);
	createTrackNodes(tracks);

	//Creates the Edges of the Bipartite Graph
	readEdges(courses, tracks, list);
	printf("\n\nNumber: ");
	int p[] = {434, 334, 314, 471, 416, 381, 354, 489, 352};
	computeTracks(courses, p, 9);

}


void createCourseNodes(Tree * courses)
{
	FILE * f = fopen("courses2.txt", "r"); //opens the information about courses
	courses->nodes = new Node*[515]; // Creates hash table
	char * prefix; // the department prefix
	char * number; // the course number
	char * courseName; // the couse name string
	int num; // the number derived from the character pointer above
	char buffer[100]; //an input buffer

	/*
	   Loop Invariant:
	   The buffer will be filled initially unless the file is missing, so it won't be null.
	   As long as i+1 != n, then it will read in i+1 after i to get informationa bout the course
	   When the file is empty, fgets will return null, and the loop will end
	 */
	while (fgets(buffer, 100, f) != NULL){

		//parsing the information
		prefix = strtok(buffer, " ");
		number = strtok(NULL, ":");
		num = atoi(number);
		courseName = strtok(NULL, "\n");

		//parsing symbol information
		symbol s = CS;
		if (!strcmp(prefix, "MA"))
			s = MA;	
		else if (!strcmp(prefix, "CS"))
			s = CS;
		else if (!strcmp(prefix, "STAT"))
			s = STAT;

		//inserts and initializes the course vertice in the hashtable
		courses->nodes[num] = new Node(new Course(courseName, num, s));
	}

	fclose(f);

}


void createTrackNodes(Tree * tracks)
{
	FILE * f = fopen("tracks.txt", "r");//opens file
	tracks->nodes = new Node*[9]; // creates hash table
	char buffer[15]; // input fields
	char * trackName;
	char * reqCount;
	int reqs;


	for (int i = 0; i < 9; i++ ){
		//intakes information about tracks and track Names
		fscanf(f, " %s ", buffer);
		trackName = strtok(buffer, ":");
		reqCount = strtok(NULL, "\0\n");
		reqs = atoi(reqCount);
		//creates every track node with the new track with the given track names

		tracks->nodes[i] = new Node(new Track(trackName));		
		tracks->nodes[i]->track->reqCounter = reqs;

	}
	fclose(f);


}

void readEdges(Tree * courses, Tree * tracks, List * list){
	//the edge variables used to initiate the edges in Bipartite Graph
	Node * t = NULL;
	Node * c = NULL;
	Edge * edge;
	Edge * altEdge;

	//IO support fields
	FILE * f = fopen("edges.txt", "r");
	char buffer[100];

	char * track;
	char * flag;
	char * prefix;
	char * courseNum;

	//information about the courses and their relationship to the track
	bool required;
	bool alt = false;
	bool trigger = false;
	symbol s;
	int murphy = 0;

	while ( fgets(buffer, 100, f) != NULL){
		//parses information about track
		track = strtok(buffer, ":");
		flag = strtok(NULL, ":");

		if (flag == NULL ) break;
		//parses information about course
		prefix = strtok(NULL, ":");
		courseNum = strtok(NULL, "\n"); 

		//parses flag information
		if (alt) {} else{
			if (!strcmp(flag, "R"))
				required = true;
			else if (!strcmp(flag, "E"))
				required = false;
			else if (!strcmp(flag, "A")){
				required = true;
				alt = true;
			}
		}

		//parses department information
		if (!strcmp(prefix, "MA"))
			s = MA;	
		else if (!strcmp(prefix, "CS"))
			s = CS;
		else if (!strcmp(prefix, "STAT"))
			s = STAT;
		//converts string to int
		murphy = atoi(courseNum);
		//retrieves node values to connect to the edge
		c = getNodeByCourse(courses, murphy);
		t = getNodeByTrackName(tracks, track);

		//creates the edge
		edge = new Edge(t, c, required);

		//executes alternative branch
		if (trigger){
			altEdge->twinNode = edge->courseNode;
			edge->twinNode = altEdge->courseNode;
			alt = false;
			trigger = false;
		}
		//adds the edges to the appropriate lists
		c->add(edge);
		c->course->totalCounter++;
		t->add(edge);
		//adds the edge to the master list which may not be necessary
		//edge->print();
		list->insert(edge);

		//creates alternative branch
		if (alt){
			altEdge = edge;
			trigger = true;
		}

	}

}


