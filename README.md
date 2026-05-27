 # Custom Containers & Algorithms

  Note: This project was created only to understand how containers work
  and was not made to replace any in the STL.

  
  A C++ library of hand-rolled data structures and algorithms built from scratch,
  applied to a real-world pathfinding demo across British Columbia cities.

  ---

  ## Overview

  Every container and algorithm in this project is implemented without using STL
  equivalents (no `std::vector`, `std::unordered_map`, etc.). The capstone demo
  uses these custom structures to run Dijkstra's shortest path across a graph of
  22 BC cities, calculating routes and estimated travel times.

  ---

  ## Implemented Containers

  | Container | Description |
  |---|---|
  | `Vector<T>` | Dynamic array with copy/move semantics, iterator support, automatic resizing |
  | `Array<T>` | Fixed-size stack-allocated array |
  | `LinkedList<T>` | Singly linked list |
  | `PriorityQueue<T>` | Min/max priority queue |
  | `UnorderedMap<K, V>` | Hash map with key-value storage |
  | `ContainerIterator<T>` | Generic iterator compatible with all custom containers |

  ## Implemented Graph Structures

  | Structure | Algorithm | Description |
  |---|---|---|
  | `WeightedGraph<T, W>` | Dijkstra's | Shortest path in a weighted undirected graph |
  | `MSTGraph<T, W>` | Prim's | Minimum spanning tree |
  | `MSTGraphK<T, W>` | Kruskal's | Minimum spanning tree (union-find approach) |
  | `Graph<T>` | — | Unweighted adjacency-list graph |

  ## Implemented Spatial Structures

  | Structure | Description |
  |---|---|
  | `KDTree<T, K>` | K-dimensional tree for nearest-neighbour search and range queries |

  ---

  ## GPS Pathfinding Demo

  The main project applies all custom containers to a real scenario: finding the
  shortest driving route between BC cities using Dijkstra's algorithm.

  - **22 cities** mapped with approximate real-world kilometre coordinates
  - **Roads** connected based on actual BC highway routes
  - **Routes solved:** Vancouver → Cranbrook, Prince Rupert → Kelowna, Fort Nelson → Creston
  - **Output:** full path, total distance in km, estimated travel time at 80 km/h

  Route: Vancouver to Cranbrook
  Path: Vancouver -> Abbotsford -> Kelowna -> Revelstoke -> Cranbrook
  Total Distance: 412.3 km
  Estimated Travel Time @ 80 km/h: 5h 9m

  ---

  ## Project Structure

  CustomContainers/
  ├── CustomContainers/     — Main project (containers + GPS demo)
  ├── BinarySearchTree/     — BST implementation
  ├── AAPAlgorithms/        — Sorting and searching algorithms
  └── GraphsExercise/       — Graph traversal exercises

  ---

  ## Building

  ### Requirements
  - Visual Studio 2022
  - No external dependencies

  ### Steps
  1. Open `CustomContainers.sln` in Visual Studio
  2. Select a project from the solution (CustomContainers, BinarySearchTree, etc.)
  3. Set configuration to **Debug x64**
  4. Build and run

  ---

  ## Tech

  - **Language:** C++17
  - **Build:** Visual Studio / MSBuild
  - **STL usage:** Intentionally minimal — containers are built from scratch as a learning exercise

  ---
