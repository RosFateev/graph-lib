#include "gtest/gtest.h"					//gtest
#include "graph-component/vertex.hpp"		//helper component
#include "graph-component/edge.hpp"			//component to test
//
#include <vector>							//
#include <string>							//
#include <algorithm>						//std::copy
#include <iterator>							//std::back_inserter





// define test fixture
template<	class id_type>
class EdgeTest : public testing::Test
{
	using vertex_type 	= component::Vertex<id_type>;
	using vertex_ptr 	= std::shared_ptr<vertex_type>;
	using edge_type 	= component::Edge<id_type>;

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
	std::vector<vertex_ptr> 	vertexpointers_;
	std::vector<edge_type> 		container1_;
	std::vector<edge_type> 		container2_;
	int 						count_;
};
//





//	Using parametrized tests for component::Vertex
#if GTEST_HAS_TYPED_TEST



// Declare which types are going to be used
typedef testing::Types<int, char> IndeciesTypes;



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
		this->vertexpointers_.emplace_back(std::make_shared<component::Vertex<TypeParam>>(i));
	}
	for(int i = 0; i < this->count_ - 1; ++i)
	{
		this->container1_.emplace_back(this->vertexpointers_[i], this->vertexpointers_[i+1]);
	}
	//assert
	for(int i = 0; i < this->count_ - 1; ++i)
	{
		ASSERT_EQ(this->container1_[i].GetVertex(0).Id(), this->vertexpointers_[i]->Id());
		ASSERT_EQ(this->container1_[i].GetVertex(1).Id(), this->vertexpointers_[i + 1]->Id());
	}
}



// Copy constructor test
TYPED_TEST(EdgeTest, MoveConstructor) 
{
	//initialize
	for(int i = 0; i < this->count_; ++i)
	{
		this->vertexpointers_.emplace_back(std::make_shared<component::Vertex<TypeParam>>(i));
	}
	for(int i = 0; i < this->count_ - 1; ++i)
	{
		this->container1_.emplace_back(this->vertexpointers_[i], this->vertexpointers_[i+1]);
	}
	//
	std::move(this->container1_.begin(), this->container1_.end(), std::back_inserter(this->container2_));
	//assert
	for(int i = 0; i < this->count_ - 1; ++i)
	{
		ASSERT_EQ(this->container1_[i].GetVertex(0).Id(), this->vertexpointers_[i]->Id());
		ASSERT_EQ(this->container1_[i].GetVertex(1).Id(), this->vertexpointers_[i + 1]->Id());
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