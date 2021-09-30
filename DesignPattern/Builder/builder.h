#ifndef BUILDER_H
#define BUILDER_H

#include "product.h"

class IBuilder
{
public:
    virtual void buildCpu() = 0;
    virtual void BuildMainboard() = 0;
    virtual void BuildRam() = 0;
    virtual void BuildVideoCard() = 0;
    virtual Computer* GetResult() = 0;
};

#endif // BUILDER_H
