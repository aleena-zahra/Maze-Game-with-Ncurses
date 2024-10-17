
#include <ncurses.h>
#include <random>
#include <cmath>
#include <iostream>
using namespace std;

// list class
struct Node
{
    int xCor, yCor;
    Node *link;

    Node(int xCor = 0, int yCor = 0)
    {
        this->xCor = xCor;
        this->yCor = yCor;
        this->link = NULL;
    }
    ~Node()
    {
        // printw("\ndestructor called for node with value: "<<this->xCor;
    }
};
class List
{
private:
    Node *head;

public:
    List()
    {
        head = NULL;
    }
    ~List()
    {
        // traverse list and delete each node until reach null
        Node *current = head;
        while (current != NULL)
        {
            Node *nextNode = current->link;
            delete current;
            current = nextNode;
        }
        head = NULL;
    }
    // insert functions
    void push(int xCor, int yCor)
    {
        // create new node and set its values
        Node *newNode = new Node(xCor, yCor);

        if (isEmpty())
        {
            head = newNode;
        }
        else
        {
            // when head isnt null store its address in new Node
            newNode->link = head;
            head = newNode;
        }
    }
    void enqueue(int xCor, int yCor)
    {
        // make the nodee
        Node *temp = new Node(xCor, yCor);
        // if empty list
        if (isEmpty())
        {
            head = temp;
        }
        else
        {
            Node *current = head;
            while (current->link != NULL)
            {
                current = current->link;
            }
            current->link = temp;
        }
        // traverse until current->next ==NULL
    }

    // delete functions
    void pop()
    {
        if (!isEmpty())
        {
            Node *temp = head; // store old head/first node
            head = head->link; // new head is next node
            delete temp;       // delete old head/first node
        }
    }
    bool deleteAtEnd()
    {
        if (isEmpty())
        {
            return false;
        }
        // only 1 node
        if (head->link == NULL)
        {
            pop();
            return true;
        }
        // delete from end when nodes>1

        Node *secondLast = head;
        while (secondLast->link->link != NULL)
        {
            secondLast = secondLast->link;
        }

        // Delete the last node
        delete (secondLast->link);

        // Change link of second last
        secondLast->link = NULL;
        return true;
    }

    bool isEmpty()
    {
        return head == NULL;
    }
    void printList()
    {
        printw("\n");
        Node *temp = head;
        while (temp != NULL)
        {

            printw("(%d , %d) ->", temp->xCor, temp->yCor);

            temp = temp->link;
        }
        printw("NULL\n");
        refresh();
    }
    Node *peek()
    {
        return head;
    }
};

// grid class
struct Cell
{
    int xCor, yCor;
    char cellType;
    Cell *up;
    Cell *down;
    Cell *right;
    Cell *left;
    Cell(int x = 0, int y = 0)
    {
        this->xCor = x;
        this->yCor = y;
        Cell *up = down = right = left = nullptr;
        this->cellType = ' ';
    }
};
class Grid
{
public:
    Cell **heads;
    Cell *door, *key;
    Cell **bomb, **coin;
    int width, height;
    int numOfItems;
    Grid(int mode = 1)
    {
        this->width = this->height = (mode + 1) * 5;
        heads = new Cell *[height];
        for (int i = 0; i < height; i++)
        {
            heads[i] = NULL;
        }
        numOfItems = mode * 2;
        bomb = new Cell *[numOfItems];
        coin = new Cell *[numOfItems];
        makeGrid();
    }
    void insertNodeAtHead(int xCor, int yCor)
    {
        // create new Carriage and set its values
        Cell *newCell = new Cell(xCor, yCor);

        if (heads[yCor] == NULL)
        {
            heads[yCor] = newCell;
        }
        else
        {

            newCell->right = heads[yCor];
            heads[yCor]->left = newCell;
            heads[yCor] = newCell;
        }
    }
    void makeGrid()
    {
        // implementing a nested linked list by making a linked list of linked lists
        // make height number of linked lists and get their heads
        for (int i = 0; i < height; i++)
        {
            for (int j = width - 1; j >= 0; j--)
            {
                insertNodeAtHead(j, i);
            }
            printw("\n");
        }
        // connect the cells in each linked list
        // connect the linked lists by connecting their heads
        linkCells();
        setItems();
    }
    void linkCells()
    {
        for (int i = 0; i < height - 1; i++)
        {
            Cell *curr = heads[i];
            Cell *next = heads[i + 1];
            while (next != NULL && curr != NULL)
            {
                curr->down = next;
                next->up = curr;
                curr = curr->right;
                next = next->right;
            }
        }
    }
    void setItems()
    {
        // Generate random coordinates for bomb, coin, key, and door
        key = setIndex(rand() % height, rand() % width, ' ');
        door = setIndex(rand() % height, rand() % width, ' ');
        for (int i = 0; i < numOfItems; i++)
        {
            bomb[i] = setIndex(rand() % height, rand() % width, 'b');
            coin[i] = setIndex(rand() % height, rand() % width, 'c');
        }
    }
    Cell *getIndex(int x, int y)
    {
        Cell *temp = heads[y];
        while (temp != NULL)
        {
            if (temp->xCor == x)
            {
                return temp;
            }
            temp = temp->right;
        }
        printw("Index Not Found");
        return NULL;
    }
    Cell *setIndex(int x, int y, char type)
    {
        Cell *cell = getIndex(x, y);
        if (cell != NULL)
        {
            cell->cellType = type;
        }
        return cell;
    }
    bool playerAndBombCollision(int xCor, int yCor)
    {
        for (int i = 0; i < numOfItems; i++)
        {
            if (bomb[i]->xCor == xCor && bomb[i]->yCor == yCor)
            {
                return true;
            }
        }
        return false;
    }
    bool playerAndCoinCollision(int xCor, int yCor)
    {
        for (int i = 0; i < numOfItems; i++)
        {
            if (coin[i]->xCor == xCor && coin[i]->yCor == yCor)
            {
                return true;
            }
        }
        return false;
    }
    void printGrid()
    {
        for (int i = 0; i < height; i++)
        {
            Cell *temp = heads[i];
            while (temp != NULL)
            {
                //  printw("( "<<temp->xCor<<","<<temp->yCor<<" ) ";
                printw("|%c", temp->cellType);
                temp = temp->right;
            }
            printw("|");
            printw("\n");
        }
        printw("\n");
    }
};
// player class
class Player
{
public:
    int xCor, yCor, distance;
    List coinsCollected, prevPositions;
    bool hasKey;
    int undoMoves;
    int score;
    char playerDirection;
    Player(int xCor = 0, int yCor = 0, int undoMoves = 6)
    {
        this->xCor = xCor;
        this->yCor = yCor;
        this->hasKey = false;
        this->undoMoves = undoMoves;
        this->score = 0;
        this->playerDirection = ' ';
    }
    void collectCoin(int xCor, int yCor)
    {
        coinsCollected.enqueue(xCor, yCor);
        undoMoves++;
        score++;
        // update the score on terminal
    }
    void pushPosition(int xCor, int yCor)
    {
        prevPositions.push(xCor, yCor);
    }
    void undoMove()
    {
        Node *prev = prevPositions.peek();
        xCor = prev->xCor;
        yCor = prev->yCor;
        prevPositions.pop();
        undoMoves--;
    }
    void setUndoMoves(int moves)
    {
        undoMoves = moves;
    }
    bool canUndo()
    {
        return undoMoves > 0;
    }
    void setPlayerDirection(char direction)
    {
        playerDirection = direction;
    }
    char getPlayerDirection()
    {
        return playerDirection;
    }
};
// maze class
class Maze
{
public:
    Player player;
    Cell **maze;
    int width, height;
    bool playing;
    int distanceOfPlayer;
    Grid grid;
    int mode; // 1 for easy, 2 for medium, 3 for hard
    int moves;
    Maze(int mode) : player(0, 0), grid(mode)
    {
        this->mode = mode;
        this->width = this->height = (mode + 1) * 5;
        this->playing = true;
        initMaze();
        moves = calculateMoves();
        printw("initially moves are %d\n", moves);
        refresh();
        calculateUndoMoves();
    }
    void initMaze()
    {
        grid.setIndex(player.xCor, player.yCor, 'P');
    }
    void drawMaze()
    {
        grid.printGrid();
    }
    void updatePlayer(int prevXCor, int prevYCor)
    {
        grid.setIndex(prevXCor, prevYCor, ' ');
        grid.setIndex(player.xCor, player.yCor, 'P');
    }
    void move(char direction)
    {
        int prevX = player.xCor;
        int prevY = player.yCor;
        bool directionSet = false;
        switch (direction)
        {
        case 'u':
            if (player.canUndo())
                undoMove();
            else
            {
                printw("Out of undos\n");
                refresh();
            }
            break;
        case 'w':
            // if previouly opposite direction was entered, dont move
            if (player.getPlayerDirection() == 's')
                break;
            player.yCor--;
            moves--;
            player.setPlayerDirection('w');
            directionSet = true;
            break;
        case 's':
            if (player.getPlayerDirection() == 'w')
                break;
            player.yCor++;
            moves--;
            player.setPlayerDirection('s');
            directionSet = true;
            break;
        case 'a':
            if (player.getPlayerDirection() == 'd')
                break;
            player.xCor--;
            moves--;
            player.setPlayerDirection('a');
            directionSet = true;
            break;
        case 'd':
            if (player.getPlayerDirection() == 'a')
                break;
            player.xCor++;
            moves--;
            player.setPlayerDirection('d');
            directionSet = true;
            break;
        }
        printw("Moves left: %d\n", moves);
        refresh();
        checkBoundary();
        updatePlayer(prevX, prevY);
        if (directionSet)
            player.pushPosition(prevX, prevY);
    }
    void undoMove()
    {
        // go back in stack once if undos available
        int prevX = player.xCor;
        int prevY = player.yCor;
        player.undoMove();
        updatePlayer(prevX, prevY);
    }
    void checkBoundary()
    {
        if (player.xCor < 0)
        {
            player.xCor = 0;
        }
        else if (player.xCor >= width)
        {
            player.xCor = width - 1;
        }
        if (player.yCor < 0)
        {
            player.yCor = 0;
        }
        else if (player.yCor >= height)
        {
            player.yCor = height - 1;
        }
    }
    void checkCollision()
    {
        if (grid.playerAndBombCollision(player.xCor, player.yCor))
        {
            // game over
            printw("Game Over");
            refresh();
            playing = false;
        }
        else if (grid.playerAndCoinCollision(player.xCor, player.yCor))
        {
            // increase score of player
            // add coin cordinates to players list
            printw("Coin Collected\n");
            refresh();
            player.collectCoin(player.xCor, player.yCor);
        }
        else if (player.xCor == grid.key->xCor && player.yCor == grid.key->yCor)
        {
            player.hasKey = true;
            printw("Key Collected\n");
            refresh();
        }
        else if (player.xCor == grid.door->xCor && player.yCor == grid.door->yCor)
        {
            if (player.hasKey)
            {
                // game won
                printw("Game Won");
                refresh();
                playing = false;
            }
            else
            {
                printw("You need a key to open the door");
                refresh();
            }
        }
    }
    int calculateMoves()
    {
        int moves = 0;
        if (mode == 1)
        {
            moves = 6;
        }
        else if (mode == 2)
        {
            moves = 2;
        }
        printw("Key at %d , %d\n", grid.key->yCor, grid.key->xCor);
        printw("Door at %d , %d\n", grid.door->yCor, grid.door->xCor);

        this->distanceOfPlayer = calculateManhattanDistance(grid.key);
        return distanceOfPlayer + calculateManhattanDistance(grid.key, grid.door) + moves;
    }
    int calculateManhattanDistance(Cell *object)
    {
        return abs(object->xCor - player.xCor) + abs(object->yCor - player.yCor);
    }
    int calculateManhattanDistance(Cell *key, Cell *door)
    {
        return abs(door->xCor - key->xCor) + abs(door->yCor - key->yCor);
    }
    bool senseDistance(Cell *key, Cell *door)
    {
        int distance = 0;
        if (player.hasKey)
            distance = calculateManhattanDistance(grid.door);
        else
            distance = calculateManhattanDistance(grid.key);

        if (distance < this->distanceOfPlayer)
        {
            this->distanceOfPlayer = distance;
            return true;
        }
        this->distanceOfPlayer = distance;
        return false;
    }
    void calculateUndoMoves()
    {
        if (mode == 1)
        {
            player.setUndoMoves(6);
        }
        else if (mode == 2)
        {
            player.setUndoMoves(4);
        }
        else if (mode == 3)
        {
            player.setUndoMoves(1);
        }
    }
    bool checkGameOver()
    {
        return moves == 0 || !playing;
    }
};

int main()
{
    initscr();
    // Print to the screen
    cbreak(); // Disable line buffering
    noecho();
    // Refresh the screen
    refresh();

    Maze maze(1);
    char direction;

    while (!maze.checkGameOver())
    {
        clear();
        printw("Score: %d\n", maze.player.score);
        printw("Moves left: %d\n", maze.moves);
        printw("Undo Moves left: %d\n", maze.player.undoMoves);
        printw("Key status: %s\n", maze.player.hasKey ? "Collected" : "Not Collected");
        maze.drawMaze();
        printw("Enter direction: ");
        direction = getch();
        maze.move(direction);
        bool closer = maze.senseDistance(maze.grid.key, maze.grid.door);
        if (closer)
        {
            printw("Getting warmer\n");
        }
        else
        {
            printw("Getting colder\n");
        }
        refresh();
        maze.checkCollision();
        napms(2000);
    }

    printw("Key at %d , %d\n", maze.grid.key->yCor, maze.grid.key->xCor);
    printw("Door at %d , %d\n", maze.grid.door->yCor, maze.grid.door->xCor);
    printw("Coins Collected: \n");
    maze.player.coinsCollected.printList();
    printw("Previous Positions: \n");
    maze.player.prevPositions.printList();
    // refresh();
    //  Wait for a key press
    getch();
    // ends ncurses
    endwin();

    return 0;
}
