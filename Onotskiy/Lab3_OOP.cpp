//Piven Denys K-21
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glaux.lib")
#pragma comment(lib,"glu32.lib") 

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
#include <ctime>
#include <time.h>
#include <queue>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/GLU.h>
#include <GL/GL.h>
#include"gl/glut.h"
#include"gl/glaux.h"

const int W = 1080;
const int H = 720;
const int eps = 24;
const int seconds = 3;
bool check = true;
bool isOk = false;
int IsTwo = 0;
float x, y;
int type;//type algorithm

int k = 0;//show res
int start;
/*
if flag == 1: draw points
if first GLUT_RIGHT_BUTTON then flag = 2 and  draw line
if second GLUT_RIGHT_BUTTON then flag = 3 and do algorithm
*/
int flag = 1;

std::vector<std::pair<int, int> > points;//(x,y)
std::vector<std::pair<int, int> > lines;

std::map<std::pair<int, int>, int> edge;//set points number 
std::map<int, std::pair<int, int> > edgeconverse;
std::vector<std::vector<bool> > graph;
std::vector<bool> used;


std::vector<std::pair<int, int> > res;


void initGraph() {
	graph.resize(points.size());
	for (int i = 0; i < graph.size(); i++) {
		graph[i].resize(points.size(), 0);
	}
	std::cout << lines.size() << std::endl;
	for (int i = 0; i < lines.size(); i += 2) {
		graph[edge[{lines[i].first, lines[i].second}]][edge[{lines[i + 1].first, lines[i + 1].second}]] = 1;
		graph[edge[{lines[i + 1].first, lines[i + 1].second}]][edge[{lines[i].first, lines[i].second}]] = 1;
	}
	for (int i = 0; i < graph.size(); i++) {
		for (int j = 0; j < graph[i].size(); j++) {
			std::cout << graph[i][j] << " ";
		}
		std::cout << std::endl;
	}
}


void setEdge() {
	for (int i = 0; i < points.size(); i++) {
		edge.insert({ {points[i].first,points[i].second},i });
		edgeconverse.insert({ i,{points[i].first,points[i].second} });
	}
	std::cout << "set edge begin: " << std::endl;
	for (auto it = edge.begin(); it != edge.end(); ++it)
	{
		std::cout << it->first.first << "\t" << it->first.second << " : " << it->second << std::endl;
	}
	std::cout << "set edge end: " << std::endl;
}


void dfs(int v) {
	used[v] = true;
	std::cout << v << std::endl;
	res.push_back({ 0,v });
	for (int i = 0; i < graph[v].size(); i++) {
		if (!used[i] && graph[v][i] == 1) {
			dfs(i);
		}
	}
	res.push_back({ 1,v });
}

void bfs(int start_) {
	std::queue<int> q;
	q.push(start_);
	used[start_] = true;
	res.push_back({ 0,start_ });
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		res.push_back({ 1,v });
		for (int i = 0; i < graph[v].size(); i++) {
			if (!used[i] && graph[v][i]) {
				q.push(i);
				res.push_back({ 0,i });
				used[i] = true;
			}
		}
	}
}

void doAlgorithm() {
	std::cout << "DO ALGORITHM BEGIN" << std::endl;
	setEdge();
	initGraph();
	switch (type) {
	case 1:
	{
		used.resize(points.size(), false);
		dfs(start);
		break;
	}
	case 2:
	{
		used.resize(points.size(), false);
		bfs(start);
		break;
	}
	}

	for (int i = 0; i < res.size(); i++) {
		std::cout << res[i].first << "\t" << res[i].second << std::endl;
	}
	std::cout << "DO ALGORITHM END" << std::endl;
}


void mouse(int button, int state, int mouseX, int mouseY) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && flag == 1) {
		check = true;
		x = mouseX;
		y = H - mouseY;
		points.push_back({ x,y });
		std::cout << x << " " << y << std::endl;
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && flag == 1) {
		check = false;
		flag = 2;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && flag == 2) {
		check = true;
		float dx = mouseX;
		float dy = H - mouseY;

		isOk = false;
		for (int i = 0; i < points.size(); i++) {
			if (abs(dx - points[i].first) <= eps && abs(dy - points[i].second) <= eps) {
				dx = points[i].first;
				dy = points[i].second;
				isOk = true;
			}
		}
		if (lines.size() % 2 == 1 && dx == lines[lines.size() - 1].first && dy == lines[lines.size() - 1].second) isOk = false;
		if (isOk) {
			lines.push_back({ dx,dy });
			++IsTwo;
		}
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && flag == 2) {
		check = false;
		doAlgorithm();
		flag = 3;
	}
	else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && flag == 3 && k < res.size()) {
		check = true;
		if (!res[k].first) {
			glColor3f(0, 1, 1);
			glPointSize(30);
			glBegin(GL_POINTS);
			glVertex2i(edgeconverse[res[k].second].first, edgeconverse[res[k].second].second);
			glEnd();
		}
		else {
			glColor3f(1, 0, 0);
			glPointSize(30);
			glBegin(GL_POINTS);
			glVertex2i(edgeconverse[res[k].second].first, edgeconverse[res[k].second].second);
			glEnd();
		}
		++k;
	}
	glutPostRedisplay();
}

void display() {
	glColor3f(0, 1, 0);

	glPointSize(30);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (float)W, 0.0, (float)H);

	if (check && flag == 1) {
		glBegin(GL_POINTS);
		glVertex2i(x, y);
		glEnd();
	}
	else if (check && flag == 2 && IsTwo % 2 == 0 && IsTwo > 0 && isOk) {
		glColor3f(0, 1, 0);
		glLineWidth(5);
		glBegin(GL_LINES);
		glVertex2i(lines[lines.size() - 1].first, lines[lines.size() - 1].second);
		glVertex2i(lines[lines.size() - 2].first, lines[lines.size() - 2].second);
		glEnd();
	}
	glFlush();
}


int main(int argc, char** argv) {
	std::cin >> type >> start;
	--start;
	glutInit(&argc, argv);
	glutInitWindowSize(W, H);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Window");

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMainLoop();
	return 0;
}
