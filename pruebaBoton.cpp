#include <SFML/Graphics.hpp>
#include <iostream>
#include "boton.h"
#include "monster.h"

using namespace std;
sf::Sprite sprite;

void draw(sf::RenderWindow &w);
void btCallback(uint16_t id);

Boton bt(sf::Vector2f(170,40), 1, btCallback, "botón_1");
Boton bt2;
sf::RenderTexture rendertext;
sf::RectangleShape rendershape(sf::Vector2f(300,300));

int main()
{
    sf::Texture texture;
    sf::RenderWindow window(sf::VideoMode(500, 400), "Test boton");
    window.setVerticalSyncEnabled(true);

    bt2.handle(btCallback);
    bt2.setId(2);
    bt2.setPosition(sf::Vector2f(30,170));
    bt2.setText("Hola BT_2");
    bt2.setSize(sf::Vector2f(200,35));
    //bt2.setBtnColor(sf::Color(0xfc,0xaf,0xaa,0x2a));
    bt2.setTextColor(sf::Color::Yellow);
    bt2.setRenderTarget(&rendertext, &rendershape);
    bt2.setTextureButton("buttons/blue-square-button.png", false);
    bt2.setTextureButton("buttons/blue-square-button_click.png", true);

    bt.setPosition(sf::Vector2f(20,20));
    bt.setText("Monger_1");
    bt.setTextColor(sf::Color(0xfe,0xff,0x5e));
    bt.setRenderTarget(&rendertext, &rendershape);
    bt.setTextureButton("buttons/buttons_PNG_green.png", false);
    bt.setTextureButton("buttons/buttons_PNG_green_click.png", true);

    if((!texture.loadFromMemory(monster,sizeof(monster))))
        return EXIT_FAILURE;
    sprite.setTexture(texture);
    uint16_t max_texture = (texture.getSize().x > texture.getSize().y) ? texture.getSize().x : texture.getSize().y;
    sprite.scale(rendershape.getSize().x / max_texture ,
                 rendershape.getSize().y / max_texture);
    cout << "texture:" << max_texture << " rendershape:" << rendershape.getSize().x << endl;
    rendertext.create(rendershape.getSize().x, rendershape.getSize().y);
    rendertext.clear(sf::Color::Yellow);
    rendertext.draw(sprite);

    rendershape.setTexture(&rendertext.getTexture());
    rendershape.setPosition(sf::Vector2f(60,70));

    while (window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event)) {

              switch (event.type){

                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::MouseButtonPressed:
                case sf::Event::MouseButtonReleased:
                    bt.checkMouse(event, window);
                    bt2.checkMouse(event, window);
                    break;

                default:
                    break;
              }
        }

        window.clear(sf::Color::White);
        draw(window);
        window.display();
    }

    return EXIT_SUCCESS;
}

void draw(sf::RenderWindow &w) {
    w.draw(rendershape);
    bt.show(w);
    bt2.show(w);
}

void btCallback(uint16_t id) {
    cout << "funcion btCallback llamada desde boton id: " << id << endl;
}
