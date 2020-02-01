#include "EngineOverheatTestSystem.h"
#include <Windows.h>

EngineOverheatTestSystem::EngineOverheatTestSystem( EngineInterface& testingEngine) :EngineTestSystemInterface(testingEngine) 
{};

bool EngineOverheatTestSystem::checkTestOnFreezing() {
	return (testTimer.getTimeInSecondsFromStart() >= maxTestDurationInSeconds) ? true : false;
}

std::pair<bool, clock_t> EngineOverheatTestSystem::testTheEngine() {
	
	testTimer.startTimeMeasurement();
	isTesting = true;

	testingEngine.startTheEngine();
	while (!testingEngine.isOverheated() && !checkTestOnFreezing()) {
		testingEngine.getEngineTemperatureAtMoment(testTimer.getTimeInSecondsFromStart());
		testTimer.waitForNextLaunch();
	}
	auto testingTime = testTimer.getTimeInSecondsFromStart();
	testingEngine.stopTheEngine();
	testTimer.stopTimeMeasurement();

	isTesting = false;
	isTested = true;

	return (!checkTestOnFreezing())? std::pair<bool, clock_t>(true, testingTime) : std::pair<bool, clock_t>(false, testingTime);
};

void EngineOverheatTestSystem::Timer::startTimeMeasurement() {
	startTime = 0;
	currentTime = 0;
	isTimerStarted = true;
}
void EngineOverheatTestSystem::Timer::stopTimeMeasurement() {
	isTimerStarted = false;
	stopTime = currentTime;
};
void EngineOverheatTestSystem::Timer::waitForNextLaunch() {
	currentTime += testingDelay;
};
clock_t EngineOverheatTestSystem::Timer::getTimeInSecondsFromStart() {
	return  currentTime;
};

void EngineOverheatTestSystem::Timer::setTestingDelay(clock_t _newDelay) {
	testingDelay = _newDelay;
};
clock_t EngineOverheatTestSystem::Timer::getTimeInSecondsFromLastLaunch() {
	return testingDelay;
};
EngineOverheatTestSystem::Timer::Timer() {};
EngineOverheatTestSystem::Timer::~Timer() {};