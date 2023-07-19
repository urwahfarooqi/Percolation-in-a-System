#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "WeightedQuickUnion.cpp"
#include <fstream>

using namespace std;

class Percolation
{
public:
    int size;
    int openSites;
    int virtualtop = 0;
    int virtualbottom;
    vector<vector<bool>> Open;
    WeightedQuickUnionUF wGrid;
    WeightedQuickUnionUF wFull;

    Percolation(int n)
        : size(n),
        openSites(0),
        virtualtop(0),
        virtualbottom(n* n + 1),
        Open(n, vector<bool>(n, false)),
        wGrid(n* n + 2),
        wFull(n* n + 1)
    {
        if (n <= 0)
        {
            throw std::out_of_range("Index out of bound!!");
        }
    }

    int map(int i, int j)
    {
        return (size * (i - 1) + j);
    }

    bool isOpen(int row, int col)
    {
        validateSite(row, col);

        return Open[row - 1][col - 1];
    }

    void open(int row, int col)
    {
        validateSite(row, col);
        int curSite = map(row, col) - 1;

        int shiftrow = row - 1;
        int shiftcol = col - 1;

        if (isOpen(row, col))
            return;

        Open[shiftrow][shiftcol] = true;
        openSites++;

        if (row == 1)
        {
            wGrid.unionOp(virtualtop, curSite);
            wFull.unionOp(virtualtop, curSite);
        }

        if (row == size)
        {
            wGrid.unionOp(virtualbottom, curSite);
        }

        // Check and open Left
        if (isOnGrid(row, col - 1) && isOpen(row, col - 1))
        {
            wGrid.unionOp(curSite, map(row, col - 1) - 1);
            wFull.unionOp(curSite, map(row, col - 1) - 1);
        }

        // Check and Open Right
        if (isOnGrid(row, col + 1) && isOpen(row, col + 1))
        {
            wGrid.unionOp(curSite, map(row, col + 1) - 1);
            wFull.unionOp(curSite, map(row, col + 1) - 1);
        }

        // Check and Open Up
        if (isOnGrid(row - 1, col) && isOpen(row - 1, col))
        {
            wGrid.unionOp(curSite, map(row - 1, col) - 1);
            wFull.unionOp(curSite, map(row - 1, col) - 1);
        }

        // Check and Open Down
        if (isOnGrid(row + 1, col) && isOpen(row + 1, col))
        {
            wGrid.unionOp(curSite, map(row + 1, col) - 1);
            wFull.unionOp(curSite, map(row + 1, col) - 1);
        }
    }

    bool isFull(int row, int col)
    {
        validateSite(row, col);
        return (wFull.find(virtualtop) == wFull.find(map(row, col) - 1));
    }

    int numberOfOpenSites()
    {
        return openSites;
    }

    bool percolates()
    {
        return wGrid.find(virtualtop) == wGrid.find(virtualbottom);
    }

    bool isOnGrid(int row, int col)
    {
        int shiftrow = row - 1;
        int shiftcol = col - 1;
        return (shiftrow >= 0 && shiftcol >= 0 && shiftrow < size && shiftcol < size);
    }

    void validateSite(int row, int col)
    {
        if (!isOnGrid(row, col))
            throw ("Index is out of bounds!!");
    }
};

int main()
{
    int n;

    ifstream inputFile("input50.txt");

    // Check if the file was opened successfully
    if (!inputFile)
    {
        cout << "Failed to open input file." << endl;
        return 1;
    }

    inputFile >> n; // Read the value of 'n' from the file

    Percolation p(n);

    int i, j;
    while (inputFile >> i >> j)
    {
        if (i == -1)
        {
            break;
        }
        else
        {
            p.open(i, j);
        }
    }

    inputFile.close();

    int gridSize = 500;
    int gridOffset = 50;     // Extra space for notation
    int borderThickness = 2; // Thickness of the border

    sf::RenderWindow window(sf::VideoMode(gridSize, gridSize + gridOffset), "Percolation");
    sf::RectangleShape blockedSite(sf::Vector2f(gridSize / n, gridSize / n));
    sf::RectangleShape openSite(sf::Vector2f(gridSize / n, gridSize / n));
    sf::RectangleShape filledSite(sf::Vector2f(gridSize / n, gridSize / n));
    sf::RectangleShape border(sf::Vector2f(gridSize, gridSize));

    blockedSite.setFillColor(sf::Color::Black);
    openSite.setFillColor(sf::Color::White);
    filledSite.setFillColor(sf::Color::Blue);
    border.setFillColor(sf::Color::Transparent);
    border.setOutlineColor(sf::Color::White);
    border.setOutlineThickness(borderThickness);

    // Add a black border around open and filled cells
    openSite.setOutlineThickness(1.f);
    openSite.setOutlineColor(sf::Color::Black);
    filledSite.setOutlineThickness(1.f);
    filledSite.setOutlineColor(sf::Color::Black);

    // Load the font
    sf::Font font;
    if (!font.loadFromFile("Ubuntu-Regular.ttf"))
    {
        cout << "Failed to load font file." << endl;
        return 1;
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // Draw the border
        window.draw(border);

        // Draw the grid of cells
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (p.isOpen(i + 1, j + 1))
                {
                    if (p.isFull(i + 1, j + 1))
                    {
                        filledSite.setPosition(j * (gridSize / n), i * (gridSize / n));
                        window.draw(filledSite);
                    }
                    else
                    {
                        openSite.setPosition(j * (gridSize / n), i * (gridSize / n));
                        window.draw(openSite);
                    }
                }
                else
                {
                    blockedSite.setPosition(j * (gridSize / n), i * (gridSize / n));
                    window.draw(blockedSite);
                }
            }
        }

        // Draw the notation
        sf::Text notationText;
        notationText.setFont(font);
        notationText.setCharacterSize(24);
        notationText.setFillColor(sf::Color::White);
        notationText.setOutlineColor(sf::Color::Black);
        notationText.setOutlineThickness(1.f);

        // Set the notation string
        notationText.setString(p.percolates() ? "Percolates. " : "Does not Percolate. ");
        notationText.setString(notationText.getString() + to_string(p.numberOfOpenSites()) + " open sites");

        // Position the notation text
        sf::FloatRect textBounds = notationText.getLocalBounds();
        notationText.setPosition((window.getSize().x - textBounds.width) / 2.f, gridSize + 10.f);

        window.draw(notationText);
        window.display();
    }

    return 0;
}
