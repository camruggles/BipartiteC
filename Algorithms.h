#ifndef ALGORITHMS
#define ALGORITHMS

Node * getNodeByTrackName(Tree * tracks, char * c);
Node * getNodeByCourse(Tree * courses, int num);
void computeCourses(Tree * tracks, int argv[], int argc);
int * getColors(Node * course);
int countActiveColors(int * argv, int argc, Node * course);



#endif
