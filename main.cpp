#include <iostream>
#include<cstdlib>
#include <ctime>
#include <curses.h> // Ensure you have included the PDCurses header
#include<math.h>
#include<string>

using namespace std;



class NodeQ{
    public:
    int x;
    int y;
    NodeQ*  next;
};
class Queue {
    NodeQ* head;

public:
    Queue() {
        head = nullptr;
    }

    void push(int x, int y) {
        NodeQ* newNode = new NodeQ();
        newNode->x = x;
        newNode->y = y;
        newNode->next = nullptr;

        // If the queue is empty, set the new node as the head.
        if (!head) {
            head = newNode;
        } else {
            NodeQ* currentPtr = head;
            while (currentPtr->next) {
                currentPtr = currentPtr->next;
            }
            currentPtr->next = newNode;
        }
    }

    void PrintAll() {
    NodeQ* currentPtr = head;
    while (currentPtr) {
        printw("Coin -( %d , %d )   ", currentPtr->x, currentPtr->y); // Print the formatted string
        currentPtr = currentPtr->next;
    }
    printw("\n"); 
}

    // Destructor to clean up memory if necessary
    ~Queue() {
        NodeQ* currentPtr = head;
        while (currentPtr->next) {
            NodeQ* nextPtr = currentPtr->next;
            delete currentPtr;
            currentPtr = nextPtr;
        }
    }
};


class Node {
public:
    char key;
    Node* up;
    Node* down;
    Node* left;
    Node* right;
};



class Board {
public:
    Node* head;
    Node* coin1;
    Node* coin2;
    int size;
    int px;
    int py;
    int kx;
    int ky;
    int dx;
    int dy;
    int bx,by;
    int c1x,c1y;
    int c2x,c2y;
    Node*player;
    bool closerOrFarther;
    bool keyStatus;
    int undoCount;
    char preDir;
    int score;
    int coinCollected;
    int moveCount;
    Queue coinsQueue;
    bool gameOver,gameWin;
    Board(int level) {
        gameOver=false;
        gameWin=false;
        coinCollected=0;
        keyStatus=false;
        if (level == 1) {
            size = 10;
            undoCount=6;
            moveCount=6;
        }
        else if(level==2){
            size = 15;
            undoCount=4;
            moveCount=2;
        }
        else if(level==3){
            size = 20;
            undoCount=1;
            moveCount=1;
        }
        else{
            size = 10;
            undoCount=6;
            moveCount=6;
            printw("Invalid Number Given as Size...(Started with size 10x10)");
        }
        score=undoCount;
        Node* headArr[size];
        for (int a = 0; a < size; a++) {
            for(int b=0;b<size;b++){
            if(b==0){
            headArr[a] = new Node();
            headArr[a]->left = nullptr;
            headArr[a]->right = nullptr;
            headArr[a]->up = nullptr;
            headArr[a]->down = nullptr;
            headArr[a]->key='@';

            }
            else{
                Node*newNode=new Node();
                newNode->key='.';
                if(b==size-1){
                    newNode->key='@';
                }
                else{
                    newNode->key='.';
                }
                if(a==0){
                    headArr[a]->up=nullptr;
                    headArr[a]->key='@';
                }
                else if(a==size-1){
                    headArr[a]->down=nullptr;
                    headArr[a]->key='@';
                }
                
                newNode->right=headArr[a];
                headArr[a]->left=newNode;
                headArr[a]=newNode;
                if(b==size-1){
                    headArr[a]->left=nullptr;
                }

            }
            }
        }


        for (int a = 0; a < size - 1; a++) {
            Node* upperNode = headArr[a];
            Node* lowerNode = headArr[a + 1];
            for (int b = 0; b < size; b++) {
                upperNode->down = lowerNode;
                lowerNode->up = upperNode;
                upperNode = upperNode->right;
                lowerNode = lowerNode->right;
            }
        }

        head = headArr[0];
    }

    bool getGameOver(){
        return gameOver;
    }
    bool getGameWin(){
        return gameWin;
    }
    void setParameters(){
        px=rand()%(size-2);
        py=rand()%(size-2);
        
        while(true){
            kx=rand()%(size-2);
            ky=rand()%(size-2);
            if(kx!=px && ky!=py){
                break;
            }
        }
        while(true){
            dx=rand()%(size-2);
            dy=rand()%(size-2);
            if(dx!=px && dy!=py && dx!=kx && dy!=ky){
                break;
            }
        }
        while(true){
            c1x=rand()%(size-2);
            c1y=rand()%(size-2);
            if(c1x!=px && c1y!=py && c1x!=kx && c1y!=ky && c1x!=dx &&c1y!=dy){
                break;
            }
        }
        while(true){
            c2x=rand()%(size-2);
            c2y=rand()%(size-2);
            if(c2x!=px && c2y!=py && c2x!=kx && c2y!=ky && c2x!=dx &&c2y!=dy &&c2x!=c1x &&c2y!=c1y){
                break;
            }
        }
        while (true) {
            bx = rand() % (size - 2);
            by = rand() % (size - 2);
            if (bx != px && by != py && bx != kx && by != ky && bx != dx && by != dy && bx != c1x && by != c1y && bx != c2x && by != c2y) {
                break;
            }
        }

        moveCount+=getTotalDistance();
    }
    
    void setPositions(){
        Node*currentRow=head->down;
        for (int a=0;a<size-2;a++){
            Node*currentPtr=currentRow->right;
            for(int b=0;b<size-2;b++){
                if(b==px && a==py){
                    currentPtr->key='P';
                    player=currentPtr;
                }
                else if(b==kx && a==ky){
                    currentPtr->key='.';
                }
                else if(b==dx && a==dy){
                    currentPtr->key='.';
                }
                else if(b==c1x && a==c1y){
                    currentPtr->key='C';
                }
                else if(b==c2x && a==c2y){
                    currentPtr->key='C';
                }
                else if(b==bx&&a==by){
                    currentPtr->key='B';
                }
                currentPtr=currentPtr->right;
            }
        currentRow=currentRow->down;
        }
    }

    void setVal(int x,int y,char val){
        Node*currentRow=head->down;
        bool bool1=false;
        for (int a=0;a<size-2;a++){
            Node*currentPtr=currentRow->right;
            for(int b=0;b<size-2;b++){
                if(b==x && a==y){
                    currentPtr->key=val;
                    bool1=true;
                    break;
                }
                currentPtr=currentPtr->right;
            }
            if(bool1){
                break;
            }
        currentRow=currentRow->down;
    }
    }


    void randomizeCoin(){
        setVal(c1x,c1y,'.');
        setVal(c2x,c2y,'.');
        while(true){
            c1x=rand()%(size-2);
            c1y=rand()%(size-2);
            if(c1x!=px && c1y!=py && c1x!=kx && c1y!=ky && c1x!=dx &&c1y!=dy){
                break;
            }
        }
        while(true){
            c2x=rand()%(size-2);
            c2y=rand()%(size-2);
            if(c2x!=px && c2y!=py && c2x!=kx && c2y!=ky && c2x!=dx &&c2y!=dy &&c2x!=c1x &&c2y!=c1y){
                break;
            }
        }
        setVal(c1x,c1y,'C');
        setVal(c2x,c2y,'C');
    }
    bool checkKeyCoincide(){
        return (kx==px && ky==py);
    }
    bool checkCoinCoincide(){
        if(c1x==px&&c1y==py){
            coinsQueue.push(c1x,c1y);
            undoCount++;
            return true;
        }
        else if(c2x==px&&c2y==py){
            coinsQueue.push(c2x,c2y);
            undoCount++;
            return true;

        }
        return false;
    }

    void MovePlayer(){
        int dist_i=getDistance();
        char dir;
        printw("Give Input");
        cin>>dir;
        if(dir=='w'){
            if(py>0){
                if(preDir=='s' && undoCount==0){
                }
                else{
                if(preDir=='s'){
                    undoCount--;
                }
                else{
                    moveCount--;
                }
                    py--;
                    player->key='.';
                    player=player->up;
                    player->key='P';
                    preDir=dir;
                }
            }
        }
        else if(dir=='s'){
            if(py<size-3){
                if(preDir=='w' && undoCount==0){
                }
                else{
                if(preDir=='w'){
                    undoCount--;
                }
                else{
                    moveCount--;
                }
                    py++;
                    player->key='.';
                    player=player->down;
                    player->key='P';
                    preDir=dir;
                }
            }
        }
        else if(dir=='d'){
            if(px<size-3){
                if(preDir=='a' && undoCount==0){
                }
                else{
                if(preDir=='a'){
                    undoCount--;
                }
                else{
                    moveCount--;
                }
                    px++;
                    player->key='.';
                    player=player->right;
                    player->key='P';
                    preDir=dir;
                }
            }
        }
        else if(dir=='a'){
            if(px>0){
                if(px>0){
                    if(preDir=='d' && undoCount==0){
                    }
                    else{
                    if(preDir=='d'){
                        undoCount--;
                    }
                    else{
                        moveCount--;
                    }
                        px--;
                        player->key='.';
                        player=player->left;
                        player->key='P';
                        preDir=dir;
                    }
                }
        }
        }
        int dist_f=getDistance();
        if(dist_f>dist_i){
            closerOrFarther=true;
        }
        else{
            closerOrFarther=false;
        }
        if(!keyStatus){
            keyStatus=checkKeyCoincide();
        }
        if(checkCoinCoincide()){
            coinCollected++;
        }
        score=undoCount+(coinCollected*2);
        gameWin=(px == dx && py == dy && keyStatus);
        gameOver= (moveCount <= 0)||(bx==px && by==py);
    }
    
    
    int getDistance(){
        if(!keyStatus)
            return abs(kx-px)+abs(ky-py);
        else{
            return abs(dx-px)+abs(dy-py);
        }
    }
    int getTotalDistance(){
        return abs(kx-px)+abs(ky-py)+abs(kx-dx)+abs(ky-dy);
    }

    void printBoard() {
        clear(); // Clear the screen
        Node* currentRow = head;

        if(gameOver||gameWin){
        setVal(kx, ky, 'K'); // Make the key visible
        setVal(dx, dy, 'D'); // Make the door visible
        displayCollectedCoins();
        }
        string Score="Score: "+to_string(score);
        mvprintw(1,2,Score.c_str());
        string MvCnt="Moves Left: "+to_string(moveCount);
        mvprintw(2,2,MvCnt.c_str());
        string UndoCnt="Undo Count: "+to_string(undoCount);
        mvprintw(3,2,UndoCnt.c_str());
        string str;
        if(!keyStatus){
            if(!closerOrFarther ){
                str="Distance to Key: Getting Closer";
            }
            else{
                str="Distance to Key: Getting Farther";
            }
        }
        else{
            if(!closerOrFarther ){
            str="Distance to Door: Getting Closer";
            }
            else{
                str="Distance to Door: Getting Farther";
            }
        }
        mvprintw(4,2,str.c_str());
        
        if(keyStatus){
            str="Key Collected";
            mvprintw(5,2,str.c_str());
        }
        
        // Print the board row by row
        for (int a = 0; a < size; a++) {
            Node* current = currentRow;
            for (int b = 0; b < size; b++) {
                mvaddch(6+a*2,10+b*4, current->key); 
                current = current->right;
            }
            currentRow = currentRow->down;
        }
        refresh(); 
    }
    void displayCollectedCoins(){
        coinsQueue.PrintAll();
    }
    void printGameOverState() {
    printBoard();
    printw("\nPress any key to exit...");
    refresh();
    getch(); // Wait for the user to press any key before exiting
}
};

void PlayGame(){
    printw("What Hardness You wanna Play...\nPRESS 1 :EASY\nPRESS 2:MEDIUM\nPRESS 3:HARD");
    int hardness;
    scanw("%d",&hardness);
    Board b1(hardness);
    b1.setParameters();
    b1.setPositions();
    b1.printBoard();
    int count=0;
    while(true){
        b1.MovePlayer();
        b1.printBoard();
        count++;
        if(count%10==0){
            b1.randomizeCoin();
        }
        if (b1.getGameWin()) {
            b1.printGameOverState();
            printw("Congratulations! You reached the door and won the game.\n");
            break;
        } else if (b1.getGameOver()) {
            b1.printGameOverState();
            printw("Game Over! \n");
            break;
        }
    }
}
int main() {
    srand(time(0));
    initscr(); // Start PDCurses mode
    noecho(); // Don't echo user input
    //cbreak(); // Disable line buffering
    PlayGame();
    return 0;
}
