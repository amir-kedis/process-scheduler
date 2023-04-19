#include "Process.h"

Process::Process(int id, unsigned int ioNum, Queue<Pair<unsigned int, unsigned int>> outIO) : 
	PID(id), IONumOfReq(ioNum), descendant(nullptr), status(NEW), IO(outIO)
{
}

int Process::GetID() const
{
	return PID;
}

Process* Process::GetDescendant() const
{
	return descendant;
}

void Process::SetDescendant(Process* child)
{
	descendant = child;
}

TimeInfo Process::GetTimeInfo() const
{
	return timeInfo;
}

void Process::SetTimeInfo(TimeInfo tI)
{
	timeInfo = tI;
}

unsigned int Process::GetIONumOfReq() const
{
	return IONumOfReq;
}

void Process::SetIONumOfReq(unsigned int ioNum)
{
	IONumOfReq = ioNum;
}

ProcessStatus Process::GetStatus() const
{
	return status;
}

void Process::SetStatus(ProcessStatus outStatus)
{
	status = outStatus;
}

Pair<unsigned int, unsigned int> Process::GetTopIOPair()
{
	if (!IO.isEmpty())
	{	
		Pair<unsigned int, unsigned int> topP = IO.peekFront();
		IO.dequeue();
		return topP;
	}
	else
	{
		Pair<unsigned int, unsigned int> emptyP(0, 0);
		return emptyP;
	}
}

bool Process::operator== (int id)
{
	return (PID == id);
}

bool Process::operator< (Process* p)
{
	return (timeInfo.RCT < p->timeInfo.RCT);
}

bool Process::NeedIO() const
{
	return false;
}

void Process::Print()
{
	std::cout << PID;
}


