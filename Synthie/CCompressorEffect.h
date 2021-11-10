#pragma once
#include "CEffect.h"
class CCompressorEffect :
    public CEffect
{
public:
	CCompressorEffect();
	virtual ~CCompressorEffect();

	virtual void Process(double* input, double* output) override;

	virtual void Start() override;

	virtual bool Generate() override;
};

