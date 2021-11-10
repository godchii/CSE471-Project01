#include "pch.h"
#include "CADSREnvelope.h"


CADSREnvelope::CADSREnvelope()
{

	mAttack = 0.05;
	mDecay = 0.;
	mSustain = 1.;
	mRelease = 0.05;
}


CADSREnvelope::~CADSREnvelope()
{
}


void CADSREnvelope::Start()
{
	m_level = 1.;
	m_time = 0.;
}


bool CADSREnvelope::Generate()
{

	if (m_time <= mAttack)
	{
		m_level = m_time / mAttack * mSustain;
	}


	else if ((m_duration - mRelease) < m_time)
	{
		m_level = (1 - (m_time - (m_duration - mRelease)) / mRelease) * mSustain;
	}


	else if (m_time > mAttack && m_time <= mAttack + mDecay)
	{
		m_level = (m_level - 1) * ((m_time - (m_duration - mDecay)) / mDecay) + 1;
	}

	else
	{
		m_level = mSustain;
	}

	m_time += GetSamplePeriod();

	return m_duration > m_time;
}
