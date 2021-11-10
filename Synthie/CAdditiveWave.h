#pragma once
#include "CSampleWave.h"

using namespace std;

class CAdditiveWave :
    public CSampleWave

{
public:
	CAdditiveWave();
	virtual ~CAdditiveWave();

	struct Vibrato
	{
		double vibrato = 0;
		double vibrato_rate = 0;
	};

	virtual void Start() override;

	virtual bool Generate() override;

	virtual void SetWavetables() override;


	void Harmonics(double* sample, double time);
	
	void DoVibrato(double* sineRads, double* vibratoRads);
	
	void Crossfade(double time, double crossfade_dur);
	
	void AddHarmonic(double harmonic) { m_harmonics.push_back(harmonic); }


	vector<double> GetHarmonics() { return m_harmonics; }
	
	bool GetVibratoFlag() { return  mVibratoFlag; }
	
	bool GetCrossfadeFlag() { return mCrossfadeFlag; }
	
	double GetCrossfadeStartTime() { return mCrossfadeInitialTime; }



	void SetVibratoFlag(bool flag) { mVibratoFlag = flag; }
	void SetVibrato(double vibrato) { mVibratoEffect.vibrato = vibrato; }
	void SetVibratoRate(double vibratoRate) { mVibratoEffect.vibrato_rate = vibratoRate; }


	void SetCrossfadeFlag(bool flag) { mCrossfadeFlag = flag; }
	void SetCrossfadeStartTime(double time) { mCrossfadeInitialTime = time; }

	void SetNextWave(CAdditiveWave* next) { mNext = next; }

private:
	vector<double> m_harmonics;

	double m_time;

	bool mVibratoFlag = false;

	bool mCrossfadeFlag = false;

	double mCrossfadeInitialTime; /// starting time of the Crossfade

	Vibrato mVibratoEffect;

	CAdditiveWave* mNext = nullptr;

};
