#include "InternalCombustionEngine.h"


InternalCombustionEngine::InternalCombustionEngine(const double outsideTemperature):EngineInterface(outsideTemperature) {};

InternalCombustionEngine::~InternalCombustionEngine() {};


InternalCombustionEngine::ICEparams::ICEparams() {};

InternalCombustionEngine::ICEparams::~ICEparams() {
	M.clear();
	V.clear();
};


void InternalCombustionEngine::ICEparams::readICEconfiguration(const char* configFileDir) {
	//TODO : Write reading config File procedure

};
		

double InternalCombustionEngine::ICEparams::getM(const double _v) const
{
	if (_v >= 0)
	{
		if (_v >= V[V.size() - 1])
			return M[M.size() - 1];
		else
			for (int i = 0; i < V.size() - 1; ++i)
				if (_v >= V[i] && _v <= V[i + 1])
					return getLinearApproximation(V[i], M[i], V[i + 1], M[i + 1], _v);
		throw  std::out_of_range("Value out of the V range.");
	}
	else
		throw std::invalid_argument("Crankshaft rotation speed cannot be negative ");
};

double InternalCombustionEngine::ICEparams::getLinearApproximation(const double beginX, const double beginY, const double endX, const double endY, const double _x) const
{
	if (beginX != endX) {
		double k = (endY - beginY) / (endX - beginX);
		double m = endY - k * endX;
		return k * _x + m;
	}
	else
		throw std::invalid_argument("Non-functional M dependency : two same V values has diffferent M values");
};



void InternalCombustionEngine::setEngineParams(ICEparams& newEnginePrams) {
	params = newEnginePrams;
}

void InternalCombustionEngine::setEngineParams(const char* pathToConfigFile) {
	params.readICEconfiguration(pathToConfigFile);
}
 bool InternalCombustionEngine::isOverheated() {
	 return isEngineOverheated;
};

 bool  InternalCombustionEngine::checkIsOverHeated() const {
	 return (engineTemperature >= params.Toverheat) ? true : false;
 }

 void InternalCombustionEngine::startTheEngine() {
	 isEngineOverheated = checkIsOverHeated();
	 isEngineWorking = true;

	 currentV = 0;
	 currentA = params.getM(currentV) / params.I;
 };
 void InternalCombustionEngine::updateCurrentV(clock_t engineWorkTimeInSeconds = 0)
 {
	 clock_t engineWorkingTime = engineWorkTimeInSeconds - previousEngineTemperatureMeasurementTimeInSeconds;
	 currentV += engineWorkingTime * currentA;
	 currentA = params.getM(currentV) / params.I;
 }
 double InternalCombustionEngine::getEngineTemperatureAtMoment(clock_t engineWorkTimeInSeconds) {
	 if (isEngineWorking) {
		 updateCurrentV(engineWorkTimeInSeconds);
		 previousEngineTemperatureMeasurementTimeInSeconds = engineWorkTimeInSeconds;
		 engineTemperature = outsideTemperature + (getHeatingRate() + getCoolingRate()) * engineWorkTimeInSeconds;
		 isEngineOverheated = checkIsOverHeated();
		 return engineTemperature;
	 }
	 else return outsideTemperature;
 };
 
 double InternalCombustionEngine::getCoolingRate()const 
 {
	 return params.C*(outsideTemperature - engineTemperature);
 };

 double InternalCombustionEngine::getHeatingRate()const
 {
	 return params.getM(currentV) * params.Hm * currentV * currentV * params.Hv;
 };

 void InternalCombustionEngine::stopTheEngine() {
	 isEngineWorking = false;
 };