#ifndef __ABSTRACT_GAME_OBJECT_HPP__
#define __ABSTRACT_GAME_OBJECT_HPP__

/**
 * @brief The AbstractGameObject class is an abstract class to create all the objects of the Conquerer game.
 */
class AbstractGameObject
{
public:
    AbstractGameObject() = default;
    AbstractGameObject(const AbstractGameObject& o) = default;

    /**
     * @brief Checks the collision between two objects
     * @param other other object to check collision
     * @return boolean representing if a collision is here
     */
    virtual bool isCollided(AbstractGameObject& other) = 0;

    /// Checks if the object is destroyed
    virtual bool isDestroyed() = 0;

private:
    float m_health;

};

#endif // __ABSTRACT_GAME_OBJECT_HPP__
