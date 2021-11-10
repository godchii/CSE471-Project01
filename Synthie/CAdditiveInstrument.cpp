#include "pch.h"
#include "CAdditiveInstrument.h"
#include "CNote.h"
#include "Notes.h"
#include "CEnvelope.h"
#include "CADSREnvelope.h"
#include <sstream>

CAdditiveInstrument::CAdditiveInstrument()
{
	m_duration = 0.1;
}


CAdditiveInstrument::CAdditiveInstrument(double bpm)
{
	m_duration = 0.1;
	m_bpm = bpm;
}


CAdditiveInstrument::~CAdditiveInstrument()
{
}


void CAdditiveInstrument::Start()
{
	mAdditiveWave.SetSampleRate(GetSampleRate());
	mAdditiveWave.Start();
	m_time = 0;

	mEnvelope = new CADSREnvelope();

	static_cast<CADSREnvelope*>(mEnvelope)->SetAttack(.05);

	static_cast<CADSREnvelope*>(mEnvelope)->SetRelease(.05);

	mAmpFilter.SetEnvelope(mEnvelope);

	mAmpFilter.SetSource(&mAdditiveWave);

	mAmpFilter.SetSampleRate(GetSampleRate());

	mAmpFilter.SetDuration(m_duration);

	mAmpFilter.Start();
}


bool CAdditiveInstrument::Generate()
{

	mEnvelope->Generate();


	if (mAdditiveWave.GetCrossfadeFlag())
	{

		auto crossfadeEndTime = mAdditiveWave.GetCrossfadeStartTime() + m_crossfade_duration;

		//if (m_time < mAdditiveWave.GetCrossfadeStartTime())
		//{

		//	mAdditiveWave.Generate();
		//}

		//else if (m_time > mAdditiveWave.GetCrossfadeStartTime() && m_time < crossfadeEndTime)
		//{

		//	mAdditiveWave.Crossfade(m_time, m_crossfade_duration);
		//}
		if (m_time > mAdditiveWave.GetCrossfadeStartTime() && m_time < crossfadeEndTime)
		{

			mAdditiveWave.Crossfade(m_time, m_crossfade_duration);
		}

		else
		{

			mAdditiveWave.Generate();
		}
	}

	else
	{
		// generate wave by adding together several sinusoids (additive wave)
		mAdditiveWave.Generate();
	}

	// generate audio sample
	auto okay = mAmpFilter.Generate();

	// read the sample, make it the result frame
	m_frame[0] = mAmpFilter.Frame(0);
	m_frame[1] = mAmpFilter.Frame(1);

	// update the time
	m_time += GetSamplePeriod();

	// returns true until the time equals the duration
	return okay;
}


void CAdditiveInstrument::SetNote(CNote* note)
{
	// Get a list of all attribute nodes and the
	// length of that list
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	note->Node()->get_attributes(&attributes);
	long len;
	attributes->get_length(&len);

	// Loop over the list of attributes
	for (int i = 0; i < len; i++)
	{
		// Get attribute i
		CComPtr<IXMLDOMNode> attrib;
		attributes->get_item(i, &attrib);

		// Get the name of the attribute
		CComBSTR name;
		attrib->get_nodeName(&name);

		// Get the value of the attribute.  A CComVariant is a variable
		// that can have any type. It loads the attribute value as a
		// string (UNICODE), but we can then change it to an integer 
		// (VT_I4) or double (VT_R8) using the ChangeType function 
		// and then read its integer or double value from a member variable.
		CComVariant value;
		attrib->get_nodeValue(&value);

		if (name == "duration")
		{
			value.ChangeType(VT_R8);

			SetDuration(value.dblVal * (1 / (m_bpm / 60)));
		}

		else if (name == "note")
		{
			SetFrequency(NoteToFrequency(value.bstrVal));
		}

		else if (name == "harmonics")
		{
			AddHarmonics(value.bstrVal);
		}

		else if (name == "vibrato")
		{
			value.ChangeType(VT_R8);
			mAdditiveWave.SetVibratoFlag(true);
			mAdditiveWave.SetVibrato(value.dblVal);
		}

		else if (name == "vibratoRate")
		{
			value.ChangeType(VT_R8);
			mAdditiveWave.SetVibratoRate(value.dblVal);
		}

		else if (name == "crossfade")
		{
			value.ChangeType(VT_R8);

			m_crossfade_duration = value.dblVal;
			mAdditiveWave.SetCrossfadeFlag(true);
			auto start_time = m_duration - m_crossfade_duration;

			mAdditiveWave.SetCrossfadeStartTime(start_time);
		}

		else if (name == "crossfadeOverlap")
		{

			value.ChangeType(VT_R8);

			auto Overlap = (1 / (m_bpm / 60)) * value.dblVal;

			auto CrossfadeTime = mAdditiveWave.GetCrossfadeStartTime();

			auto diff = CrossfadeTime - Overlap;

			mAdditiveWave.SetCrossfadeStartTime(diff);
		}
	}
}


void CAdditiveInstrument::SetNextNote(CNote* next_note)
{

	m_next = new CAdditiveInstrument();


	m_next->SetSampleRate(GetSampleRate());

	m_next->SetNote(next_note);
	m_next->Start();

	mAdditiveWave.SetNextWave(&m_next->mAdditiveWave);
}


void CAdditiveInstrument::AddHarmonics(wstring harmonics)
{

	wstringstream sstream(harmonics);

	wstring harmonic_amp;


	while (sstream >> harmonic_amp)
	{
		mAdditiveWave.AddHarmonic(stod(harmonic_amp));
	}
}