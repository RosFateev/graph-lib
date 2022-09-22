//==============================================================================
///
/// @file runner.cpp
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
#include <sstream>              // std::stringstream

// Project
// e.g.: #include "IncludeFile.h"   // MyType_t
#include "runner.h"
#include "graph-lib/algorithm/traversal/dfs.hpp"    // algorithm::dfs
#include "graph-lib/algorithm/traversal/bfs.hpp"    // algorithm::bfs
#include "graph-lib/algorithm/flow/edmonds.hpp"     // algorithm::edmonds
#include "graph-lib/algorithm/flow/dinic.hpp"       // algorithm::dinic
#include "graph-lib/utility/print.hpp"              // print_graph(), print_algorithm(),...


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
Runner::Runner() : fetcher_()
{   }

//------------------------------------------------------------------------------
//
//  <Design related information>
//
//------------------------------------------------------------------------------
void
Runner::execute()
{
    //DEBUG
    std::cout << "Type your command:\n";
    //DEBUG
    for (std::string command; std::getline(std::cin, command);)
    {
        //DEBUG
        std::cout << "command is |" << command << "|\n";
        //DEBUG

        if (!parse_command(command))
        {
            //DEBUG
            std::cout << "Quit command detected or Error occured - terminate\n";
            //DEBUG

            break;
        }

        //DEBUG
        std::cout << "Success!\n";
        //DEBUG
    }
}


//------------------------------------------------------------------------------
//
//  <Design related information>
//
//------------------------------------------------------------------------------
bool
Runner::parse_command(std::string input)
{
    // command string parameters
    std::string command("");
    std::string graphFile("");
    std::string arg1("");
    std::string arg2("");

    //DEBUG
    std::cout << "Start parsing:\n";
    //DEBUG

    std::stringstream converter(input);
    converter >> command;
    converter >> graphFile;
    converter >> arg1;
    converter >> arg2;

    //DEBUG
    std::cout << "Parsing is finished.\nStart execution.\n";
    //DEBUG

    // execute command
    return execute_command(command, graphFile, arg1, arg2);
}


//------------------------------------------------------------------------------
//
//  <Design related information>
//
//------------------------------------------------------------------------------
bool
Runner::execute_command(std::string command,
                        std::string graphFile,
                        std::string arg1,
                        std::string arg2)
{
    //DEBUG
    std::cout << "  Command to execute: |" << command << "|\n";
    std::cout << "  graph file: |" << graphFile << "|\n";
    std::cout << "  first argument: |" << arg1 << "|\n";
    std::cout << "  second argument: |" << arg2 << "|\n";
    //DEBUG

    if (command == "quit")
    {
        //DEBUG
        std::cout << "      Quit command detected - terminate\n";
        //DEBUG
        return false;
    }

    //DEBUG
    std::cout << "      Fetch graph\n";
    //DEBUG

    graph::Graph<std::string> currentGraph = fetcher_.get_graph(graphFile);

    if (command == "bfs")
    {
        //DEBUG
        std::cout << "      BFS command detected - execute\n";
        //DEBUG

        algorithm::bfs<std::string> bfsObj(&currentGraph);
        bfsObj.run(currentGraph.GetVertex(arg1));
        print_traversal_result<std::string>(bfsObj.get());

        return true;
    }

    if (command == "dfs")
    {
        //DEBUG
        std::cout << "      DFS command detected - execute\n";
        //DEBUG

        algorithm::dfs<std::string> dfsObj(&currentGraph);
        dfsObj.run(currentGraph.GetVertex(arg1));
        print_traversal_result<std::string>(dfsObj.get());

        return true;
    }

    if (command == "edmonds")
    {
        //DEBUG
        std::cout << "      Edmonds command detected - execute\n";
        //DEBUG

        algorithm::edmonds_karp<std::string> edmondsObj(&currentGraph);
        edmondsObj.run(currentGraph.GetVertex(arg1),
                       currentGraph.GetVertex(arg2));

        print_graph<std::string>(currentGraph);

        std::cout << "Max possible flow is " << edmondsObj.get() << '\n';

        return true;
    }

    if (command == "dinic")
    {
        //DEBUG
        std::cout << "      Dinic command detected - execute\n";
        //DEBUG

        algorithm::dinic<std::string> dinicObj(&currentGraph);
        dinicObj.run(currentGraph.GetVertex(arg1),
                     currentGraph.GetVertex(arg2));

        print_graph<std::string>(currentGraph);

        std::cout << "Max possible flow is " << dinicObj.get() << '\n';

        return true;
    }

    std::cout << "Unknown command - terminate\n";
    return false;
}


//==============================================================================
// End of runner.cpp
// (note: the newline at the end of the file is intentional)
//==============================================================================
