//related
//c
//std
#include <iostream>
#include <iterator>
//lib
//user 
#include "graph.hpp"
#include "graph-algorithm/bfs.hpp"
#include "graph-algorithm/dfs.hpp"
#include "graph-display/outputter.hpp"





template<   class Data>
std::ostream& operator<<(std::ostream& out, const component::UndirectedEdge<Data>& inEdge)
{
	out << "	(" << inEdge.First().Id() << ", " << inEdge.Second().Id() << ")";

	return out;
}





int main(int argc, char* argv[])
{
	// initialize graph
	component::Vertex<int> testVrtx1(1);
	component::Vertex<int> testVrtx2(2);
	component::Vertex<int> testVrtx3(3);
	component::Vertex<int> testVrtx4(4);

	graph::Graph<int, component::UndirectedEdge> testGraph1;


	std::cout << "Size of an empty graph object - " << sizeof(testGraph1) << std::endl;


	testGraph1.AddVertex(testVrtx1);
	testGraph1.AddVertex(testVrtx2);
	testGraph1.AddVertex(testVrtx3);
	testGraph1.AddVertex(testVrtx4);

	testGraph1.AddEdge(testVrtx1, testVrtx2);
	testGraph1.AddEdge(testVrtx2, testVrtx3);
	testGraph1.AddEdge(testVrtx3, testVrtx1);
	testGraph1.AddEdge(testVrtx1, testVrtx4);


	std::cout << "Size of an assembled graph object - " << sizeof(testGraph1) << std::endl;


	// check graph's contents
	testGraph1.print();
	
	

	
	pathsearch::BFS<int, component::UndirectedEdge> bfsTest1(testGraph1); 
	std::cout << "Size of an empty BFS algorithm object - " << sizeof(bfsTest1) << std::endl;	
	
	std::cout << "Testing BFS:" << std::endl;
	bfsTest1.Execute(testGraph1.GetVertex(2));
	auto bfsResult1 = bfsTest1.Result();

	for(auto iter = bfsResult1.begin(); iter != bfsResult1.end(); ++iter)
		std::cout << iter->Id() << " -> ";

	std::cout << "X" << std::endl;
	std::cout << "Size of an assembled BFS algorithm object - " << sizeof(bfsTest1) << std::endl;



	pathsearch::DFS<int, component::UndirectedEdge> dfsTest1(testGraph1);
	std::cout << "Size of an empty DFS algorithm object - " << sizeof(dfsTest1) << std::endl;

	std::cout << "Testing DFS:" << std::endl; 
	dfsTest1.Execute(testGraph1.GetVertex(2));
	auto dfsResult1 = dfsTest1.Result();

	for(auto iter = dfsResult1.begin(); iter != dfsResult1.end(); ++iter)
		std::cout << iter->Id() << " -> ";

	std::cout << "X" << std::endl;
	std::cout << "Size of an assembled DFS algorithm object - " << sizeof(dfsTest1) << std::endl;
	/**/
	
	outputter::Outputter testOutputter;

  	return 0;
}