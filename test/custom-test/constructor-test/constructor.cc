#include "constructor.hpp"





// Declaration and definition of an Initializer for objects
// It is used in ConstructorTest SetUp() function
// Uses static method to avoid construction
// INSERT BACK HERE
//










// type-parametrized tests
#if GTEST_HAS_TYPED_TEST_P



using testing::Types;



template<	typename Object>
class pConstructorTest : public ConstructorTest<Object>
{	};



//test suite types
//typedef Types<component::Vertex<int>, component::Vertex<char>> TestTypes;

// in this situation types are unknown
TYPED_TEST_SUITE_P(pConstructorTest);





// 
// Test Fixtures
//

// Default constructor:
// Compare with some predefined values
TYPED_TEST_P(pConstructorTest, DefaultConstructor)
{
	//
	this->initializer_(this->container1_, 20);
	//
	//
	this->comparator_(this->container1_, 20);
}





// register tests
REGISTER_TYPED_TEST_SUITE_P( pConstructorTest, DefaultConstructor); //, CopyConstructor, MoveConstructor);



//list of types
typedef Types<	component::Vertex<int>, 
				component::Vertex<char>,
				component::UndirectedEdge<int>,
				component::UndirectedEdge<char> 
				> ObjectTypes;



//
INSTANTIATE_TYPED_TEST_SUITE_P(componentVertexTests,		// Instance name(??)
                               pConstructorTest,            // Test case name
                               ObjectTypes);  				// Type list


#endif //GTEST_HAS_TYPED_TEST_P