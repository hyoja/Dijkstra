
#define INFINITY 9999
#define SIZEOFINDEX 9
#define false 0
#define true  1

typedef struct tuple
{
	int arrayIndex;
	char NameOfNode[9];
	struct Tuple* nextTuple;
}Tuple;

typedef struct tupleList
{
	int size;
	Tuple tulpleHead;
}TupleList;
