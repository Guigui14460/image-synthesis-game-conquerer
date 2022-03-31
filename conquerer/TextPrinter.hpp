#ifndef __TEXT_PRINTER_HPP__
#define __TEXT_PRINTER_HPP__
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include "glApi.hpp"

/**
 * @brief The TextPrinter class represents a displayer of text on screen
 */
class TextPrinter {
public:
  /**
   * @brief Constructor with default filename ("conquerer/font.png")
   * @param width width of the screen
   * @param height height of the screen
   */
  TextPrinter(uint width, uint height);

  /**
   * @brief Constructor with custom filename
   * @param width width of the screen
   * @param height height of the screen
   * @param fontFilename filename of the font to use
   */
  TextPrinter(uint width, uint height, std::string fontFilename);

  /**
   * @brief Creates a VAO for displaying some text overlay
   * @param key where to insert VAO in map
   * @param text text to display
   * @param x x-coordinates
   * @param y y-coordinates
   * @param fontsize percentage of width covered by one character
   * @param fontColor color (rgb) of the font (defaults to white)
   * @param fillColor color (rgba) of the background of the text (defaults to white)
   * @param padding white space to to border of the filling background
   */
  void printText(const std::string& key, const std::string& text, float x, float y, float fontsize, const glm::vec3& fontColor = glm::vec3(1, 1, 1), const glm::vec4& fillColor = glm::vec4(1, 1, 1, 0), uint padding = 0);

  /**
   * @brief Removes a text (VAO)
   * @param key the associated VAO to delete
   */
  void removeText(const std::string& key);

  /// Draws all the vaos created with printText
  void draw();

  /**
   * @brief Resizes the viewport stored in the TextPrinter object
   * @param width width of the viewport
   * @param height height of the viewport
   */
  void resize(uint width, uint height);
;

private:
  struct text_t {
      std::shared_ptr<VAO> vao;
      glm::vec3 color;
      glm::vec4 fillColor;

      text_t(std::shared_ptr<VAO> vao_, glm::vec3 color_, glm::vec4 fillColor_) :
          vao(vao_), color(color_), fillColor(fillColor_) {}
  };

private:
  uint m_width;   /// Width of the viewport
  uint m_height;  /// Height of the viewport
  uint m_nbChar;  /// Number of characters per row (in the font texture)
  float m_wOverH; /// Aspect ratio

  Program m_program;                        /// GLSL program for displaying text
  Texture m_fontTexture;                    /// Texture containing all the font characters
  Sampler m_sampler;                        /// Texture sampler
  std::unordered_map<std::string, std::unique_ptr<text_t>> m_texts; /// texts to show
};

#endif // __TEXT_PRINTER_HPP__
