#ifndef DIRECTOR_H
#define DERECTOR_H

#include "builder.h"

class Director
{
public:
    void Create(IBuilder *builder)
    {
        builder->buildCpu();
        builder->BuildMainboard();
        builder->BuildRam();
        builder->BuildVideoCard();
    }
};

#endif
