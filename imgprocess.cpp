#include "imgprocess.h"

imgprocess::imgprocess()
{

}

QImage imgprocess::pixeliseFunction (QImage img, int window) {
    QImage imgFinal(img.width(), img.height(), img.format());

    for (int i = 0; i < img.width(); i+=window-1) {
        for (int j = 0; j < img.height(); j+=window-1) {
            int sum[3] = {0,0,0};
            int count = 0;

            for (int x = i - window/2; x <= i + window/2; x++) {
                for (int y = j - window/2; y <= j + window/2; y++) {

                    if (x >= 0 && x < img.width() && y >= 0 && y < img.height()) {
                        count++;
                        sum[0] += img.pixelColor(x,y).red();
                        sum[1] += img.pixelColor(x,y).green();
                        sum[2] += img.pixelColor(x,y).blue();
                    }
                }
            }

            for (int x = i - window/2; x <= i + window/2; x++) {
                for (int y = j - window/2; y <= j + window/2; y++) {
                    if (x >= 0 && x < img.width() && y >= 0 && y < img.height()) {
                        imgFinal.setPixelColor(x,y,QColor(sum[0]/count, sum[1]/count, sum[2]/count));
                    }
                }
            }
        }
    }

    imgFinal.save(QString("teste.png"));
    return imgFinal;
}
