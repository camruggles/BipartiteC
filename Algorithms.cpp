#include "Structs.h"


Node * 
getNodeByTrackName(Tree * tracks, char * c){
	int i = 0;
	if ((i = getTrackNumber(c)) == -1)
		return NULL;
	return tracks->nodes[i];

}

Node * getNodeByCourse(Tree * courses, int num){
	return courses->nodes[num];

}


/*
Used in the main computation
Checks to see if enough electives have been selected to complete a track.


*/
bool checkCounters (int * counters){
	for (int i = 0; i < 9; i++){
		if (counters[i] > 0)
			return false;

	}
	return true;

}

/*
takes a int[] counters, which contains an array that dictates how many electives are still needed to complete a course
and decrements counters by int[] dec, 
all fields in dec[] are 0 or 1
the array subtraction decrements by 0 or 1 at each index for each course
*/
void decrementColors(int * counters, int * dec){
	for (int i = 0; i < 9; i++){
		counters[i] -= dec[i];

	}

	for (int i = 0; i < 9; i++){
		printf("%d: %d |||| ", i, counters[i]);
	}
	printf("\n");

}



/*
based on the track input from the commmand line, this will determine how many active tracks that a given course falls under

this is essentially the degree of a course node in the bipartite graph.  A higher degree node is selected sooner since it will fulfill requirements for more tracks
returns an int witht he number of active tracks that this course satisfies.
an active track is one of the tracks entered at command line
*/
int countActiveColors(int * argv, int argc, Node * course){
	List * l = course->edgeList;
	ListNode * ln = l->head->next;
	COLOR cobol = CSE;
	int counter = 0;
	while (ln != l->tail){
		cobol = ln->edge->color;
		for (int i = 0; i < argc; i++)
			if (cobol == argv[i]){
				++counter;
			}

		ln = ln->next;
	}

	return counter;
}


/*
this will return a int[] of size 9;
the indices of the array correspond to a track
if a track is involved with the course, than the int value at that tracks index will be a 1.

The enumeration for the tracks can be found in structs.cpp or structs.h

*/
int * getColors(Node * course){
	int * r = new int[9];

	for (int i = 0; i < 9; i++){
		r[i] = 0;

	}

	List * l = course->edgeList;
	ListNode * ln = l->head->next;
	int j = 0;
	while (ln != l->tail){
		j = ln->edge->color;
		++r[j];
		ln = ln->next;
	}
	return r;

}


//countColors();
//getColors();
void computeCourses(Tree * tracks, int * argv, int argc){
	Stack * lisp = new Stack();
	List * l;
	ListNode * ln;
	Node * node;

	int c[] = {7, 6, 6, 7, 6, 6, 6, 6, 6};
	int counters[] = {0,0,0,0,0,0,0,0,0};
	int a = 0, b = 0;

	for (int i = 0; i < argc; i++){
		counters[argv[i]] = c[argv[i]];
	}

	//implement a counter array and read the counters from tracks to setup countdowns

	//this loop adds required courses to the mix

	//this for loop iterates through the selected tracks
	for (int i = 0; i < argc; i++){
		l = tracks->nodes[argv[i]]->edgeList;
		ln = l->head->next;
		//this loop iterates through courses in a track
		while (ln != l->tail){

			if (ln->edge->req ){ 
				//this branch executes if the course isn't an alternative situation, 
				if (ln->edge->twinNode == NULL){	

					if (lisp->add(ln->edge->courseNode->course)){
						printf("%s, %d\n", ln->edge->courseNode->course->courseString.c_str(), countActiveColors(argv, argc, ln->edge->courseNode));
						int * cameron = getColors(ln->edge->courseNode);
						decrementColors(counters, cameron);
						delete [] cameron;


					}
				}
				//this branch executes if the course has an alternative choice
				else{
					//if there are alternative courses, (for SoftEngr track, you can use compilers or OS as the track elective)
					a = countActiveColors(argv, argc, ln->edge->courseNode);
					b = countActiveColors(argv, argc, ln->edge->twinNode);
				//these code blocks execute based on which alternative course has a greater degree
					if (a > b) {
						if (lisp->add(ln->edge->courseNode->course)){

							printf("%s, %d\n", ln->edge->courseNode->course->courseString.c_str(), a);
							int * cameron = getColors(ln->edge->courseNode);
							decrementColors(counters, cameron);
							delete [] cameron;
						}

					}
					else {
						if (lisp->add(ln->edge->courseNode->course)){
							printf("%s, %d\n", ln->edge->courseNode->course->courseString.c_str(), b);
							int * cameron = getColors(ln->edge->courseNode);
							decrementColors(counters, cameron);
							delete [] cameron;
						}

					}

					//this is a double increment so it skips an alternative track and moves on to the next course
					ln = ln->next;
				}
			}	
			ln = ln->next;
		}
	}
//checks to see if all of the required courses satisfy all the elective requirements
	if (checkCounters(counters)) goto terminal;

	//this iterates through several times to get courses of a higher degree added to the list first
	for (int i = 0;i < argc; i++){
		printf("%d\n", argc-i);

		//this for loop iterates through the tracks
		for (int j = 0; j < argc; j++){

			//this measure ensures that a track is skipped as soon as all the electives are met
			if (counters[ argv[j] ] <= 0){
				continue;
			}

			l = tracks->nodes[argv[j]]->edgeList;
			ln = l->head->next;

			//this while loop iterates through courses in a track
			while (ln != l->tail){
				
				node = ln->edge->courseNode;
				//this also makes sure that a track is skipped once enough electives are met
				if (counters[ argv[j]] <= 0) break;
				
				//tests to see if it is an alternative course that wasn't added, or a regular elective course
				//also tests to make sure it has the highest node degree
				if ((ln->edge->twinNode != NULL ||  !ln->edge->req) && (countActiveColors(argv, argc, node) == argc - i)      ){

					//this will add the course to the list
					printf("%s, %d\n", node->course->courseString.c_str(), countActiveColors(argv, argc, node));
					if (lisp->add(ln->edge->courseNode->course)){
						//printf("%s\n", ln->edge->courseNode->course->courseString.c_str());
						int * cameron = getColors(ln->edge->courseNode);
						decrementColors(counters, cameron);
						delete [] cameron;
						if (checkCounters(counters)) goto terminal;


					}
				}	

				ln = ln->next;
			}



		}

	}

terminal:
	printf("\n\n");
	lisp->print();

}









