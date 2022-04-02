#ifndef __COLLISION_SHAPES_HPP__
#define __COLLISION_SHAPES_HPP__
#include <cmath>
#include <vector>
#include <glm/vec3.hpp>

/**
 * @brief The CollisionShapes class contains all the shapes for the game to test collision between these shapes.
 */
class CollisionShapes {
public:
    enum shape_t { NULL_SHAPE = -1, POINT, SPHERE, RECTANGLE };

    class Shape {
    protected:
        glm::vec3 position;

    public:
        Shape() : position(0.f) {}
        Shape(const glm::vec3& pos): position(pos) {}

        inline glm::vec3 getPosition() const { return this->position; }
        inline void setPosition(const glm::vec3& pos) { this->position = pos; }
        void move(const glm::vec3& pos) { this->position += pos; }
        void rotate(const glm::vec3&) {}
        void scale(const glm::vec3&) {}
        void scale(const float) {}
        shape_t getType() { return NULL_SHAPE; }
    };

    /// Point shape (position)
    class PointShape: public Shape {
    public:
        PointShape(const glm::vec3& pos) : Shape(pos) {}

        shape_t getType() { return POINT; }
    };

    /// Sphere shape (position + radius)
    class SphereShape : public Shape {
    protected:
        float radius;

    public:
        SphereShape(const glm::vec3& pos, const float rad): Shape(pos), radius(rad) {
            if(radius < 0) throw "ERROR::CollisionShapes::SphereShape::SphereShape -> radius cannot be negative";
        }

        inline float getRadius() const { return this->radius; }
        inline void setRadius(const float rad) { this->radius = rad; }
        void scale(const float value) { this->radius *= value; }
        shape_t getType() { return SPHERE; }
    };

    /// Rectangle shape (min and max for each of the 3 dimensions)
    class RectShape : public Shape {
    protected:
        glm::vec3 min, max;

    public:
        RectShape(const glm::vec3& pos, const glm::vec3& semiSize): Shape(pos) {
            if(semiSize.x < 0 or semiSize.y < 0 or semiSize.z < 0) throw "ERROR::CollisionShapes::RectShape::RectShape -> a semi size cannot be negative";
            this->min = glm::vec3(pos.x - semiSize.x, pos.y - semiSize.y, pos.z - semiSize.z);
            this->max = glm::vec3(pos.x + semiSize.x, pos.y + semiSize.y, pos.z + semiSize.z);
        }

        inline void setPosition(const glm::vec3& pos, const glm::vec3& semiSize) {
            Shape::setPosition(pos);
            this->min = glm::vec3(pos.x - semiSize.x, pos.y - semiSize.y, pos.z - semiSize.z);
            this->max = glm::vec3(pos.x + semiSize.x, pos.y + semiSize.y, pos.z + semiSize.z);
        }
        inline glm::vec3 getMin() const { return this->min; }
        inline glm::vec3 getMax() const { return this->max; }
        void move(const glm::vec3& pos) {
            Shape::move(pos);
            this->min += pos;
            this->max += pos;
        }
        void rotate(const glm::vec3& pos, const glm::vec3& semiSize) {
            this->min = glm::vec3(pos.x - semiSize.x, pos.y - semiSize.y, pos.z - semiSize.z);
            this->max = glm::vec3(pos.x + semiSize.x, pos.y + semiSize.y, pos.z + semiSize.z);
        }
        void scale(const float value) {
            this->scale(glm::vec3(value));
        }
        void scale(const glm::vec3& value) {
            this->min -= this->position;
            this->max -= this->position;

            this->min *= value;
            this->max *= value;

            this->min += this->position;
            this->max += this->position;
        }
        shape_t getType() { return RECTANGLE; }
    };

private:
    /**
     * @brief Check the collision between two points
     * @param a
     * @param b
     * @return boolean representing if there is collision between these shapes
     */
    static bool isCollidedPointToPoint(PointShape& a, PointShape& b) {
        return a.getPosition() == b.getPosition();
    }

    /**
     * @brief Check if a point is in a rectangle
     * @param point
     * @param rect
     * @return boolean representing if there is collision between these shapes
     */
    static bool isCollidedPointToRectangle(PointShape& point, RectShape& rect) {
        return isCollided(rect, point);
    }
    /**
     * @brief Check if a point is in a rectangle
     * @param rect
     * @param point
     * @return boolean representing if there is collision between these shapes
     */
    static bool isCollidedPointToRectangle(RectShape& rect, PointShape& point){
        return (rect.getMin().x <= point.getPosition().x and point.getPosition().x <= rect.getMax().x) and
               (rect.getMin().y <= point.getPosition().y and point.getPosition().y <= rect.getMax().y) and
               (rect.getMin().z <= point.getPosition().z and point.getPosition().z <= rect.getMax().z);
    }

    /**
     * @brief Check the intersection between two rectangles
     * @param rect1
     * @param rect2
     * @return boolean representing if there is collision between these shapes
     */
    static bool isCollidedRectangleToRectangle(RectShape& rect1, RectShape& rect2){
        return (rect1.getMin().x <= rect2.getMax().x and rect1.getMax().x >= rect2.getMin().x) and
               (rect1.getMin().y <= rect2.getMax().y and rect1.getMax().y >= rect2.getMin().y) and
               (rect1.getMin().z <= rect2.getMax().z and rect1.getMax().z >= rect2.getMin().z);
    }

    /**
     * @brief Check if a point is in a sphere
     * @param point
     * @param sphere
     * @return boolean representing if there is collision between these shapes
     */
    static bool isCollidedPointToSphere(PointShape& point, SphereShape& sphere) {
        return isCollided(sphere, point);
    }
    /**
     * @brief Check if a point is in a sphere
     * @param sphere
     * @param point
     * @return boolean representing if there is collision between these shapes
     */
    static bool isCollidedPointToSphere(SphereShape& sphere, PointShape& point) {
        float distance = sqrt(
            pow(point.getPosition().x - sphere.getPosition().x, 2) +
            pow(point.getPosition().y - sphere.getPosition().y, 2) +
            pow(point.getPosition().z - sphere.getPosition().z, 2)
        );
        return distance < sphere.getRadius();
    }

    /**
     * @brief Check the intersection between a rectangle and a sphere
     * @param rect
     * @param sphere
     * @return boolean representing if there is collision between these shapes
     */
    static bool isCollidedRectangleToSphere(RectShape& rect, SphereShape& sphere){
        return isCollided(sphere, rect);
    }
    /**
     * @brief Check the intersection between a rectangle and a sphere
     * @param sphere
     * @param rect
     * @return boolean representing if there is collision between these shapes
     */
    static bool isCollidedRectangleToSphere(SphereShape& sphere, RectShape& rect){
        float x = fmax(rect.getMin().x, fmin(sphere.getPosition().x, rect.getMax().x));
        float y = fmax(rect.getMin().y, fmin(sphere.getPosition().y, rect.getMax().y));
        float z = fmax(rect.getMin().z, fmin(sphere.getPosition().z, rect.getMax().z));

        float distance = sqrt(
            pow(x - sphere.getPosition().x, 2) +
            pow(y - sphere.getPosition().y, 2) +
            pow(z - sphere.getPosition().z, 2)
        );
        return distance < sphere.getRadius();
    }

    /**
     * @brief Check the intersection between two spheres
     * @param sphere1
     * @param sphere2
     * @return boolean representing if there is collision between these shapes
     */
    static bool isCollidedSphereToSphere(SphereShape& sphere1, SphereShape& sphere2){
        float distance = sqrt(
            pow(sphere1.getPosition().x - sphere2.getPosition().x, 2) +
            pow(sphere1.getPosition().y - sphere2.getPosition().y, 2) +
            pow(sphere1.getPosition().z - sphere2.getPosition().z, 2)
        );
        return distance < (sphere1.getRadius() + sphere2.getRadius());
    }
public:
    static bool isCollided(Shape& shape1, Shape& shape2){
        if(shape1.getType() == NULL_SHAPE or shape2.getType() == NULL_SHAPE)
            throw "ERROR::CollisionShapes::isCollided -> shape cannot be an abstract class (need to be PointShape, RectShape, SphereShape)";

        if(shape1.getType() == RECTANGLE){
            RectShape& rect1 = static_cast<RectShape&>(shape1);
            if(shape2.getType() == RECTANGLE){
                RectShape& rect2 = static_cast<RectShape&>(shape2);
                return isCollidedRectangleToRectangle(rect1, rect2);
            }
            if(shape2.getType() == POINT){
                PointShape& point = static_cast<PointShape&>(shape2);
                return isCollidedPointToRectangle(point, rect1);
            }
            SphereShape& sphere = static_cast<SphereShape&>(shape2);
            return isCollidedRectangleToSphere(rect1, sphere);
        } else if(shape1.getType() == SPHERE){
            SphereShape& sphere1 = static_cast<SphereShape&>(shape1);
            if(shape2.getType() == POINT){
                PointShape& point = static_cast<PointShape&>(shape2);
                return isCollidedPointToSphere(point, sphere1);
            }
            SphereShape& sphere2 = static_cast<SphereShape&>(shape2);
            return isCollidedSphereToSphere(sphere1, sphere2);
        } else {
            PointShape& point1 = static_cast<PointShape&>(shape1);
            PointShape& point2 = static_cast<PointShape&>(shape2);
            return isCollidedPointToPoint(point1, point2);
        }
    }
};

#endif // __COLLISION_SHAPES_HPP__
