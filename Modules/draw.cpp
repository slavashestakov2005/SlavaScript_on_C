// [[not imported module]]
#include "draw.h"
#include <SFML/Graphics.hpp>
#include "../Lib/functions.h"
#include "../Lib/variables.h"
#include "../Value/nullvalue.h"
#include "../Value/numbervalue.h"
#include "../Value/arrayvalue.h"
#include "../Value/stringvalue.h"
#include "../Exception/argumentsmismatchexception.h"
#include <iostream>

using namespace SlavaScript::lang;
using namespace SlavaScript::modules::draw_f;
using SlavaScript::modules::Draw;
using SlavaScript::exceptions::ArgumentsMismatchException;

namespace SlavaScript{ namespace modules{ namespace draw_out{
    enum class Keys{
        ESCAPE,
        UP,
        DOWN,
        LEFT,
        RIGHT,
        SPACE
    };

    const sf::Color defaultColor = sf::Color(255, 255, 255);
    const int RGB = 255;
    const int defaultHeight = 480;
    const int defaultWidth = 640;
    const int defaultLimit = 100;
    const std::string defaultTitle = "SlavaScript in window";
    sf::RenderWindow window;
    sf::Color color = defaultColor;

    int correctColor(double alpha){
        if (alpha <  0) return 0;
        if (alpha > 255) return 255;
        return int(alpha);
    }
}}}

namespace SlavaScript{ namespace modules{ namespace draw_f{
    Function* window = new FunctionModule([](std::vector<Value*> values) -> Value*{
        int siz = values.size();
        if (siz < 1 || siz > 3) throw new ArgumentsMismatchException("One or two or three arguments expected");
        switch(siz){
            case (1) : {
                draw_out::window.create(sf::VideoMode(draw_out::defaultWidth, draw_out::defaultHeight), values[0] -> asString());
                break;
            }
            case (2): {
                draw_out::window.create(sf::VideoMode(values[0] -> asDouble(), values[1] -> asDouble()), draw_out::defaultTitle);
                break;
            }
            case (3): {
                draw_out::window.create(sf::VideoMode(values[1] -> asDouble(), values[2] -> asDouble()), values[0] -> asString());
                break;
            }
        }
        draw_out::window.setFramerateLimit(draw_out::defaultLimit);
        return NullValue::NULL_;
    });

    Function* color = new FunctionModule([](std::vector<Value*> values) -> Value*{
        int siz = values.size();
        if (siz > 3) throw new ArgumentsMismatchException("One or two or three arguments expected");
        if (!siz) draw_out::color = draw_out::defaultColor;
        else{
            if (siz == 1){
                int colo = values[0] -> asDouble();
                draw_out::color = sf::Color(colo / (draw_out::RGB + 1) / (draw_out::RGB + 1), colo / (draw_out::RGB + 1) % (draw_out::RGB + 1), colo % (draw_out::RGB + 1));
            }
            else{
                int red = draw_out::correctColor(values[0] -> asDouble());
                int green = draw_out::correctColor(values[1] -> asDouble());
                if (siz == 2) draw_out::color = sf::Color(red, green, draw_out::RGB);
                else{
                    int blue = draw_out::correctColor(values[2] -> asDouble());
                    draw_out::color = sf::Color(red, green, blue);
                }
            }
        }
        return NullValue::NULL_;
    });

    Function* line = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 4) throw new ArgumentsMismatchException("Four arguments expected");
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = sf::Vector2f(values[0] -> asDouble(), values[1] -> asDouble());
        line[0].color = draw_out::color;
        line[1].position = sf::Vector2f(values[2] -> asDouble(), values[3] -> asDouble());
        line[1].color = draw_out::color;
        draw_out::window.draw(line);
        return NullValue::NULL_;
    });

    Function* rect = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 4) throw new ArgumentsMismatchException("Four arguments expected");
        sf::RectangleShape rect;
        rect.setSize(sf::Vector2f(values[2] -> asDouble(), values[3] -> asDouble()));
        rect.setPosition(values[0] -> asDouble(), values[1] -> asDouble());
        rect.setOutlineThickness(5);
        rect.setOutlineColor(sf::Color::Black);
        draw_out::window.draw(rect);
        return NullValue::NULL_;
    });

    Function* frect = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 4) throw new ArgumentsMismatchException("Four arguments expected");
        sf::RectangleShape rect;
        rect.setSize(sf::Vector2f(values[2] -> asDouble(), values[3] -> asDouble()));
        rect.setPosition(values[0] -> asDouble(), values[1] -> asDouble());
        rect.setFillColor(draw_out::color);
        draw_out::window.draw(rect);
        return NullValue::NULL_;
    });

    Function* circle = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 3) throw new ArgumentsMismatchException("Three arguments expected");
        sf::CircleShape cricle(values[2] -> asDouble());
        cricle.setPosition(values[0] -> asDouble(), values[1] -> asDouble());
        draw_out::window.draw(cricle);
        return NullValue::NULL_;
    });

    Function* fcircle = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() != 3) throw new ArgumentsMismatchException("Three arguments expected");
        sf::CircleShape cricle(values[2] -> asDouble());
        cricle.setPosition(values[0] -> asDouble(), values[1] -> asDouble());
        cricle.setFillColor(draw_out::color);
        draw_out::window.draw(cricle);
        return NullValue::NULL_;
    });

    Function* repaint = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size()) throw new ArgumentsMismatchException("Zero arguments expected");
        sf::Event event;
        while (draw_out::window.pollEvent(event)) if (event.type == sf::Event::Closed) draw_out::window.close();
        //draw(*window);
        draw_out::window.display();
        return NullValue::NULL_;
    });

    Function* clear = new FunctionModule([](std::vector<Value*> values) -> Value*{
        // std::cout << "In clear size of vector : " << shapes.size() << "\tand : " << sizeof(*window) << std::endl;
        if (values.size()) throw new ArgumentsMismatchException("Zero arguments expected");
        sf::Event event;
        while (draw_out::window.pollEvent(event)) if (event.type == sf::Event::Closed) draw_out::window.close();
        draw_out::window.clear();
        // for (int i = 0; i < shapes.size(); ++i) delete shapes[i];
        // shapes.clear();
        return NullValue::NULL_;
    });

    Function* framelimit = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size() > 1) throw new ArgumentsMismatchException("Zero or one arguments expected");
        if (values.size()) draw_out::window.setFramerateLimit(values[0] -> asDouble());
        else draw_out::window.setFramerateLimit(draw_out::defaultLimit);
        return NullValue::NULL_;
    });

    Function* keypressed = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size()) throw new ArgumentsMismatchException("Zero arguments expected");
        sf::Event event;
        while (draw_out::window.pollEvent(event)){
            if (event.type == sf::Event::Closed) draw_out::window.close();
            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Escape) return new NumberValue(int(draw_out::Keys::ESCAPE));
                if (event.key.code == sf::Keyboard::Up) return new NumberValue(int(draw_out::Keys::UP));
                if (event.key.code == sf::Keyboard::Down) return new NumberValue(int(draw_out::Keys::DOWN));
                if (event.key.code == sf::Keyboard::Left) return new NumberValue(int(draw_out::Keys::LEFT));
                if (event.key.code == sf::Keyboard::Right) return new NumberValue(int(draw_out::Keys::RIGHT));
                if (event.key.code == sf::Keyboard::Space) return new NumberValue(int(draw_out::Keys::SPACE));
            }
        }
        return NumberValue::M_ONE;
    });

    Function* mousehover = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size()) throw new ArgumentsMismatchException("Zero arguments expected");
        ArrayValue* arr = new ArrayValue(2);
        sf::Vector2i pixesPos = sf::Mouse::getPosition(draw_out::window);
        sf::Vector2f pos = draw_out::window.mapPixelToCoords(pixesPos);
        arr -> set(0, new NumberValue(pos.x));
        arr -> set(1, new NumberValue(pos.y));
        sf::Event event;
        while (draw_out::window.pollEvent(event)) if (event.type == sf::Event::Closed) draw_out::window.close();
        return arr;
    });

    Function* close = new FunctionModule([](std::vector<Value*> values) -> Value*{
        if (values.size()) throw new ArgumentsMismatchException("Zero arguments expected");
        draw_out::window.close();
        return NullValue::NULL_;
    });
}}}

void Draw::initConstants(){
    Variables::set("KB_ESCAPE", new NumberValue(int(draw_out::Keys::ESCAPE)));
    Variables::set("KB_UP", new NumberValue(int(draw_out::Keys::UP)));
    Variables::set("KB_DOWN", new NumberValue(int(draw_out::Keys::DOWN)));
    Variables::set("KB_LEFT", new NumberValue(int(draw_out::Keys::LEFT)));
    Variables::set("KB_RIGHT", new NumberValue(int(draw_out::Keys::RIGHT)));
    Variables::set("KB_SPACE", new NumberValue(int(draw_out::Keys::SPACE)));
}

void Draw::initFunctions(){
    Functions::set("window", window);
    Functions::set("color", color);
    Functions::set("line", line);
    Functions::set("rect", rect);
    Functions::set("frect", frect);
    Functions::set("circle", circle);
    Functions::set("fcircle", fcircle);
    Functions::set("repaint", repaint);
    Functions::set("clear", clear);
    Functions::set("framelimit", framelimit);
    Functions::set("keypressed", keypressed);
    Functions::set("mousehover", mousehover);
    Functions::set("close", close);
}
