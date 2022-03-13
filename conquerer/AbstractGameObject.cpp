#include "AbstractGameObject.hpp"

bool AbstractGameObject::isDestroyed() {
    return this->m_health <= 0.f;
}

