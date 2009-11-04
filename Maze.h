#ifndef maze_h
#define maze_h
class Maze
{
public:
	Maze();
	~Maze();
	void drawMaze();
	void drawBox();
	void drawWall();
	void drawFloor();
	void left();
	void right();
	void forward();
	
};
#endif maze_h