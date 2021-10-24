#ifndef PROTOTYPE_H
#define PROTOTYPE_H

class Monkey
{
public:
    virtual ~Monkey() {}
    virtual Monkey* Clone() = 0;
    virtual void Play() = 0;
};

#endif // PROTOTYPE_H