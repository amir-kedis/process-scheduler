#include "Simulator.h"

void Simulator::ShowMenu()
{

}

bool Simulator::LoadInpuitFile()
{
	ifstream InFile;
	InFile.open("test.txt");
	if (!InFile.is_open())
	{
		return false;	//maybe you would need to perform other actions when the file couldn't be opened
	}

	unsigned int maxWaitingTime, RRTimeSlice, nFCFS, nSJF,
		nRR, forkProbability, stl, rtf, nProcess;

	InFile >> nFCFS >> nSJF >> nRR;
	InFile >> RRTimeSlice;
	InFile >> rtf >> maxWaitingTime >> stl >> forkProbability;
	InFile >> nProcess;

	SimulationParameters sP = scheduler.GetSimulationParameters();

	sP.MAX_WAITING_TIME = maxWaitingTime;
	sP.RR_TIME_SLICE = RRTimeSlice;
	sP.N_FCFS = nFCFS;
	sP.N_SJF = nSJF;
	sP.N_RR = nRR;
	sP.FORK_PROBABILITY = forkProbability;
	sP.STL = stl;
	sP.RTF = rtf;
	sP.N_PROCESS = nProcess;

	scheduler.SetSimulationParameters(sP);

	for (int i = 0; i < nProcess; i++)
	{
		int AT, PID, CT, N;
		InFile >> AT >> PID >> CT >> N;

		scheduler.CreateNewProcess(PID);
		// TODO: set the AT, CT and N for each process

		for (int i = 0; i < N; i++)
		{
			
			char lParenthesis, comma, rParenthesis;
			int IO_R, IO_D;
			InFile >> lParenthesis >> IO_R >> comma >> IO_D >> rParenthesis;

			// TODO: add the IO_R and IO_D values to the process
			
			if (i < N - 1)
			{
				InFile >> comma;
			}
		}
	}
	string uslessLine;
	getline(InFile, uslessLine);
	getline(InFile, uslessLine);
	int PID, killTime;
	while (InFile >> killTime >> PID)
	{
		// TODO: add the killTime and PID to SIGKILL List 
	}
	InFile.close();
	return true;
}

bool Simulator::CreateOutputFile()
{
	return true;
}

void Simulator::Run()
{
	/// TODO: This is just a test code. It will be removed later.
	ui.PrintHeadline();
	ui.PrintUIModeMenu();
	ui.PrintTimeStamp();

	scheduler.CreateProcessor(FCFS);
	scheduler.CreateProcessor(SJF);
	scheduler.CreateProcessor(RR);
	scheduler.CreateProcessor(FCFS);
	scheduler.CreateProcessor(SJF);

	scheduler.CreateNewProcess(0);
	scheduler.CreateNewProcess(2);
	scheduler.CreateNewProcess(3);
	scheduler.CreateNewProcess(4);
	scheduler.CreateNewProcess(5);
	scheduler.CreateNewProcess(6);
	scheduler.CreateNewProcess(7);
	scheduler.CreateNewProcess(8);
	scheduler.CreateNewProcess(9);
	scheduler.CreateNewProcess(10);
	scheduler.CreateNewProcess(11);

	scheduler.ScheduleNext();
	scheduler.ScheduleNext();
	scheduler.ScheduleNext();
	scheduler.ScheduleNext();
	scheduler.ScheduleNext();
	scheduler.ScheduleNext();
	scheduler.ScheduleNext();
	scheduler.ScheduleNext();
	scheduler.ScheduleNext();
	scheduler.ScheduleNext();
	scheduler.ScheduleNext();


	scheduler.CreateNewProcess(20);
	scheduler.CreateNewProcess(21);
	scheduler.CreateNewProcess(22);
	scheduler.CreateNewProcess(23);

	scheduler.TerminateProcess(nullptr);
	scheduler.TerminateProcess(nullptr);
	scheduler.TerminateProcess(nullptr);
	scheduler.TerminateProcess(nullptr);

	scheduler.CreateNewProcess(24);
	scheduler.CreateNewProcess(25);
	scheduler.CreateNewProcess(26);
	scheduler.CreateNewProcess(27);

	scheduler.BlockProcess(nullptr);
	scheduler.BlockProcess(nullptr);
	scheduler.BlockProcess(nullptr);
	scheduler.BlockProcess(nullptr);

	scheduler.RunProcesses();

	clk.Step();

	ui.PrintTimeStamp();
	Simulation();
}

void Simulator::Simulation()
{
	LoadInpuitFile();
}