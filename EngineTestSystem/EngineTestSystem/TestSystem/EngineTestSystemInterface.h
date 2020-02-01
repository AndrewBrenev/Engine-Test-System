#pragma once
#include "../pch.h"
#include "../Engine/EngineInterface.h"

class EngineTestSystemInterface
{
public:
	EngineTestSystemInterface(EngineInterface& testingEngine) :testingEngine(testingEngine) {};
	virtual ~EngineTestSystemInterface() {};
	virtual std::pair<bool, clock_t> testTheEngine() = 0;

	bool isEngineTesting() {
		return isTesting;
	};
	bool isEngineTested() {
		return isTested;
	};
	void setMaxTestDuration(clock_t _newDurationInSeconds) {
		maxTestDurationInSeconds = _newDurationInSeconds;
	};
	virtual bool checkTestOnFreezing() = 0;
protected:
	bool isTesting = false;
	bool isTested = false;

	clock_t maxTestDurationInSeconds = 130;
	EngineInterface& testingEngine;
};
