#pragma once
#include "CInstrument.h"

#include <vector>
class CEffect : public CInstrument
{
public:
	virtual ~CEffect();

	virtual void Process(double* frameIn, double* frameOut) = 0;

	void SetDelay(double delay) { mDelay = delay; }

	void SetWet(double wet) { mWet = wet; }

	void SetDry(double dry) { mDry = dry; }

	void SetThreshold(double threshold) { mThreshold = threshold; }

	virtual void SetNote(CNote* note) override;

protected:
	CEffect();

	double mTime = 5.0;
	double	mDelay;
	double	mWet;
	double	mDry;
	double  mThreshold;

	int mWrloc;
	int mRdloc;

	int Rate = 2;
	int level = 2;
	std::vector<double> m_left_queue;
	std::vector<double> m_right_queue;
	const double M_PI = 3.14159265359;
	const double RANGE = .5;
};
