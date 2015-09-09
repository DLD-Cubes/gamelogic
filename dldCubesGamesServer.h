#ifndef CUBES_GAME_SERVER_H
#define CUBES_GAME_SERVER_H

#include <map>
#include <string>
#include <vector>


struct Distance 
{
	std::string sFrom;
	std::string sTo;
	bool bIsClose;
};

class dldCubesGameServer
{

private:
	std::vector<std::string> m_vDeviceIds;

public:
	dldCubesGameServer();

	~dldCubesGameServer();

	std::vector<std::string> getDevices();

	std::vector<Distance> getDistances();

	bool setLightColor( std::string sDeviceId, int R, int G, int B );

};
#endif