#ifndef __FULL_SCREEN_APPLICATION_HPP__
#define __FULL_SCREEN_APPLICATION_HPP__
#include <glm/vec2.hpp>
#include "Application.hpp"

/// To not confuse with the FullScreenApplication class.
typedef Application WindowedApplication;

/**
 * @brief An abstract class for the main application (based on GLFW).
 * It is particular because it allows developers to create a full screen application.
 */
class FullScreenApplication
{
public:
    /**
     * @brief Constructs a full screen window and initializes the GL context.
     * @param title the title of the application
     */
    FullScreenApplication(const char* title = "An application");

    virtual ~FullScreenApplication();

    /**
     * @brief Sets the callbacks (key, mouse, resize).
     */
    virtual void setCallbacks() = 0;

    /**
     * @brief Main application loop.
     *
     * Continues until 'Esc' is pressed.
     */
    void mainLoop();

    /**
     * @brief Gets the size of the current window.
     * @return width and height in a 2d vector
     */
    glm::vec2 getWindowSize();

private:
    /**
     * @brief Updates the state of the application based on events.
     */
    virtual void update() = 0;

    /**
     * @brief Renders a frame.
     */
    virtual void renderFrame() = 0;

    /**
     * @brief Creates a window, and init the OpenGL context.
     * @param title the title of the application
     */
    void initOGLContext(const char* title);

    /**
     * @brief Initializes GLFW related parameters.
     */
    void initGLFW();

    /**
     * @brief Initializes the GLFW window.
     * @param title the title of the application
     */
    void initWindow(const char* title);

    /**
     * @brief Initializes GLEW related parameters.
     */
    void initGLEW();

    /**
     * @brief Clean up the state and quit.
     * @param return_code code to return at the end of the application execution
     */
    void shutDown(int return_code);
};

#endif // __FULL_SCREEN_APPLICATION_HPP__
