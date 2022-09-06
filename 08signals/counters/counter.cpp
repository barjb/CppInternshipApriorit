#include "counter.h"

Counter::Counter(int startValue) : m_count(startValue) {}

void Counter::Increment()
{
    ++m_count;
    if(m_emit)
        emit valueChanged(1);
}

void Counter::Decrement()
{
    --m_count;
    if(m_emit)
        emit valueChanged(-1);
}

int Counter::getCount()
{
    return m_count;
}

void Counter::setValue(int change)
{
    m_emit = false;
    if(change > 0)
        Increment();
    else if(change < 0)
        Decrement();
    m_emit = true;
}
