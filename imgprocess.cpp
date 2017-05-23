#include "imgprocess.h"

imgprocess::imgprocess()
{

}














QImage imgprocess::pixeliseFunction (QImage img, int window) {
    QImage imgFinal (img);

    for (int i = 0; i < img.width(); i+=window) {
        for (int j = 0; j < img.height(); j+=window) {
            int sum[3] = {0,0,0};
            int count = 0;

            for (int x = i - window; x <= i + window; x++) {
                for (int y = j - window; y <= j + window; y++) {

                    if (x >= 0 && x < img.width() && y >= 0 && y < img.height()) {
                        count++;
                        sum[0] += img.pixelColor(x,y).red();
                        sum[1] += img.pixelColor(x,y).green();
                        sum[2] += img.pixelColor(x,y).blue();
                    }
                }
            }

            for (int x = i - window; x <= i + window; x++) {
                for (int y = j - window; y <= j + window; y++) {

                    if (x >= 0 && x < img.width() && y >= 0 && y < img.height()) {

                        imgFinal.setPixelColor(x,y,QColor(sum[0]/count, sum[1]/count,
                                sum[2]/count));
                    }
                }
            }
        }
    }

    return imgFinal;
}
















QImage imgprocess::bestMatch (std::vector<QImage> vecImages, std::vector<double> distance,
                              int window, QImage img_original) {

    //Max summation of all the pixel into a square (window,window)
    double finalDist = pow(window,2)*255*3;

    //Block where will save the final square that has the best matches
    QImage block (window, window, img_original.format());

    for (int i = 0; i < vecImages.size(); i++) {
        double distEuclidian = 0;
        std::vector<int> rgb {0,0,0};

        //For one square, calculates the summation of all the pixels
        for (int x = 0; x < vecImages[i].width(); x++) {
            for (int y = 0; y < vecImages[i].height(); y++) {
                rgb[0] += vecImages[i].pixelColor(x,y).red();
                rgb[1] += vecImages[i].pixelColor(x,y).green();
                rgb[2] += vecImages[i].pixelColor(x,y).blue();
            }
        }

        for (int z = 0; z < 3; z++) {
            //distEuclidian += pow(rgb[z] - distance[z],2);
            distEuclidian += fabs(rgb[z] - distance[z]);
        }

        if (distEuclidian < finalDist) {
            finalDist = distEuclidian;
            block = vecImages[i];
        }
    }

    return block;
}
















QImage imgprocess::pixelArt (QImage img_original, int window, std::vector<QImage> vecImages) {
    QImage img_final = img_original.copy();

    for (int i = 0; i < img_original.width(); i+=window) {
        for (int j = 0; j < img_original.height(); j+=window) {

            std::vector<double> rgb {0,0,0};

            //Run into a square block on the original image with size (window, window)
            for (int x = i; x < i + window; x++) {
                for (int y = j; y < j + window; y++) {

                    //Verify if there's no pixel out the image
                    if (x >= 0 && x < img_original.width() &&
                        y >= 0 && y < img_original.height()) {

                        rgb[0] += img_original.pixelColor(x,y).red();
                        rgb[1] += img_original.pixelColor(x,y).green();
                        rgb[2] += img_original.pixelColor(x,y).blue();
                    }
                }
            }


            QImage block = bestMatch(vecImages, rgb, window, img_original);

            //Print into the new image (img_final)
            for (int x = i; x < i + window; x++) {
                for (int y = j; y < j + window; y++) {

                    if (x >= 0 && x < img_original.width() &&
                        y >= 0 && y < img_original.height()) {
                            img_final.setPixelColor(x, y,
                                                    QColor(block.pixelColor(x-i,y-j).red(),
                                                           block.pixelColor(x-i,y-j).green(),
                                                           block.pixelColor(x-i,y-j).blue()));
                    }
                }
            }
        }
    }

    std::cout << "Finish" << std::endl;
    return img_final;
}






