#ifndef CONCRETE_BUILDER_H
#define CONCRETE_BUILDER_H

#include "builder.h"

class ThinkPadBuilder : public IBuilder
{
public:
    ThinkPadBuilder() {m_pComputer = new Computer();}
    void BuildCpu() override {m_pComputer->SetCpu("i5-6200u");}
    void BuildMainboard() override {m_pComputer->SetMainboard("Inter DH57DD");}
    void BuildRam() override {m_pComputer->SetRam("DDR4");}
    void BuildVideoCard() override {m_pComputer->SetVideoCard("NVIDIA Gefore 920MX");}
    Computer* Getresult() override {return m_pComputer;}
private:
    Computer *m_pComputer;
}

class YogaBuilder : public IBuilder
{
public:
    YogaBuilder() {m_pComputer = new Computer();}
    void BuildCpu() override {m_pComputer->SetCpu("i7-7500U");}
    void BuildMainboard() override {m_pComputer->SetMainboard("Inter Dp55KG");}
    void BuildRam() override {m_pComputer->SetRam("DDR5");}
    void BuildVideoCard() override {m_pComputer->SetVideoCard("NVIDIA GeForce 940MX");}
    Computer* GetReult() override {return m_pComputer;}

private:
    Computer *m_pComputer;
};

#endif