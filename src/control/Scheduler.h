#pragma once
///=///////////////////////////////////////////////////=///
/// Scheduler: Main Class and controller of the program ///
///=///////////////////////////////////////////////////=///

#include "../data.h"
#include "../ds/List.h"
#include "../ds/Queue.h"
#include "../entity/Process.h"
#include "../entity/Processor.h"
#include "../entity/ProcessorFCFS.h"
#include "../entity/ProcessorSJF.h"
#include "../entity/ProcessorRR.h"
#include <iostream>
#include <string>

class Scheduler
{

	/// ////////////////////////////////// ///
	///  Scheduler Data Members and flags  ///
	/// ////////////////////////////////// ///
private:
	SimulationParameters simulationParameters;
	int nextProcessorIndex = 0; /// TODO: remove this later

	/// ////////////////////////////////// ///
	///           Scheduler Lists          ///
	/// ////////////////////////////////// ///
private:
	List<Processor*> processors;
	Queue<Process*> NEWList;
	Queue<Process*> TRMList;
	Queue<Process*> BLKList;
	Process* IOProcess;

	/// ////////////////////////////////// ///
	///    constructors and destructor     ///
	/// ////////////////////////////////// ///
public:
	Scheduler();


	/// ////////////////////////////////// ///
	///         Creation and setup         ///
	/// ////////////////////////////////// ///
	void CreateProcessor(ProcessorType aType);
	void CreateNewProcess(int id);
	SimulationParameters GetSimulationParameters();
	void SetSimulationParameters(SimulationParameters sP);


	/// ////////////////////////////////// ///
	///           UI AID Functions         ///
	/// ////////////////////////////////// ///
	void PrintRDYLists();
	void PrintTRMList();
	void PrintBLKList();
	void PrintRUNList();

	/// ////////////////////////////////// ///
	///      Process State Management      ///
	/// ////////////////////////////////// ///
	void ScheduleNext();
	void ScheduleNextFCFS(Process* process);
	void ScheduleNextSJF(Process* process);
	void ScheduleNextRR(Process* process);
	void TerminateProcess(Process* process);
	void BlockProcess(Process* process);

	/// ////////////////////////////////// ///
	///        Statistics Functions        ///
	/// ////////////////////////////////// ///
	unsigned int CalculateAverageWaitTime();
	unsigned int CalculateAverageTurnaroundTime();
	unsigned int CalculateAverageResponseTime();
	unsigned int* CalculateProcessorsUtilization();
	unsigned int* CalculateProcessorsLoad();
	unsigned int CalculateAverageProcessorsUtilization();

};

