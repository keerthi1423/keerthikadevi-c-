#include "ImageTransform.h"
#include <cmath>

using namespace uiuc;

/**
 * Illinify function
 */
PNG illinify(PNG image) {
    for (unsigned x = 0; x < image.width(); x++) {
        for (unsigned y = 0; y < image.height(); y++) {

            HSLAPixel &pixel = image.getPixel(x, y);

            double orange = 11;
            double blue = 216;

            double distToOrange = abs(pixel.h - orange);
            double distToBlue = abs(pixel.h - blue);

            distToOrange = std::min(distToOrange, 360 - distToOrange);
            distToBlue = std::min(distToBlue, 360 - distToBlue);

            if (distToOrange < distToBlue)
                pixel.h = orange;
            else
                pixel.h = blue;
        }
    }
    return image;
}

/**
 * Spotlight function
 */
PNG spotlight(PNG image, int centerX, int centerY) {

    for (unsigned x = 0; x < image.width(); x++) {
        for (unsigned y = 0; y < image.height(); y++) {

            HSLAPixel &pixel = image.getPixel(x, y);

            double dx = x - centerX;
            double dy = y - centerY;

            double distance = sqrt(dx * dx + dy * dy);

            double factor;

            if (distance > 160)
                factor = 0.2;
            else
                factor = 1 - (0.005 * distance);

            pixel.l *= factor;
        }
    }
    return image;
}

/**
 * Watermark function
 */
PNG watermark(PNG firstImage, PNG secondImage) {

    for (unsigned x = 0; x < firstImage.width() && x < secondImage.width(); x++) {
        for (unsigned y = 0; y < firstImage.height() && y < secondImage.height(); y++) {

            HSLAPixel &basePixel = firstImage.getPixel(x, y);
            HSLAPixel &stencilPixel = secondImage.getPixel(x, y);

            if (stencilPixel.l == 1.0) {
                basePixel.l += 0.2;
                if (basePixel.l > 1.0)
                    basePixel.l = 1.0;
            }
        }
    }
    return firstImage;
}
