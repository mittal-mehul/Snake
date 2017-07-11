#include<iostream>
#include<conio.h>
#include<windows.h>
using namespace std;

// user defined type co_ordinates

class co_ordinates{
    private:
        int x;
        int y;
    public:
        co_ordinates(){
            x= 0;
            y= 0;
        }
        void setX(int value){
            x= value;
        }
        void setY(int value){
            y= value;
        }
        int getX(){
            return x;
        }
        int getY(){
            return y;
        }
};

// Declaration of used functions
void loadGame(void);
void display(void);
void getInput(void);
void gamePlay(void);

//Global variables for easy access
bool gameover = false;
const int windowWidth= 25;
const int windowHeight= 25;
long score;
int nBody;
enum direction{ Stop= 0, Left, Right, Up, Down};

co_ordinates head, body[windowWidth*windowHeight], food;
direction dir;


int main(){

    loadGame();
    while(!gameover){
        display();
        getInput();
        gamePlay();
    }
    return 0;
}

void loadGame(void){
    // Set Defaults
    gameover= false;
    score=0;
    dir= Stop;
    head.setX(windowWidth/2);
    head.setY(windowHeight/2);
    food.setX(rand()% windowWidth);
    food.setY(rand()% windowHeight);
}

void getInput(void){
// Take an input only if a key is hit
  if(_kbhit()){
      switch (_getch()) {
          case 'a':
                dir= Left;
                break;
          case 'd':
                dir= Right;
                break;
          case 'w':
                dir= Up;
                break;
          case 's':
                dir= Down;
                break;
          case 'x':
                gameover= true;
                break;
        }
    }
}


void display(void){
    // Display the game status
    system("cls");
    // Top Walls
    for(int i=0; i< windowWidth+2; i++)
        cout<<"*";
    cout<<"\n";
    //Game core
    for(int i=0;i< windowWidth+2; i++){
        for(int j=0;j< windowHeight+2;j++){
            if(j==0 || j== windowWidth+1)
                cout<<"*";
            else if(i==head.getY() && j==head.getX())
                cout<<"O";
            else if(i == food.getY() && j== food.getX())
                cout<<"o";
            else{
                bool bodyPrint = false;
                for(int k=0;k<nBody;k++)
                    if(body[k].getX()==j && body[k].getY()==i ){
                        cout<<"O";
                        bodyPrint= true;
                    }
                if(!bodyPrint)
                  cout<<" ";
            }
        }
        cout<<"\n";
    }

    //Bottom Walls
    for(int i=0; i< windowWidth+2; i++)
        cout<<"*";
    cout<<"\nScore: "<<score;
}

void gamePlay(void){

    //Gameover condition

    for(int i=0;i<nBody;i++)
        if(head.getX()==body[i].getX() && head.getY()== body[i].getY()){
            gameover= true;
            return;
        }

    // Moving the body with snake
        for(int i= nBody-1;i>=1;i--)
            body[i]=body[i-1];
        body[0]= head;

    // Speed Control
    Sleep(10);
    // Movement Control
    switch (dir) {
        case Left:
            // Move Left
            head.setX(head.getX()-1);
            break;
        case Right:
            // Move Right
            head.setX(head.getX()+1);
            break;
        case Up:
            // Move Up
            head.setY(head.getY()-1);
            break;
        case Down:
            // Move Down
            head.setY(head.getY()+1);
            break;
        default:
            // Do Nothing
            break;
    }
    // Moving Through the walls
    if(head.getX()>= windowWidth)
        head.setX(0);
    else if(head.getX()<0)
        head.setX(windowWidth);
    if(head.getY()>= windowHeight)
        head.setY(0);
    else if(head.getY()<0)
        head.setY(windowHeight);

    // Getting the food
    if(head.getX()== food.getX() && head.getY()== food.getY()){
        score+=10;
        food.setX(rand()% windowWidth);
        food.setY(rand()% windowHeight);
        nBody++;
    }
}

