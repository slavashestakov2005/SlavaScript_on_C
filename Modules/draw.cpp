// [[not imported module]]
#include "draw.h"
#include "../Lib/functions.h"
#include "../Lib/utils.h"
#include "../Lib/variables.h"
#include "../Value/arrayvalue.h"
#include "../Value/nullvalue.h"
#include "../Value/numbervalue.h"
#include <SFML/Graphics.hpp>

using namespace SlavaScript::lang;
using namespace SlavaScript::modules::draw_f;
using SlavaScript::modules::Draw;


namespace SlavaScript::modules::draw_out{
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
}

namespace SlavaScript::modules::draw_f{
    CREATE_FUNCTION(window)
        int siz = values.size();
        argsCount({1, 2, 3}, values.size());
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
    FE

    CREATE_FUNCTION(color)
        int siz = values.size();
        argsCount({0, 1, 2, 3}, values.size());
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
    FE

    CREATE_FUNCTION(line)
        argsCount(4, values.size());
        sf::VertexArray line(sf::Lines, 2);
        line[0].position = sf::Vector2f(values[0] -> asDouble(), values[1] -> asDouble());
        line[0].color = draw_out::color;
        line[1].position = sf::Vector2f(values[2] -> asDouble(), values[3] -> asDouble());
        line[1].color = draw_out::color;
        draw_out::window.draw(line);
        return NullValue::NULL_;
    FE

    CREATE_FUNCTION(rect)
        argsCount(4, values.size());
        sf::RectangleShape rect;
        rect.setSize(sf::Vector2f(values[2] -> asDouble(), values[3] -> asDouble()));
        rect.setPosition(values[0] -> asDouble(), values[1] -> asDouble());
        rect.setOutlineThickness(5);
        rect.setOutlineColor(sf::Color::Black);
        draw_out::window.draw(rect);
        return NullValue::NULL_;
    FE

    CREATE_FUNCTION(frect)
        argsCount(4, values.size());
        sf::RectangleShape rect;
        rect.setSize(sf::Vector2f(values[2] -> asDouble(), values[3] -> asDouble()));
        rect.setPosition(values[0] -> asDouble(), values[1] -> asDouble());
        rect.setFillColor(draw_out::color);
        draw_out::window.draw(rect);
        return NullValue::NULL_;
    FE

    CREATE_FUNCTION(circle)
        argsCount(3, values.size());
        sf::CircleShape cricle(values[2] -> asDouble());
        cricle.setPosition(values[0] -> asDouble(), values[1] -> asDouble());
        draw_out::window.draw(cricle);
        return NullValue::NULL_;
    FE

    CREATE_FUNCTION(fcircle)
        argsCount(3, values.size());
        sf::CircleShape cricle(values[2] -> asDouble());
        cricle.setPosition(values[0] -> asDouble(), values[1] -> asDouble());
        cricle.setFillColor(draw_out::color);
        draw_out::window.draw(cricle);
        return NullValue::NULL_;
    FE

    CREATE_FUNCTION(repaint)
        argsCount(0, values.size());
        sf::Event event;
        while (draw_out::window.pollEvent(event)) if (event.type == sf::Event::Closed) draw_out::window.close();
        draw_out::window.display();
        return NullValue::NULL_;
    FE

    CREATE_FUNCTION(clear)
        argsCount(0, values.size());
        sf::Event event;
        while (draw_out::window.pollEvent(event)) if (event.type == sf::Event::Closed) draw_out::window.close();
        draw_out::window.clear();
        return NullValue::NULL_;
    FE

    CREATE_FUNCTION(framelimit)
        argsCount(0, 1, values.size());
        if (values.size()) draw_out::window.setFramerateLimit(values[0] -> asDouble());
        else draw_out::window.setFramerateLimit(draw_out::defaultLimit);
        return NullValue::NULL_;
    FE

    CREATE_FUNCTION(keypressed)
        argsCount(0, values.size());
        sf::Event event;
        while (draw_out::window.pollEvent(event)){
            if (event.type == sf::Event::Closed) draw_out::window.close();
            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Escape) SH_RET(NumberValue, int(draw_out::Keys::ESCAPE));
                if (event.key.code == sf::Keyboard::Up) SH_RET(NumberValue, int(draw_out::Keys::UP));
                if (event.key.code == sf::Keyboard::Down) SH_RET(NumberValue, int(draw_out::Keys::DOWN));
                if (event.key.code == sf::Keyboard::Left) SH_RET(NumberValue, int(draw_out::Keys::LEFT));
                if (event.key.code == sf::Keyboard::Right) SH_RET(NumberValue, int(draw_out::Keys::RIGHT));
                if (event.key.code == sf::Keyboard::Space) SH_RET(NumberValue, int(draw_out::Keys::SPACE));
            }
        }
        return NumberValue::M_ONE;
    FE

    CREATE_FUNCTION(mousehover)
        argsCount(0, values.size());
        std::shared_ptr<ArrayValue> arr = SHARE(ArrayValue, 2);
        sf::Vector2i pixesPos = sf::Mouse::getPosition(draw_out::window);
        sf::Vector2f pos = draw_out::window.mapPixelToCoords(pixesPos);
        arr -> set(0, SHARE(NumberValue, pos.x));
        arr -> set(1, SHARE(NumberValue, pos.y));
        sf::Event event;
        while (draw_out::window.pollEvent(event)) if (event.type == sf::Event::Closed) draw_out::window.close();
        return arr;
    FE

    CREATE_FUNCTION(close)
        argsCount(0, values.size());
        draw_out::window.close();
        return NullValue::NULL_;
    FE
}

void Draw::initConstants(){
    Variables::set("KB_ESCAPE", SHARE(NumberValue, int(draw_out::Keys::ESCAPE)));
    Variables::set("KB_UP", SHARE(NumberValue, int(draw_out::Keys::UP)));
    Variables::set("KB_DOWN", SHARE(NumberValue, int(draw_out::Keys::DOWN)));
    Variables::set("KB_LEFT", SHARE(NumberValue, int(draw_out::Keys::LEFT)));
    Variables::set("KB_RIGHT", SHARE(NumberValue, int(draw_out::Keys::RIGHT)));
    Variables::set("KB_SPACE", SHARE(NumberValue, int(draw_out::Keys::SPACE)));
}

void Draw::initFunctions(){
    INFO_F(window, ArgumentsInfo(1, 2))
    INFO_F(color, ArgumentsInfo(0, 3))
    QUATERNARY_F(line)
    QUATERNARY_F(rect)
    QUATERNARY_F(frect)
    TERNARY_F(circle)
    TERNARY_F(fcircle)
    WITHOUT_F(repaint)
    WITHOUT_F(clear)
    INFO_F(framelimit, ArgumentsInfo(0, 1))
    WITHOUT_F(keypressed)
    WITHOUT_F(mousehover)
    WITHOUT_F(close)
}
