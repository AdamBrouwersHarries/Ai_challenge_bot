#include "Bot.h"

using namespace std;

//constructor
Bot::Bot()
{

};

//plays a single game of Ants.
void Bot::playGame()
{
    //reads the game parameters and sets up
    cin >> state;
    state.setup();
    endTurn();

    //continues making moves while the game is not over
    while(cin >> state)
    {
        state.updateVisionInformation();
        makeMoves();
        endTurn();
    }
};

//makes the bots moves for the turn
void Bot::makeMoves()
{
    state.bug << "turn " << state.turn << ":" << endl;
    state.bug << state << endl;

	//set up the food "scent" information
	state.floodPFInformation();
	state.bug<<"done flood finding, printing results:\n";
	for(int i = 0;i<state.rows;i++)
	{
		for(int j = 0;j<state.cols;j++)
		{
			if(state.grid[i][j].isFood == false)
			{
				//state.grid[i][j].distance+
				state.bug<<(state.grid[i][j].antDistance)%10;
			}else{
				if(state.grid[i][j].ant!=-1)
				{
					state.bug<<"=";
				}else{
					state.bug<<"*";
				}
			}
		}
		state.bug<<"\n";
	}
    //picks out moves for each ant
    for(int ant = 0;ant<(int)state.myAnts.size(); ant++)
	{
		state.bug<<"ant location:"<<state.myAnts[ant].row<<","<<state.myAnts[ant].col<<" and antnum = "<<state.grid[state.myAnts[ant].row][state.myAnts[ant].col].ant<<"\n";
		//directions/distances have the lowest index as the lowest distance
		int directions[4] = {-1,-1,-1,-1};
		int distances[4] = {0xFF,0xFF,0xFF,0xFF};
		//first sort the directions in terms of "scent", with low being prefferable
		for(int i = 0;i<4;i++)
		{
			Location tempLoc = state.getLocation(state.myAnts[ant], i);
			Square tempSqu = state.grid[tempLoc.row][tempLoc.col];
			int ttDist = tempSqu.distance + tempSqu.antDistance;
			directions[i] = i;
			distances[i] = ttDist;
		}
		bool passes = true;
		while(passes == true)
		{
			passes = false;
			for(int i = 1;i<4;i++)
			{
				if(distances[i]<distances[i-1])
				{
					passes = true;
					int holder = distances[i];
					distances[i] = distances[i-1];
					distances[i-1] = holder;
					holder = directions[i];
					directions[i] = directions[i-1];
					directions[i-1] = holder;
				}
			}
		}
		//directions are now sorted! (or at least they should be...);
		//try each of the directions in turn...
		bool moved = false;
		for(int i = 0;i<4;i++)
		{
			int d = directions[i];
			Location loc = state.getLocation(state.myAnts[ant], d);
			if(!state.grid[loc.row][loc.col].isWater and state.grid[loc.row][loc.col].ant != 0)
			{
				state.makeMove(state.myAnts[ant], d);
				moved = true;
				break;
			}else{
				state.bug << "ant failed to move!, direction:"<<i<<" ant:"<<ant<<"\n";
			}
		}
	}

    state.bug << "time taken: " << state.timer.getTime() << "ms" << endl << endl;
};

//finishes the turn
void Bot::endTurn()
{
    if(state.turn > 0)
        state.reset();
    state.turn++;

    cout << "go" << endl;
};
