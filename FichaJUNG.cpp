#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>

void exercicio1();
void exercicio2();
void exercicio3();


void exercicio1()
{
	int idNo0 = 0;
	int idNo1 = 1;
	int idNo2 = 2;
	int idEdge;

	GraphViewer *gv = new GraphViewer(600, 600, true); //janela 600x600
	gv->setBackground("background.jpg"); //meter uma imagem como fundo
	gv->createWindow(600, 600);

	gv->defineVertexColor("blue"); //cor dos nos
	gv->defineEdgeColor("black");//cor das arestas

	gv->addNode(idNo0);
	gv->rearrange(); //novas alteracoes no grafo

	gv->addNode(idNo1);
	gv->addEdge(idEdge, idNo0, idNo1, EdgeType::UNDIRECTED); //aresta bidirecional
	//gv->addEdge(idEdge, idNo1, idNo2, EdgeType::DIRECTED); //aresta direcional
	gv->rearrange();

	gv->removeNode(idNo0); //remover no

	gv->addNode(idNo2);
	gv->rearrange();

	gv->addEdge(idEdge, idNo1, idNo2, EdgeType::UNDIRECTED);
	
	gv->setVertexLabel(idNo1, "Isto e um no"); //legenda para um no
	gv->setVertexColor(idNo2, "green"); //cor de um no especifico

	gv->setEdgeColor(idEdge, "yellow"); //cor de uma aresta especifica


}

void exercicio2()
{
	GraphViewer *gv = new GraphViewer(600, 600, false); //falso para se definir os nos
	
	gv->addNode(0,300,50);
	gv->addNode(1,318,58);
	gv->addNode(2,325,75);
	gv->addNode(3,318,93);
	gv->addNode(4,300,100);
	gv->addNode(5,282,93);
	gv->addNode(6,275,75);
	gv->addNode(7,282,58);

	gv->addEdge(0, 0, 1, EdgeType::UNDIRECTED);
	gv->addEdge(1, 1, 2, EdgeType::UNDIRECTED);
	gv->addEdge(2, 2, 3, EdgeType::UNDIRECTED);
	gv->addEdge(3, 3, 4, EdgeType::UNDIRECTED);
	gv->addEdge(4, 4, 5, EdgeType::UNDIRECTED);
	gv->addEdge(5, 5, 6, EdgeType::UNDIRECTED);
	gv->addEdge(6, 6, 7, EdgeType::UNDIRECTED);
	gv->addEdge(7, 7, 0, EdgeType::UNDIRECTED);
	gv->addEdge(8, 4, 9, EdgeType::UNDIRECTED);
	gv->addEdge(9, 9, 8, EdgeType::UNDIRECTED);
	gv->addEdge(10, 9, 11, EdgeType::UNDIRECTED);
	gv->addEdge(12, 11, 12, EdgeType::UNDIRECTED);
	gv->addEdge(13, 11, 13, EdgeType::UNDIRECTED);

	gv->removeNode(12);
	gv->removeNode(13);
	Sleep(30);
	gv->addNode(14, 250, 550);
	gv->addNode(15, 350, 550);

}

void exercicio3()
{
	int idNode = 0, X = 0, Y = 0;
	int idEdge = 0, idOriginNode = 0, idDestinyNode = 0;
	ifstream inFile;
	string line;

	GraphViewer *gv = new GraphViewer(1000, 600, false);
	gv->createWindow(1000, 600);

	gv->defineEdgeColor("green");
	gv->defineVertexColor("blue");
	
	inFile.open("nodes.txt");
	
	if (!inFile) {
		cerr << "Unable to open the input file";
		exit(1);
	}

	
	while (getline(inFile, line)) {
		
		stringstream linestream(line);
		string data;

		linestream >> idNode;
		getline(linestream, data, ';'); //le ate ao primeiro ; e nao fica com ele
		linestream >> X;
		getline(linestream, data, ';');
		linestream >> Y;
		gv->addNode(idNode, X, Y);

	}

	inFile.close();


	inFile.open("edges.txt");

	if (!inFile) {
		cerr << "Unable to open the input file";
		exit(1);
	}


	while (getline(inFile, line)) {
		
		stringstream linestream(line);
		string data;

		linestream >> idEdge;
		getline(linestream, data, ';'); //le ate ao primeiro ; e nao fica com ele
		linestream >> idOriginNode;
		getline(linestream, data, ';');
		linestream >> idDestinyNode;
		gv->addEdge(idEdge, idOriginNode, idDestinyNode , EdgeType::UNDIRECTED);

	}
	
	inFile.close();

	gv->rearrange();
}


int main() {
	//exercicio1();
	//exercicio2();
	//exercicio3();
	getchar();
	return 0;
}
