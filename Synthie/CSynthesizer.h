#pragma once
#include "msxml2.h"
#include <list>
#include "CInstrument.h"
#include "CNote.h"
#include <string>
#include <vector>
#include <algorithm>

#include "CAdditiveInstrument.h"

#include "CChorusEffect.h"
#include "CFlangeEffect.h"
#include "CCompressorEffect.h"
#include "CNoiseGateEffect.h"


using namespace std;

class CSynthesizer
{
public:
    //! Constructor
    CSynthesizer();

    //! Deconstructor
    virtual ~CSynthesizer();

    void Start(void);

    bool Generate(double* frame);

    void Clear(void);

    void OpenScore(CString& filename);


    //! Get the time since we started generating audio
    double GetTime() { return m_time; }

    double GetBPM() { return m_bpm; }

    //! Number of audio channels
    int GetNumChannels() { return m_channels; }

    //! Sample rate in samples per second
    double GetSampleRate() { return m_sampleRate; }

    //! Sample period in seconds (1/samplerate)
    double GetSamplePeriod() { return m_samplePeriod; }

    //! Set the number of channels
    void SetNumChannels(int n) { m_channels = n; }

    //! Set the sample rate
    void SetSampleRate(double s) { m_sampleRate = s;  m_samplePeriod = 1.0 / s; }

    std::vector<CNote> m_notes;

private:
    std::list<CInstrument*>  m_instruments;
    int		m_channels;
    double	m_sampleRate;
    double	m_samplePeriod;
    double m_time;

    double  m_bpm;                 
    int     m_beatspermeasure;  
    double  m_secperbeat;        

    int m_currentNote;
    int m_measure;
    double m_beat; 

    void XmlLoadScore(IXMLDOMNode* xml);
    void XmlLoadInstrument(IXMLDOMNode* xml);
    void XmlLoadNote(IXMLDOMNode* xml, std::wstring& instrument);

private:

    CChorusEffect mChorusEffect;

    CFlangeEffect mFlangeEffect;

    CCompressorEffect mCompressorEffect;

    CNoiseGateEffect mNoiseGateEffect;
};

#pragma comment(lib, "msxml2.lib")