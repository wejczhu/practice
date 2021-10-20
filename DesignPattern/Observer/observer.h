#ifndef OBSERVER_H
#define OBSERVER_H

class IObserver
{
public:
    virtual void Update(float price);
};

#endif // OBSERVER_H
