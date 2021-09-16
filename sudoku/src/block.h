#ifndef _SODOKU_BLOCK_H_
#define _SODOKU_BLOCK_H_

class BlockC
{
    static const int MAXCOUNT = 9;
public:
    BlockC();
    bool IsValid() const;
    bool IsFull() const;
    void Print() const;
    void PushBack(point_value_t* point);

private:
    int count;
    point_value_t* numbers[MAXCOUNT];
};

#endif
