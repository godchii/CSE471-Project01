#pragma once
#include "CEffect.h"
class CFlangeEffect :
    public CEffect
{
public:
	CFlangeEffect();
	virtual ~CFlangeEffect();

	virtual void Process(double* input, double* output) override;

	virtual void Start() override;

	virtual bool Generate() override;

private:
	std::vector<double> mOutputLeft;
	std::vector<double> mOutputRight;
};

