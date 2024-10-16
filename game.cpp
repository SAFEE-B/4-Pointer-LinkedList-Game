#include <iostream>
#include<cstdlib>
using namespace std;

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
    int c1x,c1y;
    int c2x,c2y;
    Node*player;


    Board(int level) {
        if (level == 1) {
            size = 10;
        }
        else if(level==2){
            size = 15;
        }
        else if(level==3){
            size = 20;
        }
        else{
            size = 10;
            cout<<"Invalid Number Given as Size...(Started with size 10x10)"<<endl;
        }
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
        cout<<px<<" "<<py<<" "<<dx<<" "<<dy<<" "<<kx<<" "<<ky<<" "<<c1x<<" "<<c1y<<" "<<c2x<<" "<<c2y<<endl;
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
                    currentPtr->key='K';
                }
                else if(b==dx && a==dy){
                    currentPtr->key='D';
                }
                else if(b==c1x && a==c1y){
                    currentPtr->key='C';
                }
                else if(b==c2x && a==c2y){
                    currentPtr->key='C';
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
    void MovePlayer(){
        char dir;
        cout<<"Give Input";
        cin>>dir;
        if(dir=='w'){
            if(py>0){
                py--;
                player->key='.';
                player=player->up;
                player->key='P';
            }
        }
        else if(dir=='s'){
            if(py<size-3){
                py++;
                player->key='.';
                player=player->down;
                player->key='P';
            }
        }
        else if(dir=='d'){
            if(px<size-3){
                px++;
                player->key='.';
                player=player->right;
                player->key='P';
        }
        }
        else if(dir=='a'){
            if(px>0){
                px--;
                player->key='.';
                player=player->left;
                player->key='P';
            }
        }
    }
    void printBoard(){
            Node* currentRow = head;

            // Print the board row by row
            for (int a = 0; a < size; a++) {
                Node* current = currentRow;
                for (int b = 0; b < size; b++) {
                    cout << current->key << " ";
                    current = current->right;
                }
                cout << endl;
                currentRow = currentRow->down;
            }
    }
};

void PlayGame(){
    cout<<"What Hardness You wanna Play...\nPRESS 1 :EASY\nPRESS 2:MEDIUM\nPRESS 3:HARD\n";
    int hardness;
    cin>>hardness;
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
    }
}
int main() {
    
    srand(time(0));
    PlayGame();

    return 0;
}
