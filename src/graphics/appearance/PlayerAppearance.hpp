#ifndef CR_PLAYERAPPEARANCE_HPP
#define CR_PLAYERAPPEARANCE_HPP

#include <SFML/Graphics.hpp>

namespace cr {
    
    class PlayerAppearance {

    private:
        sf::Color hairColor;
        sf::Color skinColor;
        sf::Color shirtColor;
        sf::Color glovesColor;
        sf::Color shoesColor;
        sf::Color hatColor;

    public:
        sf::Color getHairColor();
        sf::Color getSkinColor();
        sf::Color getShirtColor();
        sf::Color getGlovesColor();
        sf::Color getShoesColor();
        sf::Color getHatColor();

        void setHairColor(const sf::Color &hairColor);
        void setSkinColor(const sf::Color &skinColor);
        void setShirtColor(const sf::Color &shirtColor);
        void setGlovesColor(const sf::Color &glovesColor);
        void setShoesColor(const sf::Color &shoesColor);
        void setHatColor(const sf::Color &hatColor);
    };

}

#endif
