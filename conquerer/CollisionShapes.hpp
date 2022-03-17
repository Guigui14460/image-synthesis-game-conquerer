#ifndef __COLLISION_SHAPES_HPP__
#define __COLLISION_SHAPES_HPP__
#include <glm/vec3.hpp>
#include <cmath>

/**
 * @brief The CollisionShapes class contains all the shapes for the game to test collision between these shapes.
 */
class CollisionShapes {
public:
    /// Rectangle shape (min and max for each of the 3 dimensions)
    struct RectShape {
        float minX, minY, minZ, maxX, maxY, maxZ;
    };

    /// Sphere shape (position + radius)
    struct SphereShape {
        glm::vec3 position;
        float radius;
    };

    /// Point shape (position)
    struct PointShape {
        glm::vec3 position;
    };

    /**
     * @brief Check the collision between two points
     * @param a
     * @param b
     * @return boolean representing if there is collision between these shapes
     */
    static bool isCollided(PointShape& a, PointShape& b) {
        return a.position == b.position;
    }

    /**
     * @brief Check if a point is in a rectangle
     * @param point
     * @param rect
     * @return boolean representing if there is collision between these shapes
     */
    static bool isCollided(PointShape& point, RectShape& rect) {
        return isCollided(rect, point);
    }
    /**
     * @brief Check if a point is in a rectangle
     * @param rect
     * @param point
     * @return boolean representing if there is collision between these shapes
     */
    static bool isCollided(RectShape& rect, PointShape& point){
        return (rect.minX <= point.position.x and point.position.x <= rect.maxX) and
               (rect.minY <= point.position.y and point.position.y <= rect.maxY) and
               (rect.minZ <= point.position.z and point.position.z <= rect.maxZ);
    }

    /**
     * @brief Check the intersection between two rectangles
     * @param rect1
     * @param rect2
     * @return boolean representing if there is collision between these shapes
     */
    static bool isCollided(RectShape& rect1, RectShape& rect2){
        return (rect1.minX <= rect2.maxX and rect1.maxX >= rect2.minX) and
               (rect1.minY <= rect2.maxY and rect1.maxY >= rect2.minY) and
               (rect1.minZ <= rect2.maxZ and rect1.maxZ >= rect2.minZ);
    }

    /**
     * @brief Check if a point is in a sphere
     * @param point
     * @param sphere
     * @return boolean representing if there is collision between these shapes
     */
    static bool isCollided(PointShape& point, SphereShape& sphere) {
        return isCollided(sphere, point);
    }
    /**
     * @brief Check if a point is in a sphere
     * @param sphere
     * @param point
     * @return boolean representing if there is collision between these shapes
     */
    static bool isCollided(SphereShape& sphere, PointShape& point) {
        float distance = sqrt(
            pow(point.position.x - sphere.position.x, 2) +
            pow(point.position.y - sphere.position.y, 2) +
            pow(point.position.z - sphere.position.z, 2)
        );
        return distance < sphere.radius;
    }

    /**
     * @brief Check the intersection between a rectangle and a sphere
     * @param rect
     * @param sphere
     * @return boolean representing if there is collision between these shapes
     */
    static bool isCollided(RectShape& rect, SphereShape& sphere){
        return isCollided(sphere, rect);
    }
    /**
     * @brief Check the intersection between a rectangle and a sphere
     * @param sphere
     * @param rect
     * @return boolean representing if there is collision between these shapes
     */
    static bool isCollided(SphereShape& sphere, RectShape& rect){
        float x = fmax(rect.minX, fmin(sphere.x, rect.maxX));
        float y = fmax(rect.minY, fmin(sphere.y, rect.maxY));
        float z = fmax(rect.minZ, fmin(sphere.z, rect.maxZ));

        float distance = sqrt(
            pow(x - sphere.position.x, 2) +
            pow(y - sphere.position.y, 2) +
            pow(z - sphere.position.z, 2)
        );
        return distance < sphere.radius;
    }

    /**
     * @brief Check the intersection between two spheres
     * @param sphere1
     * @param sphere2
     * @return boolean representing if there is collision between these shapes
     */
    static bool isCollided(SphereShape& sphere1, SphereShape& sphere2){
        float distance = sqrt(
            pow(sphere1.position.x - sphere2.position.x, 2) +
            pow(sphere1.position.y - sphere2.position.y, 2) +
            pow(sphere1.position.z - sphere2.position.z, 2)
        );
        return distance < (sphere1.radius + sphere2.radius);
    }
};

#endif // __COLLISION_SHAPES_HPP__
