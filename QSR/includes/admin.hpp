#include "config.hpp"
#include <fstream>
struct coords
{
    int fromX;
    int fromY;

    int ToX;
    int Toy;
};
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
    char **buffer=nullptr;
    coords drawCords;
};
int Frame::setChar(int X, int Y, char Char)
{
    this->buffer[X][Y] = Char;
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
    for (int i = 0; i < drawCords.ToX; i++)
    {
    for (int j = 0; j < drawCords.Toy; j++)
    {
        buffer[i][j]='\0';
    }   
    }
    return 0;
}
int Frame::draw()
{
    
    for (int i = drawCords.fromX; i < drawCords.ToX; i++)
    {
        for (int j = drawCords.fromY; j < drawCords.Toy; j++)
        {
            cout << buffer[i][j];
        }
        cout << endl;
    }
    cout << this->buffer;
    return 0;
}
Frame::Frame()
{
    this->buffer.
    this->drawCords.fromX = 0;
    this->drawCords.fromY = 0;

    this->drawCords.ToX = 20;
    this->drawCords.Toy = 20;
    for (int i = 0; i < this->drawCords.ToX; i++)
    {
    for (int j = 0; j < this->drawCords.Toy; j++)
    {
        this->buffer[i][j]='\0';
    }   
    }
    Clear();
    setStr(0, 0, "TestAdmin -I");
    draw();
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