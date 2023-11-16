#ifndef FIREFLY_SIM_FIREFLY_H
#define FIREFLY_SIM_FIREFLY_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <assert.h>

namespace firefly_sim
{
  class Position{
    public:
      double x;
      double y;

      Position(double x_val, double y_val) : x(x_val), y(y_val) {}

      Position operator+(Position position){
        return (Position(x + position.x, y + position.y));
      }
      Position operator-(Position position){
        return (Position(x - position.x, y - position.y));
      }
      Position operator+(double scalar){
        return (Position(x + scalar, y + scalar));
      }
      Position operator-(double scalar){
        return (Position(x - scalar, y - scalar));
      }
      Position operator*(double scalar){
        return (Position(x * scalar, y * scalar));
      }
      Position operator/(double scalar){
        return (Position(x / scalar, y / scalar));
      }
      double operator||(Position position){
        return (sqrt(pow(x - position.x, 2) + pow(y - position.y, 2)));
      }
  };

  class Firefly{
    public:
      // Constructor
      Firefly(Position initial_position);
      // Destroyer
      ~Firefly();

      static void updateAll(sf::RenderTarget& target);

      static int getSwarmCount();

      inline double getLightIntensity(){
        return (m_firefly_light_intensity);
      }

      void setLightIntensity(double lightIntensity){
        m_firefly_light_intensity = lightIntensity;
      }

    private:
      sf::Color hex2Color_(std::string hex);
      sf::Color colorBlend_(std::string color1, std::string Color2, double alpha);
      sf::VertexArray createGradientCircle_(float radius, const sf::Color& centerColor, const sf::Color& edgeColor);
      
      void detectLight();
      void updateBrightness();
      void draw(sf::RenderTarget& target);
      void update();

    private:
      Position m_position;
      Position m_target_position;
      double target_brightness;

      double m_size;
      double shine_ratio;
      int m_firefly_index;

      double attractiveness;
      double gamma;
      double alpha;

      sf::CircleShape m_firefly_body;
      sf::VertexArray m_firefly_shiner_body;
      std::vector<sf::CircleShape> m_firefly_glow;
      double m_firefly_light_intensity;
      bool isIncreasing;

      static std::vector<Firefly*> all_fireflies;
      static double max_brightness;
      static double min_brightness;
  };
} // namespace firefly_sim

#include "firefly.hpp"

#endif // FIREFLY_SIM_FIREFLY_H