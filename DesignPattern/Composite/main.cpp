#include "composite.h"
#include "leaf.h"

int main()
{
    Component *pRoot = new Composite();
    Component *pDepart1 = new Composite();

    pDepart1->Add(new Leaf());
    pDepart1->Add(new Leaf);
    pRoot->Add(pDepart1);

    Compoent *pDepart2 = new Composite();


    pRoot->Add(new leaf());
    pRoot->Add(new leaf());
    Component* pLeaf = new Leaf();

    pRoot->Add(pLeaf);

    pRoot->Remove(pLeaf);

    pRoot->Operation(1);
    SAFE_DELETE(pRoot);

    getchar();
    return 0;
}