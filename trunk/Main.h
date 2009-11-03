#pragma once

class Main
{

public:
	Main(int argc, char** argv);
	~Main(void);

	void display();
	void handleResize(int width, int height);
};
