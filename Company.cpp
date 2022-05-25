#include "Company.h"
#include <iomanip>

Company::Company()
{
	NumberOfAutoPromotions = 0;
}

void Company::enqueueWSC(Cargo* SC)
{
	WaitingSpecialCargos.Enqueue(SC);
}

void Company::enqueueWVC(Cargo* VC, int Priority)
{
	WaitingVIPCargos.enqueue(VC, Priority);
}

void Company::insertWNC(Cargo* NC)
{
	WaitingNormalCargos.insert(NC);
}

void Company::insertFirstWNC(Cargo* NC)
{
	WaitingNormalCargos.InsertFirst(NC);
}

Cargo* Company::RemoveWNC(int id)
{
	return WaitingNormalCargos.Delete(id);
}


void Company::AddEvent(Event* E)
{
	if (E)
		EventsList.Enqueue(E);
}

//void Company::EnqueueMSC(Cargo* SC)
//{
//	MovingSpecialCargos.enqueue(SC);
//}
//
//void Company::EnqueueMNC(Cargo* NC)
//{
//	MovingNormalCargos.enqueue(NC);
//}
//
//void Company::EnqueueMVC(Cargo* VC)
//{
//	MovingVIPCargos.enqueue(VC);
//}

void Company::EnqueueDC(Cargo* SC)
{
	DeliveredCargos.Enqueue(SC);
}

void Company::EnqueueMT(Truck* MT) //////////
{
	MovingTrucks.enqueue(MT);
}


bool Company::DequeueEvent(Event*& E)
{
	return EventsList.Dequeue(E);
}

bool Company::DequeueWVC(Cargo*& VC)
{
	return WaitingVIPCargos.Dequeue(VC);
}

bool Company::DequeueWSC(Cargo*& SC)
{
	return WaitingSpecialCargos.Dequeue(SC);
}

void Company::SetNormalLoadingTruck(Truck* Nptr)
{
	NormalLoadingTruck = Nptr;
}
void Company::SetVIPLoadingTruck(Truck* Vptr)
{
	VIPLoadingTruck = Vptr;
}
void Company::SetSpecialLoadingTruck(Truck* Sptr)
{
	SpecialLoadingTruck = Sptr;
}
Truck* Company::GetNormalLoadingTruck()
{
	return NormalLoadingTruck;
}
Truck* Company::GetVIPLoadingTruck()
{
	return VIPLoadingTruck;
}
Truck* Company::GetSpecialLoadingTruck()
{
	return SpecialLoadingTruck;
}

//bool Company::DequeueMSC(Cargo*& SC)
//{
//	return MovingSpecialCargos.Dequeue(SC);
//}
//
//bool Company::DequeueMVC(Cargo*& VC)
//{
//	return MovingVIPCargos.Dequeue(VC);
//}
//
//bool Company::DequeueMNC(Cargo*& NC)
//{
//	return MovingNormalCargos.Dequeue(NC);
//}

bool Company::RemoveFirstWNC(Cargo*& NC)
{
	return WaitingNormalCargos.RemoveFirst(NC);
}

//bool Company::AllIsDelivered()
//{
//	return (WaitingNormalCargos.IsEmpty() && WaitingSpecialCargos.IsEmpty() && WaitingVIPCargos.IsEmpty()) && (MovingNormalCargos.IsEmpty() && MovingSpecialCargos.IsEmpty() && MovingVIPCargos.IsEmpty());
//}

void Company::PrintWNC()
{
	WaitingNormalCargos.Print();
}
void Company::PrintWSC()
{
	WaitingSpecialCargos.Print();
}
void Company::PrintWVC()
{
	WaitingVIPCargos.Print();
}
//void Company::PrintMNC()
//{
//	MovingNormalCargos.Print();
//}
//void Company::PrintMSC()
//{
//	MovingSpecialCargos.Print();
//}
//void Company::PrintMVC()
//{
//	MovingVIPCargos.Print();
//}
void Company::PrintDC()
{
	DeliveredCargos.SpecialPrint();
}

int Company::WaitingNormalCount()
{
	return WaitingNormalCargos.GetCount();
}

int Company::WaitingSpecialCount()
{
	return WaitingSpecialCargos.GetCount();
}

int Company::WaitingVIPCount()
{
	return WaitingVIPCargos.GetCount();
}

//int Company::MovingCount()
//{
//	return MovingNormalCargos.GetCount() + MovingSpecialCargos.GetCount() + MovingVIPCargos.GetCount();
//}
int Company::DeliveredCount()
{
	return DeliveredCargos.GetCount() ;
}

void Company::LoadFile( string Input)
{

	//opening the input file to read from

	ifstream InputFile(Input);


	//checking whether the file is opened/found 

	if (!InputFile.is_open())
	{
		cout << "Could not open the file..." << endl;
		return;
	}

	int NumN, NumS, NumVIP;
	int NSpeed, SpSpeed, VIPSpeed;
	int NCap, SCap, VIPCap;
	int j;
	int CN, CS, CV;
	int AP,No_Events;

	InputFile >> NumN >> NumS >> NumVIP;
	InputFile >> NSpeed >> SpSpeed >> VIPSpeed;
	InputFile >> NCap >> SCap >> VIPCap;
	InputFile >> j >> CN >> CS >> CV;
	Truck::SetJ(j);
	NormalTruck::SetStaticMembers(NCap, NSpeed, CN);
	SpecialTruck::SetStaticMembers(SCap, SpSpeed, CS);
	VIPTruck::SetStaticMembers(VIPCap, VIPSpeed, CV);

	for (int i = 0; i < NumN; i++)
	{
		NormalTruck* NT = new NormalTruck;
		EmptyNormalTrucks.Enqueue(NT);
	}

	for (int i = 0; i < NumS; i++)
	{
		SpecialTruck* ST = new SpecialTruck;
		EmptySpecialTrucks.Enqueue(ST);
	}
	
	for (int i = 0; i < NumVIP; i++)
	{
		VIPTruck* NVIP = new VIPTruck;
		EmptyVIPTrucks.Enqueue(NVIP);
	}

	//reading the number of events from input file

	InputFile >> AP >> MaxW >> No_Events;

	SetAutoPromotion(AP);

	//variables for diffrent events
	char EventType, CargoType;
	Time T;
	int ID, Distance, LoadTime, Cost, ExtraCost;


	for (int i = 0; i < No_Events; i++)
	{
		InputFile >> EventType;

		//switch case to check wich EVENT will be executed

		switch (EventType)
		{
		case 'R':
		{
			//allocating a new  event

			PreparationEvent* RE = new PreparationEvent;

			//reading event variables
			InputFile >> CargoType >> T.day;
			InputFile.ignore();
			InputFile >> T.hour >> ID >> Distance >> LoadTime >> Cost;
			RE->SetParameters(CargoType, T, Distance, LoadTime, Cost, ID);
			RE->SetEventTime(T);

			//adding the event to the Event queue
			AddEvent(RE);

			break;
		}
		case 'X':
		{

			//allocating a new event
			CancelEvent* CE = new CancelEvent;


			//reading event variables
			InputFile >> T.day;
			InputFile.ignore();
			InputFile >> T.hour >> ID;
			CE->SetParameters(ID);
			CE->SetEventTime(T);

			//adding the event to the Event queue
			AddEvent(CE);
			break;
		}
		case 'P':
		{
			//allocating a new event
			PromoteEvent* PE = new PromoteEvent;

			//reading event variables
			InputFile >> T.day;
			InputFile.ignore();
			InputFile >> T.hour >> ID >> ExtraCost;
			PE->SetParameters(ID, ExtraCost);
			PE->SetEventTime(T);

			//adding the event to the Event queue
			AddEvent(PE);
		}
		}
	}
}

int Company::GetAutoPromotion()
{
	return AutoPromotion;
}

void Company::SetAutoPromotion(int AP)
{
	AutoPromotion = AP*24;   // from days to hours
}

void Company::AutoPromote(Time CurrentTime)
{
	Cargo* Temp;
	if(!NormalLoadingTruck)
	while (RemoveFirstWNC(Temp))
	{
		int PrepHours;
		int AutoP = GetAutoPromotion();
		Time PrepTime = Temp->GetPreparationTime();
		PrepHours = PrepTime.day * 24 + PrepTime.hour;
		int CurrentTimeInHrs = CurrentTime.day * 24 + CurrentTime.hour;
		if (CurrentTimeInHrs - PrepHours >= AutoP)
		{
			NumberOfAutoPromotions++;
			Temp->SetCargoType('V');
			enqueueWVC(Temp, Temp->CalcPrio());
		}
		else
		{
			insertFirstWNC(Temp);
			break;
		}
	}
}

void Company::LoadCargos(int& NLT, int& SLT, int& VLT,Time CurrentTime)
{
	if (!VIPLoadingTruck)
	{
		if (!EmptyVIPTrucks.IsEmpty() && (WaitingVIPCount() >= VIPTruck::GetTruckCapacity()))
		{
			VIPTruck* VT;
			EmptyVIPTrucks.Dequeue(VT);
			VIPLoadingTruck = VT;
			Cargo* VC;
			WaitingVIPCargos.Peek(VC);
			VLT = VC->GetLoadUnloadTime();
		}

		else if (!EmptyNormalTrucks.IsEmpty() && (WaitingVIPCount() >= NormalTruck::GetTruckCapacity()))
		{
			NormalTruck* NT;
			EmptyNormalTrucks.Dequeue(NT);
			VIPLoadingTruck = NT;
			Cargo* VC;
			WaitingVIPCargos.Peek(VC);
			VLT = VC->GetLoadUnloadTime();
		}

		else if (!EmptySpecialTrucks.IsEmpty() && (WaitingVIPCount() >= SpecialTruck::GetTruckCapacity()))
		{
			SpecialTruck* ST;
			EmptySpecialTrucks.Dequeue(ST);
			VIPLoadingTruck = ST;
			Cargo* VC;
			WaitingVIPCargos.Peek(VC);
			VLT = VC->GetLoadUnloadTime();
		}
	}

	if (VLT == 0)
	{
		Cargo* VC;
		WaitingVIPCargos.Dequeue(VC);
		VIPLoadingTruck->LoadCargo(VC);
		if (VIPLoadingTruck->IsFull())
		{
			VIPLoadingTruck->SetTDC(VIPLoadingTruck->GetCargoCount() + VIPLoadingTruck->GetTDC());
			VIPLoadingTruck->SetDeliveryInterval();
			VIPLoadingTruck->SetMovingTime(CurrentTime);
			VIPLoadingTruck->SetCWT();
			MovingTrucks.enqueue(VIPLoadingTruck, VIPLoadingTruck->CalcPrio());
			VLT = -1;
			VIPLoadingTruck = nullptr;
		}
		else if (WaitingVIPCargos.Peek(VC))
		{
			VLT = VC->GetLoadUnloadTime();
		}
	}

	// ------------------------------------------- //

	if (!SpecialLoadingTruck)
	{
		if (!EmptySpecialTrucks.IsEmpty() && (WaitingSpecialCount() >= SpecialTruck::GetTruckCapacity()))
		{
			SpecialTruck* ST;
			EmptySpecialTrucks.Dequeue(ST);
			SpecialLoadingTruck = ST;
			Cargo* SC;
			WaitingSpecialCargos.Peek(SC);
			SLT = SC->GetLoadUnloadTime();
		}
	}

	if (SLT == 0)
	{
		Cargo* SC;
		WaitingSpecialCargos.Dequeue(SC);
		SpecialLoadingTruck->LoadCargo(SC);
		if (SpecialLoadingTruck->IsFull() || SpecialLoadingTruck->GetEFlag())
		{
			SpecialLoadingTruck->SetTDC(SpecialLoadingTruck->GetCargoCount() + SpecialLoadingTruck->GetTDC());
			SpecialLoadingTruck->SetDeliveryInterval();
			SpecialLoadingTruck->SetMovingTime(CurrentTime);
			SpecialLoadingTruck->SetCWT();
			MovingTrucks.enqueue(SpecialLoadingTruck, SpecialLoadingTruck->CalcPrio());
			SLT = -1;
			SpecialLoadingTruck = nullptr;
		}
		else if (WaitingSpecialCargos.Peek(SC))    
		{
			SLT = SC->GetLoadUnloadTime();
		}
	}

	// -------------------------------------------------- //

	if (!NormalLoadingTruck)
	{
		if (!EmptyNormalTrucks.IsEmpty() && (WaitingNormalCount() >= NormalTruck::GetTruckCapacity()))
		{
			NormalTruck* NT;
			EmptyNormalTrucks.Dequeue(NT);
			NormalLoadingTruck = NT;
			Cargo* NC;
			WaitingNormalCargos.RemoveFirst(NC);
			NLT = NC->GetLoadUnloadTime();
			WaitingNormalCargos.InsertFirst(NC);
		}
		else if(!EmptyVIPTrucks.IsEmpty() && (WaitingNormalCount() >= VIPTruck::GetTruckCapacity()))
		{
			VIPTruck* VT;
			EmptyVIPTrucks.Dequeue(VT);
			NormalLoadingTruck = VT;
			Cargo* NC;
			WaitingNormalCargos.RemoveFirst(NC);
			NLT = NC->GetLoadUnloadTime();
			WaitingNormalCargos.InsertFirst(NC);
		}
	}
	if (NLT == 0)
	{
		Cargo* NC;
		WaitingNormalCargos.RemoveFirst(NC);
		NormalLoadingTruck->LoadCargo(NC);
		if (NormalLoadingTruck->IsFull() || NormalLoadingTruck->GetEFlag())
		{
			NormalLoadingTruck->SetTDC(NormalLoadingTruck->GetCargoCount() + NormalLoadingTruck->GetTDC());
			NormalLoadingTruck->SetDeliveryInterval();
			NormalLoadingTruck->SetMovingTime(CurrentTime);
			NormalLoadingTruck->SetCWT();
			MovingTrucks.enqueue(NormalLoadingTruck, NormalLoadingTruck->CalcPrio());
			NLT = -1;
			NormalLoadingTruck = nullptr;
		}
		else if (WaitingNormalCargos.RemoveFirst(NC))    
		{
			NLT = NC->GetLoadUnloadTime();
			WaitingNormalCargos.InsertFirst(NC);
		}
	}
}

void Company::DeliverCargos(Time Current) //Needs Fixing
{
	int count = MovingTrucks.GetCount();
	Queue<Truck*> TempQueue;
	Truck* TempTruck;
	for (int i = 0; i < count; i++)
	{
		MovingTrucks.Dequeue(TempTruck);
		TempQueue.Enqueue(TempTruck);
		if (!TempTruck->IsEmpty())
		{
			Cargo* TempCargo;
			TempTruck->PeekCargosQueue(TempCargo);
			Time MT = TempTruck->GetMovingTime();
			int MTHours = MT.hour + MT.day * 24;
			int CurrentHours = Current.hour + Current.day * 24;
			int CDT = MTHours + TempCargo->GetDeliveryDistance() / TempTruck->GetSpeed() + TempCargo->GetLoadUnloadTime();
			if (CurrentHours == CDT)
			{
				Cargo* TempCargo2;
				TempTruck->DequeueCargo(TempCargo2);
				TempCargo2->SetCDT(Time(CDT % 24, CDT / 24));
				TempCargo2->SetTID(TempTruck->GetTID());
				DeliveredCargos.Enqueue(TempCargo2);
				Time NewMT;
				NewMT.day = (MTHours + TempCargo->GetLoadUnloadTime()) / 24;
				NewMT.hour = (MTHours + TempCargo->GetLoadUnloadTime()) % 24;
				TempTruck->SetMovingTime(NewMT);
				if (TempTruck->IsEmpty())
				{
					TempTruck->SetTotalJourneys(TempTruck->GetTotalJourneys() + 1);
				}
			}
		}
	}

	for (int i = 0; i < count; i++)
	{
		TempQueue.Dequeue(TempTruck);
		MovingTrucks.enqueue(TempTruck, TempTruck->CalcPrio());
	}
}

void Company::MoveToAvail()
{
	Truck* TempTruck;
	MovingTrucks.Peek(TempTruck);
	while (TempTruck && TempTruck->IsEmpty())
	{
		if (TempTruck->GetReturnH() == 0)
		{
			MovingTrucks.Dequeue(TempTruck);
			if (dynamic_cast<NormalTruck*>(TempTruck))
				EmptyNormalTrucks.Enqueue((NormalTruck*)TempTruck);
			if (dynamic_cast<SpecialTruck*>(TempTruck))
				EmptySpecialTrucks.Enqueue((SpecialTruck*)TempTruck);
			if (dynamic_cast<VIPTruck*>(TempTruck))
				EmptyVIPTrucks.Enqueue((VIPTruck*)TempTruck);
			MovingTrucks.Peek(TempTruck);
		}
		else
			break;
	}
}

void Company::MoveToCheckUp(Time Current) // checkup el awl fel sim
{
	Truck* TempTruck;
	MovingTrucks.Peek(TempTruck);
	while (TempTruck && TempTruck->IsEmpty())
	{ 
		if (TempTruck->GetTotalJourneys() % TempTruck->GetJ() == 0 && (TempTruck->GetReturnH() == 0))  ///////// tot in load
		{
			MovingTrucks.Dequeue(TempTruck);
			TempTruck->SetEndOfCheckUp(Current);
			if (dynamic_cast<NormalTruck*>(TempTruck))
				NormalCheckUpTrucks.Enqueue((NormalTruck*)TempTruck);
			if (dynamic_cast<SpecialTruck*>(TempTruck))
				SpecialCheckUpTrucks.Enqueue((SpecialTruck*)TempTruck);
			if (dynamic_cast<VIPTruck*>(TempTruck))
				VIPCheckUpTrucks.Enqueue((VIPTruck*)TempTruck);
		}
		else
			break;
		MovingTrucks.Peek(TempTruck);
	}
}

void Company::MoveCheckUpToAvail(Time Current)
{
	NormalTruck* TempTruck1;
	int CurrentHours = Current.hour + Current.day * 24;
	NormalCheckUpTrucks.Peek(TempTruck1);
	while (TempTruck1 && (CurrentHours == TempTruck1->GetEndOfCheckUp()))
	{
		NormalCheckUpTrucks.Dequeue(TempTruck1);
		EmptyNormalTrucks.Enqueue(TempTruck1);
		NormalCheckUpTrucks.Peek(TempTruck1);
	}

	SpecialTruck* TempTruck2;
	SpecialCheckUpTrucks.Peek(TempTruck2);
	while (TempTruck2 && (CurrentHours == TempTruck2->GetEndOfCheckUp()))
	{
		SpecialCheckUpTrucks.Dequeue(TempTruck2);
		EmptySpecialTrucks.Enqueue(TempTruck2);
		SpecialCheckUpTrucks.Peek(TempTruck2);
	}

	VIPTruck* TempTruck3;
	VIPCheckUpTrucks.Peek(TempTruck3);
	while (TempTruck3 && (CurrentHours == TempTruck3->GetEndOfCheckUp()))
	{
		VIPCheckUpTrucks.Dequeue(TempTruck3);
		EmptyVIPTrucks.Enqueue(TempTruck3);
		VIPCheckUpTrucks.Peek(TempTruck3);
	}
}

void Company::ExecuteEvents(Event*& CurrentEvent,Time CurrentTime)
{
	while (CurrentEvent && CurrentEvent->GetEventTime().day == CurrentTime.day && CurrentEvent->GetEventTime().hour == CurrentTime.hour)
	{
		CurrentEvent->Execute(*this);
		if (!EventsList.Dequeue(CurrentEvent))
			CurrentEvent = nullptr;
	}
}

void Company::HandleMaxW(int &NLT,int& SLT ,Time CurrentTime)
{
	int CurrentHours = CurrentTime.day * 24 + CurrentTime.hour;
	Cargo* NormCargo, *SpecialCargo;
	NormalTruck* NT;
	SpecialTruck* ST;
	VIPTruck* VT;
	Time PrepTime;
	int PrepHours;
	if (WaitingNormalCargos.RemoveFirst(NormCargo))
	{
		PrepTime = NormCargo->GetPreparationTime();
		WaitingNormalCargos.InsertFirst(NormCargo);
		 PrepHours = PrepTime.day * 24 + PrepTime.hour;
		if (CurrentHours - PrepHours >= MaxW)
		{
			if (!NormalLoadingTruck)
				if (!EmptyNormalTrucks.IsEmpty())
				{
					EmptyNormalTrucks.Dequeue(NT);
					NormalLoadingTruck = NT;
					NormalLoadingTruck->SetEFlag(true);
					NLT = NormCargo->GetLoadUnloadTime();
				}
				else if (!EmptyVIPTrucks.IsEmpty())
				{
					EmptyVIPTrucks.Dequeue(VT);
					NormalLoadingTruck = VT;
					NormalLoadingTruck->SetEFlag(true);
					NLT = NormCargo->GetLoadUnloadTime();
				}

		}
	}
	if (WaitingSpecialCargos.Peek(SpecialCargo))
	{
		PrepTime = SpecialCargo->GetPreparationTime();
		PrepHours = PrepTime.day * 24 + PrepTime.hour;
		if (CurrentHours - PrepHours >= MaxW)
		{
			if (!SpecialLoadingTruck)
				if (!EmptySpecialTrucks.IsEmpty())
				{
					EmptySpecialTrucks.Dequeue(ST);
					SpecialLoadingTruck = ST;
					SpecialLoadingTruck->SetEFlag(true);
					SLT = SpecialCargo->GetLoadUnloadTime();
				}
		}
	}
			
}

int Company::GetLoadingTruckCount()
{
	int count = 0;
	if (NormalLoadingTruck)
		count++;
	if (SpecialLoadingTruck)
		count++;
	if (VIPLoadingTruck)
		count++;
	return count;

}
void Company::PrintENT()
{
	EmptyNormalTrucks.Print();
}
void Company::PrintEST()
{
	EmptySpecialTrucks.Print();
}
void Company::PrintEVT() 
{
	EmptyVIPTrucks.Print();
}
int Company::GetEmptyTruckCount()
{
	return EmptyNormalTrucks.GetCount() + EmptySpecialTrucks.GetCount() + EmptyVIPTrucks.GetCount();
}
void Company::PrintMovingTrucks()
{
	Queue<Truck*> Temp;
	Truck* TruckToBePrinted;
	int Prio;
	while (MovingTrucks.Dequeue(TruckToBePrinted))
	{
		TruckToBePrinted->PrintID();
		TruckToBePrinted->PrintTruckCargos();
		Temp.Enqueue(TruckToBePrinted);
	}
	while (Temp.Dequeue(TruckToBePrinted))
	{
		MovingTrucks.enqueue(TruckToBePrinted, TruckToBePrinted->CalcPrio());
	}
}
int Company::GetMovingCargoCount()
{
	Queue<Truck*> Temp;
	Truck* TruckTemp;
	int SUM=0;
	while (MovingTrucks.Dequeue(TruckTemp))
	{
		SUM += TruckTemp->GetCargoCount();
		Temp.Enqueue(TruckTemp);
	}
	while (Temp.Dequeue(TruckTemp))
	{
		MovingTrucks.enqueue(TruckTemp, TruckTemp->CalcPrio());
	}
	return SUM;
}
int Company::GetCheckupCount()
{
	return NormalCheckUpTrucks.GetCount() + SpecialCheckUpTrucks.GetCount() + VIPCheckUpTrucks.GetCount();
}

void Company::PrintNCT()
{
	NormalCheckUpTrucks.Print();
}
void Company::PrintSCT()
{
	SpecialCheckUpTrucks.Print();
}
void Company::PrintVCT()
{
	VIPCheckUpTrucks.Print();
}

void Company::Simulate(int Type, string InputFile)
{
	int hour = 0;
	int day = 1;

	UI Interface;
	SetNormalLoadingTruck(nullptr);
	SetSpecialLoadingTruck(nullptr);
	SetVIPLoadingTruck(nullptr);

	int NLT = -1, SLT = -1, VLT = -1;

	int NAP = 0;

	LoadFile(InputFile);
	Event* CurrentEvent = nullptr;
	DequeueEvent(CurrentEvent);
	while (!AllIsDelivered()||CurrentEvent)
	{

		ExecuteEvents(CurrentEvent, Time(hour, day));

		if (hour >= 5 && hour <= 23)
		{

			HandleMaxW(NLT, SLT, Time(hour, day));

			LoadCargos(NLT, SLT, VLT, Time(hour, day));

			AutoPromote(Time(hour, day));

		}
		DeliverCargos(Time(hour, day));
		MoveToCheckUp(Time(hour, day));

		MoveToAvail();
		DecrementReturningHours();

		MoveCheckUpToAvail(Time(hour, day));

		Interface.Display(*this, Type, Time(hour, day));

		AdvanceSimTime(hour,day, NLT, SLT, VLT);


	} 
	Interface.DisplayT3(*this, Type, Time(hour,day));
}

void Company::AdvanceSimTime(int& hour, int& day, int& NLT, int& SLT, int& VLT)
{

	hour++;
	if (hour == 24)
	{
		hour = 0;
		day++;
	}
	NLT--;
	SLT--;
	VLT--;

}

void Company::GenerateOutputFile(Time EndSimTime)
{


	ofstream OutputFile("Output.txt");

	//checking whether the file is opened/found 
	if (!OutputFile.is_open())
	{
		cout << "Could not open the file..." << endl;
		return;
	}

	OutputFile << "CDT    ID   PT     WT    TID" << endl;

	int NumNC = 0, NumSC = 0, NumVC = 0;
	int TotalWaitHours = 0;
	int TotalActiveHours = 0;
	int NumOfDeliveredCargos = DeliveredCargos.GetCount();
	Cargo* DeliveredCargo;
	
	for (int i = 0; i < NumOfDeliveredCargos; i++)
	{
		DeliveredCargos.Dequeue(DeliveredCargo);

		OutputFile << DeliveredCargo->GetCDT().day << ":" <<setw(2)<<setfill('0')<< DeliveredCargo->GetCDT().hour << "   " << DeliveredCargo->GetID() << "   ";
		OutputFile << DeliveredCargo->GetPreparationTime().day << ":" <<setw(2) << setfill('0')<< DeliveredCargo->GetPreparationTime().hour << "   ";
		OutputFile << DeliveredCargo->GetWT().day << ":" << setw(2) << setfill('0') << DeliveredCargo->GetWT().hour << "   ";
		OutputFile << DeliveredCargo->GetTID() << endl;

		TotalWaitHours += DeliveredCargo->GetWT().day * 24 + DeliveredCargo->GetWT().hour;

		if (DeliveredCargo->GetCT() == 'N')
			NumNC++;
		else if (DeliveredCargo->GetCT() == 'S')
			NumSC++;
		else
			NumVC++;
	}
	OutputFile << "����������������������������" << endl;

	OutputFile << "Cargos: " << NumOfDeliveredCargos << " [N: " << NumNC << ", S: " << NumSC << ", V: " << NumVC << "]" << endl;
	OutputFile << "Cargo Avg Wait = " << (TotalWaitHours / NumOfDeliveredCargos) / 24 << ":" << (TotalWaitHours / NumOfDeliveredCargos) % 24 << endl;
	OutputFile << "Auto-promoted Cargos: " << 100 * NumberOfAutoPromotions / (NumberOfAutoPromotions + NumNC) << "%" << endl;

	OutputFile << "Trucks: " << EmptyNormalTrucks.GetCount() + EmptySpecialTrucks.GetCount() + EmptyVIPTrucks.GetCount() << " [N: " << EmptyNormalTrucks.GetCount();
	OutputFile << ",S: " << EmptySpecialTrucks.GetCount() << ", V: " << EmptyVIPTrucks.GetCount() << "]" << endl;

	NormalTruck* TempNTruck;
	SpecialTruck* TempSTruck;
	VIPTruck* TempVTruck;
	int NumNT = EmptyNormalTrucks.GetCount();
	int NumST = EmptySpecialTrucks.GetCount();
	int NumVT = EmptyVIPTrucks.GetCount();

	int TDC;
	int TotalJourneys;
	int TruckCap=NormalTruck::GetTruckCapacity();

	float TruckUtilization = 0;
	for (int i = 0; i < NumNT; i++)
	{
		EmptyNormalTrucks.Dequeue(TempNTruck);
		TotalActiveHours += TempNTruck->GetActiveTime();
		TDC = TempNTruck->GetTDC();
		TotalJourneys = TempNTruck->GetTotalJourneys();
		if(!(TDC==0|| TotalJourneys==0))
			TruckUtilization += TDC / float(TruckCap * TotalJourneys) * (TotalActiveHours / float(EndSimTime.day * 24 - 24 + EndSimTime.hour));
	}

	TruckCap = SpecialTruck::GetTruckCapacity();
	for (int i = 0; i < NumST; i++)
	{
		EmptySpecialTrucks.Dequeue(TempSTruck);
		TotalActiveHours += TempSTruck->GetActiveTime();
		TDC = TempSTruck->GetTDC();
		TotalJourneys = TempSTruck->GetTotalJourneys();
		if (!(TDC == 0 || TotalJourneys == 0))
			TruckUtilization += TDC / float(TruckCap * TotalJourneys) * (TotalActiveHours / float(EndSimTime.day * 24 - 24 + EndSimTime.hour));
	}

	TruckCap = VIPTruck::GetTruckCapacity();
	for (int i = 0; i < NumVT; i++)
	{
		EmptyVIPTrucks.Dequeue(TempVTruck);
		TotalActiveHours += TempVTruck->GetActiveTime();
		TDC = TempVTruck->GetTDC();
		TotalJourneys = TempVTruck->GetTotalJourneys();
		if (!(TDC == 0 || TotalJourneys == 0))
			TruckUtilization += TDC / float(TruckCap * TotalJourneys) * (TotalActiveHours / float(EndSimTime.day * 24 - 24 + EndSimTime.hour));
	}

	OutputFile << "Avg Active time = " << (100*TotalActiveHours / (EndSimTime.day * 24 -24 + EndSimTime.hour)) << "%" << endl;

	if ((NumNT + NumST + NumVT) == 0)
		OutputFile << "Avg utilization = 0%" << endl;
	else
		OutputFile << "Avg utilization = "<< int(100* TruckUtilization /(NumNT + NumST + NumVT)) <<"%" << endl;
}

bool Company::AllIsDelivered()
{
	return (WaitingNormalCargos.IsEmpty() && WaitingSpecialCargos.IsEmpty() && MovingTrucks.IsEmpty() && NormalCheckUpTrucks.IsEmpty() && SpecialCheckUpTrucks.IsEmpty() && VIPCheckUpTrucks.IsEmpty());
}


void Company::DecrementReturningHours()
{
	int count = MovingTrucks.GetCount();
	Queue<Truck*> TempQueue;
	Truck* TempTruck;
	for (int i = 0; i < count; i++)
	{
		MovingTrucks.Dequeue(TempTruck);
		TempQueue.Enqueue(TempTruck);
		if (TempTruck->IsEmpty())
		{
			TempTruck->SetReturnH(TempTruck->GetReturnH() - 1);
		}
	}

	for (int i = 0; i < count; i++)
	{
		TempQueue.Dequeue(TempTruck);
		MovingTrucks.enqueue(TempTruck, TempTruck->CalcPrio());
	}
}
