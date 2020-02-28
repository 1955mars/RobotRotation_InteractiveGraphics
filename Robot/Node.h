#pragma once
#include <vector>

using namespace std;


typedef struct _translation
{
	float x;
	float y;
}NodeTranslation;

typedef float NodeRotation;

typedef struct _quad
{
	float left;
	float right;
	float top;
	float bottom;
}Quad;

class Node
{
public: 
	Node* parentNode;
	vector<Node*> childNodes;
	Quad quad;
	bool highlight;

	NodeTranslation translation;
	NodeRotation rotation;

	Node(NodeTranslation tr, NodeRotation r, Node* parent, Quad q);

	void updateTranslation(NodeTranslation tr);
	void updateRotation(NodeRotation r);

	void addChildNode(Node* c);
};