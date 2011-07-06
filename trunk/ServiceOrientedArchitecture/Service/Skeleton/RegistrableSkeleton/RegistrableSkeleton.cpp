#include "RegistrableSkeleton.h"
#include <iostream>
using namespace std;

RegistrableSkeleton::RegistrableSkeleton() {}

RegistrableSkeleton::RegistrableSkeleton(string serviceIDToSet)
    : Skeleton(serviceIDToSet) {}

RegistrableSkeleton::RegistrableSkeleton
(string serviceIDToSet, TcpIpPassiveSocket* listeningSocketToShare)
    : Skeleton(serviceIDToSet, listeningSocketToShare) {}

string RegistrableSkeleton::getRegistrationInfo()
{
    string registrationInfoToReturn = serviceID;
    registrationInfoToReturn.append("@");
    if(!sharedListeningSocket) // Se il socket è condiviso con altri serventi allora dovrà essere il gestore del pool 
							   // ad inserire l' informazione relativa all' indirizzo.
	{
	registrationInfoToReturn.append(listeningSocket->getAddress()); //TODO controllare perché ancora non abbiamo controllato neanche quello di prima
	}
    return registrationInfoToReturn;
}
