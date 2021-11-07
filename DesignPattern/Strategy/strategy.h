#ifndef STRATEGY_H
#define STRAGEGY_H

class ITransport
{
public:
    virtual ~ITransport() {}
    virtual void Run() = 0;
};

#endif // STRATEGY_H
