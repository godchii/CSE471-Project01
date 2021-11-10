#pragma once
#include "CAudioNode.h"
class CAR :
    public CAudioNode
{
public:
	CAR();
	~CAR();
	CAudioNode* m_source;
	void SetSource(CAudioNode* const& source) { m_source = source; }
	void SetDuration(double d) { m_duration = d; }
	virtual void Start();
	virtual bool Generate();
	int InAttackRange();
private:
	double m_duration;
	double m_attack;
	double m_release;
	double m_time;
};

