#ifndef THINGS
#define THINGS

#include <string>

enum symbol {
	CS,
	MA,
	STAT

};

enum Side{
	TRACK,
	COURSE

};

enum COLOR{
	CSE = 0, CGV=1, MI=2, DBIS=3, FCS=4, SoftEngr=5, Systems=6, PL=7, Security=8

};


class Track{
	public:
		std::string trackString;
		//t
		Track(char * c);

		int reqCounter;

};

class Course{
	public:
		std::string courseString;
		int courseNumber;
		symbol department;

		int totalCounter;
		Course(char * e, int n, symbol co);
		void print();

};

class Node;

class Edge{
	public:
//		Track * t;
//		Course * c;

		Node * trackNode;
		Node * courseNode;
		COLOR color;
		//Course * ac;
		Node * twinNode;
		bool req;

		Edge(Node * tr, Node * course, bool b);
		Edge(Node * tr, Node * course, Node * altCourse, bool b);
		void print();
		~Edge();

};

class List;
class ListNode;

class Node{
	public:
		List * edgeList;
		//e

		Course * course;
		Track * track;

		Node(Course * c);
		Node(Track * t);
		int edgeCounter;
		void add(Edge * edge);

};

class Tree{
	public:
		Node ** nodes;
		Side side;

};

class DoubleTree{
	public:
		Tree *leftTree;
		Tree *rightTree;

};

class ListNode{
	public:
		Edge * edge;
		ListNode * next;
		ListNode * prev;

		void print();
		ListNode(Edge * e);
		ListNode();
		~ListNode();

};

class List{

	public:
		ListNode * head;
		ListNode * tail;


		List();
		~List();
		void insert(Edge * e);
		void insert();
		void print();
		void printp();
		void printc();

};

class Stack{

	public:
		int current;
		int size;

		Course ** stack;

		bool add(Course * course);
		void reSize();
		bool contains(Course * target);
		Stack();
		~Stack();
		void print();



};

int getTrackNumber(char * c);

#endif
