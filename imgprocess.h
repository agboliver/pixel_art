#ifndef IMGPROCESS_H
#define IMGPROCESS_H
#include <QImage>

class imgprocess
{
public:
    imgprocess();

public slots:
    QImage pixeliseFunction (QImage img, int window);
};

#endif // IMGPROCESS_H
