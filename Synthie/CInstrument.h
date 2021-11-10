#pragma once
#include "CAudioNode.h"
#include "CNote.h"
#include "CAmpFilter.h"

class CInstrument :
    public CAudioNode
{
public:
    CInstrument();

    virtual ~CInstrument();

    CInstrument(double);

    virtual void SetNote(CNote* note) = 0;

    double Send(int i) { return mSends[i]; }

    void SetSend(int i, double value) { mSends[i] = value; }

protected:
 
    CAmpFilter mAmpFilter;
 
    CEnvelope* mEnvelope;

    double mSends[5];
};

