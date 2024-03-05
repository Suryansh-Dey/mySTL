#include <bits/stdc++.h>
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

    private:
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
         * 
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
         * - time complexity O(1)
         * @return
         * - `Node::UNDEFINED_NODE` if `this` is at dead end
         * - `NodeId` of newly visited `node` otherwise
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
        std::vector<Node> graph;

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
    };
}
using namespace MyStl;
template <typename type>
void MyStl::print1D(type array1D)
{
    for (auto element : array1D)
        std::cout << element << ' ';
}
template <typename type>
void MyStl::print1D(type array1D, size_t size)
{
    for (size_t i = 0; i < size; i++)
        std::cout << array1D[i] << ' ';
}
std::pair<uint32_t, uint32_t> MyStl::firstDifferenceFile(const char *outputFilePath, const char *testFilePath)
{
    std::ifstream outputFile(outputFilePath), testFile(testFilePath);
    uint32_t lineNo = 0;
    std::string outputLine, testLine;
    bool outputEOF = false, testEOF = false;
    while (!testEOF && !outputEOF)
    {
        if (testLine.size() != outputLine.size() && (testLine.size() + 1 != outputLine.size() || outputLine[outputLine.size() - 1] >= '0'))
            return std::make_pair(lineNo + 1, outputLine.size());
        for (uint32_t colNo = 0; colNo < outputLine.size(); colNo++)
        {
            if (outputLine[colNo] != testLine[colNo] && colNo != outputLine.size() - 1 && outputLine[outputLine.size() - 1] >= '0')
                return std::make_pair(lineNo + 1, colNo + 1);
        }
        lineNo++;
        outputEOF = bool(getline(outputFile, outputLine));
        testEOF = bool(getline(testFile, testLine));
    }
    if(outputEOF || testEOF)
        return std::make_pair(lineNo, 0);
    return std::make_pair(0, 0);
}
BitArray::BitArray(uint32_t size) : size(size), bits(size / elementSize + size % elementSize != 0)
{
}
void BitArray::set(uint32_t index)
{
    this->bits[index / elementSize] |= 1ULL << (index % elementSize);
}
void BitArray::unset(uint32_t index)
{
    this->bits[index / elementSize] &= ~(1ULL << (index % elementSize));
}
bool BitArray::get(uint32_t index)
{
    return this->bits[index / elementSize] & (1ULL << (index % elementSize));
}
void BitArray::operator|=(BitArray &bitArray)
{
    for (uint32_t elementNo = 0; elementNo < this->bits.size() && elementNo < bitArray.bits.size(); elementNo++)
        this->bits[elementNo] |= bitArray.bits[elementNo];
}
void BitArray::operator&=(BitArray &bitArray)
{
    for (uint32_t elementNo = 0; elementNo < this->bits.size() && elementNo < bitArray.bits.size(); elementNo++)
        this->bits[elementNo] &= bitArray.bits[elementNo];
}
void BitArray::operator^=(BitArray &bitArray)
{
    for (uint32_t elementNo = 0; elementNo < this->bits.size() && elementNo < bitArray.bits.size(); elementNo++)
        this->bits[elementNo] ^= bitArray.bits[elementNo];
}
void BitArray::bitwiseNot()
{
    for (uint32_t elementNo = 0; elementNo < this->bits.size(); elementNo++)
        this->bits[elementNo] = ~(this->bits[elementNo]);
}
BitArray BitArray::operator~() const
{
    BitArray bitArray = *this;
    for (uint32_t elementNo = 0; elementNo < bitArray.bits.size(); elementNo++)
        bitArray.bits[elementNo] = ~(bitArray.bits[elementNo]);
    return bitArray;
}
void BitArray::print() const
{
    for (uint32_t elementNo = 0; elementNo < this->bits.size(); elementNo++)
    {
        for (uint32_t bitNo = 0; bitNo < elementSize && bitNo + elementSize * elementNo < this->getSize(); bitNo++)
        {
            if (bitNo == 8)
                printf(" ");
            printf("%c ", bool(this->bits[elementNo] & (1ULL << bitNo)));
        }
    }
}
uint32_t BitArray::getSize() const
{
    return this->size;
}
Node::Node(NodeId nodeId) : nodeId(nodeId)
{
    if (nodeId == Node::UNDEFINED_NODE)
        throw std::runtime_error("Node id should be a natural number\n");
}
void Node::point(const Node &node, Neighbour::Weight weight)
{
    this->neighbours.emplace_back(Neighbour{node.nodeId, weight});
}
bool Node::unpoint(const Node &node)
{
    for (Neighbour &neighbour : this->neighbours)
    {
        if (neighbour.nodeId == node.nodeId)
        {
            neighbour.nodeId = Node::UNDEFINED_NODE;
            return true;
        }
    }
    return false;
}
bool Node::unpointLastVisit(Graph &graph)
{
    if (this->lastVisited().nodeId == Node::UNDEFINED_NODE)
        return false;
    this->neighbours[this->neighbourIndexToVisit - 1].nodeId = Node::UNDEFINED_NODE;
    return true;
}
void Node::connect(Node &node, Neighbour::Weight weight)
{
    this->neighbours.emplace_back(Neighbour{node.nodeId, weight});
    node.neighbours.emplace_back(Neighbour{this->nodeId, weight});
}
bool Node::disconnect(Node &node)
{
    for (Neighbour &neighbour : this->neighbours)
    {
        if (neighbour.nodeId == node.nodeId)
        {
            neighbour.nodeId = Node::UNDEFINED_NODE;
            goto nextStep;
        }
    }
    return false;
nextStep:
    for (Neighbour &neighbour : node.neighbours)
    {
        if (neighbour.nodeId == this->nodeId)
        {
            neighbour.nodeId = Node::UNDEFINED_NODE;
            break;
        }
    }
    return true;
}
bool Node::disconnectLastVisit(Graph &graph)
{
    if (this->lastVisited().nodeId == Node::UNDEFINED_NODE)
        return false;
    for (Neighbour &neighbour : graph[this->neighbours[this->neighbourIndexToVisit - 1].nodeId].neighbours)
    {
        if (neighbour.nodeId == this->nodeId)
        {
            neighbour.nodeId = Node::UNDEFINED_NODE;
            this->neighbours[this->neighbourIndexToVisit - 1].nodeId = Node::UNDEFINED_NODE;
            return true;
        }
    }
    return false;
}
Node::Neighbour Node::move(Graph &graph)
{
    for (uint32_t neighbourInex = this->neighbourIndexToVisit; neighbourInex < neighbours.size(); neighbourInex++)
    {
        if (not graph[neighbours[neighbourInex].nodeId].isVisited() && neighbours[neighbourInex].nodeId != Node::UNDEFINED_NODE)
        {
            graph[neighbours[neighbourInex].nodeId].markVisited(this->nodeId);
            this->neighbourIndexToVisit = neighbourInex + 1;
            return neighbours[neighbourInex];
        }
    }
    return Neighbour{Node::UNDEFINED_NODE, 0};
}
Node::NodeId Node::lastVisitorId() const
{
    return this->visitorNodeId;
}
Node::Neighbour Node::lastVisitor(const Graph &graph) const
{
    return Neighbour{this->lastVisitorId(), graph[this->lastVisitorId()].lastVisited().weight};
}
void Node::markVisited(NodeId visitorNodeId)
{
    this->visitorNodeId = visitorNodeId;
}
bool Node::isVisited() const
{
    return this->visitorNodeId != UNDEFINED_NODE;
}
void Node::reset()
{
    this->visitorNodeId = Node::Node::UNDEFINED_NODE;
    this->neighbourIndexToVisit = 0;
}
Node::Neighbour Node::lastVisited() const
{
    return this->neighbourIndexToVisit == 0 ? Neighbour{Node::UNDEFINED_NODE, 0} : this->neighbours[this->neighbourIndexToVisit - 1];
}
Node::Neighbour Node::hasVisitedNeighbour(const Graph &graph) const
{
    for (Neighbour neighbour : this->neighbours)
    {
        if (graph[neighbour.nodeId].isVisited() && graph[neighbour.nodeId].nodeId != this->lastVisitorId())
            return neighbour;
    }
    return Neighbour{Node::UNDEFINED_NODE, 0};
}
uint32_t Node::neighbourCount() const
{
    return this->neighbours.size();
}
std::vector<Node::Neighbour> Node::get_neighbours() const
{
    return this->neighbours;
}
void Node::priortiseNeighbourByHeighWeight()
{
    std::sort(this->neighbours.begin(), this->neighbours.end(), [](Neighbour neighbour1, Neighbour neighbour2)
              { return neighbour1.weight > neighbour2.weight; });
}
void Node::priortiseNeighbourByLowWeight()
{
    std::sort(this->neighbours.begin(), this->neighbours.end(), [](Neighbour neighbour1, Neighbour neighbour2)
              { return neighbour1.weight < neighbour2.weight; });
}
void Node::priortiseNeighbourByHeighNodeId()
{
    std::sort(this->neighbours.begin(), this->neighbours.end(), [](Neighbour neighbour1, Neighbour neighbour2)
              { return neighbour1.nodeId > neighbour2.nodeId; });
}
void Node::priortiseNeighbourByLowNodeId()
{
    std::sort(this->neighbours.begin(), this->neighbours.end(), [](Neighbour neighbour1, Neighbour neighbour2)
              { return neighbour1.nodeId < neighbour2.nodeId; });
}

Graph::Graph(uint32_t nodeCount)
{
    this->graph.emplace_back(Node(nodeCount));
    for (uint32_t nodeNo = 1; nodeNo <= nodeCount; nodeNo++)
        this->graph.emplace_back(Node(nodeNo));
}
void Graph::reset()
{
    for (Node &node : this->graph)
        node.reset();
}
Node &Graph::operator[](Node::NodeId nodeId)
{
    return graph[nodeId];
}
const Node &Graph::operator[](Node::NodeId nodeId) const
{
    return graph[nodeId];
}
void Graph::priortiseNeighbourByHeighWeight()
{
    for (Node &node : this->graph)
    {
        node.priortiseNeighbourByHeighWeight();
        node.reset();
    }
}
void Graph::priortiseNeighbourByLowWeight()
{
    for (Node &node : this->graph)
    {
        node.priortiseNeighbourByLowWeight();
        node.reset();
    }
}
void Graph::priortiseNeighbourByHeighNodeId()
{
    for (Node &node : this->graph)
    {
        node.priortiseNeighbourByHeighNodeId();
        node.reset();
    }
}
void Graph::priortiseNeighbourByLowNodeId()
{
    for (Node &node : this->graph)
    {
        node.priortiseNeighbourByLowNodeId();
        node.reset();
    }
}
void Graph::inputEdges(uint32_t numberOfEdges)
{
    for (uint32_t edgeNo = 0; edgeNo < numberOfEdges; edgeNo++)
    {
        int node1, node2, weight;
        scanf("%d%d%d", &node1, &node2, &weight);
        this->graph[node1].connect(graph[node2], weight);
    }
}
void Graph::inputDirectedEdges(uint32_t numberOfEdges)
{
    for (uint32_t edgeNo = 0; edgeNo < numberOfEdges; edgeNo++)
    {
        int node1, node2, weight;
        scanf("%d%d%d", &node1, &node2, &weight);
        this->graph[node1].point(graph[node2], weight);
    }
}