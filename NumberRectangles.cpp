// NumberRectangles.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>
#include <vector>
#include <time.h>
#include <algorithm> 

using namespace std;


/*Given a set of input coordinates determine the maximum number of rectangles that can be drawn*/

/*
    0  1  2  3  4  5  6  7  8  9  10 11 12 13 14
0   .  .  .  .  .  .  .  .  .  .  .  .  .  .  .
1   .  .  +--------+--------------------------+\---\------\
2   .  .  |  1  .  |  4  .  .  .  .  .  .  .  | 5   \      \
3   .  .  |  .  .  |  .  .  .  .  .  .  .  .  |/     \      \
4   .  .  +--------+-----------------+--------+\      8      \
5   .  .  |  2  .  |  7  .  .  .  .  |  3  .  | 6    /        \
6   .  .  |  .  .  |  .  .  .  .  .  |  .  .  |/    /          9
7   .  .  +--------------+-----------+--------+----/          /
8   .  .  .  .  .  |  .  .  .  .  .  .  .  .  |              /
9   .  .  .  .  .  |  .  .  .  .  .  .  .  .  |             /
10  .  .  .  .  .  +--------------------------+------------/
*/


uint32_t numSquaresFromPairs(uint32_t pairs);

map<pair<int, int>, int> linecount;

#define MAX_Y (15)
#define MAX_X (15)


typedef struct _Point_t {
    int x;
    int y;
} Point_t;

// Given a number of input points, determine how many rectangles can be drawn amongst sets of 4 unique points
Point_t arr[] = {
    {2,1},
    {5,1},
    {14,1},
    {2,4},
    {5,4},
    {11,4},
    {14,4},
    {2,7},
    {7,7},
    {11,7},
    {14,7},
    {5,10},
    {14,10},
};

Point_t problem2[] = {
    {2,1},
    {2,4},
    {2,7},
    {2,10},
    {4,1},
    {4,4},
    {4,6},
    {4,10},
    {7,4},
    {7,6},
    {7,7},
    {9,1},
    {9,4},
    {12,1},
    {12,4},
    {16,4},
    {16,7},
    {16,10},
    {20,1},
    {20,4},
    {20,6},
};

int main()
{
    srand(time(NULL));
    
    cout << "Count possible rectangles.\n";
    int answer = 0;
    for(int pIdx = 0; pIdx < sizeof(problem2)/sizeof(Point_t); pIdx++)
    {
        //first count number vertical lines from x's to given y's stored as pairs of y's
        //the number of rectangles for these lines follows triangular number sequence where N>2
        Point_t& ptBelow = problem2[pIdx];
        for (int idx2 = 0; idx2 < sizeof(problem2) / sizeof(Point_t); idx2++) {
            Point_t& ptAbove = problem2[idx2];
            if (ptBelow.x == ptAbove.x && ptBelow.y < ptAbove.y) {
                pair<int, int> new_pair(ptBelow.y, ptAbove.y);
                answer += linecount[new_pair];
                linecount[new_pair]++;
            }
        }
    }

    int answer2 = 0;
    for(map<pair<int,int>, int>::iterator i = linecount.begin(); i != linecount.end(); i++) {
        pair<int,int> y_coords = i->first;
        int numLinesForPair = i->second;

        answer2 += numSquaresFromPairs(i->second);
        cout << "(" << y_coords.first << "," << y_coords.second << "): " << numLinesForPair << " - " << answer2 << endl;
    }

    cout << "\n\nNumber of Rectangles: " << answer2 << " - " << answer << "\n";
}

uint32_t numSquaresFromPairs(uint32_t pairs) {
    return (pairs >> 1 ) * (pairs - ((pairs+1) & 1));
}
