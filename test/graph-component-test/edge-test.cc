#include "gtest/gtest.h"					//gtest
#include "graph-component/vertex.hpp"		//helper component
#include "graph-component/edge.hpp"			//component to test
//
#include <vector>							//
#include <string>							//
#include <algorithm>						//std::copy
#include <iterator>							//std::back_inserter





// define test fixture
template<	class Data>
class EdgeTest : public testing::Test
{
protected:
	//required functions
	void 	SetUp() 	override
	{
		// # of elements
		count_ = 20;	
	}

	void 	TearDown() 	override
	{	}

public:
	std::vector<component::Vertex<Data>> 			vertices_;
	std::vector<component::UndirectedEdge<Data>> 	container1_;
	std::vector<component::UndirectedEdge<Data>> 	container2_;
	int 											count_;
};
//





//	Using parametrized tests for component::Vertex
#if GTEST_HAS_TYPED_TEST

using testing::Types;



// Declare which types are going to be used
typedef Types<int, char> IndeciesTypes;



// declare what test fixture uses which types
TYPED_TEST_SUITE(EdgeTest, IndeciesTypes);





//
// Tests
//

// Default constructor test
TYPED_TEST(EdgeTest, DataConstructor) 
{
	//initialize
	for(int i = 0; i < this->count_; ++i)
	{
		this->vertices_.emplace_back(i);
	}
	for(int i = 0; i < this->count_ - 1; ++i)
	{
		this->container1_.emplace_back(this->vertices_[i], this->vertices_[i+1]);
	}
	//assert
	for(int i = 0; i < this->count_ - 1; ++i)
	{
		ASSERT_EQ(this->container1_[i].First().Id(), i);
		ASSERT_EQ(this->container1_[i].Second().Id(), i+1);
	}
}



// Copy constructor test
TYPED_TEST(EdgeTest, CopyConstructor) 
{
	//initialize
	for(int i = 0; i < this->count_; ++i)
	{
		this->vertices_.emplace_back(i);
	}
	for(int i = 0; i < this->count_ - 1; ++i)
	{
		this->container1_.emplace_back(this->vertices_[i], this->vertices_[i+1]);
	}
	//
	std::copy(this->container1_.begin(), this->container1_.end(), std::back_inserter(this->container2_));
	//assert
	for(int i = 0; i < this->count_ - 1; ++i)
	{
		ASSERT_EQ(this->container2_[i].First().Id(), i);
		ASSERT_EQ(this->container2_[i].Second().Id(), i+1);
	}
}


/*
// assignment operator test
TYPED_TEST(EdgeTest, MoveConstructor) 
{
	//

}
*/
#endif // GTEST_HAS_TYPED_TEST