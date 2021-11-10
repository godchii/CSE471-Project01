#pragma once
#include "CEnvelope.h"
class CADSREnvelope :
    public CEnvelope
{
public:
	CADSREnvelope();
	virtual ~CADSREnvelope();

	//! Start the node generation
	virtual void Start() override;
	//! Cause one sample to be generated
	virtual bool Generate() override;




	void SetAttack(double attack) { mAttack = attack; }

	void SetDecay(double decay) { mDecay = decay; }

	void SetSustain(double sustain) { mSustain = sustain; }

	void SetRelease(double release) { mRelease = release; }

private:

	double mAttack;
	double mDecay;
	double mSustain;
	double mRelease;
};

