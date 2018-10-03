#include "boton.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
// Constructores
Boton::Boton(sf::Vector2f tam,  const std::string &txtbot): sf::RectangleShape(tam) {
    this->setText(txtbot);
    init();
}
// Pasamos un vector con el tama�o, el id del boton y la rutina de callback
Boton::Boton(sf::Vector2f tam, uint16_t id, void(*callback)(uint16_t), const std::string &txtbot): Boton(tam, txtbot) {
    this->id = id;
    this->cbkFunc = callback;
}

// M�todo de inicializaci�n
void Boton::init() {
  this->setFillColor(this->colFill); //color de fondo bot�n
  //cargamos la fuente
  if( !this->font.loadFromFile("Boton/fonts/DejaVuSerif.ttf")) {
    cout << "no pudo cargarse la fuente." << endl;
  }
  this->textBtn.setFont(this->font);
  this->textBtn.setFillColor(this->textColor);
//  this->tx_pressed.loadFromFile("Boton/boton.png");
//  this->setTexturePressed(tx_pressed);
//  this->setTextureUnpressed(tx_pressed);
}

// M�todos de clase

// Carga una textura para el boton
void Boton::setTextureButton(const string &file, bool pressed){

    if(pressed) {
       this->tx_pressed.loadFromFile(file);
    } else {
        if(this->tx_unpressed.loadFromFile(file)){
            this->textureButton = &this->tx_unpressed;
       }

    }
}

/* checkMouse:
    event: Manejador de eventos de la llamada
    w: Ventana
    container: en el caso de que el boton deba dibujarse dentro de un objeto shape contenedor
*/
void Boton::checkMouse(sf::Event &event, sf::RenderWindow &w) {

    sf::Vector2i posMouse = sf::Mouse::getPosition(w);
    // Si se define shape contenedor y existe RenderTexture, desplazamos las coordenadas del mouse
    // de lo contrario se tendr� en cuenta la ventana como superficie de render
    if( this->rndrShape && this->rndrText ) {
        posMouse -= sf::Vector2i(this->rndrShape->getGlobalBounds().left ,this->rndrShape->getGlobalBounds().top);
    }
     // comprobamos que el rat�n se puls� dentro del bot�n
    if( this->getGlobalBounds().contains(posMouse.x, posMouse.y) ) {
        sf::Mouse::Button bt =  event.mouseButton.button;
        if( bt == sf::Mouse::Left ) {
            if ( event.type == sf::Event::MouseButtonPressed )  {
                if(this->textureButton)
                    this->textureButton = &tx_pressed;
                else
                    this->setFillColor(this->colClick);

                if( this->cbkFunc ) // si se asign� callback llamamos a la funci�n
                    this->cbkFunc(this->id);
                else
                    cout << "funcion callback no definida." << endl;
            }
        }
    }
    // cuando soltamos el bot�n en cualquier parte
    if ( event.type == sf::Event::MouseButtonReleased )  {
        if(this->textureButton)
            this->textureButton = &tx_unpressed;
        else
            this->setFillColor(this->colFill);
    }
}

// Asignamos texto al bot�n en base a la altura del mismo
void Boton::setText(const std::string &text) {
     this->textBtn.setString(text);
     this->textBtn.setCharacterSize(this->getSize().y * 0.7f);
}

// Renderiza el boton en la ventana o en el contenedor si existe
void Boton::show(sf::RenderWindow &w) {
    setPositionTxt();
    if( this->textureButton ) {
        this->setTexture(textureButton, true);
    }
    if(this->rndrText) { // existe un renderTexture
        this->rndrText->draw(*this);
        this->rndrText->draw(this->textBtn);
        rndrText->display();
    } else { // renderizamos directamente en la ventana
        w.draw(*this);
        w.draw(this->textBtn);
    }
}

// Calcula la posici�n centrada del texto dentro del bot�n
void Boton::setPositionTxt() {
    uint16_t wtxt = this->textBtn.getGlobalBounds().width;
    uint16_t wbtn = this->getGlobalBounds().width;
    uint16_t htxt = this->textBtn.getGlobalBounds().height;
    uint16_t hbtn = this->getGlobalBounds().height;
    // Centramos el texto en el bot�n
    this->textBtn.setPosition( this->getPosition().x + (wbtn-wtxt)/2, this->getPosition().y + (hbtn-htxt)/2 - 5);
}

