#include "Company.h"

Company::Company()
{

}

void Company::enqueueWSC(SpecialCargo SC)
{
	WaitingSpecialCargos.Enqueue(SC);
}

void Company::enqueueWVC(VIPCargo VC)
{
	WaitingVIPCargos.enqueue(VC);
}

void Company::insertWNC(NormalCargo NC)
{
	WaitingNormalCargos.insert(NC);
}


Node<NormalCargo>* Company::RemoveWNC(int id)
{
	return WaitingNormalCargos.Delete(id);
}