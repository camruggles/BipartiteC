#ifndef ALGORITHMS
#define ALGORITHMS

Node * getNodeByTrackName(Tree * tracks, char * c);
Node * getNodeByCourse(Tree * courses, int num);

int * getColors(Node * course);
int countActiveColors(int * argv, int argc, Node * course);

void computeTracks(Tree * curriculum, int * courses, int n);
void computeCourses(Tree * tracks, int argv[], int argc);
//void decrementColors();


#endif
