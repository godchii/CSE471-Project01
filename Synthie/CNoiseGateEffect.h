#pragma once
#include "CEffect.h"
class CNoiseGateEffect :
    public CEffect
{
public:
	CNoiseGateEffect();
	virtual ~CNoiseGateEffect();

	virtual void Process(double* input, double* output) override;

	virtual void Start() override;

	virtual bool Generate() override;

private:
	double mGateL;
	double mGateR;
};

