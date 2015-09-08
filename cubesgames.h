#ifndef CUBES_GAME_H
#define CUBES_GAME_H

#include <map>
#include <string>
#include <vector>

class Color
{
	public:
		int m_R;
    	int m_G;
		int m_B;

		Color( int R, int G, int B ):(m_R(R), m_G(G), m_B(B)) {};
};

class Rssi
{
private:
	std::map<std::string,bool> m_mDeviceToIsClose;

public:
	Rssi();
	~Rssi();
	void addItem( std::string sDevice, bool bIsClose );
	bool isEveryoneClose();
};


class dldCubesGame
{

private:

	std::map<Color,std::vector<Color>> m_mColorToComponent;
	std::vector<std::string> m_devices;
	dldCubesGamesServer m_server;
	Rssi m_rssi;
	int nTimeout;


	Color COLOR_PINK, COLOR_RED, COLOR_WHITE, COLOR_ORANGE, COLOR_YELLOW, COLOR_PURPLE, COLOR_BLUE,	COLOR_GREEN, COLOR_BLACK;


public:

	dldCubesGame();

	~dldCubesGame();

	bool initGame( Color color );

	bool playGame();	

	bool playGameStep();

	bool playSound();

	bool waitForCompletion();

	bool waitForDistance();
}


#endif