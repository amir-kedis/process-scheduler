#pragma once
///=//////////////////////////////////////////////////////=///
/// UI Class: reads and writes data to the standard output ///
///=//////////////////////////////////////////////////////=///

#include <iostream>
#include <windows.h>
#include "../data.h"

class UI
{
	/// Data Members
	UIMode mode;

public:
	/// Output functions
	void WriteWarning(std::string msg);
	void WriteError(std::string msg);

	/// Color Control functions
	void ResetColor();
	void SetColor(Color color);

	/// Mode Management functions
	void SetMode(UIMode aMode);
};

