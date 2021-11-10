#include "pch.h"
#include "CFlangeEffect.h"

CFlangeEffect::CFlangeEffect()
{
}


CFlangeEffect::~CFlangeEffect()
{
}

void CFlangeEffect::Process(double* input, double* output)
{
	double delayVariance = (RANGE * mDelay) * sin(2 * PI * Rate);
	double newDelay = mDelay + delayVariance;

	mWrloc = (mWrloc + 1) % 200000;
	m_left_queue[mWrloc] = input[0];

	int delayLength = int((newDelay * m_sampleRate + 0.5)) * 2;
	int rdloc = (mWrloc + 200000 - delayLength) % 200000;

	// Wet
	output[0] = input[0] / 3 + m_left_queue[rdloc] / 3 + (mOutputLeft[rdloc] * level) / 3;
	output[0] *= mWet;

	// Dry
	output[0] += input[0] * mDry;
	mOutputLeft[mWrloc] = output[0];


	mWrloc = (mWrloc + 1) % 200000;
	m_right_queue[mWrloc] = input[1];
	rdloc = (mWrloc + 200000 - delayLength) % 200000;

	// Wet
	output[1] = input[1] / 3 + m_right_queue[(rdloc + 1) % 200000] / 3 + (mOutputRight[(rdloc + 1) % 200000] * level) / 3;
	output[1] *= mWet;

	// Dry
	output[1] += input[1] * mDry;

	mOutputRight[mWrloc] = output[1];
}

void CFlangeEffect::Start()
{
	mWrloc = 0;
	mRdloc = 0;
	mOutputLeft.resize(200000);
	mOutputRight.resize(200000);
}

bool CFlangeEffect::Generate()
{
	return true;
}
