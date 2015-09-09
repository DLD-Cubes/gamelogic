
#include <map>
#include <ctime>
#include "cubesgames.h"
#include <stdio.h>

Rssi::Rssi()
{

}

Rssi::~Rssi()
{

}

void Rssi::addItem( std::string sFromDevice, std::string sToDevice, bool bIsClose )
{
	m_mDeviceToIsClose.push_back({sFromDevice, sToDevice, bIsClose});
}

/*
bool Rssi::isEveryoneClose()
{
	for(it = m_mDeviceToIsClose.begin(); it != m_mDeviceToIsClose.end(); it++)
	{
		if(!it->second)
		{
			return false;
		}
	}

	return true;
}
*/

void dldCubesGame::addColor( Color mainColor, Color component1, Color component2 )
{
	Color arr[] = { component1, component2 };
	std::vector<Color> vComponents(arr, arr + sizeof(arr) / sizeof(arr[0]) );
	m_mColorToComponent.insert(std::pair< Color,std::vector<Color> >(mainColor, vComponents));
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


bool dldCubesGame::initGame( Color mainColor )
{
	m_server.setLightColor( m_devices[0], mainColor.m_R,  mainColor.m_G, mainColor.m_B );
	Color compColor = m_mColorToComponent[mainColor][0];
	m_server.setLightColor( m_devices[1], compColor.m_R, compColor.m_G, compColor.m_B);
	compColor = m_mColorToComponent[mainColor][1];
	m_server.setLightColor( m_devices[2], compColor.m_R, compColor.m_G, compColor.m_B);
	playSound();
	return true;
}

bool dldCubesGame::playGameStep( Color mainColor )
{
	initGame(mainColor);
	waitForStepCompletion();
	playSound();
	waitForDistance();
}

bool dldCubesGame::playGame()
{
	playGameStep(COLOR_PINK);
	playGameStep(COLOR_ORANGE);
	playGameStep(COLOR_PURPLE);
	playGameStep(COLOR_GREEN);
}

bool dldCubesGame::playSound()
{
		
}


bool dldCubesGame::waitForStepCompletion()
{
	std::clock_t start = std::clock();
	bool bIsEveryoneClose;
	do
	{
		//Waiting for the kids to get distant or timeout
		std::vector<Distance> vDistances = m_server.getDistances();
		int i; 
		bIsEveryoneClose = true;
		for(i = 0; i < vDistances.size(); i++)
		{
			//m_rssi.addItem( vDistances[i].sFrom, vDistances[i].sTo, vDistances[i].bIsClose);
			if(!vDistances[i].bIsClose)
			{
				bIsEveryoneClose = false;
				break;
			}
		}


		double duration = (std::clock() - start ) / (double) CLOCKS_PER_SEC;
		if(duration >= nTimeout)
		{
			return false;
		}		
	}
	while(!bIsEveryoneClose);

	return true;
}

bool dldCubesGame::waitForDistance()
{
	std::clock_t start = std::clock();
	bool bIsEveryoneClose;
	do
	{
		//Waiting for the kids to get distant or timeout
		std::vector<Distance> vDistances = m_server.getDistances();
		int i; 
		bIsEveryoneClose = true;
		for(i = 0; i < vDistances.size(); i++)
		{
			//m_rssi.addItem( vDistances[i].sFrom, vDistances[i].sTo, vDistances[i].bIsClose);
			if(!vDistances[i].bIsClose)
			{
				bIsEveryoneClose = false;
				break;
			}
		}

		double duration = (std::clock() - start ) / (double) CLOCKS_PER_SEC;
		if(duration >= nTimeout)
		{
			return false;
		}		
	}
	while(bIsEveryoneClose);

	return true;
}

/*
bool dldCubesGame::waitForStepCompletion()
{
	std::vector<Distance> vDistances = m_server.getDistances();
	int i;
	for(i = 0; i < vDistances.size(); i++)
	{
		m_rssi.addItem( vDistances[i].sFrom, vDistances[i].sTo, vDistances[i].bIsClose);
	}

	std::clock_t start = std::clock();

	while(!m_rssi.isEveryoneClose())
	{
		//Waiting for the kids to get distant or timeout
		double duration = (std::clock() - start ) / (double) CLOCKS_PER_SEC;
		if(duration >= nTimeout)
		{
			return false;
		}		
	}
}

bool dldCubesGame::waitForDistance()
{
	std::vector<Distance> vDistances = m_server.getDistances();
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
		duration = (std::clock() - start ) / (double) CLOCKS_PER_SEC;
		if(duration >= nTimeout)
		{
			return false;
		}		
 	}
 	return true;

 }
*/

 int main()
 	{
 		dldCubesGame* game = new dldCubesGame();
 		game->playGame();
 	}
