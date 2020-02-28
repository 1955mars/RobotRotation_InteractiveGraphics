#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <iostream>
#include <math.h>

#include "Node.h"

using namespace std;

int win_width = 640;
int win_height = 480;
float canvas_width = 20.0f; float canvas_height = 20.0f;

Node* rootNode = nullptr;

Node* currSelectNode = nullptr;
int selectSiblingIndex = 0;
int numSiblings = 0;


void SelectNode(Node* n)
{
    if (currSelectNode)
        currSelectNode->highlight = false;
    currSelectNode = n;
    currSelectNode->highlight = true;
}

void CreateBodyParts()
{
    NodeTranslation nTr = { 0.0f, 0.0f };
    NodeRotation nR = 0.0f;
   
    Quad qLowerBody = { -1.5f, 1.5f, 2.0f, 0.0f };
    Node* lowerBody = new Node(nTr, nR, nullptr, qLowerBody);
    rootNode = lowerBody;
 
    nTr.x = 1.0f; nTr.y = 0.0f;
    Quad qRightThigh = { -0.5f, 0.5f, 0.0f, -2.0f };
    Node* rightThigh = new Node(nTr, nR, lowerBody, qRightThigh);

    nTr.x = -1.0f; nTr.y = 0.0f;
    Quad qLeftThigh = { -0.5f, 0.5f, 0.0f, -2.0f };
    Node* leftThigh = new Node(nTr, nR, lowerBody, qLeftThigh);

    nTr.x = 0.0f; nTr.y = 2.0f;
    Quad qUpperBody = { -2.5f, 2.5f, 2.0f, 0.0f };
    Node* upperBody = new Node(nTr, nR, lowerBody, qUpperBody);

    nTr.x = 0.0f; nTr.y = -2.0f;
    Quad qRightLeg = { -0.5f, 0.5f, 0.0f, -2.0f };
    Node* rightLeg = new Node(nTr, nR, rightThigh, qRightLeg);

    nTr.x = 0.0f; nTr.y = -2.0f;
    Quad qleftLeg = { -0.5f, 0.5f, 0.0f, -2.0f };
    Node* leftLeg = new Node(nTr, nR, leftThigh, qleftLeg);

    nTr.x = 0.0f; nTr.y = 2.0f;
    Quad qNeck = { -0.25f, 0.25f, 1.0f, 0.0f };
    Node* neck = new Node(nTr, nR, upperBody, qNeck);

    nTr.x = 2.5f; nTr.y = 1.0f;
    Quad qRightArm = { 0.0f, 2.0f, 0.5f, -0.5f };
    Node* rightArm = new Node(nTr, nR, upperBody, qRightArm);

    nTr.x = -2.5f; nTr.y = 1.0f;
    Quad qLeftArm = { -2.0f, 0.0f, 0.5f, -0.5f };
    Node* leftArm = new Node(nTr, nR, upperBody, qLeftArm);

    nTr.x = 0.0f; nTr.y = -2.0f;
    Quad qRightFoot = { -0.5f, 1.5f, 0.0f, -1.0f };
    Node* rightFoot = new Node(nTr, nR, rightLeg, qRightFoot);

    nTr.x = 0.0f; nTr.y = -2.0f;
    Quad qLeftFoot = { -1.5f, 0.5f, 0.0f, -1.0f };
    Node* leftFoot = new Node(nTr, nR, leftLeg, qLeftFoot);

    nTr.x = 0.0f; nTr.y = 1.0f;
    Quad qHead = { -1.0f, 1.0f, 2.0f, 0.0f };
    Node* head = new Node(nTr, nR, neck, qHead);

    nTr.x = 2.0f; nTr.y = 0.0f;
    Quad qRightForeArm = { 0.0f, 2.0f, 0.5f, -0.5f };
    Node* rightForeArm = new Node(nTr, nR, rightArm, qRightForeArm);

    nTr.x = -2.0f; nTr.y = 0.0f;
    Quad qLeftForeArm = { -2.0f, 0.0f, 0.5f, -0.5f };
    Node* leftForeArm = new Node(nTr, nR, leftArm, qLeftForeArm);

    nTr.x = 2.0f; nTr.y = 0.0f;
    Quad qRightHand = { 0.0f, 1.5f, 0.75f, -0.75f };
    Node* rightHand = new Node(nTr, nR, rightForeArm, qRightHand);

    nTr.x = -2.0f; nTr.y = 0.0f;
    Quad qLeftHand = { -1.5f, 0.0f, 0.75f, -0.75f };
    Node* leftHand = new Node(nTr, nR, leftForeArm, qLeftHand);

    SelectNode(rootNode);
 
}


void drawQuad(Quad q, bool select)
{
    if (select)
    {
        glColor3f(1.0f, 0.0f, 0.0f);
        glLineWidth(3.0f);
    }
    else
    {
        glColor3f(0.0f, 0.0f, 0.0f);
        glLineWidth(1.5f);
    }
    glBegin(GL_LINE_LOOP);
    glVertex2f(q.left, q.bottom);
    glVertex2f(q.left, q.top);
    glVertex2f(q.right, q.top);
    glVertex2f(q.right, q.bottom);
    glEnd();
    glLineWidth(1.0f);
}

void DrawNodes(Node* n)
{
    glTranslatef(n->translation.x, n->translation.y, 0.0f);
    glRotatef(n->rotation, 0.0f, 0.0f, 1.0f);

    drawQuad(n->quad, n->highlight);
    for (int i = 0; i < n->childNodes.size(); i++)
    {
        glPushMatrix();
        DrawNodes(n->childNodes[i]);
        glPopMatrix();
    }
}

void display(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    DrawNodes(rootNode);
    
    glutSwapBuffers();
}


void reshape(int w, int h)
{
    win_width = w;
    win_height = h;

    //cout << "w = " << w << " h = " << h << endl;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-canvas_width / 2.0f, canvas_width / 2.0f, -canvas_height / 2.0f, canvas_height / 2.0f);
    glViewport(0, 0, (GLsizei)win_width, (GLsizei)win_height);

    glutPostRedisplay();
}

void arrowInputs(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        if (currSelectNode->parentNode)
        {
            SelectNode(currSelectNode->parentNode);
        }
        else
        {
            cout << "No parent node" << endl;
        }
        break;

    case GLUT_KEY_DOWN:
        selectSiblingIndex = 0;
        if (currSelectNode->childNodes.size() > 0)
        {
            SelectNode((currSelectNode->childNodes)[selectSiblingIndex]);
        }
        else
        {
            cout << "No children nodes" << endl;
        }
        break;

    case GLUT_KEY_LEFT:
        if (currSelectNode == rootNode)
            break;

        numSiblings = currSelectNode->parentNode->childNodes.size();
        if (numSiblings <= 0)
            break;

        selectSiblingIndex--;
        if (selectSiblingIndex < 0)
        {
            selectSiblingIndex = numSiblings - 1;
        }
        SelectNode(currSelectNode->parentNode->childNodes[selectSiblingIndex]);
        break;

    case GLUT_KEY_RIGHT:
        if (currSelectNode == rootNode)
            break;

        numSiblings = currSelectNode->parentNode->childNodes.size();
        if (numSiblings <= 0)
            break;

        selectSiblingIndex++;
        if (selectSiblingIndex == numSiblings)
        {
            selectSiblingIndex = 0;
        }
        SelectNode(currSelectNode->parentNode->childNodes[selectSiblingIndex]);
        break;

    case GLUT_KEY_CTRL_L:
        cout << "Control left pressed" << endl;
        currSelectNode->rotation += 6.0f;
        break;

    case GLUT_KEY_CTRL_R:
        cout << "Control right pressed" << endl;
        currSelectNode->rotation -= 6.0f;
        break;

    }
    glutPostRedisplay();
}


int main(int argc, char* argv[])
{
    CreateBodyParts();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(win_width, win_height);
    glutCreateWindow("Humanoid Robot");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);

    glutSpecialFunc(arrowInputs);

    glutMainLoop();
    return 0;

}