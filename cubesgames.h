#ifndef CUBES_GAME_H
#define CUBES_GAME_H

#include <map>
#include <string>
#include <vector>
#include "dldCubesGamesServer.h"

class Color
{
	public:
		int m_R;
    	int m_G;
		int m_B;

		Color(){}
		Color( int R, int G, int B ):m_R(R), m_G(G), m_B(B) {}
};

bool operator<(const Color& lhs, const Color& rhs)
{
	return ((lhs.m_R < rhs.m_R) ||
	        ((lhs.m_R == rhs.m_R) && (lhs.m_G < rhs.m_G)) ||
	        ((lhs.m_R == rhs.m_R) && (lhs.m_G == rhs.m_G) && (lhs.m_B < rhs.m_B)));
}

class Rssi
{
private:
	//std::map<std::string,bool> m_mDeviceToIsClose;
	std::vector<Distance>  m_mDeviceToIsClose;

public:
	Rssi();
	~Rssi();
	void addItem( std::string sDevice,std::string sToDevice, bool bIsClose );
	//bool isEveryoneClose();
};

typedef std::vector<Color> ColorVector;

class dldCubesGame
{

private:

	std::map<Color,ColorVector> m_mColorToComponent;
	std::vector<std::string> m_devices;
	dldCubesGameServer m_server;
	Rssi m_rssi;
	double nTimeout;


	Color COLOR_PINK, COLOR_RED, COLOR_WHITE, COLOR_ORANGE, COLOR_YELLOW, COLOR_PURPLE, COLOR_BLUE,	COLOR_GREEN, COLOR_BLACK;


public:

	dldCubesGame();

	~dldCubesGame();

	bool initGame( Color color );

	bool playGame();	

	bool playGameStep( Color mainColor );

	bool playSound();

	bool waitForStepCompletion();

	bool waitForDistance();

	void addColor( Color mainColor, Color component1, Color component2 );
};


#endif