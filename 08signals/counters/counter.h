#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>
class Counter : public QObject
{
    Q_OBJECT
public:
    Counter(int startValue);
    void Increment();
    void Decrement();
    int getCount();
private:
    int m_count;
    bool m_emit = true;
signals:
    void valueChanged(int change);
public slots:
    void setValue(int change);
};

#endif // COUNTER_H
