#ifndef ACTIVITY_H
#define ACTIVITY_H

// =========================================================
// File: actitivy.h
// Author: Misael Jiménez Hernández
// Date: 18 de Noviembre del 2020
// =========================================================

#include "ugraph.h"
#include "array"

template <class Vertex>
void dfs2(Vertex v, const UnweightedGraph<Vertex>* graph,
    std::set<Vertex> &reached, std::stack<Vertex> &TS) {
	typename std::set<Vertex>::iterator itr;
  
  reached.insert(v);
  std::set<Vertex> connected = graph -> getConnectionFrom(v);
  for(itr = connected.begin(); itr != connected.end(); itr++){
  	if(reached.find(*itr)== reached.end()){
  		dfs2(*itr, graph, reached, TS);
	  }
  }
  TS.push(v);
}

template <class Vertex>
std::string topologicalSort(const UnweightedGraph<Vertex>* graph) {
  typename std::vector<Vertex>::iterator itr;
  std::stringstream aux;
  std::set<Vertex> visited;
  std::stack<Vertex> pending;
  
  std::vector<Vertex> vtx = graph->getVertexes();
  
  for(itr = vtx.begin(); itr != vtx.end(); itr++){
  	if(visited.find(*itr) == visited.end()){
  		dfs2(*itr, graph, visited, pending);
	  }
  }
  
  aux<< "[";
  while(pending.size() !=0){
  	aux << pending.top();
  	pending.pop();
  	if(pending.size() > 0){
  		aux << " ";
	  }
  }
  aux << "]";

  
  return aux.str();
}

template <class Vertex>
bool isBipartite(const UnweightedGraph<Vertex>* graph) {
  typename std::vector<Vertex>::iterator itr;
  typename std::set<Vertex>::iterator j;
  
  std::vector<Vertex> vertexes = graph -> getVertexes();
  std::queue<Vertex> Queue;
  std::vector<int> Color(vertexes.size(), -1);
  itr = vertexes.end() -1;
  Color[*itr] = 1;
  Queue.push(*itr);
  Vertex v;
  while(!Queue.empty()){
  	v = Queue.front();
  	Queue.pop();
  	std::set<Vertex> connected = graph -> getConnectionFrom(v);
  	for(j = connected.begin(); j != connected.end(); j++){
  		if(Color[*j]== -1){
  			Color[*j] =1 - Color[v];
  			Queue.push(*j);
		  }
		  else if(Color[*j] == Color[v]){
		  	return false;
		  }
	  }
  }
  return true;
}

template <class Vertex>
bool isCyclic(Vertex v, const UnweightedGraph<Vertex>* graph,
  std::set<Vertex> &reached, Vertex parent) {
  typename std::set<Vertex>::iterator itr;
  reached.insert(v);
  std::set<Vertex> connected = graph -> getConnectionFrom(v);
  for(itr = connected.begin(); itr != connected.end(); itr++){
  	if(reached.find(*itr) == reached.end()){
  		if(isCyclic(*itr, graph, reached, parent)){
  			return true;
		  }
	  }
	  else if(*itr != parent){
	  	return true;
	  }
  }
  return false;
}

template <class Vertex>
bool isTree(const UnweightedGraph<Vertex>* graph) {
  typename std::vector<Vertex>::iterator itr;
  std::set<Vertex> reached;
  std::vector<Vertex> vertexes = graph ->getVertexes();
  itr = vertexes.begin();
  Vertex p = 0;
  if(isCyclic(*itr, graph, reached, p)){
  	return false;
  }
  for(itr = vertexes.begin(); itr != vertexes.end(); itr++){
  	if(reached.find(*itr) == reached.end()){
  		return false;
	  }
  }

  return true;
}

#endif /* ACTIVITY_H */
