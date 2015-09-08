#ifndef CUBES_GAME_SERVER_H
#define CUBES_GAME_SERVER_H

#include std::map;


Struct Distance 
{
	String sFrom;
	String sTo;
	bool bIsClose;
}

class dldCubesGameServer
{
private:
	std::vector<string> m_vDeviceIds;

public:
	dldCubesGameServer()
	{

	}

	~dldCubesGameServer()
	{

	}

	std::vector<String> getDevices()
	{
		return m_vDeviceNames;
	};

	std::vector<Distance> getDistances()
	{

	}


	bool setLightColor( String sDeviceId int R, int G, int B )
	{

	}

}