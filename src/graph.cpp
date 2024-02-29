#include "../mySTL.hpp"
using namespace MyStl;
Node::Node(NodeId nodeId) : nodeId(nodeId)
{
    if (nodeId == Node::UNDEFINED_NODE)
        throw std::runtime_error("Node id should be a natural number\n");
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
    if (this->lastVisit() == Node::UNDEFINED_NODE)
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
Node::NodeId Node::move(Graph &graph)
{
    for (uint32_t neighbourInex = this->neighbourIndexToVisit; neighbourInex < neighbours.size(); neighbourInex++)
    {
        if (not graph[neighbours[neighbourInex].nodeId].isVisited() && neighbours[neighbourInex].nodeId != Node::UNDEFINED_NODE)
        {
            graph[neighbours[neighbourInex].nodeId].markVisited(this->nodeId);
            this->neighbourIndexToVisit = neighbourInex + 1;
            return neighbours[neighbourInex].nodeId;
        }
    }
    return Node::UNDEFINED_NODE;
}
Node::NodeId Node::backtrack() const
{
    return this->visitorNodeId;
}
void Node::markVisited(NodeId visitorNodeId)
{
    this->visitorNodeId = visitorNodeId;
}
bool Node::isVisited() const
{
    return this->visitorNodeId != Node::UNDEFINED_NODE;
}
void Node::reset()
{
    this->visitorNodeId = Node::Node::UNDEFINED_NODE;
    this->neighbourIndexToVisit = 0;
}
Node::NodeId Node::lastVisit() const
{
    return this->neighbourIndexToVisit == 0 ? Node::UNDEFINED_NODE : this->neighbours[this->neighbourIndexToVisit - 1].nodeId;
}
bool Node::hasVisitedNeighbour(const Graph &graph) const
{
    for (Neighbour neighbour : this->neighbours)
    {
        if (graph[neighbour.nodeId].isVisited())
            return true;
    }
    return false;
}
uint32_t Node::neighbourCount() const
{
    return this->neighbours.size();
}
std::vector<Node::Neighbour> Node::get_neighbours() const
{
    return this->neighbours;
}
inline void Node::priortiseNeighbourByHeighWeight()
{
    std::sort(this->neighbours.begin(), this->neighbours.end(), [](Neighbour neighbour1, Neighbour neighbour2)
              { return neighbour1.weight > neighbour2.weight; });
}
inline void Node::priortiseNeighbourByLowWeight()
{
    std::sort(this->neighbours.begin(), this->neighbours.end(), [](Neighbour neighbour1, Neighbour neighbour2)
              { return neighbour1.weight < neighbour2.weight; });
}
inline void Node::priortiseNeighbourByHeighNodeId()
{
    std::sort(this->neighbours.begin(), this->neighbours.end(), [](Neighbour neighbour1, Neighbour neighbour2)
              { return neighbour1.nodeId > neighbour2.nodeId; });
}
inline void Node::priortiseNeighbourByLowNodeId()
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