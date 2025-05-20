#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

enum class FoodType { Dot, Skill, Fruit };

class Food {
protected:
    Vector2f position;
    Vector2f size; // Added size as a member variable
    int foodValue;
    bool isEaten;
    FoodType type;
    Texture texture;
    Sprite image;
    int fruitImageIndex;

public:
    // Updated constructor to accept position and size
    Food(FoodType type, int value, Vector2f pos, Vector2f sz);
    virtual FloatRect getBounds() const {
        return FloatRect(position.x, position.y, size.x, size.y);
    }
    virtual void draw(RenderWindow& window) = 0;
    void setEaten();
    bool eaten() const;
    int getValueScore() const;
    FoodType getType() const;
    Vector2f getPosition() const;
    void setPosition(Vector2f pos);
};

class Dot : public Food {
public:
    Dot(Vector2f pos); 
    void draw(RenderWindow& window) override;
};

class Skill : public Food {
public:
    Skill(Vector2f position); // Constructor accepts position
    void draw(RenderWindow& window) override;
};

class Fruit : public Food {
public:
    Fruit(Vector2f pos); // Constructor accepts position
    void draw(RenderWindow& window) override;
};
