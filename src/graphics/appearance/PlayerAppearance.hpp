#ifndef CR_PLAYERAPPEARANCE_HPP
#define CR_PLAYERAPPEARANCE_HPP

#include <SFML/Graphics.hpp>

#include "HairType.hpp"
#include "HelmetType.hpp"

namespace cr {
    
    class PlayerAppearance {

    private:
        sf::Color hairColor;
        sf::Color skinColor;
        sf::Color shirtColor;
        sf::Color glovesColor;
        sf::Color shoesColor;
        sf::Color hatColor;
        HelmetType helmetType;
        HairType hairType;
        bool sunglasses;

    public:
        sf::Color getHairColor() const;
        sf::Color getSkinColor() const;
        sf::Color getShirtColor() const;
        sf::Color getGlovesColor() const;
        sf::Color getShoesColor() const;
        sf::Color getHatColor() const;
        HelmetType getHelmetType() const;
        HairType getHairType() const;
        bool hasSunglasses() const;

        void setHairColor(const sf::Color &hairColor);
        void setSkinColor(const sf::Color &skinColor);
        void setShirtColor(const sf::Color &shirtColor);
        void setGlovesColor(const sf::Color &glovesColor);
        void setShoesColor(const sf::Color &shoesColor);
        void setHatColor(const sf::Color &hatColor);
        void setHelmetType(const HelmetType& helmetType);
        void setHairType(const HairType& hairType);
        void setSunglasses(const bool &sunglasses);
    };

}

#endif
