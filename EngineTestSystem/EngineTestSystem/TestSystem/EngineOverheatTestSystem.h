#pragma once

#include "EngineTestSystemInterface.h"

class EngineOverheatTestSystem: public EngineTestSystemInterface
{
public:
	EngineOverheatTestSystem( EngineInterface& testingEngine);
	 ~EngineOverheatTestSystem() {};
	virtual std::pair<bool, clock_t> testTheEngine() override;
	virtual bool checkTestOnFreezing() override;
private:

	class Timer {
	private:
		clock_t startTime;
		clock_t currentTime;
		clock_t stopTime;
		clock_t testingDelay = 0.5;
		bool isTimerStarted = false;
	public:
		Timer();
		~Timer();
		void startTimeMeasurement();
		void stopTimeMeasurement();
		void waitForNextLaunch();
		void setTestingDelay(clock_t);

		clock_t getTimeInSecondsFromStart();
		clock_t getTimeInSecondsFromLastLaunch();
	} testTimer;
	
};
