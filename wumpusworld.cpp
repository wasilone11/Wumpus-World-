#include <iostream>
#include <cmath>
#include <sstream>
#include<cstdlib>
#include<fstream>

using namespace std;

#define GRIDSIZE 4
#define UP      0
#define DOWN    2
#define LEFT    3
#define RIGHT   1
#define MAX_SHOTS 3
#define FAILED -1

string to_string(int x)
{
    std::string out_string;
    std::stringstream ss;
    ss << x;
    return ss.str();
}


class Position
{

    int x, y;

public:

    Position (int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    Position() {}

    // Modify the following four so that the resulting position does not leave the grid
    void moveRight()
    {
        if(x>=3)
        {
            cout<<"Cannot move Right" << endl;
            return ;
        }
        else
            x++;
    }

    void moveLeft()
    {
        if(x<=0)
        {
            cout<<"Cannot move Left" << endl;
            return ;
        }
        else
            x--;
    }

    void moveUp()
    {
        if(y>=3)
        {
            cout<<"Cannot move up" << endl;
            return ;
        }
        else
            y++;
    }

    void moveDown()
    {
        if(y<=0)
        {
            cout<<"Cannot move down"<<endl;
            return ;
        }
        else
            y--;
    }

    bool isAdjacent(Position p)
    {
        //implement the function

        if((abs(x-p.getX()==0)&&abs(y-p.getY()==1))||(abs(x-p.getX()==1)&&abs(y-p.getY()==0)))
            return true;
        else
            return false;
    }

    bool isSamePoint(Position p)
    {
        //implement the function
        if((abs(x-p.getX()==0)&&abs(y-p.getY()==0))||(abs(x-p.getX()==0)&&abs(y-p.getY()==0)))
            return true;
        else
            return false;
    }
    bool is_above(Position p)
    {
        if(x==p.x&&y<p.y)
            return true;
        return false;
    }

    bool is_below(Position p)
    {
        if(x==p.x&&y>p.y)
            return true;
        return false;
    }

    bool is_right(Position p)
    {
        if(y==p.y&&x<p.x)
            return true;
        return false;
    }

    bool is_left(Position p)
    {
        if(y==p.y&&x>p.x)
            return true;
        return false;
    }
    int getX()
    {
        return x;
    }

    int getY()
    {
        return y;
    }

};


class Wumpus
{
    int xwumpus,ywumpus;
    bool killed;
    Position p;

public:

    Wumpus(int x, int y)
    {
        p = Position(x, y);
        killed = false;
    }

    Wumpus()
    {
        //...
        p=Position(rand()%GRIDSIZE,rand()%GRIDSIZE);

        killed = false;
    }

    void kill()
    {
        killed = true;
    }
    bool is_killed()
    {
        return killed;
    }
    Position getPosition()
    {
        return p;
    }

};


class Player
{

    int direction;
    int total_shots;
    bool killed;
    Position p;

public:

    Player()
    {
        //...
        direction=UP;
        total_shots=MAX_SHOTS;
        killed=false;
        p=Position(0,0);
    }

    void turnLeft()
    {
        direction=(direction+GRIDSIZE-1)%GRIDSIZE;
    }

    void turnRight()
    {
        //...
        if(direction==RIGHT)
            direction=DOWN;
        if(direction==DOWN)
            direction=LEFT;
        if(direction==LEFT)
            direction=UP;
        if(direction==UP)
            direction=RIGHT;
    }

    void moveForward()
    {
        //...
        if(direction ==UP)
            p.moveUp();
        else if(direction ==DOWN)
            p.moveDown();
        else if(direction ==RIGHT)
            p.moveRight();
        else
            p.moveLeft();
    }

    void kill()
    {
        killed = true;
    }
    bool isAbove(Position ptn)
    {
        return p.is_above(ptn);
    }
    bool isBelow(Position ptn)
    {
        return p.is_below(ptn);
    }
    bool isAdjacent(Position ptn)
    {
        return p.isAdjacent(ptn);
    }
    bool isRight(Position ptn)
    {
        return p.is_right(ptn);
    }
    bool isLeft(Position ptn)
    {
        return p.is_left(ptn);
    }
    bool isSamePoint(Position ptn)
    {
        return p.isSamePoint(ptn);
    }
    int shoot()
    {
        {
            if(total_shots)
            {
                total_shots--;
                return direction;
            }
        }
    }
    string getPositionInfo()
    {
        return "Player is now at " + to_string(p.getX()) + ", " + to_string(p.getY());
    }

    string getDirectionInfo()
    {
        string s;
        if (direction == UP)
            s = "up";
        if (direction == DOWN)
            s = "down";
        if (direction == LEFT)
            s = "left";
        if (direction == RIGHT)
            s = "right";
        return "Player is moving at direction: " + s;
    }

};



class WumpusWorld
{

private:

    Player player;
    Wumpus wumpus;
    Position pit_position;
    Position gold_position;
    bool ended;

public:

    WumpusWorld()
    {
        //...
        pit_position=Position(rand()%GRIDSIZE,rand()%GRIDSIZE);
        gold_position=Position(rand()%GRIDSIZE,rand()%GRIDSIZE);
    }

    WumpusWorld(int wumpus_x, int wumpus_y)
    {
        //...
        wumpus=Wumpus(wumpus_x, wumpus_y);
        pit_position=Position(rand()%GRIDSIZE,rand()%GRIDSIZE);
        gold_position=Position(rand()%GRIDSIZE,rand()%GRIDSIZE);
    }

    WumpusWorld(int wumpus_x, int wumpus_y, int gold_x, int gold_y)
    {
        wumpus=Wumpus(wumpus_x, wumpus_y);
        pit_position=Position(rand()%GRIDSIZE,rand()%GRIDSIZE);
        gold_position=Position(gold_x,gold_y);

    }

    WumpusWorld(int wumpus_x, int wumpus_y, int gold_x, int gold_y, int pit_x, int pit_y)
    {
        //...
        wumpus=Wumpus(wumpus_x, wumpus_y);
        gold_position=Position(gold_x,gold_y);
        pit_position=Position(pit_x,pit_y);
    }

    void moveForward()
    {
        player.moveForward();
        return showGameState();
    }

    void turnLeft()
    {
        player.turnLeft();
        return showGameState();
    }

    void turnRight()
    {
        player.turnRight();
        return showGameState();
    }

    void shoot()
    {
        int r=player.shoot();
        if(r!=FAILED &&!wumpus.is_killed())
        {
            if(r==UP && player.isAbove(wumpus.getPosition()))
                wumpus.kill();
            else if(r==DOWN && player.isBelow(wumpus.getPosition()))
                wumpus.kill();
            else if(r==LEFT && player.isLeft(wumpus.getPosition()))
                wumpus.kill();
            else if(player.isRight(wumpus.getPosition()))
                wumpus.kill();

            if (wumpus.is_killed())
            {
                cout<<"Woah ! You killed the Wumpus"<<endl;
            }
            else
            {
                cout<<"Bad Luck . Try again"<<endl;
            }
        }
        return showGameState();
    }

    void showGameState()
    {
        cout << player.getPositionInfo() << endl;
        cout << player.getDirectionInfo() << endl;

        if (player.isAdjacent(wumpus.getPosition()))
        {
            cout << "stench!" << endl;
        }

        if (player.isSamePoint(wumpus.getPosition()))
        {
            cout << "Player is killed!" << endl;
            player.kill();
            cout << "Game over!" << endl;
            ended = true;
        }

        if (player.isSamePoint(gold_position))
        {
            cout << "Got the gold!" << endl;
            cout << "Game ended, you won!" << endl;
            ended = true;
        }
    }

    bool isOver()
    {
        return ended;
    }

};


int main()
{
    int c, wumpus_x, wumpus_y, gold_x, gold_y, pit_x, pit_y;
    // take the six integers input from file
    ifstream fin;
    fin.open("wumpus_world.txt");
    fin>>wumpus_x>>wumpus_y>>gold_x>>gold_y>>pit_x>>pit_y;

    WumpusWorld w(wumpus_x, wumpus_y, gold_x, gold_y, pit_x, pit_y);
    w.showGameState();
    while (!w.isOver())
    {
        cout << "1: move forward" << endl;
        cout << "2: Turn left" << endl;
        cout << "3: Turn right" << endl;
        cout << "4: Shoot" << endl;
        cin >> c;
        if (c == 1)
        {
            w.moveForward();
        }
        else if (c == 2)
        {
            w.turnLeft();
        }
        else if (c == 3)
        {
            w.turnRight();
        }
        else if (c == 4)
        {
            w.shoot();
        }
    }
    fin.close();
    return 0;
}

