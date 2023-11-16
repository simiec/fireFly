#ifndef FIREFLY_SIM_APPLICATION_H
#define FIREFLY_SIM_APPLICATION_H

#include <iostream>
#include <vector>
#include "firefly.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <assert.h>

namespace firefly_sim
{
  class Application{
    public:
      // Constructor
      Application(const int FPS = 60, const int WIDTH = 800, const int HEIGHT = 600);

      // Destructor
      ~Application();

      // Update the application (next frame)
      void update();

      // Check if the window is still operating
      bool isWindowOpen(){
        return m_window.isOpen();
      }
      
      // Change background color
      void setBackgroundColor(std::string hex);
    private:
      // Convert hexadecimal number to color
      sf::Color hex2Color_(std::string hex);

      // Draw background
      void backgroundDrawer_();

      // Handle user triggered events
      void eventHandler_();

      void resetSimulator_();

      // Draw line
      sf::RectangleShape getLine_(sf::Vector2f startPoint, sf::Vector2f endPoint, double lineThickness, std::string color = "393E46", int alpha = 255);

    private:
      sf::RenderWindow m_window;
      sf::Color m_background_color;

      const int WINDOW_WIDTH;
      const int WINDOW_HEIGHT;
      const int m_fps;
      int m_frame;
      bool m_paused;

      int m_swarm_sample_count;
      std::vector<firefly_sim::Firefly*> swarm;
  };
} // namespace firefly_sim

#include "application.hpp"

#endif // FIREFLY_SIM_APPLICATION_H