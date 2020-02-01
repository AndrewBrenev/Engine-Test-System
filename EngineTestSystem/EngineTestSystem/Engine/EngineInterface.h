#pragma once
#include "../pch.h"

class EngineInterface
{
public:
	EngineInterface(double outsideTemperature) :engineTemperature(outsideTemperature), outsideTemperature(outsideTemperature){};
	virtual ~EngineInterface() {};

	virtual double getEngineTemperatureAtMoment(clock_t) = 0;
	virtual bool isOverheated() = 0;
	virtual void startTheEngine() = 0;
	virtual void stopTheEngine() = 0;
protected:
	bool isEngineWorking = false;
	bool isEngineOverheated = false;
	double engineTemperature;
	double outsideTemperature;
};
