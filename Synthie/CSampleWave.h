#pragma once
#include "CAudioNode.h"
#include <vector>
class CSampleWave :
    public CAudioNode
{
public:
	CSampleWave();
	virtual ~CSampleWave();

	double GetWavetableSize() { return m_wavetable.size(); }

	virtual void SetWavetables() = 0;

	void SetFrequency(double frequency) { mFrequency = frequency; }

	void SetAmp(double x) { mAmp = x; }


protected:
	std::vector<double> m_wavetable;
	double mFrequency;
	double mAmp;
	int mPhase;
};

