#pragma once
#include "CEffect.h"
class CChorusEffect :
    public CEffect
{
public:
	CChorusEffect();
	virtual ~CChorusEffect();

	virtual void Process(double* input, double* output) override;

	virtual void Start() override;

	virtual bool Generate() override;
};

