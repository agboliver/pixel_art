#ifndef IMGPROCESS_H
#define IMGPROCESS_H
#include <QImage>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

class imgprocess
{
public:
    imgprocess();

public slots:
    QImage pixeliseFunction (QImage img, int window);

    QImage bestMatch (std::vector<QImage> vecImages, std::vector<double> distance,
                      int window, QImage img_original);

    QImage pixelArt (QImage img_original, int window, std::vector<QImage> vecImages);
};

#endif // IMGPROCESS_H
