#pragma once
#include "CInstrument.h"
#include "CAdditiveWave.h"

#include <list>

class CAdditiveInstrument :
    public CInstrument
{
public:
	CAdditiveInstrument();

	CAdditiveInstrument(double bpm);

	virtual ~CAdditiveInstrument();


	virtual bool Generate() override;

	virtual void SetNote(CNote* note) override;

	virtual void Start() override;

	void SetNextNote(CNote* next_note);
	
	void AddHarmonics(std::wstring harmonics);


	void SetFrequency(double freq) { mAdditiveWave.SetFrequency(freq); }

	void SetAmplitude(double amp) { mAdditiveWave.SetAmp(amp); }

	void SetDuration(double duration) { m_duration = duration; }

private:
	double m_time;
	double m_duration;
	double m_crossfade_duration = 0;

	CAdditiveWave mAdditiveWave;
	CAdditiveInstrument* m_next = nullptr;
};

