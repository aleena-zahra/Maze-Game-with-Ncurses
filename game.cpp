#include<iostream>
using namespace std;

int calculateManhattanDistance(int xCor, int yCor){
    return xCor + yCor;
}
class Player{
    public:
        int xCor, yCor;
        int distance = 100;
        Player(int xCor=0, int yCor=0){
            this->xCor = xCor;
            this->yCor = yCor;
        }
        
        void senseDistance(){
            int distance = calculateManhattanDistance(xCor, yCor);
            if(distance<this->distance){
                cout << "Getting warmer!" << endl;
            }else if(distance>this->distance){
                cout << "Getting colder!" << endl;
            }
            this->distance = distance;
        }
};
struct cell{
    int xCor, yCor;
    char cellType;
};
class Grid{
    public:
    Player player;
    cell bomb, coin, key, door;
    cell **grid;
    
        int width, height;
        Grid(int width, int height): player(0, 0){
            player =  Player(0,0);
            this->width = width;
            this->height = height;
            grid= new cell*[height];
            for(int i =0 ; i<height ; i++){
                grid[i] = new cell[width];
            }
            initGrid();
        }
        void initGrid(){
            for(int i =0 ; i<height; i++){
                for(int j = 0; j<width; j++){
                    grid[j][i].xCor = j;
                    grid[j][i].yCor = i;
                    grid[j][i].cellType = ' ';
                }
            }

            // Generate random coordinates for bomb, coin, key, and door
            bomb.xCor = rand() % height;
            bomb.yCor = rand() % width;
            bomb.cellType = 'b';
            grid[bomb.xCor][bomb.yCor] = bomb;

            coin.xCor = rand() % height;
            coin.yCor = rand() % width;
            coin.cellType = 'c';
            grid[coin.xCor][coin.yCor] = coin;

            key.xCor = rand() % height;
            key.yCor = rand() % width;
            key.cellType = ' ';
            grid[key.xCor][key.yCor] = key;

            door.xCor = rand() % height;
            door.yCor = rand() % width;
            door.cellType = ' ';
            grid[door.xCor][door.yCor] = door;

            grid[player.xCor][player.yCor].cellType = 'P';
        
        }
        void drawGrid(){
            for(int i = 0; i<height; i++){
                for(int j = 0; j<width; j++){
                    cout <<"| "<< grid[j][i].cellType ;
                    if(j==width-1)
                    cout<<" |";
                }
                
                cout << endl;
            }
        }
        void updatePlayer(int prevXCor,int prevYCor){
            grid[prevXCor][prevYCor].cellType = ' ';
            grid[player.xCor][player.yCor].cellType = 'P';
        }
        void move(char direction){
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
            updatePlayer(prevX,prevY);
        }
        
};


int main(){
    Grid game(6,6);
    game.drawGrid();
    char direction;
    cout<<"Enter direction: ";
    cin>>direction;
    game.move(direction);
    game.drawGrid();
    cout<<endl;
}