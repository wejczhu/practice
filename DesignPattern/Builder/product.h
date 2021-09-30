#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>

using namespace std;

class Computer
{
public:
    void SetCpu(string cpu) {m_strCpu = cpu;}
    void SetMainboard(string mainboard){m_strMainboard = mainboard;}
    void SetRam(string ram){m_strRam = ram;}
    void setVideoCard(string videoCard){m_strVideoCard = videoCard;}

    string GetCPU(){return m_strCpu;};
    string GetMainboard({return m_strMainboard;});
    string GetRam({return m_strRam;});
    string getVideoCard({return m_strVideoCard;});

private:
    string m_strCpu;
    string m_strMainboard;
    string m_strRam;
    string m_strVideoCard;
};

#endif
