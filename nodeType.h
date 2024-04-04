#ifndef H_NodeType
#define H_NodeType

#include <iostream>
#include <cassert>

using namespace std;

//Definition of the node

template <class Type>
struct nodeType
{
	Type info;
	nodeType<Type>* link;
};

#endif