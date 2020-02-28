#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include "Node.h"
#include <vector>

using namespace std;

Node::Node(NodeTranslation tr, NodeRotation r, Node* parent, Quad q)
{
	translation = tr;
	rotation = r;

	parentNode = parent;
	if (parent != nullptr)
	{
		//TODO: Check if the child node is already added
		parent->addChildNode(this);
	}

	highlight = false;
	
	quad = q;
}


void Node::updateTranslation(NodeTranslation tr)
{
	translation = tr;
}

void Node::updateRotation(NodeRotation r)
{
	rotation = r;
}

void Node::addChildNode(Node* c)
{
	childNodes.push_back(c);
}
