#include <iostream>
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
    int size;

    Board(int level) {
        if (level == 1) {
            size = 10;
        }
        else if(level==2){
            size = 16;
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

int main() {
    Board b1(3);
    b1.printBoard();


    return 0;
}
