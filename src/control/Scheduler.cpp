#include "Scheduler.h"
#include <cstdlib>

/// ////////////////////////////////// ///
///    constructors and destructor     ///
/// ////////////////////////////////// ///
Scheduler::Scheduler(Clock* clk)
	:simulationParameters(0, 0, 0, 0, 0, 0, 0, 0, 0),
	IOProcess(nullptr)
{
	this->clk = clk;
}

Scheduler::~Scheduler()
{
	for (int i = 1; i <= processors.GetLength(); i++)
	{
		delete processors.GetEntry(i);
		processors.Remove(i);
	}

	for (int i = 0; i < TRMList.getSize(); i++)
	{
		delete TRMList.peekFront();
		TRMList.dequeue();
	}
}


/// ////////////////////////////////// ///
///         Creation and setup         ///
/// ////////////////////////////////// ///
void Scheduler::CreateAllProcessors()
{
	for (int i = 0; i < simulationParameters.N_FCFS; i++)
		CreateProcessor(FCFS);

	for (int i = 0; i < simulationParameters.N_SJF; i++)
		CreateProcessor(SJF);

	for (int i = 0; i < simulationParameters.N_RR; i++)
		CreateProcessor(RR);
}

void Scheduler::CreateProcessor(ProcessorType aType)
{
	Processor* newProcessor;
	switch (aType)
	{
	case FCFS:
		newProcessor = new ProcessorFCFS(this);
		break;
	case SJF:
		newProcessor = new ProcessorSJF(this);
		break;
	case RR:
		newProcessor = new ProcessorRR(this);
		break;
	default:
		newProcessor = new ProcessorFCFS(this);
		break;
	}

	processors.Insert(processors.GetLength() + 1, newProcessor);
}

void Scheduler::CreateNewProcess(int id)
{
	// create new processor
	int N = 0;			//set NumOfIORequest with 0
	Queue<Pair<unsigned int, unsigned int>> emptyQ;			//empty Queue to initialize process with
	Process* newProcess = new Process(id, N, emptyQ);
	newProcess->SetStatus(NEW);
	// add processor to the NEW list
	NEWList.enqueue(newProcess);
}

void Scheduler::CreateNewProcess(int AT, int PID, int CT, int N,
	Queue<Pair<unsigned int, unsigned int>>& outIO)
{
	// create new processor
	Process* newProcess = new Process(PID, N, outIO);
	newProcess->SetStatus(NEW);

	TimeInfo timeInfo;
	timeInfo.AT = AT;
	timeInfo.CT = CT;
	timeInfo.RCT = CT;

	newProcess->SetTimeInfo(timeInfo);

	// add processor to the NEW list
	NEWList.enqueue(newProcess);
}

SimulationParameters Scheduler::GetSimulationParameters()
{
	return simulationParameters;
}

void Scheduler::SetSimulationParameters(SimulationParameters sP)
{
	simulationParameters = sP;
}

bool Scheduler::isDone()
{
	// this means we must change N_PROCESS when we fork .. or terminate the program in another way

	return (simulationParameters.N_PROCESS == TRMList.getSize());
}

void Scheduler::AddToSIGKILL(Pair<unsigned int, unsigned int> outP)
{
	SIGKILL.enqueue(outP);
}

/// ////////////////////////////////// ///
///           UI AID Functions         ///
/// ////////////////////////////////// ///
std::string  Scheduler::RDYListsToString()
{
	std::string str = "";
	for (int i = 1; i <= processors.GetLength(); i++)
	{
		Processor* processor = processors.GetEntry(i);
		str += "Processor " + std::to_string(i) + " ";
		str += processor->ToString();
	}
	return str;
}

std::string Scheduler::TRMListToString()
{
	std::string str = "";
	str += std::to_string(TRMList.getSize()) + " TRM: ";
	str += TRMList.ToString();
	str += "\n";
	return str;
}

std::string Scheduler::BLKListToString()
{
	std::string str = "";
	str += std::to_string(BLKList.getSize()) + " BLK: ";
	str += BLKList.ToString();
	str += "\n";
	return str;
}

std::string Scheduler::RUNListToString()
{
	std::string* RUNList = new std::string[processors.GetLength()];
	unsigned int runListSize = 0;

	for (int i = 1; i <= processors.GetLength(); i++)
	{
		Processor* processor = processors.GetEntry(i);
		if (processor->GetCurrentProcess() != nullptr)
		{
			RUNList[runListSize++] = std::to_string(processor->GetCurrentProcess()->GetID()) + "(P" + std::to_string(i) + ")";
		}
	}

	std::string str = "";

	str += std::to_string(runListSize) + " RUN: ";
	for (unsigned int i = 0; i < runListSize; i++)
	{
		str += RUNList[i];
		if (i < runListSize - 1)
		{
			str += ", ";
		}
	}

	if (runListSize == 0)
	{
		str += "Empty List";
	}

	str += "\n";
	return str;
}

std::string Scheduler::SimulationParametersToString()
{
	std::string str = "";
	str += "Simulation Parameters:\n";
	str += ".-----------------------------------------------------------------------------------------------------------.\n";
	str += "| NP\t" + std::to_string(simulationParameters.N_PROCESS);
	str += " | N_FCFS\t" + std::to_string(simulationParameters.N_FCFS);
	str += " | N_RR\t" + std::to_string(simulationParameters.N_RR);
	str += " | N_SJF\t" + std::to_string(simulationParameters.N_SJF);
	str += " | FB\t" + std::to_string(simulationParameters.FORK_PROBABILITY);
	str += " | MWT\t" + std::to_string(simulationParameters.MAX_WAITING_TIME);
	str += " | TS\t" + std::to_string(simulationParameters.RR_TIME_SLICE);
	str += " | RTF\t" + std::to_string(simulationParameters.RTF);
	str += " | STL\t" + std::to_string(simulationParameters.STL);
	str += " |\n";
	str += "'-----------------------------------------------------------------------------------------------------------'\n";
	return str;
}

/// ////////////////////////////////// ///
///     Process State Management       ///
/// ////////////////////////////////// ///
void Scheduler::ScheduleNext()
{
	while (!NEWList.isEmpty())
	{
		Process* process = NEWList.peekFront();

		TimeInfo timeInfo = process->GetTimeInfo();
		if (timeInfo.AT != clk->GetTime())
			return;

		NEWList.dequeue();

		/// TODO: implement the scheduling algorithm (Phase 2)

		// get the next processor
		Processor* processor = processors.GetEntry(nextProcessorIndex + 1);
		nextProcessorIndex = (nextProcessorIndex + 1) % processors.GetLength();

		// schedule the process
		processor->AddProcessToList(process);
	}
}

void Scheduler::ScheduleNextFCFS(Process* process)
{
}

void Scheduler::ScheduleNextSJF(Process* process)
{
}

void Scheduler::ScheduleNextRR(Process* process)
{
}

void Scheduler::TerminateProcess(Process* process)
{
	if (process->GetStatus() == TRM)
	{
		return;
	}
	process->SetStatus(TRM);
	TRMList.enqueue(process);
}

void Scheduler::BlockProcess(Process* process)
{
	if (process->GetStatus() == BLK)
	{
		return;
	}

	process->SetStatus(BLK);
	BLKList.enqueue(process);
}

/// ////////////////////////////////// ///
///        Simulation Functions        ///
/// ////////////////////////////////// ///

void Scheduler::RunProcesses()
{
	for (int i = 0; i < processors.GetLength(); i++)
	{
		Processor* processor = processors.GetEntry(i + 1);
		if (processor->GetStatus() == IDLE)
		{
			processor->ExecuteProcess(clk->GetTime());
		}

	}
}

void Scheduler::MoveToRDY(Process* process)
{
	// get the next processor
	Processor* processor = processors.GetEntry(nextProcessorIndex + 1);
	nextProcessorIndex = (nextProcessorIndex + 1) % processors.GetLength();

	// schedule the process
	processor->AddProcessToList(process);
}

void Scheduler::MoveFromRun()
{
	for (int i = 0; i < processors.GetLength(); i++)
	{
		Processor* processor = processors.GetEntry(i + 1);
		Process* CurrentProcess = processor->GetCurrentProcess();
		if (CurrentProcess == nullptr)
			continue;

		TimeInfo timeInfo = CurrentProcess->GetTimeInfo();

		if (timeInfo.RT + timeInfo.AT == clk->GetTime())
			continue;

		int probability = (rand() % 100) + 1;
		if (probability <= 15)
		{
			processor->SetStatus(IDLE);
			processor->SetCurrentProcess(nullptr);
			BlockProcess(CurrentProcess);

			TimeInfo timeInfo = CurrentProcess->GetTimeInfo();
			timeInfo.BT = clk->GetTime();
			CurrentProcess->SetTimeInfo(timeInfo);
		}
		else if (probability >= 20 && probability <= 30)
		{
			processor->SetStatus(IDLE);
			processor->SetCurrentProcess(nullptr);
			MoveToRDY(CurrentProcess);
		}
		else if (probability >= 50 && probability <= 60)
		{
			processor->SetStatus(IDLE);
			processor->SetCurrentProcess(nullptr);
			TerminateProcess(CurrentProcess);
		}
	}
}

void Scheduler::MoveFromBLK()
{
	int probability = (rand() % 100) + 1;
	if (BLKList.isEmpty())
		return;

	Process* BlockedProcess = BLKList.peekFront();

	if (BlockedProcess->GetTimeInfo().BT == clk->GetTime())
		return;

	if (probability < 10)
	{
		BLKList.dequeue();
		MoveToRDY(BlockedProcess);
	}
}

int Scheduler::SimulateKill()
{
	int RandID = rand() % 31;
	for (int i = 0; i < simulationParameters.N_FCFS; i++)
	{
		Processor* processor = processors.GetEntry(i + 1);
		ProcessorFCFS* processorFCFS = dynamic_cast<ProcessorFCFS*>(processor);
		bool found = processorFCFS->KillProcess(RandID);

		if (found)
			return RandID;
	}
	return -1;
}

/// ////////////////////////////////// ///
///        Statistics Functions        ///
/// ////////////////////////////////// ///

unsigned int Scheduler::CalculateAverageWaitTime()
{
	return 0;
}

unsigned int Scheduler::CalculateAverageTurnaroundTime()
{
	return 0;
}

unsigned int Scheduler::CalculateAverageResponseTime()
{
	return 0;
}

unsigned int* Scheduler::CalculateProcessorsUtilization()
{
	return nullptr;
}

unsigned int* Scheduler::CalculateProcessorsLoad()
{
	return nullptr;
}

unsigned int Scheduler::CalculateAverageProcessorsUtilization()
{
	return 0;
}

