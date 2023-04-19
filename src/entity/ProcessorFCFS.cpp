#include "ProcessorFCFS.h"
#include "../control/Scheduler.h"

void ProcessorFCFS::IOHandler()
{
}

void ProcessorFCFS::WorkStealingHandler()
{
}

void ProcessorFCFS::MigratonHandler()
{
}

bool ProcessorFCFS::KillProcessHandler(int PID)
{
	Process* killedProcess = readyList.RemoveById(PID);
	if (killedProcess == nullptr)
		return false;
	if (killedProcess == GetCurrentProcess())
	{
		SetCurrentProcess(nullptr);
		SetStatus(IDLE);
	}
	scheduler->TerminateProcess(killedProcess);
	return true;
}

void ProcessorFCFS::ForkHandler()
{
}

ProcessorFCFS::ProcessorFCFS(Scheduler* outScheduler)
	:Processor(outScheduler, FCFS)
{
}

 ProcessorFCFS::ExecuteProcess(int CurrentTime, int ID)
{
	//TODO: remove this later

	if (ID != -1)
		return KillProcessHandler(int PID);

	if (readyList.IsEmpty())
	{
		return nullptr;
	}
	Process* process = readyList.GetEntry(1);
	if (process->GetTimeInfo().AT == CurrentTime)
		return nullptr;

	readyList.Remove(1);
	currentProcess = process;
	process->SetStatus(RUN);
	SetStatus(BUSY);

	TimeInfo timeInfo = process->GetTimeInfo();
	timeInfo.RT = CurrentTime - timeInfo.AT;

	process->SetTimeInfo(timeInfo);

	return nullptr;
}

void ProcessorFCFS::AddProcessToList(Process* process)
{
	process->SetStatus(RDY);
	readyList.Insert(readyList.GetLength() + 1, process);
}

std::string ProcessorFCFS::ToString()
{
	std::string str = "[FCFS]: " + std::to_string(readyList.GetLength()) + " RDY: ";
	str += readyList.ToString();
	str += "\n";
	return str;
}
