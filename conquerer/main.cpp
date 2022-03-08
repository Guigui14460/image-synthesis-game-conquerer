#include <iostream>
#include <cstdlib>
#include <vector>

#define GLM_FORCE_SWIZZLE
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ConquererApplication.hpp"
#include "glApi.hpp"
#include "termcolor/termcolor.hpp"

int main(int, char**){
    ConquererApplication app;
    app.setCallbacks();
    app.mainLoop();
	return EXIT_SUCCESS;
}
