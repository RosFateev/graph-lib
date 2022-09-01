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
        using coordinate_type       = std::pair<float, float>;
        using coordinate_container  = std::vector<coordinate_type>;

        int vertexCount_;

        /// @brief X-coordinate of the upper-left corner of a sector.
        float x_;

        /// @brief y-coordinate of the upper-left corner of a sector.
        float y_;

        /// @brief Coordinate space width.
        float width_;

        /// @brief Coordinate space height.
        float height_;

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
                                           heigh_(height)
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
                                                      heigh_(positioner.height_)
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
        heigh_ = positioner.height_;

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
    sector_type
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
        return (power % 2 == 0) ?   typename Positioner::sector_type( 1 << (power / 2), 1 << (power / 2)) : 
                                    typename Positioner::sector_type( 1 << (power / 2), 1 << ((power / 2) + 1));
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

        //
        auto new_factors = Factors(vertexCount_);

        // if graph dimension has changed
        if ((sectors_[sector_index].Get(0) != new_factors.Get(0)) ||
            (sectors_[sector_index].Get(1) != new_factors.Get(1)))
        {
            // set new dimensions
            sectors_[sector_index].Set(new_factors.Get(0),new_factors.Get(1));
        }

        // allow padding
        int row_count = sectors_[sector_index].Get(0) + 2;
        int col_count = sectors_[sector_index].Get(1) + 2;

        // calculate positions
        float local_width = width_ / col_sector_count_;
        float local_height = height_ / row_sector_count_;
        float x_0 = (sector_index % col_sector_count_) * local_width;
        float y_0 = ((sector_index % col_sector_count_) % row_sector_count_) * local_height;
        float xStep = float(local_width / col_count);
        float yStep = float(local_height / row_count);
        
        // vertical direction
        for(int j = 1; j < row_count; ++j)
        {
            // x axis
            for(int i = 1; i < col_count; ++i)
            {
                coordinates_.emplace_back(x_0 + xStep * i, y_0 + yStep * j);
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
