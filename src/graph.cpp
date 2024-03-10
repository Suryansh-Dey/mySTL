#include "../mySTL.hpp"
using namespace MyStl;
Node::Node(NodeId nodeId) : nodeId(nodeId)
{
    if (nodeId == Node::UNDEFINED_NODE)
        throw std::runtime_error("MyStl::Node::Node() failed.\nNode id should be a natural number\n");
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
    uint32_t neighbourIndex = this->neighbourIndexToVisit;
    while (neighbourIndex < this->neighbours.size() && (this->neighbours[neighbourIndex].nodeId == Node::UNDEFINED_NODE || this->neighbours[neighbourIndex].nodeId == this->lastVisitorId()))
    {
        neighbourIndex++;
    }
    this->neighbourIndexToVisit = neighbourIndex + (neighbourIndex < this->neighbours.size());
    return neighbourIndex < this->neighbours.size() ? this->neighbours[neighbourIndex] : Neighbour{Node::UNDEFINED_NODE, 0};
}
Node::Neighbour Node::moveUnvisited(Graph &graph)
{
    for (uint32_t neighbourIndex = this->neighbourIndexToVisit; neighbourIndex < this->neighbours.size(); neighbourIndex++)
    {
        if (!graph[this->neighbours[neighbourIndex].nodeId].isVisited() && this->neighbours[neighbourIndex].nodeId != Node::UNDEFINED_NODE && this->neighbours[neighbourIndex].nodeId != this->lastVisitorId())
        {
            this->neighbourIndexToVisit = neighbourIndex + 1;
            return this->neighbours[neighbourIndex];
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
const std::vector<Node::Neighbour> &Node::get_neighbours() const
{
    return this->neighbours;
}
uint32_t Node::get_priorty(Node::NodeId neighbour) const
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
void Node::priortiseNeighbourHighest(Node::NodeId neighbour)
{
    std::swap(this->neighbours[get_priorty(neighbour)], this->neighbours[this->neighbours.size() - 1]);
}
void Node::priortiseNeighbourLowest(Node::NodeId neighbour)
{
    std::swap(this->neighbours[get_priorty(neighbour)], this->neighbours[0]);
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
    this->lastUnvisitedNodeId = 1;
}
Node &Graph::operator[](Node::NodeId nodeId)
{
    return this->graph[nodeId];
}
const Node &Graph::operator[](Node::NodeId nodeId) const
{
    return this->graph[nodeId];
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
        Node::NodeId node1, node2;
        Node::Neighbour::Weight weight;
        scanf("%d%d%d", &node1, &node2, &weight);
        this->graph[node1].connect(this->graph[node2], weight);
    }
}
void Graph::inputDirectedEdges(uint32_t numberOfEdges)
{
    for (uint32_t edgeNo = 0; edgeNo < numberOfEdges; edgeNo++)
    {
        Node::NodeId node1, node2;
        Node::Neighbour::Weight weight;
        scanf("%d%d%d", &node1, &node2, &weight);
        this->graph[node1].point(this->graph[node2], weight);
    }
}
Node::NodeId Graph::unvisitedNode()
{
    while (this->lastUnvisitedNodeId < this->graph.size() && this->graph[this->lastUnvisitedNodeId].isVisited())
    {
        this->lastUnvisitedNodeId++;
    }
    if (this->lastUnvisitedNodeId >= this->graph.size())
        return Node::UNDEFINED_NODE;
    return this->lastUnvisitedNodeId;
}