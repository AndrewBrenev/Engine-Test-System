#include "pch.h"
#include "Engine/InternalCombustionEngine.h"
#include "TestSystem/EngineOverheatTestSystem.h"


int main() {
	try {
		double outsideTemperature(-10);
		std::cout << "Please, enter the outside temperature : ";
		std::cin >> outsideTemperature;
		InternalCombustionEngine testingEngine(outsideTemperature);
		testingEngine.setEngineParams("./ICE.config");
		EngineOverheatTestSystem testingStand(testingEngine);
		auto overheatTestResault = testingStand.testTheEngine();

		if (overheatTestResault.first)
			std::cout << "Engine overheated after " << overheatTestResault.second << " seconds!" << std::endl;
		else
			std::cout << "Failed to wait for the engine to overheat after " << overheatTestResault.second <<
			" seconds of measurement. Test completed when duration exceeded." << std::endl;
	}
	catch (std::exception & e)
	{
		std::cout << "Failed! Found an exeption: " << e.what() << std::endl;
	}
	system("pause");
	return 0;
}