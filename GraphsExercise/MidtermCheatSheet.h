#pragma once
/*
* 

vector → fast access, contiguous, cache-friendly, few allocations O(n) 
list   → fast insert/remove, stable iterators, many allocations (doubly linked list) O(n) deque   → fast insert/remove at both ends, contiguous blocks of memory, O(n)

Big O notion: O(1) < O(log n) < O(n) < O(n log n) < O(n²) < O(2ⁿ)
means that the time (or space) complexity of an algorithm grows at most as fast as the function inside the O() notation, ignoring constant factors and lower-order terms.
used to describe the upper bound of an algorithm's growth rate, providing a way to compare the efficiency of different algorithms as the input size increases.
- way to compare and predict the performance of algorithms, especially for large input sizes, by focusing on their growth rates rather than specific implementation details or hardware characteristics.
- can  be used to determine which algorithm to use for a given problem, especially when dealing with large datasets, by analyzing their time and space complexities.
- Manage expectation to maintain faster processing systems

Stack → LIFO (Last In, First Out) data structure, where the last element added is the first one to be removed. O(1) for push and pop operations.
Queue → FIFO (First In, First Out) data structure, where the first element added is the first one to be removed. O(1) for enqueue and dequeue operations.
-difference between stack and queue is the order in which elements are added and removed. In a stack, 
-the last element added is the first one to be removed (LIFO), while in a queue, the first element added is the first one to be removed (FIFO).

Heap and Priority Queue:
- Heap is a specialized tree-based data structure that satisfies the heap property, where the parent node is either greater than or equal to (max-heap) or less than or equal to (min-heap) its child nodes.
insertion and deletion is O(log n) converting sequential data into a heap is O(n)


- Priority Queue is an abstract data type that operates similarly to a regular queue but with an added feature: each element has a priority associated with it.
Elements with higher priority are dequeued before elements with lower priority.

KD Tree:
a binary tree
each node represents k demnsions (k-dimensional point)
right non leaf node generated a hyperplane that divides the space into two parts, and the left non leaf node generated a hyperplane that divides the space into two parts
0(log n) for search, insertion, and deletion operations in a balanced KD Tree, but can degrade to O(n) in the worst case (e.g., when the tree becomes unbalanced).


Graphs:
- series of nodes that branch things together
- can be used to represent relationships between entities, such as social networks, transportation systems, or computer networks.
- can be directed (edges have a direction) or undirected (edges do not have a direction).
- can be weighted (edges have weights or costs) or unweighted (edges do not have weights).

A graph:

✅ Can branch

✅ Can loop back

✅ Can have cycles

✅ Can have multiple paths between the same points

✅ Does not need a single root

A tree:

❌ No cycles

❌ One parent per node

❌ Clear top-down branching

BFS (Breadth-First Search) and DFS (Depth-First Search) are two common graph traversal algorithms.
- BFS explores the graph level by level, starting from a given source node and visiting all 
its neighbors before moving on to the neighbors' neighbors. It uses a queue data structure to keep track of the
nodes to be explored next. 
BFS is useful for finding the shortest path in an unweighted graph and for traversing all nodes in a graph.

DFS explores the graph by going as deep as possible along each branch before backtracking. 
It uses a stack data structure (or recursion) to keep track of the nodes to be explored next. 
DFS is useful for tasks such as topological sorting, detecting cycles in a graph, 
and exploring all possible paths in a graph.

DFS:
Depth-First Search explores nodes using a stack, going as deep as possible before backtracking.

BFS:
Breadth-First Search explores nodes using a queue and finds the shortest path in an unweighted graph.


*/




