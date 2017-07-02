#include "Structs.h"

Node * getNodeByTrackName(Tree * tracks, char * c);
Node * getNodeByCourse(Tree * courses, int num);
//int getTrackNumber(char * c);

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


bool checkCounters (int * counters){
	for (int i = 0; i < 9; i++){
		if (counters[i] > 0)
			return false;

	}
	return true;

}

void decrementColors(int * counters, int * dec){
	for (int i = 0; i < 9; i++){
		counters[i] -= dec[i];

	}

	for (int i = 0; i < 9; i++){
		printf("%d: %d |||| ", i, counters[i]);
	}
	printf("\n");

}




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

	for (int i = 0; i < argc; i++){
		l = tracks->nodes[argv[i]]->edgeList;
		ln = l->head->next;

		while (ln != l->tail){

			if (ln->edge->req /*&& ln->edge->twinNode==NULL*/){ 
				//printf("%p\n", (void*)ln->edge->twinNode);

				if (ln->edge->twinNode == NULL){	

					if (lisp->add(ln->edge->courseNode->course)){
						printf("%s\n", ln->edge->courseNode->course->courseString.c_str());
						int * cameron = getColors(ln->edge->courseNode);
						decrementColors(counters, cameron);
						delete [] cameron;


					}
				}
				else{
					a = countActiveColors(argv, argc, ln->edge->courseNode);
					b = countActiveColors(argv, argc, ln->edge->twinNode);
					if (a > b) {
						if (lisp->add(ln->edge->courseNode->course)){

							printf("%s\n", ln->edge->courseNode->course->courseString.c_str());
							int * cameron = getColors(ln->edge->courseNode);
							decrementColors(counters, cameron);
							delete [] cameron;


						}

					}
					else {
						if (lisp->add(ln->edge->courseNode->course)){
							printf("%s\n", ln->edge->courseNode->course->courseString.c_str());
							int * cameron = getColors(ln->edge->courseNode);
							decrementColors(counters, cameron);
							delete [] cameron;


						}

					}
					ln = ln->next;

				}
				//test first node to see if it has other colors and count the degree
				//test second node to see if its required for other colors and count the degree
				//find the max between the two and add the winner to the list.



			}	

			ln = ln->next;
		}
	}

	if (checkCounters(counters)) goto terminal;
	for (int i = 0;i < argc; i++){
        printf("%d\n", argc-i);
		for (int j = 0; j < argc; j++){
			l = tracks->nodes[argv[j]]->edgeList;
			ln = l->head->next;

			while (ln != l->tail){
				node = ln->edge->courseNode;
                
				if ((ln->edge->twinNode != NULL ||  !ln->edge->req) && (countActiveColors(argv, argc, node) == argc - i)      ){
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









