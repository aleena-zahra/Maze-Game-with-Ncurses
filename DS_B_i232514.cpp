//Aleena Zahra DS-3B DATA STRUCTURES ASSIGNMENT 2 MAZE GAME
#include <ncurses.h>
#include <iostream>
using namespace std;
#define MAX_TIME 60
//make static variable
static int num = 103;
int generateRandomNum()
{
    num = (num * 1103515245 + 12345)  & 0x7FFFFFFF;
    return num;
}
// list class
struct Node
{
    int xCor, yCor;
    char cellType;
    Node *link;

    Node(int xCor = 0, int yCor = 0,char cellType = ' ')
    {
        this->xCor = xCor;
        this->yCor = yCor;
        cellType = cellType;
        this->link = NULL;
    }
    void setIndex(int x,int y,char type)
    {
        this->xCor = x;
        this->yCor = y;
        this->cellType = type;
    }
    ~Node()
    {
        // printw("\ndestructor called for node with value: "<<this->xCor;
        link = NULL;
    }
};
class List
{
private:
    Node *head;
    List(const List &list) {}

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
    void push(int xCor, int yCor,char cellType=' ')
    {
        // create new node and set its values
        Node *newNode = new Node(xCor, yCor,cellType);

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
    void deleteAtIndex(int index){
        if(index==0){
            pop();
            return;
        }
        Node *temp = head;
        for(int i = 0; temp!=NULL && i<index-1;i++){
            temp = temp->link;
        }
        //now at index-1 of what to delete
        if(temp==NULL || temp->link == NULL){
            return;
        }
        Node *next = temp->link->link;
        delete temp->link;
        printw("Deleted at index %d\n",index);
        temp->link = next;
        
    }
    int find(int xCor,int yCor,char cellType=' '){
        Node *temp = head;
        int index = -1;
        while(temp!=NULL){
            index++;
            if(temp->xCor ==xCor && temp->yCor == yCor && temp->cellType == cellType){ 
                return index;
            }
            temp = temp->link;
        }
        if(temp!=NULL)
           return index; 
        return -1;
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
    Cell *childList;
    Cell(int x = 0, int y = 0)
    {
        this->xCor = x;
        this->yCor = y;
        Cell *up = down = right = left = childList = NULL;
        this->cellType = ' ';
    }
    ~Cell()
    {
        up = down = right = left = NULL;
    }
};
class Grid
{
    Cell *head;
    Cell *originalGrid;
    Node door, key;
    List bomb, coin;
    int width, height;
    int numOfItems;
    Grid(const Grid &grid) {}

public:
    Grid(int mode = 1)
    {
        this->width = this->height = (mode + 1) * 5;
        numOfItems = mode * 2;
        makeGrid();
    }
    ~Grid()
    {
        Cell *row = head;
        while (row != NULL) {
            Cell *current = row;
            row = row->childList; // Move to the next row
            while (current != NULL) {
                Cell *nextCell = current->right;
                delete current;
                current = nextCell;
            }
        }
        row = originalGrid;
        while (row != NULL) {
            Cell *current = row;
            row = row->childList; // Move to the next row
            while (current != NULL) {
                Cell *nextCell = current->right;
                delete current;
                current = nextCell;
            }
        }
    }
  
    void makeGrid()
    {
        // implementing a nested linked list by making a linked list of linked lists
        // make height number of linked lists
        //in a loop, first set prev row, prev cell and current list's head to null
        Cell *prevRow = NULL;
        for (int y = 0; y < height; y++) {
            Cell *prevCell = NULL;
            Cell *currentListHead = NULL;
            for (int x = 0; x < width; x++) {
                Cell *newCell = new Cell(x, y);
                // Set the top-left corner
                if (x == 0 && y == 0) {
                    head = newCell;
                    originalGrid = newCell;
                }   
                // Connect right and left
                if (prevCell != NULL) {
                    prevCell->right = newCell;
                    newCell->left = prevCell;
                }
                // Connect up and down
                if (prevRow != NULL) {
                    Cell *aboveCell = prevRow;
                    for (int i = 0; i < x; i++) {
                        if (aboveCell->right != NULL) {
                            aboveCell = aboveCell->right;
                        }
                    }
                    newCell->up = aboveCell;
                    aboveCell->down = newCell;
                }
                // Move to the next cell in the row
                prevCell = newCell;
                // Mark the head of this row
                if (x == 0) {
                    currentListHead = newCell;
                }
            }

            // Link this row to the previous row using childList
            if (prevRow != NULL) {
                prevRow->childList = currentListHead;
            }

            // Move to the next row
            prevRow = currentListHead;
        }

        // Set items on the grid (coins, bombs, key, door)
        setItems();
    }
    
    void setItems()
    {
        //make a copy of grid and store as original grid
        
        // Generate random coordinates for bomb, coin, key, and door
        key.setIndex(generateRandomNum() % height, generateRandomNum() % width, ' ');
        door.setIndex(generateRandomNum() % height, generateRandomNum() % width, ' ');
        setCollectibles();
    }
    int getHeight(){
        return height;
    }
    int getWidth(){
        return width;
    }
    void setCollectibles(){
        printw("generating coins and bombs\n");
        refresh(); 
        napms(2000);
        for (int i = 0; i < numOfItems; i++)
        {   
            int x,y;
            do{
            x = generateRandomNum() % height;
            y = generateRandomNum() % width;
            }while(getIndex(x,y)->cellType != ' ');

            printw("Bomb at %d , %d\n", x, y);
            bomb.push(x,y,'b');
            setIndex(x,y,'b');

            //coins
            do{
            x = generateRandomNum() % height;
            y = generateRandomNum() % width;
            }while(getIndex(x,y)->cellType != ' ');
            //pause screen
            coin.push(x,y,'c');
            setIndex(x,y,'c');
        }
    }
   
    Cell *getIndex(int x, int y) {
        Cell *currentRow = head;
        // Move down y rows
        for (int i = 0; i < y && currentRow != NULL; i++) {
            currentRow = currentRow->childList;
        }
        if (currentRow == NULL) return NULL;

        // Move right x columns
        Cell *current = currentRow;
        for (int j = 0; j < x && current != NULL; j++) {
            current = current->right;
        }
        return current;
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
    Node *getKey()
    {
        return &key;
    }
    bool playerAndBombCollision(int xCor, int yCor)
    {
        //figure out another way to check collisions
            return getIndex(xCor,yCor)->cellType == 'b';
    }
    bool playerAndCoinCollision(int xCor, int yCor)
    {
        int index = coin.find(xCor,yCor);
            if (getIndex(xCor,yCor)->cellType == 'c')
            {
                printw("Coin and player collide\n");
                refresh();
                return true;
            }
        
        return false;
    }
    void printGrid() {
    Cell *currentRow = head;
    while (currentRow != NULL) {
        Cell *temp = currentRow;
        while (temp != NULL) {
            printw("|");
            if (temp->cellType == 'P')
                attron(COLOR_PAIR(3));

            printw("%c", temp->cellType);

            attroff(COLOR_PAIR(3));
            temp = temp->right; // Move to the next cell in the row
        }
        printw("|");
        printw("\n");
        currentRow = currentRow->childList; // Move to the next row
    }
    printw("\n");
}

    Node* getDoor()
    {
        return &door;
    }
    void printOriginalGrid(){
        Cell *temp = originalGrid;
    }
};
// player class
class Player
{
    int xCor, yCor, distance;
    List coinsCollected, prevPositions;
    bool hasKey;
    int undoMoves;
    int score;
    char playerDirection;
    Player(const Player &player) {}

public:
    Player(int xCor = 0, int yCor = 0, int undoMoves = 6)
    {
        this->xCor = xCor;
        this->yCor = yCor;
        this->hasKey = false;
        this->undoMoves = undoMoves;
        this->score = 0;
        this->playerDirection = ' ';
    }
    ~Player()
    {
        // delete
        coinsCollected.~List();
        prevPositions.~List();
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
    // setters
    void setPlayerDirection(char direction)
    {
        playerDirection = direction;
    }
    void setXCor(int xCor)
    {
        this->xCor = xCor;
    }
    void setYCor(int yCor)
    {
        this->yCor = yCor;
    }
    void setHasKey(bool hasKey)
    {
        this->hasKey = hasKey;
    }

    // getters
    char getPlayerDirection()
    {
        return playerDirection;
    }
    int getXCor()
    {
        return xCor;
    }
    int getYCor()
    {
        return yCor;
    }
    int getScore()
    {
        return score;
    }
    bool getHasKey()
    {
        return hasKey;
    }
    List *getCoinsCollected()
    {
        return &coinsCollected;
    }
    List *getPrevPositions()
    {
        return &prevPositions;
    }
    int getUndoMoves()
    {
        return undoMoves;
    }
};
// maze class
class Maze
{
    Player player;
    int width, height;
    bool playing;
    int distanceOfPlayer;
    Grid grid;
    int mode; // 1 for easy, 2 for medium, 3 for hard
    int moves;

public:
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
    ~Maze()
    {
        // delete grid;
        grid.~Grid();
        player.~Player();
    }
    void initMaze()
    {
        grid.setIndex(player.getXCor(), player.getYCor(), 'P');
    }
    void drawMaze()
    {
        grid.printGrid();
    }
    void updatePlayer(int prevXCor, int prevYCor)
    {
        grid.setIndex(prevXCor, prevYCor, ' ');
        grid.setIndex(player.getXCor(), player.getYCor(), 'P');
    }
    void move(char direction)
    {
        int prevX = player.getXCor();
        int prevY = player.getYCor();
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
            {
                break;
            }
            {
                int y = player.getYCor();
                player.setYCor(y - 1);
                moves--;
                player.setPlayerDirection('w');
                directionSet = true;
            }
            break;
        case 's':
            if (player.getPlayerDirection() == 'w')
            {
                break;
            }
            {
                int y = player.getYCor();
                player.setYCor(y + 1);
                moves--;
                player.setPlayerDirection('s');
                directionSet = true;
            }
            break;
        case 'a':
            if (player.getPlayerDirection() == 'd')
            {
                break;
            }
            {
                int x = player.getXCor();
                player.setXCor(x - 1);
                moves--;
                player.setPlayerDirection('a');
                directionSet = true;
            }
            break;

        case 'd':
            if (player.getPlayerDirection() == 'a')
            {
                break;
            }
            {
                int x = player.getXCor();
                player.setXCor(x + 1);
                moves--;
                player.setPlayerDirection('d');
                directionSet = true;
            }
            break;
        }
        refresh();
        checkBoundary();
        checkCollision();
        updatePlayer(prevX, prevY);
        if (directionSet){
            player.pushPosition(prevX, prevY);
        }
        
    }
    void undoMove()
    {
        // go back in stack once if undos available
        int prevX = player.getXCor();
        int prevY = player.getYCor();
        player.undoMove();
        updatePlayer(prevX, prevY);
    }
    void checkBoundary()
    {
        if (player.getXCor() < 0)
        {
            player.setXCor(0);
        }
        else if (player.getXCor() >= width)
        {
            player.setXCor(width - 1);
        }
        if (player.getYCor() < 0)
        {
            player.setYCor(0);
        }
        else if (player.getYCor() >= height)
        {
            player.setYCor(height - 1);
        }
    }
    void checkCollision()
    {
        if (grid.playerAndBombCollision(player.getXCor(), player.getYCor()))
        {
            // game over
            printw("Game Over");
            refresh();
            playing = false;
        }
        else if (grid.playerAndCoinCollision(player.getXCor(), player.getYCor()))
        {
            // increase score of player
            // add coin cordinates to players list

            printw("Coin Collected\n");
            refresh();
            player.collectCoin(player.getXCor(), player.getYCor());
        }
        else if (player.getXCor() == grid.getKey()->xCor && player.getYCor() == grid.getKey()->yCor)
        {
            player.setHasKey(true);
            printw("Key Collected\n");
            refresh();
        }
        else if (player.getXCor() == grid.getDoor()->xCor && player.getYCor() == grid.getDoor()->yCor)
        {
            if (player.getHasKey())
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
        printw("Key at %d , %d\n", grid.getKey()->yCor, grid.getKey()->xCor);
        printw("Door at %d , %d\n", grid.getDoor()->yCor, grid.getDoor()->xCor);

        this->distanceOfPlayer = calculateManhattanDistance(grid.getKey());
        return distanceOfPlayer + calculateManhattanDistance(grid.getKey(), grid.getDoor()) + moves;
    }
    int calculateManhattanDistance(Node *object)
    {
        return abs(object->xCor - player.getXCor()) + abs(object->yCor - player.getYCor());
    }
    int calculateManhattanDistance(Node *key, Node *door)
    {
        return abs(door->xCor - key->xCor) + abs(door->yCor - key->yCor);
    }
    bool senseDistance(Node *key, Node *door)
    {
        int distance = 0;
        if (player.getHasKey())
            distance = calculateManhattanDistance(grid.getDoor());
        else
            distance = calculateManhattanDistance(grid.getKey());

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
    // getters
    Grid *getGrid()
    {
        return &grid;
    }
    Player *getPlayer()
    {
        return &player;
    }
    int getMoves()
    {
        return moves;
    }
    void refreshItems(){
        //remove coins and bombs
        for(int i =0 ; i<grid.getHeight();i++){
            for(int j = 0; j<grid.getWidth();j++){
                if(grid.getIndex(i,j)->cellType == 'c' || grid.getIndex(i,j)->cellType == 'b'){
                    grid.setIndex(i,j,' ');
                }
            }
        }
        grid.setCollectibles();
    }
    
};

int main()
{
    initscr();     // Initialize ncurses
    start_color(); // Start color functionality
    cbreak();      // Disable line buffering
    int row=20,col=72;
    WINDOW *menuWin = newwin(10, 40, 5, 20);
    WINDOW *startWin = newwin(row,col, 2, 4);
    box(menuWin, 0, 0);
    box(startWin, 0, 0);
    keypad(menuWin, TRUE);
    noecho();      // Disable echoing of characters
    //dont show curser
    curs_set(0);
    refresh();     // Refresh the screen
    // Define color pairs
    init_pair(1, COLOR_RED, COLOR_BLACK);   // Pair 1: Red text on black background
    init_pair(2, COLOR_GREEN, COLOR_BLACK); // Pair 2: Green text on black background
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_WHITE);
    init_pair(6, COLOR_BLUE, COLOR_WHITE);
    clear();                                // Clear the screen
    //make game menu that uses keys to select difficulty
    int highlighted = 0, choice;
    // Print welcome message and description on startWin
    //wattron(startWin, COLOR_PAIR(5));
    wbkgd(startWin, COLOR_PAIR(5));
    wbkgd(menuWin, COLOR_PAIR(6));
    int length=10;
    mvwprintw(startWin, 1, (col - 24) / 2, "Welcome to the Maze Game"); // Centered title
    mvwprintw(startWin, 4+length, 2, "Trapped in a dark maze, you can only see the ground beneath your feet.");
    mvwprintw(startWin, 5+length, 2, "Somewhere in the shadows, a hidden key unlocks the way out,");
    mvwprintw(startWin, 6+length, 2, "but you can't see it, and you don't know where it is.");
    mvwprintw(startWin, 7+length, 2, "You can sense when you're moving closer to the key,");
    mvwprintw(startWin, 8+length, 2, "guiding your steps through the darkness.");
  //  wattroff(startWin, COLOR_PAIR(5));

    // Refresh windows to display content
    refresh();      // Refresh the main screen
    wrefresh(startWin); // Display the startWin content
    while(1){
        for(int i =0 ; i<3 ; i++){
            if(i== highlighted){
                wattron(menuWin, A_REVERSE);
            }
            mvwprintw(menuWin, i+2, 17, "Level %d", i+1);
            wattroff(menuWin, A_REVERSE);
        }
        choice = wgetch(menuWin);
        switch(choice){
            case KEY_UP:
                highlighted--;
                if(highlighted == -1){
                    highlighted = 0;
                }
                break;
            case KEY_DOWN:
                highlighted++;
                if(highlighted == 3){
                    highlighted = 2;
                }
                break;
            default:
                break;
        }
        if(choice == 10){
            break;
        }
    }
    Maze maze(highlighted+1);
    char direction;
    int time = 0;
    while (!maze.checkGameOver())
    {
        clear();
        if (time++ > MAX_TIME)
        {
            printw("YOU RAN OUT OF TIME!\nGAME OVER\n");
            break;
        }
        int timeLeft = MAX_TIME - time;
        attron(COLOR_PAIR(1)); // turn on the attribute of color pair 1
        printw("Time Left: %d\n", timeLeft);
        printw("Score: %d\n", maze.getPlayer()->getScore());
        printw("Moves left: %d\n", maze.getMoves());
        printw("Undo Moves left: %d\n", maze.getPlayer()->getUndoMoves());
        printw("Key status: %s\n", maze.getPlayer()->getHasKey() ? "Collected" : "Not Collected");
        attroff(COLOR_PAIR(1)); // turn off the attribute of color pair 1
        maze.drawMaze();
        attron(COLOR_PAIR(2)); // turn on the attribute of color pair 2
        printw("Enter direction(W/A/S/D/U): ");
        attroff(COLOR_PAIR(2)); // turn off the attribute of color pair 2
        direction = getch();
        maze.move(direction);
        bool closer = maze.senseDistance(maze.getGrid()->getKey(), maze.getGrid()->getDoor());
        if (closer){
            attron(COLOR_PAIR(1));
            printw("Getting warmer\n");
            attroff(COLOR_PAIR(1));
        }
        else {
            attron(COLOR_PAIR(4));
            printw("Getting colder\n");
            attroff(COLOR_PAIR(4));
        }
        if(time%5==0){
            maze.refreshItems();
        }
        
        refresh();
        //maze.checkCollision();
        napms(2000);
    }

    printw("Key at y:%d ,x: %d\n", maze.getGrid()->getKey()->yCor, maze.getGrid()->getKey()->xCor);
    printw("Door at y:%d , x:%d\n", maze.getGrid()->getDoor()->yCor, maze.getGrid()->getDoor()->xCor);
    printw("Coins Collected: \n");
    maze.getPlayer()->getCoinsCollected()->printList();
    printw("Previous Positions: \n");
    maze.getPlayer()->getPrevPositions()->printList();
    // refresh();
    //  Wait for a key press
    getch();
    // ends ncurses
    endwin();

    return 0;
}
