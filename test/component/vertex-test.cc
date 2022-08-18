#include "gtest/gtest.h"					//gtest
#include "graph-component/vertex.hpp"		//component to test
//
#include <vector>							//
#include <string>							//
#include <algorithm>						//std::copy
#include <iterator>							//std::back_inserter





// define test fixture
template<	class id_type>
class VertexTest : public testing::Test
{
	using vertex_type = component::Vertex<id_type>;

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
	std::vector<vertex_type> 	container1_;
	std::vector<vertex_type> 	container2_;
	std::vector<vertex_type> 	container3_;
	int 						count_;
};
//





//	Using parametrized tests for component::Vertex
#if GTEST_HAS_TYPED_TEST

using testing::Types;



// Declare which types are going to be used
typedef Types<int, char> IndeciesTypes;



// declare what test fixture uses which types
TYPED_TEST_SUITE(VertexTest, IndeciesTypes);





//
// Tests
//

// Default constructor test
TYPED_TEST(VertexTest, DataConstructor) 
{
	//initialize
	for(int i = 0; i < this->count_; ++i)
	{
		this->container1_.emplace_back(i);
	}
	//assert
	for(int i = 0; i < this->count_; ++i)
	{
		ASSERT_EQ(this->container1_[i].Id(), i);
	}
}



// Copy constructor test
TYPED_TEST(VertexTest, CopyConstructor) 
{
	//initialize first
	for(int i = 0; i < this->count_; ++i)
	{
		this->container1_.emplace_back(i);
	}
	//initialize second
	std::copy(this->container1_.begin(), this->container1_.end(), std::back_inserter(this->container2_));

	//assert
	for(int i = 0; i < this->count_; ++i)
	{
		ASSERT_EQ(this->container2_[i].Id(), i);
	}
}



/*
// assignment operator test
TYPED_TEST(VertexTest, AssignmentOperator) 
{
	//

}
*/

#endif // GTEST_HAS_TYPED_TEST