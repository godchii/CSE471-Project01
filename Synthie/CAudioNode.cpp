#include "pch.h"
#include "CAudioNode.h"

CAudioNode::CAudioNode()
{
	m_frame[0] = 0;
    m_frame[1] = 0;
    m_sampleRate = 44100;
    m_samplePeriod = 1.0 / 44100.0;
    m_bpm = 1.0 / (120.0 / 60.0);

}

CAudioNode::~CAudioNode()
{

}
