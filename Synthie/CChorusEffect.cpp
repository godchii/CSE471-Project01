#include "pch.h"
#include "CChorusEffect.h"

CChorusEffect::CChorusEffect()
{
}


CChorusEffect::~CChorusEffect()
{
}

void CChorusEffect::Start()
{
	mWrloc = 0;
	mRdloc = 0;
	m_left_queue.resize(200000);
	m_right_queue.resize(200000);
}

bool CChorusEffect::Generate()
{
	return true;
}

void CChorusEffect::Process(double* input, double* output)
{

	double delayVariance = (RANGE * mDelay) * sin(2 * PI * Rate);
	double newDelay = mDelay + delayVariance;

	mWrloc = (mWrloc + 1) % 200000;
	m_left_queue[mWrloc] = input[0];
	mWrloc = (mWrloc + 1) % 200000;
	m_right_queue[mWrloc] = input[1];

	int delayLength = int((newDelay * GetSampleRate() + 0.5)) * 2;
	int rdloc = (mWrloc + 200000 - delayLength) % 200000;

	output[0] = input[0] / 2 + m_left_queue[rdloc] / 2;
	output[0] *= mWet;
	output[0] += input[0] * mDry;

	mWrloc = (mWrloc + 1) % 200000;
	m_right_queue[mWrloc] = input[1];
	rdloc = (mWrloc + 200000 - delayLength) % 200000;
	output[1] = input[1] / 2 + m_right_queue[rdloc] / 2;
	output[1] *= mWet;


	output[1] += input[1] * mDry;

}
