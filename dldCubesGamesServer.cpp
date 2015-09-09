#include "dldCubesGamesServer.h"
#include <iostream>

using namespace std;
//	std::vector<std::string> m_vDeviceIds;

	dldCubesGameServer::dldCubesGameServer()
	{
		cout << "Initializing server" << endl;
	}

	dldCubesGameServer::~dldCubesGameServer()
	{
		cout << "At the server destructor" << endl;
	}

	std::vector<std::string> dldCubesGameServer::getDevices()
	{
		cout << "In Get Devices" << endl;
		std::vector<std::string> v;
		v.push_back("device1");
		v.push_back("device2");
		v.push_back("device3");
		//cout << "getDevices vector is " << v << endl;
		cout << "getDevices ended" << endl;
		return v;
	};

	std::vector<Distance> dldCubesGameServer::getDistances()
	{
	     cout << "in GetDistances" << endl;
	     Distance dist1 = {"device1", "device2", true};
	     Distance dist2 = {"device2", "device3", true};
	     
	     std::vector<Distance> sub; 

	     //Push back new subject created with default constructor.
    	 sub.push_back({"device1", "device2", true});
    	 sub.push_back({"device2", "device3", true});

	     return sub;
	}


	bool dldCubesGameServer::setLightColor( std::string sDeviceId, int R, int G, int B )
	{
		cout << "setting light color " << R << "," << G << ", " << B << endl;
	}

