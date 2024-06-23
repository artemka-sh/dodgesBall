#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

#define SCREEN_SIZE_X 800
#define SCREEN_SIZE_Y 600
#define START_DAMAGE_TIME 0.5f

class AngryBall{
private:
    std::time_t startTime;
    sf::CircleShape circle;
    sf::Vector2f moveVect;
    sf::Transform circlecenter;
    const int radius = 10;
    const int max = 2;
    const int min = -2;
public:
    AngryBall()
    {
        startTime = time(NULL);
        circle.setRadius(radius);
        circle.setOutlineColor(sf::Color::White);
        circle.setOutlineThickness(1);
        circle.setPosition(rand()%SCREEN_SIZE_X , rand()%SCREEN_SIZE_Y);
        moveVect.x = getRandom();
        while(moveVect.x == 0)
        {
            moveVect.x = getRandom();
        }
        moveVect.y = getRandom();
        while(moveVect.y == 0)
        {
            moveVect.y = getRandom();
        }
        circlecenter.translate(-radius, -radius);
        
    }

    int getRandom()
    {
        return min + rand() % (max + max + 1);
    }
    void update()
    {
        circle.move(moveVect);
        if(isValid())
            circle.setFillColor(sf::Color::Red);
    }
    sf::CircleShape drowcircle()
    {
        return circle;
    }
    sf::Transform getTransform()
    {
        return circlecenter;
    }
    sf::FloatRect getBounds(){
        return circle.getGlobalBounds();
    }
    bool isValid()
    { //time(NULL) - startTime
        if(std::difftime(time(NULL), startTime)  > START_DAMAGE_TIME) 
            return true;
        else 
            return false;
        
        
    }
};

int main()
{
    srand(228);
    sf::RenderWindow window(sf::VideoMode(SCREEN_SIZE_X, SCREEN_SIZE_Y), "DON'T TOUCH ANY OBJECTS");
    window.setFramerateLimit(60);
    window.setMouseCursorVisible(false);

    sf::Transform circlecenter;
    circlecenter.translate(-50, -50);
    
    sf::Texture circleTexture;
    circleTexture.loadFromFile("face.png");
    
    sf::CircleShape circle(50);
    circle.setRadius(50);
    circle.setOutlineColor(sf::Color::White);
    circle.setOutlineThickness(1);
    circle.setPosition(400, 300);
    circle.setTexture(&circleTexture); //circle.setFillColor(sf::Color::Black);


    std::vector<AngryBall*> angryBalls;
    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            //std::cout << "Mouse position: (" << mousePos.x << ", " << mousePos.y << ")" << std::endl;
            circle.setPosition(mousePos.x, mousePos.y);
        }

        if(rand()%10==0 and rand()%3==0)
            angryBalls.push_back(new AngryBall());

        for(auto it = angryBalls.begin(); it != angryBalls.end();)
        {
           (*it)->update();

           if((*it)->drowcircle().getPosition().x > SCREEN_SIZE_X || (*it)->drowcircle().getPosition().x < 0 ||
              (*it)->drowcircle().getPosition().y > SCREEN_SIZE_Y || (*it)->drowcircle().getPosition().y < 0){
                delete (*it);
                angryBalls.erase(it);                
            }
            else
            {
                (*it)->update();
                if(circle.getGlobalBounds().intersects((*it)->getBounds()) && (*it)->isValid()){
                    window.close();
                }
                it++;
                
            }
              
        }



        window.clear();
        window.draw(circle/*, circlecenter*/);
        for(AngryBall* x: angryBalls)
        {
            window.draw(x->drowcircle()/*, x->getTransform()*/);
        }
        window.display();
    }

    for (AngryBall* x: angryBalls)
    {
        delete x;
    }
    return 0;
}