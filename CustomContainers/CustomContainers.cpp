#include <iostream>
#include <string>
#include "Graph.h"
#include "UnorderedMap.h"
#include "Globals.h"

void GraphTest()
{
    std::cout << "Graphs and graph traversal\n";

    Graph<int> myGraph;
    Vector<int> graphData;

    // Create 10 nodes
    for (int i = 0; i < 10; ++i)
    {
        graphData.PushBack(i);
        myGraph.AddItem(&graphData[i]);
    }

    // Valid links
    myGraph.AddLink(0, 1);
    myGraph.AddLink(0, 2);
    myGraph.AddLink(1, 3);
    myGraph.AddLink(1, 4);
    myGraph.AddLink(2, 4);
    myGraph.AddLink(2, 5);
    myGraph.AddLink(3, 7);
    myGraph.AddLink(4, 8);
    myGraph.AddLink(5, 9);

    Vector<const int*> connectionsDFS;
    Vector<const int*> connectionsBFS;

    myGraph.GetAllConnectionDFS(0, connectionsDFS);
    myGraph.GetAllConnectionsBFS(0, connectionsBFS);

    std::cout << "DFS Connections from Node 0: ";
    for (int i = 0; i < connectionsDFS.Size(); ++i)
        std::cout << *connectionsDFS[i] << " ";
    std::cout << "\n";

    std::cout << "BFS Connections from Node 0: ";
    for (int i = 0; i < connectionsBFS.Size(); ++i)
        std::cout << *connectionsBFS[i] << " ";
    std::cout << "\n";

    Vector<const int*> pathDFS;
    Vector<const int*> pathBFS;

    myGraph.GetPathDFS(0, 9, pathDFS);
    myGraph.GetPathBFS(0, 9, pathBFS);

    std::cout << "DFS Path from Node 0 to 9: ";
    for (int i = 0; i < pathDFS.Size(); ++i)
        std::cout << *pathDFS[i] << " ";
    std::cout << "\n";

    std::cout << "BFS Path from Node 0 to 9: ";
    for (int i = 0; i < pathBFS.Size(); ++i)
        std::cout << *pathBFS[i] << " ";
    std::cout << "\n";
}

void VancouverGraphExample()
{
    struct City
    {
        std::string name;

    };

    // Create a city object
     // add all the cities to a vector
     // add the cities to the graph then link them where applicable
     // print all connections

    Vector<std::string> cities;
    cities.PushBack("Vancouver"); //0
    cities.PushBack("Burnaby"); //1
    cities.PushBack("Richmond"); //2
    cities.PushBack("Surrey"); //3
    cities.PushBack("Coquitlam"); //4
    cities.PushBack("Delta"); //5
    cities.PushBack("New_Westminster"); //6
    cities.PushBack("North_Vancouver"); //7
    cities.PushBack("Victoria"); //8
    cities.PushBack("Nanaimo"); //9
    cities.PushBack("Quinzel"); //10
    cities.PushBack("Langley"); //11
    cities.PushBack("Abbotsford"); //12
    cities.PushBack("Maple_Ridge"); //13
    cities.PushBack("Port_Coquitlam"); //14

    Graph<std::string> vancouverMap;
    for (int i = 0; i < cities.Size(); ++i)
    {
        vancouverMap.AddItem(&cities[i]);
    }

    // Core Metro Vancouver
    vancouverMap.AddLink(0, 1); // Vancouver - Burnaby
    vancouverMap.AddLink(0, 2); // Vancouver - Richmond
    vancouverMap.AddLink(0, 7); // Vancouver - North Vancouver

    // Burnaby / New West / Tri-Cities
    vancouverMap.AddLink(1, 6); // Burnaby - New Westminster
    vancouverMap.AddLink(1, 4); // Burnaby - Coquitlam
    vancouverMap.AddLink(6, 4); // New Westminster - Coquitlam

    // Tri-Cities → Fraser Valley
    vancouverMap.AddLink(4, 14); // Coquitlam - Port Coquitlam
    vancouverMap.AddLink(14, 13); // Port Coquitlam - Maple Ridge

    // Richmond / Delta / Surrey
    vancouverMap.AddLink(2, 5); // Richmond - Delta
    vancouverMap.AddLink(5, 3); // Delta - Surrey
    vancouverMap.AddLink(3, 13); // Surrey - Maple Ridge

    // Fraser Valley
    vancouverMap.AddLink(13, 11); // Maple Ridge - Langley
    vancouverMap.AddLink(11, 12); // Langley - Abbotsford

    // Vancouver Island
    vancouverMap.AddLink(0, 8); // Vancouver - Victoria (ferry abstraction)
    vancouverMap.AddLink(8, 9); // Victoria - Nanaimo

    // Fictional
    vancouverMap.AddLink(10, 11); // Quinzel - Langley
    vancouverMap.AddLink(10, 13); // Quinzel - Maple Ridge




    std::cout << "Connected Cities of Greater Vancouver\n";
    vancouverMap.PrintGraph();

    int startCityIndex = 0; // Vancouver
    Vector<const std::string*> connectionsDFS;
    Vector<const std::string*> connectionsBFS;
    vancouverMap.GetAllConnectionDFS(0, connectionsDFS);
    vancouverMap.GetAllConnectionsBFS(0, connectionsBFS);

    std::cout << "Cities connecte To " << cities[startCityIndex] << " using DFS: ";
    for (int i = 0; i < connectionsDFS.Size(); ++i)
    {
        std::cout << *connectionsDFS[i] << " ";
    }

    std::cout << "\n\n";
    std::cout << "Cities connected To " << cities[startCityIndex] << " using BFS: ";
    for (int i = 0; i < connectionsBFS.Size(); ++i)
    {
        std::cout << *connectionsBFS[i] << " ";
    }
    std::cout << "\n\n";
    int islandStartIndex = 8; // Victoria
    connectionsBFS.Clear();
    connectionsDFS.Clear();
    vancouverMap.GetAllConnectionsBFS(islandStartIndex, connectionsBFS);
    vancouverMap.GetAllConnectionDFS(islandStartIndex, connectionsDFS);

    std::cout << "\nCities connected To " << cities[islandStartIndex] << " using DFS: ";
    for (int i = 0; i < connectionsDFS.Size(); ++i)
    {
        std::cout << *connectionsDFS[i] << " ";
    }

    std::cout << "\n\n";
    std::cout << "Cities connected To " << cities[islandStartIndex] << " using BFS: ";
    for (int i = 0; i < connectionsBFS.Size(); ++i)
    {
        std::cout << *connectionsBFS[i] << " ";
    }
    std::cout << "\n\n";

    int startingIndex = 0; // Vancouver
    int endingIndex = 9;   // Nanaimo
    Vector<const std::string*> cityRoute;
    if (vancouverMap.GetPathDFS(startingIndex, endingIndex, cityRoute))
    {
        std::cout << "DFS Path from " << cities[startingIndex] << " to " << cities[endingIndex] << ": ";
        for (int i = 0; i < cityRoute.Size(); ++i)
        {
            std::cout << (*cityRoute[i]) << " ";
        }
        std::cout << "\n";
    }
    else
    {
        std::cout << "No DFS path found\n\n";
    }
    std::cout << "\n";

    cityRoute.Clear();
    std::cout << "Getting path from " << cities[startingIndex] << " to " << cities[endingIndex] << " using BFS\n";

    if (vancouverMap.GetPathBFS(startingIndex, endingIndex, cityRoute))
    {
        std::cout << "BFS Path from " << cities[startingIndex] << " to " << cities[endingIndex] << ": ";
        for (int i = cityRoute.Size() - 1; i >= 0; --i)
        {
            std::cout << (*cityRoute[i]) << " ";
        }
        std::cout << "\n";
    }
    else
    {
        std::cout << "No BFS path found\n\n";

    }
}

struct Tile
{
    int x = 0;
    int y = 0;

    //used after doing path finding
	bool isInPath = false;
    void Draw() const
    {
        if (isInPath)
        {
            std::cout << "[X]";
        }
        else
        {
            std::cout << "[ ]";
        }
	}  
    friend std::ostream& operator<<(std::ostream& os, const Tile& t)
    {
        os << t.x << "_" << t.y;
        return os;
    }
};

void DrawTileMap(int width, int height, const Vector<Tile>& tileMap)
{
    std::cout << "    ";
    for (int w = 0; w < width; ++w)
    {
        if (w < 10)
            std::cout << "0" << w << " ";
        else
            std::cout << w << " ";
    }
    std::cout << "\n";

    for (int h = 0; h < height; ++h)
    {
        if (h < 10)
            std::cout << "0" << h << " ";
        else
            std::cout << h << " ";

        for (int w = 0; w < width; ++w)
        {
            int index = w + (h * width);
            tileMap[index].Draw();
        }
        std::cout << "\n";
    }
}

void VancouverGraphExercise()
{
    Vector<Tile> tileMap;
    Graph<Tile> tileMapGraph;

    std::string input;
    bool isDone = false;

    std::cout << "Tile Map and Pathfinding Example\n\n";

    while (!isDone)
    {
        system("cls");
        std::cout << "Tile Map\n";

        int width = 0;
        int height = 0;
        std::cout << "Enter map width: ";
        std::cin >> width;
        std::cout << "Enter map height: ";
        std::cin >> height;

        // Reset everything
        tileMapGraph.Terminate();
        tileMap.Clear();

        // Build tile map
        tileMap.Resize(width * height);
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                int index = x + (y * width);
                tileMap[index].x = x;
                tileMap[index].y = y;
                tileMap[index].isInPath = false;
            }
        }

        // Add tiles to graph
        for (int i = 0; i < tileMap.Size(); ++i)
        {
            tileMapGraph.AddItem(&tileMap[i]);
        }

        // Link grid neighbors
        for (int y = 0; y < height; ++y)
        {
            for (int x = 0; x < width; ++x)
            {
                int currentIndex = x + (y * width);

                if (x + 1 < width)
                    tileMapGraph.AddLink(currentIndex, currentIndex + 1);

                if (y + 1 < height)
                    tileMapGraph.AddLink(currentIndex, currentIndex + width);
            }
        }

        // Draw empty map
        DrawTileMap(width, height, tileMap);

        int startX, startY, endX, endY;
        std::cout << "Enter start X: ";
        std::cin >> startX;
        std::cout << "Enter start Y: ";
        std::cin >> startY;
        std::cout << "Enter end X: ";
        std::cin >> endX;
        std::cout << "Enter end Y: ";
        std::cin >> endY;

        // Bounds check
        if (startX < 0 || startX >= width || startY < 0 || startY >= height ||
            endX < 0 || endX >= width || endY < 0 || endY >= height)
        {
            std::cout << "Invalid coordinates.\n";
            std::cin.ignore();
            std::cin.get();
            continue;
        }

        int startIndex = startX + (startY * width);
        int endIndex = endX + (endY * width);

        Vector<const Tile*> path;

        // Run DFS ONCE
        if (tileMapGraph.GetPathDFS(startIndex, endIndex, path))
        {
            for (int i = 0; i < path.Size(); ++i)
            {
                int index = path[i]->x + (path[i]->y * width);
                tileMap[index].isInPath = true;
            }
        }

        system("cls");
        std::cout << "Path From (" << startX << ", " << startY
            << ") to (" << endX << ", " << endY << ")\n\n";

        // Draw result
        DrawTileMap(width, height, tileMap);

        std::cout << "\nType 'done' to quit or press Enter to continue: ";
        std::cin.ignore();
        isDone = (input == "done");
    }
}




class Player
{
private:
    std::string _name;
    int _score;

public:
    Player(const std::string& name = "", int score = 0)
        : _name(name), _score(score)
    {
    }

    const std::string& GetName() const
    {
        return _name;
    }

    int GetScore() const
    {
        return _score;
    }

    void SetScore(int score)
    {
        _score = score;
    }
};



int main()
{
    std::cout << "===== VECTOR + SORT TEST =====\n";

    Vector<Player> players;

    players.PushBack(Player("Alice", 90));
    players.PushBack(Player("Bob", 75));
    players.PushBack(Player("Charlie", 100));
    players.PushBack(Player("Dave", 60));

    std::cout << "\nBefore Sorting:\n";
    for (std::size_t i = 0; i < players.Size(); ++i)
    {
        std::cout << players[i].GetName()
            << " - "
            << players[i].GetScore()
            << "\n";
    }

    std::function<bool(const Player&, const Player&)> sortByScore =
        [](const Player& a, const Player& b)
        {
            return a.GetScore() < b.GetScore();
        };

    Globals::BubbleSort(players, sortByScore);

    std::cout << "\nAfter BubbleSort (Ascending by Score):\n";
    for (std::size_t i = 0; i < players.Size(); ++i)
    {
        std::cout << players[i].GetName()
            << " - "
            << players[i].GetScore()
            << "\n";
    }

    std::cout << "\n===== UNORDERED MAP TEST =====\n";

    UnorderedMap<std::string, int> carPrices;

    carPrices.Insert("Ford", 10000);
    carPrices.Insert("Chevy", 25000);
    carPrices["Dodge"] = 30000;
    carPrices["BMW"] = 100000;

    std::cout << "Ford: " << carPrices["Ford"] << "\n";
    std::cout << "Chevy: " << carPrices["Chevy"] << "\n";
    std::cout << "Dodge: " << carPrices["Dodge"] << "\n";
    std::cout << "BMW: " << carPrices["BMW"] << "\n";

    if (carPrices.Has("Ford"))
        std::cout << "Ford exists in map\n";

    carPrices.Remove("Ford");

    if (!carPrices.Has("Ford"))
        std::cout << "Ford successfully removed\n";

    std::cout << "\nTotal elements: " << carPrices.GetCount() << "\n";

    return 0;
}
