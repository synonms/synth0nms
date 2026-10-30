#include "Adsr.h"

void Adsr::update(const float attack, const float decay, const float sustain, const float release)
{
    m_adsrParameters.attack = attack;
    m_adsrParameters.decay = decay;
    m_adsrParameters.sustain = sustain;
    m_adsrParameters.release = release;

    setParameters(m_adsrParameters);
}
