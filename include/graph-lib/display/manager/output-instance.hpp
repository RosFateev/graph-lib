#ifndef GRAPH_DISPLAY_MANAGER_OUTPUT_INSTANCE
#define GRAPH_DISPLAY_MANAGER_OUTPUT_INSTANCE





// std
#include <sstream>





// Forward declaration
namespace graph
{
    template<   typename    id_type>
    class Graph;
}

namespace output
{
    class Coordinate;
}





//! output
/*!
 * Namespace containing all structures used to display graph.
 */
namespace output
{
    //! OutputInstance
    /*!
     * Class associated with graph to enable displaying. It contains:
     *  - reference to a graph object 
     *  - drawer component handling printing
     */
    template< typename id_type>
    class OutputInstance
    {
        using graph_type            = graph::Graph<id_type>;
        using coordinate_type       = Coordinate;
        using coordinate_container  = std::vector<coordinate_type>;

    public:

        //! Value constructor
        /*!
         * Constructs an OutputInstance.
            \param const graph_type&
         */
                            OutputInstance(     const graph_type&);

        //! Move constructor
        /*!
         * Constructs an OutputInstance.
            \param OutputInstance&&
         */
                            OutputInstance(OutputInstance&&);
        
        //! Move assignment operator
        /*!
            \param OutputInstance&&
            \return OutputInstance&
         */
        OutputInstance&     operator=(OutputInstance&&);

        //! Graph
        /*!
         * Graph reference getter.
            \return const graph_type&
         */
        const graph_type&   Graph() const;

        //! UpdateCoordinates
        /*!
         * Update vertex coordinates of related graph.
            \param const coordinate_container&
         */
        void                UpdateCoordinates( const coordinate_container&);



    private:

        //! graphEntry
        /*!
         * Reference to graph object.
         */
        const graph_type&   graphEntry_;
    };
} // namespace output










//
// OutputInstance implementation
//
namespace output
{
    // constructor
    template< typename id_type>
    OutputInstance<id_type>::OutputInstance(    const typename OutputInstance<id_type>::graph_type&     inGraph) :   graphEntry_(inGraph)
    {   }

    template< typename id_type>
    OutputInstance<id_type>::OutputInstance(OutputInstance<id_type>&& inInstance) : graphEntry_(std::move(inInstance.graphEntry_))
    {   }

    template< typename id_type>
    OutputInstance<id_type>& OutputInstance<id_type>::operator=(OutputInstance<id_type>&& inInstance)
    {
        graphEntry_ =   std::move(inInstance.graphEntry_);

        return *this;
    }



    // display
    template< typename id_type>
    void OutputInstance<id_type>::UpdateCoordinates( const typename OutputInstance<id_type>::coordinate_container& coordinates)
    {
        auto coordinates_iterator = coordinates.begin();

        for (auto vertex_iterator = graphEntry_.v_begin(); vertex_iterator != graphEntry_.v_end(); ++vertex_iterator)
        {
            (*vertex_iterator)->Coordinate(coordinates_iterator->x_, coordinates_iterator->y_);

            ++coordinates_iterator;
        }
    }

} // namespace output



#endif // GRAPH_DISPLAY_MANAGER_OUTPUT_INSTANCE