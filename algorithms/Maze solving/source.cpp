#include <iostream>
#include <utility> // for pair
#include <vector>
#include <stack>
using namespace std;

typedef pair<int, int> point;
typedef vector<vector<int>> matrix;

bool outOfMaze(const matrix& maze, point p)
{
	if ((p.first >= maze.size() || p.first < 0) || (p.second >= maze[0].size() || p.second < 0))
	{
		return true;
	}
	return false;
}

void solveMaze(matrix& maze, point& source, point& destination)
{
	stack<point> path;
	point current = source;
	while (current != destination)
	{
		maze[current.first][current.second] = 2;
		if (!outOfMaze(maze,make_pair(current.first - 1, current.second)) && maze[current.first - 1][current.second] == 1) // up
		{
			path.push(current);
			current = make_pair(current.first - 1, current.second);
		}
		else if (!outOfMaze(maze, make_pair(current.first + 1, current.second)) && maze[current.first + 1][current.second] == 1) // down
		{
			path.push(current);
			current = make_pair(current.first + 1, current.second);
		}
		else if (!outOfMaze(maze, make_pair(current.first, current.second + 1)) && maze[current.first][current.second + 1] == 1) // right
		{
			path.push(current);
			current = make_pair(current.first, current.second + 1);
		}
		else if (!outOfMaze(maze, make_pair(current.first, current.second - 1)) && maze[current.first][current.second - 1] == 1) // left
		{
			path.push(current);
			current = make_pair(current.first, current.second - 1);
		}
		else
		{
			maze[current.first][current.second] = 3;
			current = path.top();	// only returns the top element does not remove it
			path.pop();				// only remove the element does not return it
		}
		if (path.empty())
		{
			//cout << "all path visited, no more left";
			exit(0);
		}
	}
}

void solveMazeRecursively(matrix& maze, point source, point destination)
{
	if (source == destination)
	{
		return;
	}
	maze[source.first][source.second] = 2;
	if (!outOfMaze(maze, make_pair(source.first - 1, source.second)) && maze[source.first - 1][source.second] == 1) // up
	{
		solveMazeRecursively(maze, make_pair(source.first - 1, source.second), destination);
	}
	else if (!outOfMaze(maze, make_pair(source.first + 1, source.second)) && maze[source.first + 1][source.second] == 1) // down
	{
		solveMazeRecursively(maze, make_pair(source.first + 1, source.second), destination);
	}
	else if (!outOfMaze(maze, make_pair(source.first, source.second + 1)) && maze[source.first][source.second + 1] == 1) // right
	{
		solveMazeRecursively(maze, make_pair(source.first, source.second + 1), destination);
	}
	else if (!outOfMaze(maze, make_pair(source.first, source.second - 1)) && maze[source.first][source.second - 1] == 1) // left
	{
		solveMazeRecursively(maze, make_pair(source.first, source.second - 1), destination);
	}
	else
	{
		maze[source.first][source.second] = 3;
		if (!outOfMaze(maze, make_pair(source.first - 1, source.second)) && maze[source.first - 1][source.second] == 2) // up
		{
			solveMazeRecursively(maze, make_pair(source.first - 1, source.second), destination);
		}
		else if (!outOfMaze(maze, make_pair(source.first + 1, source.second)) && maze[source.first + 1][source.second] == 2) // down
		{
			solveMazeRecursively(maze, make_pair(source.first + 1, source.second), destination);
		}
		else if (!outOfMaze(maze, make_pair(source.first, source.second + 1)) && maze[source.first][source.second + 1] == 2) // right
		{
			solveMazeRecursively(maze, make_pair(source.first, source.second + 1), destination);
		}
		else if (!outOfMaze(maze, make_pair(source.first, source.second - 1)) && maze[source.first][source.second - 1] == 2) // left
		{
			solveMazeRecursively(maze, make_pair(source.first, source.second - 1), destination);
		}
		else
		{
			//cout << "all path visited, no more left";
			exit(0);
		}
	}

}

int main()
{
	matrix maze = { {0,1,0,0,0,1,1,0},
					{0,1,1,0,0,0,0,0},
					{1,1,1,1,1,1,0,1},
					{1,0,1,0,1,1,1,1},
					{0,0,1,1,1,1,0,1},
					{1,1,1,0,1,1,1,1},
					{1,1,1,0,0,1,1,0},
					{1,1,1,1,1,1,1,1},
					{1,0,1,0,1,0,1,1} };

	point source = { 0, 1 }, destination = { 7, 5 };

	solveMaze(maze, source, destination);

	for (auto vec : maze) // the path will have value 2
	{
		for (int val : vec)
			cout << val << ' ';
		cout << endl;
	}

	// TODO make function to solve 3D maze
}
