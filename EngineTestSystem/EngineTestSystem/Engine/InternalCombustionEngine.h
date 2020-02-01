#pragma once
#include "EngineInterface.h"

class InternalCombustionEngine :public EngineInterface
{
private:
	double getCoolingRate()const;
	double getHeatingRate()const;

	bool checkIsOverHeated() const;
	void updateCurrentV(clock_t );

	double currentV = 0;
	double currentA = 0;
	clock_t previousEngineTemperatureMeasurementTimeInSeconds = 0;

	struct  ICEparams {

		double I = 100;
		std::vector<double> M = { 20,75,100,105,75,0 };
		std::vector<double> V = { 0,75,150,200,250,300 };
		double Toverheat = 110;
		double Hm = 0.01;
		double Hv = 0.0001;
		double C = 0.1;

		double getLinearApproximation(const double beginX, const double beginY, const double endX, const double endY, const double _x) const;
		void readICEconfiguration(const char* configFileDir);
		ICEparams();
		~ICEparams();

		double getM(const double _v) const;
	} params;

public:
	InternalCombustionEngine(const double outsideTemperature);
	~InternalCombustionEngine();

	virtual double getEngineTemperatureAtMoment(clock_t) override;
	virtual bool isOverheated() override;
	virtual void startTheEngine()override;
	virtual void stopTheEngine()override;

	void setEngineParams(ICEparams&);
	void setEngineParams(const char*);
};
