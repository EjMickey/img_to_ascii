#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <fstream>

int main()
{
    std::vector<char> chars{ ' ', '.', ',', ';', '-', '+', '#' };

    sf::Image image;
    std::string file_name;
    std::cout << "Enter file path: ";
    std::cin >> file_name;
    if (image.loadFromFile(file_name))
    {
        std::ofstream txt;
        txt.open("art.txt");
        auto pixelsArr = image.getPixelsPtr();
        sf::Vector2u image_size = image.getSize();
        for (size_t i = 0; i<image_size.y;i++)
        {
            for (size_t j = 0; j < image_size.x; j++)
            {  
                auto pixel = image.getPixel(j,i);
                int it = (pixel.r + pixel.g + pixel.b)/3;
                float val = 255.0/chars.size();
                for (size_t k = 0; k < chars.size(); k++)
                {
                    if (it < val)
                    {
                        txt << chars[k];
                        break;
                    }
                    else val += 255.0 / chars.size();
                }
                int dr = it - pixel.r;
                int dg = it - pixel.g;
                int db = it - pixel.b;
                float t = 1;
                sf::Color pixel_color(pixel.r + dr * t, pixel.g + dg * t, pixel.b + db * t);
                image.setPixel(j, i, pixel_color);
            }
            txt << '\n';
        }
        //image.saveToFile("wkurwiony.png");
        txt.close();
    }

    return 0;
}