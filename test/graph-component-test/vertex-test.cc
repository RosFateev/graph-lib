#include "gtest/gtest.h"
#include "graph-component/vertex.hpp"
#include <vector>



TEST(VertexTestSuite, VertexIntConstructorTest) 
{
	// Arrange
	const int size = 4;

	std::vector<component::Vertex<int>> dataHolder = { component::Vertex<int>(0),
	                                                   component::Vertex<int>(1),
	                                                   component::Vertex<int>(2),
	                                                   component::Vertex<int>(3) };

	// Act
	const int expected_value [] = { 0, 1, 2, 3 };

	// Assert
	for(int i = 0; i < size; i++)
		EXPECT_EQ(dataHolder[i].Id(), expected_value[i]);
}

TEST(VertexTestSuite, VertexCopyConstructorTest) 
{
	// Arrange
	component::Vertex<int> testVertex1(1);
	component::Vertex<int> testVertex2(testVertex1);

	// Act (in this test arrange and act is merged)
	
	// Assert
	EXPECT_EQ(testVertex1.Id(), testVertex2.Id());
}


TEST(VertexTestSuite, VertexAssignmentOperatorTest) 
{
	// Arrange
	std::vector<component::Vertex<int>> dataHolder = { component::Vertex<int>(0),
	                                                   component::Vertex<int>(1),
	                                                   component::Vertex<int>(2),
	                                                   component::Vertex<int>(3) };

	// Act (in this test arrange and act is merged)
	dataHolder[0] = dataHolder[1];
	dataHolder[3] = dataHolder[2] = dataHolder[1]; 
	
	// Assert
	for(int i = 0; i < 4; i++)
		EXPECT_EQ(dataHolder[i].Id(), dataHolder[1].Id());
}