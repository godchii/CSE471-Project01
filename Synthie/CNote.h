#pragma once
#include <string>

using namespace std;

class CNote
{
public:
    CNote();
    virtual ~CNote();

    bool operator<(const CNote& b);

    void XmlLoad(IXMLDOMNode* xml, std::wstring& instrument);

    int Measure() const { return m_measure; }
    double Beat() const { return m_beat; }
    const std::wstring& Instrument() const { return m_instrument; }
    IXMLDOMNode* Node() { return m_node; }

private:
    std::wstring m_instrument;
    int m_measure;
    double m_beat;
    CComPtr<IXMLDOMNode> m_node;
};

