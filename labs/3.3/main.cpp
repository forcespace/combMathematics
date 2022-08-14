#include <fstream>
#include <iostream>
#include <optional>
#include <vector>
#include <cmath>

std::string programMessage[] = {
        "Invalid arguments count",
        "Usage: numbers.exe <input file name",
        "Failed to open input for reading",
        "Print input matrix",
        "Print Kirchhoff matrix",
        "Number of spanning trees = "
};

struct Args
{
    std::string inputFile;
};

std::optional<Args> parseArgs(int argc, char* argv[])
{
    if (argc != 2)
    {
        return std::nullopt;
    }
    Args args;
    args.inputFile = argv[1];
    return args;
}

std::optional<std::ifstream> openFile(const std::string& inputFile)
{
    std::ifstream input;
    input.open(inputFile);
    if (!input.is_open())
    {
        return std::nullopt;
    }
    else
    {
        return input;
    }
}

std::vector<std::vector<int>> getAdjacencyMatrix(std::ifstream& inputFile)
{
    int numOfVertices;
    inputFile >> numOfVertices;
    std::vector<std::vector<int>> adjacencyMatrix(numOfVertices, std::vector<int>(numOfVertices, 0));
    for (int i = 0; i < numOfVertices; i++)
    {
        for (int j = 0; j < numOfVertices; j++)
        {
            inputFile >> adjacencyMatrix[i][j];
        }
    }

    return adjacencyMatrix;
}

std::vector<std::vector <float>> getKirchhoffMatrix(std::vector<std::vector <int>> adjacencyMatrix)
{
    std::vector<std::vector<float>> kirchhoffMatrix(adjacencyMatrix.size(), std::vector<float>(adjacencyMatrix.size(), 0));
    int adjacent = 1;
    for (int i = 0; i < adjacencyMatrix.size(); i++)
    {
        for (int j = 0; j < adjacencyMatrix.size(); j++)
        {
            if (adjacencyMatrix[i][j] == adjacent)
            {
                kirchhoffMatrix[i][j] = -1;
                ++kirchhoffMatrix[i][i];
            }
        }
    }

    return kirchhoffMatrix;
}

std::vector<std::vector <float>> getMatrixForAlgebraicAddition(const std::vector<std::vector <float>>& matrix)
{
    std::vector<std::vector <float>> resultMatrix(matrix.size() - 1, std::vector<float>(matrix.size() -1, 0));
    for (int i = 0; i < matrix.size() - 1; i++)
    {
        for (int j = 0; j < matrix.size() - 1; j++)
            resultMatrix[i][j] = matrix[i][j];
    }

    return resultMatrix;
}

void bringingMatrixToTriangularForm(std::vector<std::vector <float>>& matrix)
{
    for (int col = 0; col < matrix.size() - 1; col++)
    {
        for (int row = col + 1; row < matrix.size(); row++)
        {
            if (matrix[col][col] != 0)
            {
                float k = matrix[row][col] / matrix[col][col];
                for (int i = 0; i < matrix.size(); i++)
                {
                    matrix[row][i] = round((matrix[row][i] - k * matrix[col][i]) * 100) / 100;
                }
            }
        }
    }
}

int getDeterminant(const std::vector<std::vector <float>>& matrix)
{
    float determinant = 1;
    for (int i = 0; i < matrix.size(); i++)
    {
        determinant *= matrix[i][i];
    }

    return determinant;
}


void printMatrix(const std::vector<std::vector<int>>& matrix)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix.size(); j++)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "" << std::endl;
    }
}

void printMatrix(const std::vector<std::vector<float>>& matrix)
{
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix.size(); j++)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "" << std::endl;
    }
}

int main(int argc, char* argv[])
{
    auto args = parseArgs(argc, argv);
    if (!args)
    {
        std::cout << programMessage[0] << std::endl;
        std::cout << programMessage[1] << std::endl;

        return 1;
    }

    auto inputFile = openFile(args->inputFile);
    if (!inputFile)
    {
        std::cout << programMessage[2] << std::endl;

        return 1;
    }

    auto inputMatrix = getAdjacencyMatrix(*inputFile);
    auto kirchhoffMatrix = getKirchhoffMatrix(inputMatrix);

    std::cout << programMessage[3] << std::endl;
    printMatrix(inputMatrix);

    std::cout << programMessage[4] << std::endl;
    printMatrix(kirchhoffMatrix);

    auto algebraicAdditionalMatrix = getMatrixForAlgebraicAddition(kirchhoffMatrix);
    bringingMatrixToTriangularForm(algebraicAdditionalMatrix);
    int numOfSpanningTrees = getDeterminant(algebraicAdditionalMatrix);
    std::cout << programMessage[5] << numOfSpanningTrees << "" << std::endl;

    return 0;
}