#include<iostream>
using namespace std;

//list class
struct Node{
    int xCor,yCor;
    Node *link;

    Node(int xCor=0,int yCor=0){
        this->xCor = xCor;
        this->yCor = yCor;
        this->link = NULL;
    }
    ~Node(){
       // cout<<"\ndestructor called for node with value: "<<this->xCor;
    }
};
class List{
    private:
    Node *head;
    public:
    List(){
        head = NULL;
    }
    ~List(){
        //traverse list and delete each node until reach null
        Node* current = head;
        while (current != NULL) {
            Node* nextNode = current->link;
            delete current;
            current = nextNode;  
        }
        head = NULL;
    }
    
    void insertAtHead(int xCor,int yCor){
        //create new node and set its values
        Node* newNode = new Node(xCor,yCor);

        if(isEmpty()){
            head = newNode;
        }
        else{
            //when head isnt null store its address in new Node
            newNode->link = head;
            head = newNode;
        }
    }
    void insertAtEnd(int xCor,int yCor){
        //make the nodee
        Node *temp = new Node(xCor,yCor);
        //if empty list
        if(isEmpty()){
            head = temp;
        }
        else{
            Node *current = head;
            while(current->link !=NULL){
                current = current->link;
            }
            current->link = temp;
        }
        //traverse until current->next ==NULL
    }
    bool insertAfterPosition(int position,int xCor,int yCor){
        Node *newNode = new Node(xCor,yCor);
        if(position< 0){
            return false;
        }
        if(position == 0){
            insertAtHead(xCor,yCor);
        }
        else{
            int index =0;
            Node *current = head;
            Node *next;
            while(current->link!=NULL && index<position){
                current = current->link;
                index++;
            }
            next = current->link;
            current->link = newNode;
            newNode->link = next;
            
        }
        return true;
    }
    
    //delete functions
    void deleteAtStart(){
        if(!isEmpty()){
            Node *temp = head; //store old head/first node
            head = head->link; //new head is next node
            delete temp;      //delete old head/first node
        }
    }
    bool deleteAtEnd() {
        if (isEmpty()) {
            return false;
        }
        //only 1 node
        if (head->link == NULL) {
            deleteAtStart();
            return true;
        }
        //delete from end when nodes>1
        
        Node* secondLast = head;
        while (secondLast->link->link != NULL) {
            secondLast = secondLast->link;
        }

        // Delete the last node
        delete (secondLast->link);

        // Change link of second last
        secondLast->link = NULL;
        return true;
    }

    bool deleteAtIndex(int position){
        if(position<0){
            return false;
        }
        if(position==0){
            deleteAtStart();
            return true;
        }
        Node *current = head;
        Node *previous = NULL;
        int index = 0;
        while (current->link->link != NULL && index<position) {
            previous = current;
            current = current->link;
            index++;
        }
        previous->link = current->link;
        // Delete the node
        delete current;
        return true;
    }
    bool deleteAtValue(int value){
        if(head->xCor == value){
            deleteAtStart();
            return true;
        }
        Node *current = head;
        Node *previous = NULL;

        while (current->link->link != NULL && current->xCor!=value && current->yCor!=value) {
            previous = current;
            current = current->link;
        }
        previous->link = current->link;
        // Delete the node
        delete current;
        return true;
    }

    bool isEmpty(){
        return head==NULL;
    }
    void printList(){
        cout<<endl;
        Node *temp = head;
        while(temp!=NULL){
            cout<<temp->xCor<<","<<temp->yCor<<"->";
            
            temp = temp->link;
            
        }
        cout<<"NULL\n";
    }
    Node* getHead(){
        return head;
    }
    
};

//grid class
struct Cell{
    int xCor, yCor;
    char cellType;
    Cell *up;
    Cell *down;
    Cell *right;
    Cell *left;
    Cell(int x=0, int y=0){
        this->xCor = x;
        this->yCor = y;
        Cell *up = down = right = left = nullptr;
        this->cellType = ' ';
    }

};
class Grid{
    public:
    Cell **heads;
    Cell *door, *key;
    Cell *bomb, *coin;
    int width, height;
    Grid(int w=6, int h=6){
        this->width = w;
        this->height = h;
        heads = new Cell*[height];
        for (int i =0 ; i<height;i++){
            heads[i] = NULL;
        }
        makeGrid();
        
    }
    void insertNodeAtHead(int xCor,int yCor){
        // create new Carriage and set its values
        Cell *newCell = new Cell(xCor,yCor);

        if (heads[yCor]==NULL)
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
    void makeGrid(){
        //implementing a nested linked list by making a linked list of linked lists
        //make height number of linked lists and get their heads
        for (int i =0 ; i<height;i++){
            for (int j =width-1 ; j>=0 ; j--){
                insertNodeAtHead(j,i);
            }
            cout<<endl;
     }
        //connect the cells in each linked list
        //connect the linked lists by connecting their heads
        linkCells();
        setItems();
        
    }
    void linkCells(){
        for(int i =0 ; i<height-1 ; i++){
            Cell *curr = heads[i];
            Cell *next = heads[i+1];
            while(next!=NULL && curr!=NULL){
                curr->down = next;
                next->up = curr;
                curr = curr->right;
                next = next->right;
            }
        }
    }
    void setItems(){
        // Generate random coordinates for bomb, coin, key, and door
            key = setIndex(rand() % height,rand() % width,' ');
            door = setIndex(rand() % height,rand() % width,' ');
            bomb = setIndex(rand() % height,rand() % width,'b');
            coin = setIndex(rand() % height,rand() % width,'c');
            
    }
    Cell* getIndex(int x, int y){
        Cell *temp = heads[y];
        while (temp!=NULL){
            if (temp->xCor == x){
                return temp;
            }
            temp = temp->right;
        }
        cout<<"Index Not Found";
        return NULL;
    }
    Cell* setIndex(int x, int y, char type){
        Cell *cell = getIndex(x,y);
        if (cell!=NULL){
            cell->cellType = type;
        }
        return cell;
    }
    void printGrid(){
        for (int i =0 ; i<height;i++){
            Cell *temp = heads[i];
            while (temp!=NULL){
              //  cout<<"( "<<temp->xCor<<","<<temp->yCor<<" ) ";
              cout<<"|"<<temp->cellType;
                temp = temp->right;
            }
            cout<<"|";
            cout<<endl;
        }
        cout<<endl;
    }
};
//player class
class Player{
    public:
    int xCor, yCor,distance;
    List coinsCollected,prevPositions;
    bool hasKey;
    
        Player(int xCor=0, int yCor=0){
            this->xCor = xCor;
            this->yCor = yCor;
            this->hasKey = false;
        }
        int calculateManhattanDistance(Cell* object){
            return object->xCor - xCor + object->yCor - yCor;
        }
        void senseDistance(Cell* key, Cell* door){
            int distance = calculateManhattanDistance(key);
            if(distance<this->distance){
                cout << "Getting warmer!" << endl;
            }else if(distance>this->distance){
                cout << "Getting colder!" << endl;
            }
            this->distance = distance;
        }
        void collectCoin(int xCor,int yCor){
            coinsCollected.insertAtEnd(xCor,yCor);
            //update the score on terminal
        }
        void pushPosition(int xCor,int yCor){
            prevPositions.insertAtHead(xCor,yCor);
        }
        void undoMove(){
            Node* prev = prevPositions.getHead();
            xCor = prev->xCor;
            yCor = prev->yCor;
            prevPositions.deleteAtStart();
        }
};
//maze class
class Maze{
    public:
    Player player;
    Cell** maze;
    int width, height;
    bool playing;
    Grid grid;
        Maze(int width, int height): player(0, 0),grid(width, height){
            this->width = width;
            this->height = height;
            this->playing = true;
            initMaze();
        }
        void initMaze(){
            grid.setIndex(player.xCor,player.yCor,'P');
        
        }
        void drawMaze(){
            grid.printGrid();
        }
        void  updatePlayer(int prevXCor,int prevYCor){
            grid.setIndex(prevXCor,prevYCor,' ');
            grid.setIndex(player.xCor,player.yCor,'P');
        }
        void  move(char direction){
            int prevX = player.xCor;
            int prevY = player.yCor;
            switch(direction){
                case 'w':
                    player.yCor--;
                    break;
                case 's':
                    player.yCor++;
                    break;
                case 'a':
                    player.xCor--;
                    break;
                case 'd':
                    player.xCor++;
                    break;
            }
            checkBoundary();
            updatePlayer(prevX,prevY);
            player.pushPosition(prevX,prevY);

        }
        void undoMove(){
            //go back in stack once if undos available
            int prevX = player.xCor;
            int prevY = player.yCor;
            player.undoMove();
            updatePlayer(prevX,prevY);
        }
        void  checkBoundary(){
            if(player.xCor<0){
                player.xCor = 0;
            }else if(player.xCor>=width){
                player.xCor = width-1;
            }
            if(player.yCor<0){
                player.yCor = 0;
            }else if(player.yCor>=height){
                player.yCor = height-1;
            }
        }
        void checkCollision(){
            if(player.xCor == grid.bomb->xCor && player.yCor == grid.bomb->yCor){
                //game over
                cout<<"Game Over";
                playing = false;
            }
            else if(player.xCor == grid.coin->xCor && player.yCor == grid.coin->yCor){
                //increase score of player
                //add coin cordinates to players list
                cout<<"Coin Collected";
                player.collectCoin(player.xCor,player.yCor);
            }
            else if(player.xCor == grid.key->xCor && player.yCor == grid.key->yCor){
                player.hasKey = true;
                cout<<"Key Collected";
                
            }
            else if(player.xCor == grid.door->xCor && player.yCor == grid.door->yCor){
                if(player.hasKey){
                    //game won
                    cout<<"Game Won";
                    playing = false;
                }
                else{
                    cout<<"You need a key to open the door";
                }
            }
        }
};
int main(){
    Maze maze(6,6);
    char direction;
    int moves = 36;
    while(moves--&&maze.playing){
        cout<<"Enter direction: ";
        cin>>direction;
        if(direction == 'u'){
            maze.undoMove();
        }
        maze.move(direction);
        maze.player.senseDistance(maze.grid.key,maze.grid.door);
        maze.drawMaze();
        maze.checkCollision();
    }
    maze.player.coinsCollected.printList();
    maze.player.prevPositions.printList();
    return 0;
}

