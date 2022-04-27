#include "PreparationEvent.h"
#include "Company.h"

bool PreparationEvent::Execute( Company& Comp) {
	//checking wich cargo type will be created

	if (CargoType == 'S')
	{
		//allocating a cargo 
		//assumed that Prep time is event time
		Cargo SC(EventTime, LoadTime, Distance, Cost, ID,'S');
		//enqueuing the cargo into the waiting special queue
		Comp.enqueueWSC(SC);
	}
	else if (CargoType == 'V')
	{
		//allocating a cargo 
		//assumed that Prep time is event time
		Cargo V(EventTime, LoadTime, Distance, Cost, ID,'V');
		//enqueuing the cargo into the waiting vip queue
		Comp.enqueueWVC(V);
	}
	else if (CargoType == 'N')
	{
		//allocating a cargo 
		//assumed that Prep time is event time
		Cargo N(EventTime, LoadTime, Distance, Cost, ID,'N');
		//enqueuing the cargo into the waiting normal list
		Comp.insertWNC(N);
	}
	return true;
}


void PreparationEvent::SetParameters(char CT, Time ET, int D, int LT, int C,int id)
{
	CargoType = CT;
	EventTime = ET;
	Distance = D;
	LoadTime = LT;
	Cost = C;
	ID = id;
}
