#include "pch.h"
#include "CAdditiveWave.h"
#include <cmath>

CAdditiveWave::CAdditiveWave()
{
	mPhase = 0;
	mAmp = 0.1;
	mFrequency = 440;
}


CAdditiveWave::~CAdditiveWave()
{
}


void CAdditiveWave::Start()
{
	mPhase = 0;
	m_time = 0;
	SetWavetables();
}


bool CAdditiveWave::Generate()
{
	m_frame[0] = m_wavetable[mPhase];

	m_frame[1] = m_frame[0];

	mPhase = (mPhase + 1) % m_wavetable.size();

	return true;
}

void CAdditiveWave::Harmonics(double* sample, double time)
{
	auto NyquistFrequency = GetSampleRate() / 2;

	for (auto x = 0; x < m_harmonics.size() && (mFrequency * (x + 1)) < NyquistFrequency; x++)
	{

		auto harmonic = x + 1;

		*sample += m_harmonics[x] * (mAmp / harmonic) * (sin(time * 2 * PI * harmonic * mFrequency));
	}
}

void CAdditiveWave::SetWavetables()
{
	auto tableSize = GetSampleRate();

	m_wavetable.resize(tableSize);

	double sineRads = 0;

	double vibratoRads = 0;

	for (auto i = 0; i < tableSize; i++, m_time += 1. / GetSampleRate())
	{
		auto sample = sin(sineRads) * mAmp;

		if (m_harmonics.size() > 0)
		{
			Harmonics(&sample, m_time);
		}

		if (mVibratoFlag)
		{
			DoVibrato(&sineRads, &vibratoRads);
		}

		m_wavetable[i] = sample;
	}
}



void CAdditiveWave::DoVibrato(double* sineRads, double* vibratoRads)
{
		
	double diff = sin(*vibratoRads) * mVibratoEffect.vibrato;

	double res1 = 2 * PI * (mFrequency + diff);

	double res2 = 2 * PI * mVibratoEffect.vibrato_rate;
	
	*sineRads += res1 / m_sampleRate;

	*vibratoRads += res2 / m_sampleRate;
}


void CAdditiveWave::Crossfade(double time, double crossfadeDur)
{
	
	auto elapse = time - mCrossfadeInitialTime;
	
	double nextf[2];
	
	double currentf[2];
	
	double interP;

	if (mNext != nullptr && mPhase < mNext->GetWavetableSize() && mPhase < GetWavetableSize())
	{
		
		nextf[0] = nextf[1] = mNext->m_wavetable[mPhase];
		
		currentf[0] = currentf[1] = m_wavetable[mPhase];
		
		interP = currentf[0] * ((crossfadeDur - elapse) / crossfadeDur) +
			nextf[0] * (elapse / crossfadeDur);

		
		m_frame[0] = m_frame[1] = interP;
	}

	else
	{
		m_frame[0] = m_wavetable[mPhase];
		m_frame[1] = m_frame[0];
	}
	
	mPhase = (mPhase + 1) % m_wavetable.size();
}