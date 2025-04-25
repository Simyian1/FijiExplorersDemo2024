//to compile
//Get into the directory with cannibals.cpp and run:
//g++ - o cannibals cannibals.cpp


#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <array>

const int MAX_DEPTH = 10000;

int printPath(std::array<int, 6> riv, bool left, std::map<std::string, int>& memo);
void printCur(std::array<int, 6> riv, bool left, int E, int C);

int main()
{
	std::array<int, 6> riv = { 3,3,0,0,0,0 }; // E C  \E C/ E C
	std::map<std::string, int> memo;

    std::cout << "\nSolution:\n";

    //inital solve call
	printPath(riv, true, memo);
   
    printCur(riv, true, 0, 0);  // print final state

	return 0;
}

std::string getStateKey(std::array<int, 6> riv, bool left) {
	// convert state and boat position to a unique key
	std::string key = left ? "L" : "R";
	for (int i = 0; i < 6; ++i) {
		key += std::to_string(riv[i]);
	}
	return key;
}

void printCur(std::array<int, 6> riv, bool left, int E, int C)
{
	std::string leftS = "";
	std::string rightS = "";
	std::string boatS = "";
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < riv[i]; ++j)
		{
			if (i % 2 == 0)//even i is E
			{
				if (i == 0)//left shore
				{
					leftS += 'E';
				}
				else if (i == 2)//boat
				{
					boatS += 'E';
				}
				else if (i == 4)//right shore
				{
					rightS += 'E';
				}
			}
			else // odd i is C
			{
				if (i == 1)//left shore
				{
					leftS += 'C';
				}
				else if (i == 3)//boat
				{
					boatS += 'C';
				}
				else if (i == 5)//right shore
				{
					rightS += 'C';
				}
			}
		}
	}

    // add the current people to boat
    boatS = std::string(E, 'E') + std::string(C, 'C');


    // cionistent padding
    while (leftS.size() < 6) leftS += '_';
    while (rightS.size() < 6) rightS += '_';
    while (boatS.size() < 2) boatS += '_';
    //setup arrows
    std::string lArrow = !left ? "<- " : "   ", rArrow = !left ? "   " : " ->";
    //final ouput, right and left s swapped due to output issue
    std::cout << rightS << " " <<  lArrow << " \\_" << boatS << "_ / " << rArrow << " " << leftS << std::endl;
}

bool isValidState(std::array<int, 6> riv) {
    // check left shore
    if (riv[0] > 0 && riv[0] < riv[1])
    {
        return false;
    }
    // check right shore
    if (riv[4] > 0 && riv[4] < riv[5])
    {
        return false;
    }
    return true;
}

int printPath(std::array<int, 6> riv, bool left, std::map<std::string, int>& memo)
{
    std::string key = getStateKey(riv, left);

    // check if the state is already visited
    if (memo.count(key))
    {
        return 0;
    }
    //set memo key
    memo[key] = 1;

    // base case
    if (riv[4] == 3 && riv[5] == 3)
    {
        return 1;
    }

    // try all possible moves
    int moves[5][2] = { {1, 0}, {0, 1}, {1, 1}, {2, 0}, {0, 2} }; // (E, C) pairs
    for (int i = 0; i < 5; ++i)
    {
        int e = moves[i][0], c = moves[i][1];

        // apply
        if (left)// moving from left to right
        {
            if (riv[0] >= e && riv[1] >= c)
            {
                riv[0] -= e;
                riv[1] -= c;
                riv[4] += e;
                riv[5] += c;
                if (isValidState(riv))
                {
                    if (printPath(riv, !left, memo))
                    {
                        printCur(riv, left, e, c); //print path
                        return 1;
                    }
                }

                // backtrack
                riv[0] += e;
                riv[1] += c;
                riv[4] -= e;
                riv[5] -= c;
            }
        }
        else// moving from right to left
        {
            if (riv[4] >= e && riv[5] >= c)
            {
                riv[4] -= e;
                riv[5] -= c;
                riv[0] += e;
                riv[1] += c;
                if (isValidState(riv))
                {
                    if (printPath(riv, !left, memo))
                    {
                        printCur(riv, left, e, c); //print path
                        return 1;
                    }
                }
                // backtrack
                riv[4] += e;
                riv[5] += c;
                riv[0] -= e;
                riv[1] -= c;
            }
        }
    }
    return 0;
}


