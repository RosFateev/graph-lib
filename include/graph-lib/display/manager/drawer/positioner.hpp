#ifndef GRAPH_DISPLAY_MANAGER_DRAWER_SECTOR
#define GRAPH_DISPLAY_MANAGER_DRAWER_SECTOR





// std
#include <vector>
#include <map>
// user
#include "graph-implementation/implementation-support.hpp"





// forward declaration
namespace output
{
    template< typename id_type>
    class OutputterManager;

    template< typename id_type>
    class OutputterManager;
}





//! output
/*!
 * Namespace containing all structures used to display graph.
 */
namespace output
{
    //! WritableTuple
    /*!
     * Simple writable tuple.
     */
    template< typename data_type>
    class WritableTuple
    {

    public:

        //! Default constructor
        /*!
         * Construct tuple.
         */
                            WritableTuple() : first_(), second_()
        {   }
        //! Value constructor
        /*!
         * Construct tuple.
            \param data_type
            \param data_type
         */
                            WritableTuple(  data_type first, 
                                            data_type second) : first_(first), second_(second)
        {   }

        //! Set
        /*!
         * Set tuple item of given index with given value.
            \param int
            \param data_type
         */
        void                Set(int index, data_type newValue)
        {
            (index == 0 ? first_ = newValue : second_ = newValue);
        }

        //! Set
        /*!
         * Set tuple with given values.
            \param data_type
            \param data_type
         */
        void                Set(data_type newValue1, data_type newValue2)
        {
            first_ = newValue1;
            second_ = newValue2;
        }
        
        //! Get
        /*!
         * Get tuple item of given index.
            \param int
         */
        const data_type&    Get(int index) const
        {
            return (index == 0 ? first_ : second_);
        }

    private:
        //! first
        /*!
         * First value.
         */
        float first_;
        
        //! second
        /*!
         * Second value.
         */
        float second_;
    };

} // namespace output





//! output
/*!
 * Namespace containing all structures used to display graph.
 */
namespace output
{
    //! Positioner
    /*!
     * Class responsible for managing coordinates of all OutputInstances in OutputterManager.
     */
    class Positioner
    {
        using coordinate_type       = WritableTuple<float>;
        using coordinate_container  = std::vector<coordinate_type>;
        using graph_ptr             = graph::Graph*;
        using sector_container      = std::map<graph_ptr, coordinate_container>;

    public:
        
        //! Value constructor
        /*!
         *  Constructs Positioner object with given window dimensions.
            \param int
            \param int
         */
                                Positioner(int, int);
        
        //! Move constructor
        /*!
         *  Move-constructs Positioner object.
            \param Positioner&&
         */
                                Positioner(Positioner&&);
        
        //! Move assignment
        /*!
         *  Move-constructs Positioner object.
            \param Positioner&&
            \return Positioner&
         */
        Positioner&             operator=(Positioner&&);



        //! ComputeSector
        /*!
         *  Compute coordinates of OutputInstance of given size located in a sector of given index. 
            \param int
            \param int
            \return coordinate_container
         */
        coordinate_container    ComputeSector(int, int);

        //! GenerateSectors
        /*!
         *  Split coordinate space into sectors w.r.t. number of OutputInstances of manager component. 
            \param int
         */
        template< typename id_type>
        void                    GenerateSectors( const OutputterManager<id_type>&);


        
    private:

        //! Factors
        /*!
         * Determine split dimensions based on factors with minimal difference of N, where N - power of two.
            \param int
            \return WritableTuple<int>
         */
        sector_type             Factors(int);

        //! SimpleCompute
        /*!
         *  Compute coordinates of an instance in a specific sector.
            \param int
         */
        coordinate_container    SimpleCompute(int);

        //! SpringSystemCompute
        /*!
         *  Compute coordinates of an instance in a specific sector using spring system method.
            \param int
         */
        coordinate_container    SpringSystemCompute(int);
        
        //! BarycentricCompute
        /*!
         *  Compute coordinates of an instance in a specific sector using barycentric method.
            \param int
         */
        coordinate_container    BarycentricCompute(int);



    private:

        //! width
        /*!
         * Coordinate space width.
         */
        int                 width_;
        
        //! height
        /*!
         * Coordinate space height.
         */
        int                 height_;

        //! row_sector_count
        /*!
         * Vertical sector partition of window.
         */
        int                 row_sector_count_;
        
        //! col_sector_count
        /*!
         * Horizontal sector partition of window.
         */
        int                 col_sector_count_;
        
        //! sectors_
        /*!
         * Partition container of coordinate space into sectors.
         */
        sector_container    sectors_;

    };

} //    namespace output













//
// Positioner implementation
//
namespace output
{
    // constructor
    Positioner::Positioner(     int width, int height) :    width_(width), 
                                                            height_(height),
                                                            sectors_()
    {   }

    Positioner::Positioner(Positioner&& positioner) :   width_(positioner.width_), 
                                                        height_(positioner.height_),
                                                        sectors_(std::move(positioner.sectors_))
    {    }

    Positioner&     Positioner::operator=(Positioner&& positioner)
    {
        width_ = positioner.width_;
        height_ = positioner.height_;
        sectors_ = std::move(positioner.sectors_);

        return *this;
    }



    // update coordinate space partition
    template< typename id_type>
    void    Positioner::GenerateSectors( const OutputterManager<id_type>& manager)
    {
        // new instance was added/old instance was removed - recompute partition and all sectors coordinaters
        if (manager.Instances().size() != sectors_)
        {
            auto partition_factors = Factors(manager.Instances().size());
            row_sector_count_ = partition_factors.Get(0);
            col_sector_count_ = partition_factors.Get(1);
            sectors_ = typename Positioner::sector_container( row_sector_count_ * col_sector_count_, 0);

            auto sectors_iterator = sectors_.begin();
            for (auto instance_iterator = manager.Instances().begin(); instance_iterator != manager.Instances().end(); ++instance_iterator)
            {
                *sectors_iterator = Factors(instance_iterator->Graph().Size());

                ++sectors_iterator;
            }
        }
    }


    // recompute coordinates of an instance in a specific sector
    typename Positioner::coordinate_container    Positioner::ComputeSector(int sector_index, int vertex_count)
    {
        // select how coordinates should be computed
        return SimpleCompute(sector_index, vertex_count);
        //SpringSystemCompute();
        //BarycentricCompute();
    }





    //
    // Private methods
    //
    // compute factors
    typename Positioner::sector_type     Positioner::Factors( int vertex_count)
    {
        // determine split dimensions based on factors with minimal difference of N, 
        // where N - power of two
        int currentMax = 1;
        int power = 0;

        while (currentMax < vertex_count)
        {
            currentMax <<= 1;
            ++power;
        }

        return (power % 2 == 0) ?   typename Positioner::sector_type( 1 << (power / 2), 1 << (power / 2)) : 
                                    typename Positioner::sector_type( 1 << (power / 2), 1 << ((power / 2) + 1));
    }



    // Based on window dimensions determine equally spaced locations to uniformly spread the vertices
    void    Positioner::SimpleCompute(int sector_index, int vertex_count)
    {
        //
        auto new_factors = Factors(vertex_count);

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
    }



    // Compute coordinates of a graph assuming it is a spring system
    void    Positioner::SpringSystemCompute()
    {
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
    }



    // eigenvalues compute (?)
    void    Positioner::BarycentricCompute()
    {

    }


} //    namespace output



#endif // GRAPH_DISPLAY_MANAGER_DRAWER_SECTOR