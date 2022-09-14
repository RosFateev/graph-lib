//==============================================================================
///
/// @file positioner.h
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

//==============================================================================
// Include only once
//
#ifndef GRAPH_LIB_DISPLAY_DRAWER_POSITIONER
#define GRAPH_LIB_DISPLAY_DRAWER_POSITIONER


//------------------------------------------------------------------------------
// Include files
//------------------------------------------------------------------------------
// System
// e.g.: #include <iostream>        // stdout
#include <utility>              // std::pair

// Project
// e.g.: #include "IncludeFile.h"   // MyType_t


//------------------------------------------------------------------------------
// Constants
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Macros
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Forward declarations
//------------------------------------------------------------------------------
// (none)


//------------------------------------------------------------------------------
// Data types
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
/// @brief namespace containing all structures used to display graph.
///
//------------------------------------------------------------------------------
namespace output
{
    //------------------------------------------------------------------------------
    /// @brief Generates coordinates of a graph.
    ///
    //------------------------------------------------------------------------------
    class Positioner
    {
        using coordinate_type       = std::pair<float, float>;
        using coordinate_container  = std::vector<coordinate_type>;

    public:

        //------------------------------------------------------------------------------
        /// @brief Value constructor.
        ///
        /// @param[in] vertexCount Number of vertices in a graph.
        ///
        /// @param[in] x X-coordinate of the upper-left corner of a sector.
        ///
        /// @param[in] y y-coordinate of the upper-left corner of a sector.
        ///
        /// @param[in] width Coordinate space width.
        ///
        /// @param[in] height Coordinate space height.
        ///
        //------------------------------------------------------------------------------
        Positioner(int vertexCount,
                   float x,
                   float y,
                   float width,
                   float height);
        
        //------------------------------------------------------------------------------
        /// @brief Move constructor.
        ///
        /// @param[in] positioner Positioner object.
        ///
        //------------------------------------------------------------------------------
        Positioner(Positioner&& positioner);
        
        //------------------------------------------------------------------------------
        /// @brief Move assignment operator.
        ///
        /// @param[in] positioner Positioner object.
        ///
        /// @return Reference to itself.
        ///
        //------------------------------------------------------------------------------
        Positioner&
        operator=(Positioner&& positioner);



        //------------------------------------------------------------------------------
        /// @brief Compute coordinates of graph. 
        ///
        /// @return Container with coordinates.
        ///
        //------------------------------------------------------------------------------
        coordinate_container
        ComputeCoordinates();


    private:

        //------------------------------------------------------------------------------
        /// @brief Compute split factors.
        ///
        /// Determine split dimensions based on factors with minimal difference of N,
        /// where N - power of two.
        ///
        /// @return Computed split factors.
        ///
        //------------------------------------------------------------------------------
        std::pair<int,int>
        Factors();

        //------------------------------------------------------------------------------
        /// @brief Compute coordinates of a graph in a straight-forward manner.
        ///
        /// @return Container with coordinates.
        ///
        //------------------------------------------------------------------------------
        coordinate_container
        SimpleCompute();

        //------------------------------------------------------------------------------
        /// @brief Compute coordinates of a graph in a circle shape.
        ///
        /// @return Container with coordinates.
        ///
        //------------------------------------------------------------------------------
        coordinate_container
        CircleCompute();

        //------------------------------------------------------------------------------
        /// @brief Compute coordinates of a graph using spring system method.
        ///
        /// @return Container with coordinates.
        ///
        //------------------------------------------------------------------------------
        coordinate_container
        SpringSystemCompute();
        
        //------------------------------------------------------------------------------
        /// @brief Compute coordinates of a graph using barycentric method.
        ///
        /// @return Container with coordinates.
        ///
        //------------------------------------------------------------------------------
        coordinate_container
        BarycentricCompute();



    private:

        /// @brief Number of vertices in a graph.
        int vertexCount_;

        /// @brief X-coordinate of the upper-left corner of a sector.
        float x_;

        /// @brief y-coordinate of the upper-left corner of a sector.
        float y_;

        /// @brief Coordinate space width.
        float width_;

        /// @brief Coordinate space height.
        float height_;

    };

} //    namespace output



//
#endif // GRAPH_LIB_DISPLAY_DRAWER_POSITIONER
//==============================================================================
// End of positioner.h
// (note: the newline at the end of the file is intentional)
//==============================================================================
