#ifndef VISITOR_H
#define VISITOR_H

class BellTower;
class TerracottaWarriors;

class IVisitor
{
public:
    virtual ~ITvisitor() {}
    virtual void Visit(BellTower*) = 0;
    virtual void visit(TerracottaWarriors *) = 0;
};

#endif // VISITOR_H

