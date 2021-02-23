#include "gtest/gtest.h"								//gtest
#include "graph-implementation/manager.hpp"				//
//
#include <vector>										//
#include <string>										//
#include <algorithm>									//std::copy
#include <iterator>										//std::back_inserter





template<	class Data>
class ManagerTest : public testing::Test
{
protected:
	void SetUp() override
	{

	}

	void TearDown() override
	{
		
	}
};





//	Using parametrized tests for component::Vertex
#if GTEST_HAS_TYPED_TEST

using testing::Types;



// Declare which types are going to be used
typedef Types<int, char> IndeciesTypes;



// declare what test fixture uses which types
TYPED_TEST_SUITE(ManagerTest, IndeciesTypes);





//
// Tests
//

// Default constructor test
TYPED_TEST(ManagerTest, DataConstructor) 
{
	ASSERT_EQ(1, 1);
}



// Copy constructor test
TYPED_TEST(ManagerTest, CopyConstructor) 
{
	ASSERT_EQ(1, 1);	
}


/*
// assignment operator test
TYPED_TEST(ManagerTest, MoveConstructor) 
{
	//

}
*/
#endif // GTEST_HAS_TYPED_TEST