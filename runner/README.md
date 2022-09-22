# Runner

A simple command-line tool for **graph-lib** library, which allows to execute algorithms on input graphs.

## Installation

1. Move runner folder outside of `graph-lib` directory
2. Add a copy of `graph-lib` library beside `include` and `src` directories
3. Install:
 
```bash
# build
cd ${build_dir}
cmake -S ${runner_dir}
cmake --build .
```

## Usage

Upon launching executable it starts to accept commands in form `[command] [graph file] [argument1] [argument2]`, each on a separate line.

Possible commands:
* `quit` - stops runner loop
* `dfs file vertex` - execute *DFS* algorithm on graph from *file* starting with *vertex*.
* `bfs file vertex` - execute *BFS* algorithm on graph from *file* starting with *vertex*.
* `edmonds file source sink` - execute *Edmonds*-Karp algorithm on graph from *file* computing flow from *source* to *sink*.
* `edmonds file source sink` - execute *Dinic* algorithm on graph from *file* computing flow from *source* to *sink*.

Example:
```bash
./runner
# enter command
dfs mygraph.txt vertex1
edmonds anothergraph.txt source sink
quit
```

## Graph input file format

**Rules**:
* Each vertex/edge is on a separate line
* Vertices are separated from edges by a line containing `---`.
* Vertices are put before edges.
* Edge has the following strucutre `<[vertex1] [vertex2] [direction] [weight] [capacity] [flow]>`.
    * `[vertex1]` and `[vertex2]` data fields are **required**, the others are optional. However, if you want to specify let's say
    edge capacity - you must also specify all fields before it (direction and weight). Default values for each data field is:
        * `[direction]`: `---`
        * `[weight]`: 0
        * `[capacity]`: 0
        * `[flow]`: 0
    * Edge data fields are delimeted by a single space character.

**Example**:
Consider the following graph
```
       0/5
 (1) -----> (4)
  |    2     |
1 |          |
  |          |
  V    3/7   |
 (2) -----> (3)

```
The corresponding description file graph.txt will look like this:
```
1
2
3
4
---
1 2 --> 1
1 4 --> 2 5
2 3 --> 0 7 3
3 4
```
