#include "gtest/gtest.h"
#include "graph-component/vertex.hpp"
#include "graph-component/edge.hpp"



TEST(EdgeTestSuite, EdgeVertexConstructorTest) 
{
	// Arrange
	component::Vertex<int> testVertex1(1);
	component::Vertex<int> testVertex2(2);
	component::UndirectedEdge<int> testEdge(testVertex1, testVertex2, 1);
	// Act (in this test arrange and act is merged)
	
	// Assert
	const int expected_weight = 1;
	const int expected_vertex_id_1 = 1;
	const int expected_vertex_id_2 = 2;

	EXPECT_EQ(testEdge.Weight(), expected_weight);
	EXPECT_EQ(testEdge.First().Id(), expected_vertex_id_1);
	EXPECT_EQ(testEdge.Second().Id(), expected_vertex_id_2);
}

TEST(EdgeTestSuite, EdgeCopyConstructorTest)
{
	// Arrange
	component::Vertex<int> testVertex1(1);
	component::Vertex<int> testVertex2(2);
	component::UndirectedEdge<int> testEdge1(testVertex1, testVertex2, 1);
	component::UndirectedEdge<int> testEdge2(testEdge1);

	//Assert
	const int expected_weight = 1;
	const int expected_vertex_id_1 = 1;
	const int expected_vertex_id_2 = 2;

	EXPECT_EQ(testEdge2.Weight(), expected_weight);
	EXPECT_EQ(testEdge2.First().Id(), expected_vertex_id_1);
	EXPECT_EQ(testEdge2.Second().Id(), expected_vertex_id_2);
}