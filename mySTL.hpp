#include <bits/stdc++.h>
#pragma once
namespace MyStl
{
    template <typename type>
    void print1D(type array1D);
    template <typename type>
    void print1D(type array1D, size_t size);
    std::pair<uint32_t, uint32_t> firstDifferenceFile(const char *outputFilePath, const char *testFilePath);

    class BitArray
    {
        typedef std::vector<unsigned long long> Bits;

    public:
        BitArray(uint32_t size);
        void set(uint32_t index);
        void unset(uint32_t index);
        bool get(uint32_t index);
        void operator|=(BitArray &);
        void operator&=(BitArray &);
        void operator^=(BitArray &);
        void bitwiseNot();
        BitArray operator~() const;
        void print() const;
        inline uint32_t getSize() const;

    protected:
        static constexpr uint32_t elementSize = sizeof(unsigned long long) * 8;
        uint32_t size;
        Bits bits;
    };

    class Graph;
    class Node
    {
        friend Graph;

    public:
        typedef unsigned int NodeId;
        struct Neighbour
        {
            typedef int Weight;
            NodeId nodeId;
            Weight weight;
        };
        static constexpr uint32_t UNDEFINED_NODE = 0;
        Node(NodeId nodeId);
        /**
         * @warning
         * connecting with Node of NodeId = 0 will lead to undefined behaviour
         */
        void point(const Node &node, Neighbour::Weight weight);
        /**
         * Disconnects `this` from `node`
         * - time complexity O(`this.neighbourCount`)
         * @return
         * - `false` on failure due to no existing connection
         * of `this` with `node`
         * - `true` otherwise
         */
        bool unpoint(const Node &node);
        /**
         * Disconnects the `node` which `this` visited last time
         * - time complexity O(1)
         * @return
         * - `false` if `this` never visited any node
         * - `true` otherwise
         */
        bool unpointLastVisit(Graph &graph);
        /**
         * @warning
         * connecting with Node of NodeId = 0 will lead to undefined behaviour
         */
        void connect(Node &node, Neighbour::Weight weight);
        /**
         * Disconnects `this` from `node`
         * - time complexity O(`this.neighbourCount`)
         * @return
         * - `false` on failure due to no existing connection
         * of `this` with `node`
         * - `true` otherwise
         */
        bool disconnect(Node &node);
        /**
         * Disconnects the `node` which `this` visited last time
         * - time complexity O(1)
         * @return
         * - `false` if `this` never visited any node || on failure due to
         * no existing connection of `this` with `node`
         * - `true` otherwise
         */
        bool disconnectLastVisit(Graph &graph);
        /**
         * - moves to an unvisited node
         * - time complexity at worst case O(neighbour count)
         * however, even if you call the function number of times before
         * last Neighbour is reached and before Graph::reset() is called, total time complexity will still be
         * O(neighbour count) instead of number of calls * O(neighbour count)
         * @return
         * - `Node::UNDEFINED_NODE` if `this` is at dead end
         * - `NodeId` of newly visited `node` otherwise
         * @note
         * it doesn't mark it to be visited
         */
        Neighbour move(Graph &graph);
        /**
         * - time complexity O(1)
         * @return
         * - `Node::UNDEFINED_NODE` if `this` is unvisited `node`
         * - `NodeId` of last visitor of `this` otherwise
         */
        inline NodeId lastVisitorId() const;
        /**
         * - time complexity O(1)
         * @return
         * - `Neighbour` which visited `this` last time
         * - `Neighbour{nodeId = UNDEFINED_NODE, weight = 0}` if `this` is unvisited
         */
        inline Neighbour lastVisitor(const Graph &graph) const;
        /**
         * - time complexity O(1)
         */
        inline void markVisited(NodeId visitorNodeId);
        /**
         * - time complexity O(1)
         */
        inline bool isVisited() const;
        /**
         * - time complexity O(1)
         * @return
         * - `Neighbour` which `this` visited last time
         * - `Neighbour{nodeId = UNDEFINED_NODE, weight = 0}` if `this` never visited any node
         */
        inline Neighbour lastVisited() const;
        /**
         * - time complexity O(`this.neighbourCount`)
         * @return
         * - `Neighbour` (whose `nodeId` is `true` if treated as boolean) which is visited by any node
         * EXCEPT FOR THE NEIGHBOUR NODE WHICH VISITED `this` LAST TIME
         * - `Neighbour{nodeId = UNDEFINED_NODE, weight = 0}` (whose `nodeId` is `false` if treated as boolean) if no such node found
         */
        inline Neighbour hasVisitedNeighbour(const Graph &graph) const;
        /**
         * - time complexity O(1)
         */
        inline uint32_t neighbourCount() const;
        /**
         * - time complexity O(`this.neighbourCount`)
         */
        inline std::vector<Neighbour> get_neighbours() const;
        /**
         * - time complexity O(`this.neighbourCount` * log(`this.neighbourCount`))
         */
        inline void priortiseNeighbourByHeighWeight();
        /**
         * - time complexity O(`this.neighbourCount` * log(`this.neighbourCount`))
         */
        inline void priortiseNeighbourByLowWeight();
        /**
         * - time complexity O(`this.neighbourCount` * log(`this.neighbourCount`))
         */
        inline void priortiseNeighbourByHeighNodeId();
        /**
         * - time complexity O(`this.neighbourCount` * log(`this.neighbourCount`))
         */
        inline void priortiseNeighbourByLowNodeId();

    protected:
        inline void reset();
        NodeId nodeId;
        std::vector<Neighbour> neighbours;
        NodeId visitorNodeId = UNDEFINED_NODE;
        uint32_t neighbourIndexToVisit = 0;
    };

    class Graph
    {
    public:
        Graph(uint32_t nodeCount);
        Node &operator[](Node::NodeId nodeId);
        const Node &operator[](Node::NodeId nodeId) const;
        void reset();
        void priortiseNeighbourByHeighWeight();
        void priortiseNeighbourByLowWeight();
        void priortiseNeighbourByHeighNodeId();
        void priortiseNeighbourByLowNodeId();
        void inputEdges(uint32_t numberOfEdges);
        void inputDirectedEdges(uint32_t numberOfEdges);
        /**
         * - `time complexity` O(next unvisited NodeId - last returned NodeId)
         * - In long, even if you call the function number of times before
         * last NodeId is reached and before Graph::reset() is called, total time complexity will still be
         * O(last NodeId or number of nodes) instead of number of calls
         * * O(last NodeId or number of nodes)
         * @return
         * - `NodeId` of first unvisited node in the graph
         * - `UNDEFINED_NODE` if all nodes in the graph is visited already
         */
        Node::NodeId unvisitedNode();

    protected:
        std::vector<Node> graph;
        Node::NodeId lastUnvisitedNodeId = 1;
    };
}
//lib files
#include "src/others.cpp"
#include "src/bitArray.cpp"
#include "src/graph.cpp"