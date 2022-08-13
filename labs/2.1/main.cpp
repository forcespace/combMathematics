#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>
#include <stack>

struct PointsMap
{
    int startPoint;
    int endPoint;
};

std::set<int> getResultCutVertices(std::vector<std::vector<int>> graph, int root, std::vector<int> tin, std::vector<int> tout, std::vector<PointsMap> reverseEdges);

bool isEdgeInReverse(int first, int second, std::vector<PointsMap> &reverseEdges, std::vector<int> tin);

void checkStack(const std::stack<int>& stack)
{
    if (stack.empty())
    {
        return;
    }
}

void printStack(std::stack<int> stack)
{
    checkStack(stack);

    int temp = stack.top();
    stack.pop();

    printStack(stack);

    std::cout << temp << ' ';
    stack.push(temp);
}

std::vector<std::vector<int>> getMatrix(std::ifstream &input)
{
    int countVertices;
    int countEdges;
    int primaryPoint;
    int secondaryPoint;
    int step = 1;

    input >> countVertices >> countEdges;
    std::vector<std::vector<int>> matrix(countVertices + step, std::vector<int>(countVertices + step, 0));

    while (input >> primaryPoint >> secondaryPoint)
    {
        matrix[primaryPoint][secondaryPoint] = step;
        matrix[secondaryPoint][primaryPoint] = step;
    }

    return matrix;
}

void initEdges(std::vector<PointsMap> &reverseEdges, PointsMap &edge, int parent, int vertex, int i, std::vector<int> &tin, std::vector<int> &tout, std::vector<bool> &visited)
{
    if (visited[i] && tin[vertex] - tin[i] > 1 && !tout[parent] && i != parent)
    {
        if (i < vertex)
        {
            edge.startPoint = i;
        }
        else
        {
            edge.startPoint = vertex;
        }

        if (i > vertex)
        {
            edge.endPoint = i;
        }
        else
        {
            edge.endPoint = vertex;
        }

        reverseEdges.push_back(edge);
    }
}

void iterateGraph(const std::vector<std::vector<int>> &graph, std::vector<int> &tin, std::vector<int> &tout, std::vector<PointsMap> &reverseEdges, int graphSize, int timer, std::vector<bool> &visited, PointsMap &edge, int parent, std::stack<int> &stack, bool isPath)
{
    while (!stack.empty())
    {
        int vertex = stack.top();
        visited[vertex] = true;

        if (isPath)
        {
            tin[vertex] = ++timer;
        }

        isPath = false;
        for (int i = 1; i < graphSize; ++i)
        {
            if (graph[vertex][i] == 1)
            {
                if (!visited[i])
                {
                    parent = stack.top();
                    stack.push(i);
                    isPath = true;
                    break;
                }

                initEdges(reverseEdges, edge, parent, vertex, i, tin, tout, visited);
            }
        }

        if (!isPath)
        {
            parent = stack.top();
            stack.pop();
            tout[vertex] = ++timer;
        }
    }
}

void DFS(const std::vector<std::vector<int>> graph, int root, std::vector<int> &tin, std::vector<int> &tout, std::vector<PointsMap> &reverseEdges)
{
    int graphSize = graph.size();
    int timer = 0;
    std::vector<bool> visited(graphSize, false);
    PointsMap edge;
    int parent = 0;
    int vertex = root;
    std::stack<int> stack;
    stack.push(vertex);
    bool isPath = true;

    iterateGraph(graph, tin, tout, reverseEdges, graphSize, timer, visited, edge, parent, stack, isPath);
}

std::set<int> getVertices(const std::vector<std::vector<int>>& graph)
{
    int root = 1;
    int graphSize = graph.size();
    std::vector<int> tin(graphSize, 0);
    std::vector<int> tout(graphSize, 0);
    std::vector<PointsMap> reverseEdges;

    DFS(graph, root, tin, tout, reverseEdges);

    std::set<int> cutVertices = getResultCutVertices(graph, root, tin, tout, reverseEdges);

    return cutVertices;
}

void getRootVertices(const std::vector<std::vector<int>> &graph, const std::vector<int> &tin, const std::vector<int> &tout, std::set<int> &weedingVertices, int graphSize, int vertexStep, int vertex)
{
    bool isRootVertices = false;

    for (int i = 1; i < graphSize; i++)
    {
        if (graph[vertex][i] == vertexStep && tin[i] - vertexStep == tin[vertex] && tout[i] + vertexStep == tout[vertex])
        {
            isRootVertices = true;
        }
    }

    if (!isRootVertices)
    {
        weedingVertices.insert(vertex);
    }
}

void initChild(const std::vector<std::vector<int>> &graph, std::vector<int> &tin, const std::vector<int> &tout, std::vector<PointsMap> &reverseEdges, int graphSize, int vertex, int &branches, int &edges, int &parentOfHangingVertice)
{
    branches= 0;
    edges= 0;

    for (int child = 1; child < graphSize; child++)
    {
        if (graph[vertex][child] == 1)
        {
            edges = ++edges;
            parentOfHangingVertice = child;

            if (tin[vertex] < tin[child] && tout[vertex] > tout[child] && !isEdgeInReverse(vertex, child, reverseEdges, tin))
            {
                branches++;
                bool isReverseEdge = false;

                for (int descendant = 1; descendant < graphSize; ++descendant)
                {
                    if (tin[child] <= tin[descendant] && tout[child] >= tout[descendant])
                    {
                        for (auto &edge: reverseEdges)
                        {
                            if (edge.endPoint == descendant && tin[edge.startPoint] < tin[vertex])
                            {
                                isReverseEdge = true;
                            }
                        }
                    }
                }

                if (isReverseEdge)
                {
                    --branches;
                }
            }
        }
    }
}

std::set<int> getResultCutVertices(std::vector<std::vector<int>> graph, int root, std::vector<int> tin, std::vector<int> tout, std::vector<PointsMap> reverseEdges)
{
    std::set<int> weedingVertices;
    int graphSize = graph.size();
    int sizeStep = 3;
    int vertexStep = 1;

    if (graphSize <= sizeStep)
    {
        return weedingVertices;
    }

    for (int vertex = 1; vertex < graphSize; vertex++)
    {
        if (vertex == root)
        {
            getRootVertices(graph, tin, tout, weedingVertices, graphSize, vertexStep, vertex);

            continue;
        }

        int branches;
        int edges;
        int parentOfHangingVertice;

        initChild(graph, tin, tout, reverseEdges, graphSize, vertex, branches, edges, parentOfHangingVertice);

        if (edges == 1)
        {
            weedingVertices.insert(parentOfHangingVertice);
        }

        if (branches != 0)
        {
            weedingVertices.insert(vertex);
        }
    }

    return weedingVertices;
}

bool isEdgeInReverse(int first, int second, std::vector<PointsMap> &reverseEdges, std::vector<int> tin)
{
    int start = tin[first] < tin[second] ? first : second;
    int end = tin[first] > tin[second] ? first : second;
    bool edgeInReverse = false;

    for (auto x: reverseEdges)
    {
        if (x.endPoint == end && x.startPoint == start)
        {
            edgeInReverse = true;
        }
    }

    return edgeInReverse;
}

void getPoints(std::ifstream &input)
{
    std::__1::vector<std::vector<int>> matrix = getMatrix(input);

    std::set<int> cutVertices = getVertices(matrix);

    copy(cutVertices.begin(), cutVertices.end(), std::ostream_iterator<int>(std::cout, " "));
}

int main(int argc, char *argv[])
{
    std::ifstream input(argv[1]);

    if (!input.is_open())
    {
        return 1;
    }

    getPoints(input);
}