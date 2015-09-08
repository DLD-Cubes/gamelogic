#include "cubesgames.h"
#include <stdio.h>
#include <map>
#include <ctime>


Rssi::Rssi()
{

}

void Rssi::addItem( String sFromDevice, String sToDevice, bool bIsClose )
{
	m_mDeviceToIsClose.insert( sFromDevice, bIsClose );
	m_mDeviceToIsClose.insert( sToDevice, bIsClose );
}


bool Rssi::isEveryoneClose
{
	std::map<String,bool>::iterator it; 
	for(it = map.begin(); it != map.end(); it++)
	{
		if(!it->second)
		{
			return false;
		}
	}

	return true;
}




dldCubesGame::dldCubesGame()
{

	COLOR_PINK = Color(175, 75, 148);
	COLOR_RED = Color(255,0,0);
	COLOR_WHITE = Color(255,255,255);
	COLOR_ORANGE = Color(237,120,6), 
	COLOR_YELLOW = Color(255,255,0);
	COLOR_PURPLE = Color(128, 0, 255);
	COLOR_BLUE = Color(0,0,255);
	COLOR_GREEN = Color(0,255,0); 
	COLOR_BLACK = Color(0,0,0);

	addColor(COLOR_PINK, COLOR_RED, COLOR_WHITE);
	addColor(COLOR_ORANGE, COLOR_RED, COLOR_YELLOW);
	addColor(COLOR_PURPLE, COLOR_RED, COLOR_BLUE);
	addColor(COLOR_GREEN, COLOR_BLUE, COLOR_YELLOW);

	//Get resources
	m_devices = m_server.getDevices();

	nTimeout = 5 * 60;

}

dldCubesGame::~dldCubesGame()
{

}


dldCubesGame::initGame( Color mainColor )
{
	m_server.setLightColor( m_devices[0], mainColor.m_R,  mainColor.m_G, mainColor.m_B );
	Color compColor = m_mColorToComponent[mainColor][0];
	m_server.setLightColor( m_devices[1], compColor.m_R, compColor.m_G, compColor.m_B);
	compColor = m_mColorToComponent[mainColor][1];
	m_server.setLightColor( m_devices[2], compColor.m_R, compColor.m_G, compColor.m_B);
	playSound();
}

void addColor( Color mainColor, Color component1, Color component2 )
{
	std::sp<std::vector<Color>> vComponents(2);
	vComponents.insert( component1 );
	vComponents.insert( component2 );
	m_mColorToComponent.insert(mainColor, vComponents);
}


bool playGameStep( Color mainColor )
{
	initGame(mainColor);
	waitForStepCompletion();
	playSound();
	waitForDistance();
}

bool playGame()
{
	playGameStep(COLOR_PINK);
	playGameStep(COLOR_ORANGE);
	playGameStep(COLOR_PURPLE);
	playGameStep(COLOR_GREEN);
}

bool playSound()
{
		
}

bool waitForCompletion()
{
	std::vector<Distance> vDistances = m_server.getDistances();
	int i;
	for(i = 0; i < vDistances.size(); i++)
	{
		m_rssi.addItem( vDistances[i].sFrom, vDistances[i].sTo, vDistances[i].bIsClose);
	}


	while(!m_rssi.isEveryoneClose())
	{
		//Waiting for the kids to get distant or timeout
		duration = (std::clock() - start ) / (double) CLOCKS_PER_SECOND;
		if(duration >= nTimeOut)
		{
			return false;
		}		
	}
}

bool waitForDistance()
{
	Vector<Distance> vDistances = m_server.getDistances();
	int i;
	for(i = 0; i < vDistances.size(); i++)
	{
		m_rssi.addItem( vDistances[i].sFrom, vDistances[i].sTo, vDistances[i].bIsClose);
	}

	std::clock_t start = std::clock();
	double duration;

	while(m_rssi.isEveryoneClose())
	{
		//Waiting for the kids to get close or timeout
		duration = (std::clock() - start ) / (double) CLOCKS_PER_SECOND;
		if(duration >= nTimeOut)
		{
			return false;
		}		
 	}
 	return true;
}
