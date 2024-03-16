#include "../mySTL.hpp"

MyStl::Node::Node(NodeId nodeId) : nodeId(nodeId)
{
    if (nodeId == MyStl::Node::UNDEFINED_NODE)
        throw std::runtime_error("MyStl::Node::Node() failed.\nNode id should be a natural number\n");
}
void MyStl::Node::point(const Node &node, Neighbour::Weight weight) noexcept
{
    this->neighbours.emplace_back(Neighbour{node.nodeId, weight});
}
bool MyStl::Node::unpoint(const Node &node) noexcept
{
    for (Neighbour &neighbour : this->neighbours)
    {
        if (neighbour.nodeId == node.nodeId)
        {
            neighbour.nodeId = MyStl::Node::UNDEFINED_NODE;
            return true;
        }
    }
    return false;
}
bool MyStl::Node::unpointLastVisit(Graph &graph) noexcept
{
    if (this->lastVisited().nodeId == MyStl::Node::UNDEFINED_NODE)
        return false;
    this->neighbours[this->neighbourIndexToVisit - 1].nodeId = MyStl::Node::UNDEFINED_NODE;
    return true;
}
void MyStl::Node::connect(Node &node, Neighbour::Weight weight) noexcept
{
    this->neighbours.emplace_back(Neighbour{node.nodeId, weight});
    node.neighbours.emplace_back(Neighbour{this->nodeId, weight});
}
bool MyStl::Node::disconnect(Node &node) noexcept
{
    for (Neighbour &neighbour : this->neighbours)
    {
        if (neighbour.nodeId == node.nodeId)
        {
            neighbour.nodeId = MyStl::Node::UNDEFINED_NODE;
            goto nextStep;
        }
    }
    return false;
nextStep:
    for (Neighbour &neighbour : node.neighbours)
    {
        if (neighbour.nodeId == this->nodeId)
        {
            neighbour.nodeId = MyStl::Node::UNDEFINED_NODE;
            break;
        }
    }
    return true;
}
bool MyStl::Node::disconnectLastVisit(Graph &graph) noexcept
{
    if (this->lastVisited().nodeId == MyStl::Node::UNDEFINED_NODE)
        return false;
    for (Neighbour &neighbour : graph[this->neighbours[this->neighbourIndexToVisit - 1].nodeId].neighbours)
    {
        if (neighbour.nodeId == this->nodeId)
        {
            neighbour.nodeId = MyStl::Node::UNDEFINED_NODE;
            this->neighbours[this->neighbourIndexToVisit - 1].nodeId = MyStl::Node::UNDEFINED_NODE;
            return true;
        }
    }
    return false;
}
MyStl::Node::Neighbour MyStl::Node::move(Graph &graph) noexcept
{
    uint32_t neighbourIndex = this->neighbourIndexToVisit;
    while (neighbourIndex < this->neighbours.size() && (this->neighbours[neighbourIndex].nodeId == MyStl::Node::UNDEFINED_NODE || this->neighbours[neighbourIndex].nodeId == this->lastVisitorId()))
    {
        neighbourIndex++;
    }
    this->neighbourIndexToVisit = neighbourIndex + (neighbourIndex < this->neighbours.size());
    return neighbourIndex < this->neighbours.size() ? this->neighbours[neighbourIndex] : Neighbour{MyStl::Node::UNDEFINED_NODE, 0};
}
MyStl::Node::Neighbour MyStl::Node::moveUnvisited(Graph &graph) noexcept
{
    for (uint32_t neighbourIndex = this->neighbourIndexToVisit; neighbourIndex < this->neighbours.size(); neighbourIndex++)
    {
        if (!graph[this->neighbours[neighbourIndex].nodeId].isVisited() && this->neighbours[neighbourIndex].nodeId != MyStl::Node::UNDEFINED_NODE && this->neighbours[neighbourIndex].nodeId != this->lastVisitorId())
        {
            this->neighbourIndexToVisit = neighbourIndex + 1;
            return this->neighbours[neighbourIndex];
        }
    }
    return Neighbour{MyStl::Node::UNDEFINED_NODE, 0};
}
MyStl::Node::NodeId MyStl::Node::lastVisitorId() const noexcept
{
    return this->visitorNodeId;
}
MyStl::Node::Neighbour MyStl::Node::lastVisitor(const Graph &graph) const noexcept
{
    return Neighbour{this->lastVisitorId(), graph[this->lastVisitorId()].lastVisited().weight};
}
void MyStl::Node::markVisited(NodeId visitorNodeId) noexcept
{
    this->visitorNodeId = visitorNodeId;
}
bool MyStl::Node::isVisited() const noexcept
{
    return this->visitorNodeId != MyStl::Node::UNDEFINED_NODE;
}
void MyStl::Node::reset() noexcept
{
    this->visitorNodeId = MyStl::Node::UNDEFINED_NODE;
    this->neighbourIndexToVisit = 0;
}
MyStl::Node::Neighbour MyStl::Node::lastVisited() const noexcept
{
    return this->neighbourIndexToVisit == 0 ? Neighbour{MyStl::Node::UNDEFINED_NODE, 0} : this->neighbours[this->neighbourIndexToVisit - 1];
}
MyStl::Node::Neighbour MyStl::Node::hasVisitedNeighbour(const Graph &graph) const noexcept
{
    for (Neighbour neighbour : this->neighbours)
    {
        if (graph[neighbour.nodeId].isVisited() && graph[neighbour.nodeId].nodeId != this->lastVisitorId())
            return neighbour;
    }
    return Neighbour{MyStl::Node::UNDEFINED_NODE, 0};
}
uint32_t MyStl::Node::neighbourCount() const noexcept
{
    return this->neighbours.size();
}
const std::vector<MyStl::Node::Neighbour> &MyStl::Node::get_neighbours() const noexcept
{
    return this->neighbours;
}
uint32_t MyStl::Node::get_priorty(MyStl::Node::NodeId neighbour) const
{
    uint32_t neighbourIdx = 0;
    while (neighbourIdx < this->neighbours.size())
    {
        if (this->neighbours[neighbourIdx].nodeId == neighbour)
            return neighbourIdx;
        neighbourIdx++;
    }
    throw std::runtime_error("MyStl::Node::get_priorty() failed./nNo neighbour has given NodeId");
}
void MyStl::Node::priortiseNeighbourHighest(MyStl::Node::NodeId neighbour)
{
    std::swap(this->neighbours[get_priorty(neighbour)], this->neighbours[0]);
}
void MyStl::Node::priortiseNeighbourLowest(MyStl::Node::NodeId neighbour)
{
    std::swap(this->neighbours[get_priorty(neighbour)], this->neighbours[this->neighbours.size() - 1]);
}
void MyStl::Node::priortiseNeighbourByHeighWeight() noexcept
{
    std::sort(this->neighbours.begin(), this->neighbours.end(), [](Neighbour neighbour1, Neighbour neighbour2)
              { return neighbour1.weight > neighbour2.weight; });
}
void MyStl::Node::priortiseNeighbourByLowWeight() noexcept
{
    std::sort(this->neighbours.begin(), this->neighbours.end(), [](Neighbour neighbour1, Neighbour neighbour2)
              { return neighbour1.weight < neighbour2.weight; });
}
void MyStl::Node::priortiseNeighbourByHeighNodeId() noexcept
{
    std::sort(this->neighbours.begin(), this->neighbours.end(), [](Neighbour neighbour1, Neighbour neighbour2)
              { return neighbour1.nodeId > neighbour2.nodeId; });
}
void MyStl::Node::priortiseNeighbourByLowNodeId() noexcept
{
    std::sort(this->neighbours.begin(), this->neighbours.end(), [](Neighbour neighbour1, Neighbour neighbour2)
              { return neighbour1.nodeId < neighbour2.nodeId; });
}

MyStl::Graph::Graph(uint32_t nodeCount) noexcept
{
    this->graph.emplace_back(MyStl::Node(nodeCount));
    for (uint32_t nodeNo = 1; nodeNo <= nodeCount; nodeNo++)
        this->graph.emplace_back(MyStl::Node(nodeNo));
}
void MyStl::Graph::reset() noexcept
{
    for (Node &node : this->graph)
        node.reset();
    this->lastUnvisitedNodeId = 1;
}
MyStl::Node &MyStl::Graph::operator[](MyStl::Node::NodeId nodeId)
{
    return this->graph[nodeId];
}
const MyStl::Node &MyStl::Graph::operator[](MyStl::Node::NodeId nodeId) const
{
    return this->graph[nodeId];
}
void MyStl::Graph::priortiseNeighbourByHeighWeight() noexcept
{
    for (MyStl::Node &node : this->graph)
    {
        node.priortiseNeighbourByHeighWeight();
        node.reset();
    }
}
void MyStl::Graph::priortiseNeighbourByLowWeight() noexcept
{
    for (MyStl::Node &node : this->graph)
    {
        node.priortiseNeighbourByLowWeight();
        node.reset();
    }
}
void MyStl::Graph::priortiseNeighbourByHeighNodeId() noexcept
{
    for (MyStl::Node &node : this->graph)
    {
        node.priortiseNeighbourByHeighNodeId();
        node.reset();
    }
}
void MyStl::Graph::priortiseNeighbourByLowNodeId() noexcept
{
    for (MyStl::Node &node : this->graph)
    {
        node.priortiseNeighbourByLowNodeId();
        node.reset();
    }
}
void MyStl::Graph::inputEdges(uint32_t numberOfEdges) noexcept
{
    for (uint32_t edgeNo = 0; edgeNo < numberOfEdges; edgeNo++)
    {
        MyStl::Node::NodeId node1, node2;
        MyStl::Node::Neighbour::Weight weight;
        scanf("%d%d%d", &node1, &node2, &weight);
        this->graph[node1].connect(this->graph[node2], weight);
    }
}
void MyStl::Graph::inputDirectedEdges(uint32_t numberOfEdges) noexcept
{
    for (uint32_t edgeNo = 0; edgeNo < numberOfEdges; edgeNo++)
    {
        MyStl::Node::NodeId node1, node2;
        MyStl::Node::Neighbour::Weight weight;
        scanf("%d%d%d", &node1, &node2, &weight);
        this->graph[node1].point(this->graph[node2], weight);
    }
}
MyStl::Node::NodeId MyStl::Graph::unvisitedNode() noexcept
{
    while (this->lastUnvisitedNodeId < this->graph.size() && this->graph[this->lastUnvisitedNodeId].isVisited())
    {
        this->lastUnvisitedNodeId++;
    }
    if (this->lastUnvisitedNodeId >= this->graph.size())
        return MyStl::Node::UNDEFINED_NODE;
    return this->lastUnvisitedNodeId;
}