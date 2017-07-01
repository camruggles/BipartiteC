//Create Makefile
#include "Structs.h"
//Linking h files and class files

//86, 96, 101, 179

int getTrackNumber(char * c){
	std::string zach = c;
	if (zach == "CSE") return 0;
	else if (zach == "CGV") return 1;
	else if (zach == "MI") return 2;
	else if (zach == "DBIS") return 3;
	else if (zach == "FCS") return 4;
	else if (zach == "SoftEngr") return 5;
	else if (zach == "Systems") return 6;
	else if (zach == "PL") return 7;
	else if (zach == "Security") return 8;
	return -1;



}




/*
Track
--------------------------------------------------
*/
Track::Track(char * c){
	trackString = c;
	reqCounter = 0;
}



/*
Course
--------------------------------------------------
*/
Course::Course(char * e, int n, symbol co){
	courseString = e;
	courseNumber = n;
	department = co;
	totalCounter = 0;

}

void Course::print(){
	char * prefix;
	
	switch(department){
		case CS: prefix = strdup("CS"); break;
		case MA: prefix = strdup("MA"); break;
		case STAT: prefix = strdup("STAT"); break;
	}

	printf("%s, %d, %s\n", prefix, courseNumber, courseString.c_str());

}


/*
Edge
--------------------------------------------------
*/

Edge::Edge(Node * tr, Node * course, bool b){
	courseNode = course;
	trackNode  = tr; 
	twinNode = NULL;
	req = b;
	color = (COLOR) getTrackNumber(strdup(tr->track->trackString.c_str()));


}

Edge::Edge(Node * tr, Node * course, Node * altCourse, bool b){
	courseNode = course;
	twinNode = altCourse;
	req = b;
	trackNode = tr;

}

void
Edge::print(){
	printf("%d, %s, %p, %p\n", (int) color, courseNode->course->courseString.c_str(), (void*) trackNode, (void*)courseNode);	

}

Edge::~Edge(){
//	if (twinNode != NULL){
//		twinNode = NULL;
//	}
printf("You can't delete an edge");	
}

/*
List Node
--------------------------------------------------
*/
ListNode::ListNode(Edge * e){
	edge = e;

}

ListNode::ListNode(){}

void ListNode::print(){
	edge->print();
}

ListNode::~ListNode(){
	ListNode * n = next, *p = prev;
	n->prev = p;
	p->next = n;
	//if (edge != NULL)
	//delete edge;

}  //recursive deletion?



/*
Node
--------------------------------------------------
*/
Node::Node(Course * c){
	course = c;
	track = NULL;
	edgeList = new List();
	edgeCounter = 0;
}

Node::Node(Track * t){
	track = t;
	course = NULL;
	edgeList = new List();
	edgeCounter = 0;
}

void Node::add(Edge * edge){
	edgeList->insert(edge);	
	edgeCounter++;
}




/*
List
--------------------------------------------------
*/


List::	List(){
	head = new ListNode(NULL);
	tail = new ListNode(NULL);
//	printf("Head:%p\n Tail:%p\n", (void*)head, (void*)tail);
	head->prev = NULL;
	head->next = tail;
	tail->prev = head;
	tail->next = NULL;

}

void List::insert(Edge * e){

	ListNode * n = new ListNode(e);
	ListNode * p;
	p = tail->prev;

	n->prev = p;
	n->next = tail;
	p->next = n;
	tail->prev = n;
}

void List::insert(){
	ListNode * n = new ListNode();
	ListNode * p;
	p = tail->prev;

	n->prev = p;
	n->next = tail;
	p->next = n;
	tail->prev = n;

}

void List::print(){
	printf("head: %p\n", (void*)head);
//	return;
	ListNode * c = head->next;
	int i = 0;
	while (c != tail){
		
		printf("i: %d\nPrev: %p\nNext: %p\n\n", i++, (void *) c->prev, (void*) c->next);
		c = c->next;
	
	}

	printf("tail: %p\n", (void*)tail);

}

void List::printp(){
	ListNode * c = head->next;
	while (c != tail){
		printf("Track : %p\nCourse : %p\n\n", (void*)c->edge->trackNode, (void*)c->edge->courseNode); 	
		c = c->next;
	}
}

void List::printc(){
	ListNode * c = head->next;
	while (c != tail){
		printf("Track : %s\nCourse : %s\n\n", strdup(c->edge->trackNode->track->trackString.c_str()), strdup(c->edge->courseNode->course->courseString.c_str())); 	
		c = c->next;
	}


}

List::~List(){
	ListNode * n = head->next;
	ListNode *l;
	while (n != tail){
		l = n;	
		n = n->next;
		delete l;
		l = NULL;
	}
	delete head;
	delete tail;

}

/*
///---------------------------------------------
Stack
*/

Stack::Stack(){
	size = 20;
	stack = new Course*[size];
	current = -1;
}

bool Stack::add(Course * course){
	if (!contains(course)){
		if (current == (size-1)){
			reSize();
		}
		stack[++current] = course;
		return true;
	}

	return false;

}

void Stack::reSize(){
	size *= 2;
	Course ** newStack;
	newStack = new Course*[size];
	for (int i = 0; i <= current; i++){
		newStack[i] = stack[i];
	
	}

	delete [] stack;
	stack = newStack;
	

}

bool Stack::contains(Course * target){
	if (current == -1){
		return false;
	}

	for (int i = 0; i <= current; i++){
		if (target == stack[i]){
			return true;
		
		}
	
	}

	return false;

}

void Stack::print(){
	if (current == -1){
		printf("Stack is empty\n");
		return;
	
	}
	printf("%d\n", current+1);
	for (int i = 0; i <= current; i++){
		printf("%s\n", stack[i]->courseString.c_str());
	}

}




