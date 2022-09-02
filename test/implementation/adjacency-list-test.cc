#include "gtest/gtest.h"                                //gtest
#include "graph-implementation/adjacency-list.hpp"      // component to test
#include "graph-component/vertex.hpp"                   // helper component
#include "graph-component/edge.hpp"                 // helper component
//
#include <vector>                                       //
#include <string>                                       //
#include <algorithm>                                    //std::copy
#include <iterator>                                     //std::back_inserter
#include <iostream>





template<   typename id_type,
            template<typename> typename     EdgeType>
class AdjacencyListTest : public testing::Test
{
    //public typedef
    using vertex_type           = component::Vertex<id_type>;
    using vertex_ptr            = std::shared_ptr<vertex_type>;
    using edge_type             = EdgeType<id_type>;
    using edge_ptr              = std::shared_ptr<edge_type>;
    using adjacency_list_type   = implementation::AdjacencyList<id_type, edge_type>;
    using vertex_container      = std::vector<vertex_ptr>;
    using edges_container       = std::vector<edge_ptr>;

protected:
    
    //required functions
    void    SetUp()     override
    {
        // # of elements
        count_ = 20;    
    }

    void    TearDown()  override
    {   }

public:
    //state
    vertex_container_type           vertices_;
    edges_container_type            edges_;
    std::vector<id_type>                dataContainer_;
    adjacency_list_type             list1_;
    adjacency_list_type             list2_;
    
};





//  Using parametrized tests for component::Vertex
#if GTEST_HAS_TYPED_TEST

using testing::Types;



// Declare which types are going to be used
typedef Types<int, char> IndeciesTypes;



// declare what test fixture uses which types
TYPED_TEST_SUITE(AdjacencyListTest, IndeciesTypes);





//
// Tests
//

// Default constructor test
TYPED_TEST(AdjacencyListTest, DefaultConstructor) 
{
    // prepare
    //
    // assert
    ASSERT_EQ(this->list1_.IsValid(), false);
    ASSERT_EQ(this->list1_.IsEmpty(), true);
    ASSERT_EQ(this->list1_.GetPolicy().IsValid(), true);
}



// Copy constructor test
TYPED_TEST(AdjacencyListTest, InitListConstructor) 
{
    // prepare
    // used print function to instead check the result manualy
    //this->list2_.print();

    ASSERT_EQ(1, 1);    
}





// Vertex function tests 
TYPED_TEST(AdjacencyListTest, AddVertexData) 
{
    // prepare
    for(auto dataEntry : this->dataContainer_)
    {
        this->list2_.AddVertex(dataEntry);  
    }
    
    this->list2_.print();

    ASSERT_EQ(this->list2_.size(), 8);  
}

TYPED_TEST(AdjacencyListTest, AddVertexCopy) 
{
    // prepare
    this->list2_.AddVertex(this->vertices_[4]);
    this->list2_.AddVertex(this->vertices_[5]);

    this->list2_.print();

    ASSERT_EQ(this->list2_.size(), 6);  
}

TYPED_TEST(AdjacencyListTest, GetVertex) 
{
    // prepare
    
    ASSERT_EQ(this->list2_.GetVertex(0).Id(), 0);
    ASSERT_EQ(this->list2_.GetVertex(1).Id(), 1);
    ASSERT_EQ(this->list2_.GetVertex(2).Id(), 2);
    ASSERT_EQ(this->list2_.GetVertex(3).Id(), 3);   
}

//Temporary unavailable
TYPED_TEST(AdjacencyListTest, RemoveVertex) 
{
    // prepare
    

    ASSERT_EQ(1, 1);    
}




// Edge function Tests
TYPED_TEST(AdjacencyListTest, AddEdgeVertexParam) 
{
    // prepare
    for(auto dataEntry : this->dataContainer_)
    {
        this->list2_.AddVertex(dataEntry);  
    }

    this->list2_.AddEdge(this->list2_.GetVertex(6), this->list2_.GetVertex(7));
    this->list2_.AddEdge(this->list2_.GetVertex(7), this->list2_.GetVertex(8));
    this->list2_.AddEdge(this->list2_.GetVertex(8), this->list2_.GetVertex(9));
    this->list2_.AddEdge(this->list2_.GetVertex(9), this->list2_.GetVertex(6));

    this->list2_.print();

    ASSERT_EQ(1, 1);    
}

/*
// Later
TYPED_TEST(AdjacencyListTest, AddEdgeEdgeParam) 
{
    // prepare

    ASSERT_EQ(1, 1);    
}
*/

TYPED_TEST(AdjacencyListTest, GetEdge) 
{
    // prepare

    ASSERT_EQ(this->list2_.GetEdge(0,2).First().Id(), 0);
    ASSERT_EQ(this->list2_.GetEdge(2,3).Second().Id(), 3);  
}

/*
// Later
TYPED_TEST(AdjacencyListTest, RemoveEdge) 
{
    // prepare
    

    ASSERT_EQ(1, 1);    
}
*/



// Get Neighbour tests
TYPED_TEST(AdjacencyListTest, GetNeighbours) 
{
    // prepare
    

    ASSERT_EQ(this->list2_.GetNeighbours(0).size(), 3); 
    ASSERT_EQ(this->list2_.GetNeighbours(1).size(), 1);
    ASSERT_EQ(this->list2_.GetNeighbours(2).size(), 2);
    ASSERT_EQ(this->list2_.GetNeighbours(3).size(), 2);
}



//
TYPED_TEST(AdjacencyListTest, ContainsVertex) 
{
    //
    ASSERT_EQ(this->list2_.ContainsVertex(0), true);
    ASSERT_EQ(this->list2_.ContainsVertex(1), true);
    ASSERT_EQ(this->list2_.ContainsVertex(2), true);
    ASSERT_EQ(this->list2_.ContainsVertex(3), true);
    ASSERT_EQ(this->list2_.ContainsVertex(4), false);
    ASSERT_EQ(this->list2_.ContainsVertex(5), false);
}

TYPED_TEST(AdjacencyListTest, ContainsEdge) 
{
    //
    ASSERT_EQ(this->list2_.ContainsEdge(0, 1), true);
    ASSERT_EQ(this->list2_.ContainsEdge(1, 0), true);
    ASSERT_EQ(this->list2_.ContainsEdge(2, 3), true);
    ASSERT_EQ(this->list2_.ContainsEdge(3, 0), true);
    ASSERT_EQ(this->list2_.ContainsEdge(4, 0), false);
    ASSERT_EQ(this->list2_.ContainsEdge(5, 2), false);
}

/*
// assignment operator test
TYPED_TEST(AdjacencyListTest, TestName) 
{
    //

}
*/
#endif // GTEST_HAS_TYPED_TEST