/*Author: Suryansh Dey
This is free library;
There is NO warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/
#pragma once
#include <bits/stdc++.h>
namespace MyStl
{
    template <typename type>
    void print1D(type array1D) noexcept;
    template <typename type>
    void print1D(type array1D, size_t size) noexcept;
    /**
     * @return
     * - `(line_number, column_number)` of first difference
     * - `std::pair(0, 0)` if both files are same
     * - `std::pair(min(lines_in_outputFile, lines_in_testFile), 0)` if
     * they have different number of lines
     * @exception
     * if cannot open the given outputFilePath or testFilePath
     * @note
     * it ignores one trailing space of outputFile lines (if present) and one trailing blank line
     * of outputFile (if present)
     */
    std::pair<uint32_t, uint32_t> fileFirstDifference(const char *outputFilePath, const char *testFilePath);
    /**
     * syntax:
     * FOR(number_of_times_to_loop){
     *      cout << "Note: i is accessible here: " << i << '\n';
     * }
     * @note
     * i is accessible inside the loop which varies from 1 to number_of_times_to_loop-1
     * throught the loop as usual
     */
#define FOR(end) for (int i = 0; i < end; i++)

    class BitArray
    {
        typedef std::vector<unsigned long long> Bits;

    public:
        BitArray(uint32_t size) noexcept;
        /**
         * @warning
         * trying to excess index < 1 or index >= `this->size` will
         * lead to exception from std::vector or undefined behaviour
         */
        void set(uint32_t index);
        /**
         * @warning
         * trying to excess index < 1 or index >= `this->size` will
         * lead to exception from std::vector or undefined behaviour
         */
        void unset(uint32_t index);
        /**
         * @warning
         * trying to excess index < 1 or index >= `this->size` will
         * lead to exception from std::vector or undefined behaviour
         */
        bool get(uint32_t index);
        void operator|=(BitArray &) noexcept;
        void operator&=(BitArray &) noexcept;
        void operator^=(BitArray &) noexcept;
        void bitwiseNot() noexcept;
        BitArray operator~() const noexcept;
        void print() const noexcept;
        inline uint32_t getSize() const noexcept;

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
         * - time complexity O(1)
         */
        NodeId get_nodeId() const noexcept;
        /**
         * - creates an directed edge
         * - time complexity O(1)
         * @warning
         * connecting with Node of NodeId = 0 will lead to undefined behaviour
         */
        void point(const Node &node, Neighbour::Weight weight);
        /**
         * Disconnects `this` from `node`
         * - time complexity O(`this->neighbourCount`)
         * @return
         * - `false` on failure due to no existing connection
         * of `this` with `node`
         * - `true` otherwise
         */
        bool unpoint(const Node &node) noexcept;
        /**
         * Disconnects the `node` which `this` visited last time
         * - time complexity O(1)
         * @return
         * - `false` if `this` never visited any node
         * - `true` otherwise
         */
        bool unpointLastVisit(Graph &graph) noexcept;
        /**
         * creates an undirected edge
         * time complexity O(1)
         * @warning
         * connecting with Node of NodeId = 0 will lead to undefined behaviour
         */
        void connect(Node &node, Neighbour::Weight weight);
        /**
         * Disconnects `this` from `node`
         * - time complexity O(`this->neighbourCount`)
         * @return
         * - `false` on failure due to no existing connection
         * of `this` with `node`
         * - `true` otherwise
         */
        bool disconnect(Node &node) noexcept;
        /**
         * Disconnects the `node` which `this` visited last time
         * - time complexity O(1)
         * @return
         * - `false` if `this` never visited any node || on failure due to
         * no existing connection of `this` with `node`
         * - `true` otherwise
         */
        bool disconnectLastVisit(Graph &graph) noexcept;
        /**
         * - average time complexity O(1)
         * - worst time complexity O(`this->neighbourCount`)
         * however, even if you call the function number of times before
         * Graph::reset() is called, total time complexity will still be
         * O(`this->neighbourCount`) instead of O(number of calls * this->neighbourCount)
         * @return
         * - `Node::UNDEFINED_NODE` if `this` is at dead end or all the neighbours
         * are already visited by `this`
         * - `NodeId` of newly visited `node` otherwise
         * @note
         * - it never returns the neighbour which visited `this` last time
         * - it doesn't mark it to be visited
         */
        Neighbour move(Graph &graph) noexcept;
        /**
         * - time complexity at worst case O(`this->neighbourCount`)
         * however, even if you call the function number of times before
         * Graph::reset() is called, total time complexity will still be
         * O(`this->neighbourCount`) instead of O(number of calls * this->neighbourCount)
         * @return
         * - `Node::UNDEFINED_NODE` if `this` is at dead end or all the neighbours
         * are already visited
         * - `NodeId` of newly visited `node` otherwise
         * @note
         * - it never returns the neighbour which visited `this` last time
         * - it doesn't mark it to be visited
         */
        Neighbour moveUnvisited(Graph &graph) noexcept;
        /**
         * - time complexity O(1)
         * @return
         * - `Node::UNDEFINED_NODE` if `this` is unvisited `node`
         * - `NodeId` of last visitor of `this` otherwise
         */
        inline NodeId lastVisitorId() const noexcept;
        /**
         * - time complexity O(1)
         * @return
         * - `Neighbour` which visited `this` last time
         * - `Neighbour{nodeId = UNDEFINED_NODE, weight = 0}` if `this` is unvisited
         */
        inline Neighbour lastVisitor(const Graph &graph) const noexcept;
        /**
         * - time complexity O(1)
         */
        inline void markVisited(NodeId visitorNodeId) noexcept;
        /**
         * - time complexity O(1)
         */
        inline bool isVisited() const noexcept;
        /**
         * - time complexity O(1)
         * @return
         * - `Neighbour` which `this` visited last time
         * - `Neighbour{nodeId = UNDEFINED_NODE, weight = 0}` if `this` never visited any node
         */
        inline Neighbour lastVisited() const noexcept;
        /**
         * - time complexity O(`this->neighbourCount`)
         * @return
         * - `Neighbour` (whose `nodeId` is `true` if treated as boolean) which is visited by any node
         * EXCEPT FOR THE NEIGHBOUR NODE WHICH VISITED `this` LAST TIME
         * - `Neighbour{nodeId = UNDEFINED_NODE, weight = 0}` (whose `nodeId` is `false` if treated as boolean) if no such node found
         */
        inline Neighbour hasVisitedNeighbour(const Graph &graph) const noexcept;
        /**
         * - time complexity O(1)
         */
        inline uint32_t neighbourCount() const noexcept;
        /**
         * - time complexity O(1)
         * @note
         * higher the index of a neighbour lower the priorty
         */
        inline const std::vector<Neighbour> &get_neighbours() const noexcept;
        /**
         * - time complexity O(priorty it has already)
         * @return
         * - higher the number lower the priorty
         * - `0` representing ` highest priorty
         * @exception
         * - if there is no neighbour of given NodeId
         */
        uint32_t get_priorty(Node::NodeId Neighbour) const;
        /**
         * - time complexity O(priorty it has already)
         * @exception
         * - if there is no neighbour of given NodeId
         */
        inline void priortiseNeighbourHighest(Node::NodeId neighbour);
        /**
         * - time complexity O(priorty it has already)
         * @exception
         * - if there is no neighbour of given NodeId
         */
        inline void priortiseNeighbourLowest(Node::NodeId neighbour);
        /**
         * - time complexity O(`this->neighbourCount` * log(`this->neighbourCount`))
         */
        inline void priortiseNeighbourByHeighWeight() noexcept;
        /**
         * - time complexity O(`this->neighbourCount` * log(`this->neighbourCount`))
         */
        inline void priortiseNeighbourByLowWeight() noexcept;
        /**
         * - time complexity O(`this->neighbourCount` * log(`this->neighbourCount`))
         */
        inline void priortiseNeighbourByHeighNodeId() noexcept;
        /**
         * - time complexity O(`this->neighbourCount` * log(`this->neighbourCount`))
         */
        inline void priortiseNeighbourByLowNodeId() noexcept;

    protected:
        inline void reset() noexcept;
        NodeId nodeId;
        std::vector<Neighbour> neighbours;
        NodeId visitorNodeId = UNDEFINED_NODE;
        uint32_t neighbourIndexToVisit = 0;
    };

    class Graph
    {
    public:
        Graph(uint32_t nodeCount);
        /**
         * - time complexity O(1)
         */
        uint32_t nodeCount() const noexcept;
        /**
         * @warning
         * trying to excess index < 1 or index >= `this->nodeCount` will
         * lead to exception from std::vector or undefined behaviour
         */
        Node &operator[](Node::NodeId nodeId);
        /**
         * @warning
         * trying to excess index < 1 or index >= `this->nodeCount` will
         * lead to exception from std::vector or undefined behaviour
         */
        const Node &operator[](Node::NodeId nodeId) const;
        /**
         * - resets the whole graph to just initialised state but don't disconnect or connect
         * any pair of nodes
         * - time complexity O(`this->nodeCount`)
         */
        void reset() noexcept;
        /**
         * - time complexity O(`this->nodeCount` * log(`this->nodeCount`))
         */
        void priortiseNeighbourByHeighWeight() noexcept;
        /**
         * - time complexity O(`this->nodeCount` * log(`this->nodeCount`))
         */
        void priortiseNeighbourByLowWeight() noexcept;
        /**
         * - time complexity O(`this->nodeCount` * log(`this->nodeCount`))
         */
        void priortiseNeighbourByHeighNodeId() noexcept;
        /**
         * - time complexity O(`this->nodeCount` * log(`this->nodeCount`))
         */
        void priortiseNeighbourByLowNodeId() noexcept;
        void inputEdges(uint32_t numberOfEdges) noexcept;
        void inputDirectedEdges(uint32_t numberOfEdges) noexcept;
        /**
         * - time complexity O(next unvisited NodeId - last returned NodeId)
         * - In long, even if you call the function number of times before
         * last NodeId is reached and before Graph::reset() is called, total time complexity will still be
         * O(last NodeId or number of nodes) instead of O(number of calls
         * * last NodeId or number of nodes)
         * @return
         * - `NodeId` of first unvisited node in the graph
         * - `UNDEFINED_NODE` if all nodes in the graph is visited already
         */
        Node::NodeId unvisitedNode() noexcept;
        /**
         * - adds `nodeCount` number of nodes
         * - time complexity O(nodeCount)
         */
        void add(uint32_t nodeCount = 1);
        /**
         * - removes last node
         * - time complexity O(1)
         */
        void pop_back() noexcept;

    protected:
        std::vector<Node> graph;
        Node::NodeId lastUnvisitedNodeId = 1;
    };
}
// MYSTL_END
#include "src/others.cpp"
#include "src/bitArray.cpp"
#include "src/graph.cpp"