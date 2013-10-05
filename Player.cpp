#include "Player.hpp"
#include "Houses.hpp"

Player::Player(House theHouse, int theId):
    id(theId), house(theHouse), color(Houses::getDefaultColor(house))
{
    //init a trike

}

sf::Color Player::getColor() const
{
    return color;
}

bool Player::operator ==(const Player &other) const
{
    return (id==other.id);
}

bool Player::operator !=(const Player &other) const
{
    return !(*this==other);
}

void Player::recolor(sf::Image &image) const
{
    sf::Vector2u imageSize = image.getSize();

    for (unsigned int i=0; i<imageSize.x; ++i){
        for (unsigned int j=0; j<imageSize.y; ++j){
            sf::Color pixelColor = image.getPixel(i,j);
            if ((pixelColor == sf::Color(125,0,0))
                ||(pixelColor == sf::Color(214,0,0))
                ||(pixelColor == sf::Color(60,0,0))
                ||(pixelColor == sf::Color(89,0,0))
                ||(pixelColor == sf::Color(153,0,0))
                ||(pixelColor == sf::Color(182,0,0))
                )
            {
                image.setPixel(i,j,color);
            }
        }
    }
}

const sf::Texture &Player::getTexture(Unit::Type type) const
{
  auto found = textures.find(type);
  if (found == textures.end()){
    sf::Image image;
    image.loadFromFile("graphics/Unit_Trike.bmp");
    image.createMaskFromColor(sf::Color(0,0,0));
    recolor(image);

    sf::Texture texture;
    texture.loadFromImage(image);
    textures.insert({type, std::move(texture)});
    return textures[type];
  }
  return *found;
}
