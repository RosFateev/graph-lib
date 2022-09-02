//==============================================================================
///
/// @file positioner.cpp
///
/// @brief <description>
///
/// <Detailed description>
///
/// The documentation is available on the following website:
/// <website>
///
/// Support email: <email>
///
//==============================================================================


//------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------
// System
// e.g.: #include <iostream>        // stdout
#include <vector>

// Project
// e.g.: #include "IncludeFile.h"   // MyType_t
#include "graph-lib/display/drawer/positioner.h"


//------------------------------------------------------------------------------
// Global references
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Constants
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Macros
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Local data types
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Forward function declarations
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Variable definitions
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Function definitions
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//
//  <Design related information>
//
//------------------------------------------------------------------------------
namespace output
{
    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    Positioner::Positioner(int vertexCount,
                           float x,
                           float y,
                           float width,
                           float height) : vertexCount_(vertexCount),
                                           x_(x),
                                           y_(y),
                                           width_(width),
                                           height_(height)
    {   }
    
    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    Positioner::Positioner(Positioner&& positioner) : vertexCount_(positioner.vertexCount_),
                                                      x_(positioner.x_),
                                                      y_(positioner.y_),
                                                      width_(positioner.width_),
                                                      height_(positioner.height_)
    {   }
    
    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    Positioner&
    Positioner::operator=(Positioner&& positioner)
    {
        vertexCount_ = positioner.vertexCount_;
        x_ = positioner.x_;
        y_ = positioner.y_;
        width_ = positioner.width_;
        height_ = positioner.height_;

        return *this;
    }
    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    typename Positioner::coordinate_container
    Positioner::ComputeCoordinates()
    {
        // select how coordinates should be computed
        return SimpleCompute();
        //SpringSystemCompute();
        //BarycentricCompute();
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    std::pair<int, int>
    Positioner::Factors()
    {
        // determine split dimensions based on factors with minimal difference of N, 
        // where N - power of two
        int currentMax = 1;
        int power = 0;

        while (currentMax < vertexCount_)
        {
            currentMax <<= 1;
            ++power;
        }

        // ?
        return (power % 2 == 0) ? std::pair<int,int>( 1 << (power / 2), 1 << (power / 2)) : 
                                  std::pair<int,int>( 1 << (power / 2), 1 << ((power / 2) + 1));
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    typename Positioner::coordinate_container
    Positioner::SimpleCompute()
    {
        typename Positioner::coordinate_container result;

        // determine max number of vertices in a row and column of placement grid 
        auto factors = Factors();

        // allow padding
        int rowCount = factors.first + 2;
        int colCount = factors.second + 2;

        // calculate positions
        float x_0 = 0.f;
        float y_0 = 0.f;
        float xStep = float(width_ / colCount);
        float yStep = float(height_ / rowCount);
        
        // vertical direction
        for(int j = 1; j < rowCount; ++j)
        {
            // x axis
            for(int i = 1; i < colCount; ++i)
            {
                result.emplace_back(x_0 + xStep * i, y_0 + yStep * j);
            }
        }

        return result;
    }

    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    typename Positioner::coordinate_container
    Positioner::SpringSystemCompute()
    {
        typename Positioner::coordinate_container result;
        /*
        c1= 2,c2= 1,c3= 1,c4= 0.1

        adj_force = c1∗log(d/c2)
        non-adj_force = c3/d^2
        ---

        algorithm SPRING(G:graph);
        place vertices of G in random locations;
        repeat M times 
            calculate the force on each vertex;
            move the vertex c4∗(force on vertex)
        draw graph on CRT or plotter.
        */

        return result;
    }
    
    //------------------------------------------------------------------------------
    //
    //  <Design related information>
    //
    //------------------------------------------------------------------------------
    typename Positioner::coordinate_container
    Positioner::BarycentricCompute()
    {
        typename Positioner::coordinate_container result;

        /*
        Algorithm description
        */

        return result;
    }

} // namespace output



//==============================================================================
// End of positioner.cpp
// (note: the newline at the end of the file is intentional)
//==============================================================================
