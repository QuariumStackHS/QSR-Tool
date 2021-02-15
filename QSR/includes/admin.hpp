#include "config.hpp"
#include <fstream>
struct coord
{
    int x;
    int y;
};
class Frame
{
public:
    Frame();
    int setChar(int, int, char);
    int draw();
    int Clear();
    int setStr(int, int, string);

private:
    vector<string>buffer;
    int fromX;
    int fromY;

    int ToX;
    int Toy;
};
int Frame::setChar(int X, int Y, char Char)
{
    /*auto x = this->buffer[X].begin();
    //auto y = this->buffer[X][Y].begin();
    buffer[X].insert(x+Y,Char);*/
    //this->buffer->insert(yChar);
    return 0;
}
int Frame::setStr(int X, int Y, string str)
{
    int strsize = strlen(str.c_str());
    for (int i = 0; i < strsize; i++)
    {
        this->setChar(X, Y + i, str.c_str()[i]);
    }

    return 0;
}
int Frame::Clear()
{
buffer.clear();
    return 0;
}
int Frame::draw()
{
    
    for (int i = fromX; i < ToX; i++)
    {
        
        cout << buffer[i]<<endl;
    }
    //cout << this->buffer;
    return 0;
}
Frame::Frame()
{
    
    fromX = 0;
    fromY = 0;

    ToX = 20;
    Toy = 20;
    buffer.clear();
}
/*

|                   |
|                   |
|                   |
|                   |
|                   |
|                   ^
X->_________________Y

*/