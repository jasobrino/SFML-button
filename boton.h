#ifndef BOTON_HPP_INCLUDED
#define BOTON_HPP_INCLUDED
#include <SFML/Graphics.hpp>

class Boton: public sf::RectangleShape {

    uint16_t id {};
    sf::Texture tx_pressed {};
    sf::Texture tx_unpressed {};
    sf::Texture *textureButton {nullptr};
    // definición de colores para el botón
    sf::Color colFill {sf::Color::Cyan};
    sf::Color colClick {sf::Color(0xaa,0xaa,0xbb,0xff)};
    sf::Color textColor {sf::Color::Black};
    // atributos para el texto
    sf::Font font;
    sf::Text textBtn;
    sf::RenderTexture *rndrText {nullptr};
    sf::Shape *rndrShape {nullptr};

    void (*cbkFunc)(uint16_t) {nullptr}; //guarda el puntero de la rutina de callback
    // función de inicialización
    void init();

public:
    // Constructor por defecto: con tamaño inicial fijo
    Boton(): Boton(sf::Vector2f(70,30)) {}
    // Constructor paso de vector con tamaño y texto(opcional)
    Boton(sf::Vector2f tam,  const std::string &txtbot="?");
    // Constructor paso tamaño, id y rutina de callback
    Boton(sf::Vector2f tam, uint16_t id, void(*callback)(uint16_t), const std::string &txtbot="?");
    // getters y setters
    uint16_t getId() { return this->id; }
    void setId(uint16_t id) { this->id = id; }
    void setRenderTarget(sf::RenderTexture *rndtx, sf::Shape *rndshp) { this->rndrText = rndtx; this->rndrShape = rndshp; }
    void setText(const std::string &text);
    void setBtnColor(const sf::Color col) { this->colFill = col; this->setFillColor(col); }
    void setTextColor(const sf::Color col) { this->textColor = col; this->textBtn.setFillColor(this->textColor); }
    void setTextureButton(const std::string &file, bool pressed); //carga la textura del boton pulsado(true)/sin pulsar(false)
    // checkMouse: recibe el manejador de eventos y la ventana para comprobar si se pulsa dentro del mismo
    void checkMouse(sf::Event &event, sf::RenderWindow &w);
    // manejador de la rutina de callback
    void handle(void(*callback)(uint16_t)) { this->cbkFunc = callback; }
    void show(sf::RenderWindow &w);
    //void setPosition(const sf::Vector2f& pos);
    void setPositionTxt();
};


#endif // BOTON_HPP_INCLUDED
