#ifndef PNGClass
#define PNGClass

#include <iostream>
#include <SDL2/SDL.h>

#include "ColorClass.h"
#include "../src/lodepng.cpp"

const char RED = 0;
const char GREEN = 1;
const char BLUE = 2;
const char OPACITY = 3;

class PNG {

    public:

        // Instance variables
        const char* fileName;
        unsigned int width;
        unsigned int height;
        Uint8* rawData;
        Color** pixels;

        PNG(const char* filename) {

            std::vector<unsigned char> returnData;
            unsigned int failed = lodepng::decode(returnData, this->width, this->height, filename);

            if (failed) {
                std::cerr << "Error loading PNG file: " << lodepng_error_text(failed) << std::endl;
                return;
            }

            this->fileName = filename;
            int size = this->width * this->height;
            this->rawData = new Uint8[size * 4];
            this->pixels = new Color*[size];

            for (int i = 0; i < size * 4; i += 4) {

                Uint8 r = (Uint8) returnData[i];
                Uint8 g = (Uint8) returnData[i + 1];
                Uint8 b = (Uint8) returnData[i + 2];
                Uint8 o = (Uint8) returnData[i + 3];

                this->rawData[i] = r;
                this->rawData[i + 1] = g;
                this->rawData[i + 2] = b;
                this->rawData[i + 3] = o;

                this->pixels[i / 4] = new Color(o, r, g, b);

            }
            
            return;
        }

        PNG(PNG* input, int startx, int starty, int endx, int endy) {

            this->width = (endx - startx);
            this->height = (endy - starty);

            this->fileName = NULL;
            int size = this->width * this->height;
            this->rawData = new Uint8[size * 4];
            this->pixels = new Color*[size];

            for (int i = 0; i < size; i += 1) {

                int x = ((i % this->width) + startx);
                int y = (int) (i / this->width) + (starty);

                Uint8 r = input->getChannel( x, y, RED);
                Uint8 g = input->getChannel( x, y, GREEN);
                Uint8 b = input->getChannel( x, y, BLUE);
                Uint8 o = input->getChannel( x, y, OPACITY);

                if (r == -1 || g == -1 || b == -1 || o == -1) {
                    std::cout << "color channel failed to get" << std::endl;
                    system("pause");
                    return;
                }

                this->rawData[i * 4] = r;
                this->rawData[(i * 4) + 1] = g;
                this->rawData[(i * 4) + 2] = b;
                this->rawData[(i * 4) + 3] = o;

                this->pixels[i] = new Color(o, r, g, b);

            }
            
            return;
        }

        ~PNG() {

            for (int i = 0; i < this->width * this-> height; i++) {
                delete this->pixels[i];
            }

            delete[] this->rawData;
            delete[] this->pixels;

            return;
        }

        Color* getPixel(int x, int y) {
            if (x >= this->width || y >= this->height) return NULL;
            return this->pixels[ (this->width * y) + x ];
        }

        bool setPixel(int x, int y, Color* pixel) {
            if (x >= this->width || y >= this->height) return false;
            if (pixel == NULL) return false;
            this->pixels[ (this->width * y) + x ] = pixel;
            return true;
        }

        Uint8 getChannel(int x, int y, char channel) {
            if (x >= this->width || y >= this->height) return -1;
            if (channel > 3 || channel < 0) return -1;
            return this->rawData[ (((this->width * y) + x) * 4) + channel];
        }

        bool setChannel(int x, int y, char channel, Uint8 value) {
            if (x >= this->width || y >= this->height) return false;
            if (channel > 3 || channel < 0) return false;
            this->rawData[ (((this->width * y) + x) * 4) + channel] = value;
            return true;
        }


    private:


};

#endif