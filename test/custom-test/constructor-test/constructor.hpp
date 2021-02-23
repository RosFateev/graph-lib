#ifndef CUSTOM_TEST_CONSTRUCTOR_TEST_CONSTRUCTOR_H
#define CUSTOM_TEST_CONSTRUCTOR_TEST_CONSTRUCTOR_H



//includes
#include "gtest/gtest.h"
#include <vector>						// container for the test fixture
#include "graph-component/vertex.hpp"
#include "graph-component/edge.hpp"










// forward declare initializer functor (DOESN'T WORK)
//
//template<	typename Object>
//class Initializer;

//template<	typename Object>
//class Comparator;
template<	typename 	Object>
class Initializer
{
public:
			Initializer();
	
	void 	operator()();

};



template<	>
class Initializer<component::Vertex<int>>
{
public:
			Initializer()
			{	}

	void 	operator()(std::vector<component::Vertex<int>>& inContainer, int inCount)
	{
		for(int i = 0; i < inCount; ++i)
		{
			inContainer.emplace_back(i);	
		}
	}
};



template<	>
class Initializer<component::Vertex<char>>
{
public:
			Initializer()
			{	}

	void 	operator()(std::vector<component::Vertex<char>>& inContainer, int inCount)
	{
		for(int i = 0; i < inCount; ++i)
		{
			inContainer.emplace_back(i);	
		}
	}
};



template<	>
class Initializer<component::UndirectedEdge<int>>
{
public:
			Initializer()
			{	}

	void 	operator()(std::vector<component::UndirectedEdge<int>>& inContainer, int inCount)
	{
		for(int i = 0; i < inCount; ++i)
		{
			inContainer.emplace_back(component::Vertex(i), component::Vertex(i + 1));	
		}
	}
};



template<	>
class Initializer<component::UndirectedEdge<char>>
{
public:
			Initializer()
			{	}

	void 	operator()(std::vector<component::UndirectedEdge<char>>& inContainer, int inCount)
	{
		for(int i = 0; i < inCount; ++i)
		{
			inContainer.emplace_back(component::Vertex((char)i), component::Vertex(char(i + 1)));	
		}
	}
};





// Declaration and definition of an Comparator Object
template<	typename 	Object>
class Comparator
{
public:
			Comparator();

	void 	operator()();
};



template<	>
class Comparator<component::Vertex<int>>
{
public:
			Comparator()
			{	}

	void 	operator()(std::vector<component::Vertex<int>>& inContainer, int inCount)
	{
		for(int i = 0; i < inCount; ++i)
		{
			EXPECT_EQ(inContainer[i].Id(), i);	
		}
	}
};



template<	>
class Comparator<component::Vertex<char>>
{
public:
			Comparator()
			{	}

	void 	operator()(std::vector<component::Vertex<char>>& inContainer, int inCount)
	{
		for(int i = 0; i < inCount; ++i)
		{
			EXPECT_EQ(inContainer[i].Id(), i);	
		}
	}
};



template<	>
class Comparator<component::UndirectedEdge<int>>
{
public:
			Comparator()
			{	}

	void 	operator()(std::vector<component::UndirectedEdge<int>>& inContainer, int inCount)
	{
		for(int i = 0; i < inCount; ++i)
		{
			EXPECT_EQ(inContainer[i].First().Id(), i);
			EXPECT_EQ(inContainer[i].Second().Id(), i + 1);	
		}
	}
};



template<	>
class Comparator<component::UndirectedEdge<char>>
{
public:
			Comparator()
			{	}

	void 	operator()(std::vector<component::UndirectedEdge<char>>& inContainer, int inCount)
	{
		for(int i = 0; i < inCount; ++i)
		{
			EXPECT_EQ(inContainer[i].First().Id(), i);
			EXPECT_EQ(inContainer[i].Second().Id(), i + 1);	
		}
	}
};
//










// test fixture
// uses a container to store objects to test
template<	typename Object>
class ConstructorTest : public testing::Test 
{
	using object_container 	= std::vector<Object>;

protected:

	// initialization
	void 		SetUp() override;



	//clean up
	void 		TearDown() override;

public:
	//state
	int 					count_;
	object_container 		container1_;
	object_container		container2_;
	Initializer<Object> 	initializer_;
	Comparator<Object> 		comparator_;
};










//Definitions
template<	typename Object>
void ConstructorTest<Object>::SetUp()
{	}



template<	typename Object>
void ConstructorTest<Object>::TearDown()
{	}




/*
//Definitions
template<	typename Object>
void ConstructorTest<Object>::SetUp(std::initializer_list<Object> inList)
{
	container_ = inList;
}

template<	typename Object>
void ConstructorTest<Object>::SetUp(const Iterator inBegin, const Iterator inEnd)
{
	std::copy(inBegin, inEnd, std::back_inserter(container_));
}


template<	class ObjectType>
void ConstructorTest<ObjectType>::TearDown(){}
*/


#endif // CUSTOM_TEST_CONSTRUCTOR_TEST_CONSTRUCTOR_H
		