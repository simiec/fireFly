#include "firefly.h"

std::vector<firefly_sim::Firefly*> firefly_sim::Firefly::all_fireflies = {};
double firefly_sim::Firefly::max_brightness = 0;
double firefly_sim::Firefly::min_brightness = 0;

firefly_sim::Firefly::Firefly(firefly_sim::Position initial_position)
: m_position(initial_position)
, m_target_position(0,0)
, shine_ratio(0.0)
, m_size(2.0f)
, attractiveness(2.4)
, gamma(1E-5)
, alpha(1E+2)
{
  m_firefly_index = all_fireflies.size();
  all_fireflies.push_back(this);
  m_firefly_body.setRadius(m_size);
  m_firefly_body.setFillColor(sf::Color::Transparent);
  m_firefly_body.setOutlineThickness(m_size * 2 / 5);
  m_firefly_body.setOutlineColor(hex2Color_("FFCF96"));
  m_firefly_shiner_body = createGradientCircle_(m_size, sf::Color::Transparent, hex2Color_("FFCF96"));

  m_firefly_light_intensity = 0;
  isIncreasing = true;

  max_brightness = 0;
}

int firefly_sim::Firefly::getSwarmCount(){
  return all_fireflies.size();
}

firefly_sim::Firefly::~Firefly(){
  auto it = std::remove(all_fireflies.begin(), all_fireflies.end(), this);
  all_fireflies.erase(it, all_fireflies.end());
}

void firefly_sim::Firefly::updateAll(sf::RenderTarget& target){
  for (Firefly* firefly : all_fireflies){
    firefly->updateBrightness();
  }
  
  max_brightness = 0;
  min_brightness = 2000;
  for (Firefly* firefly : all_fireflies){
    if (firefly->getLightIntensity() > max_brightness){
      max_brightness = firefly->getLightIntensity();
    }
    if (firefly->getLightIntensity() < min_brightness){
      min_brightness = firefly->getLightIntensity();
    }
  }

  for (Firefly* firefly : all_fireflies){
    //firefly->setLightIntensity((firefly->getLightIntensity() - min_brightness) / (max_brightness - min_brightness));
  }

  for (Firefly* firefly: all_fireflies){
    firefly->detectLight();
    firefly->update();
    firefly->draw(target);
  }

}

void firefly_sim::Firefly::updateBrightness(){
  //Case 1: 
  double value = std::abs(m_position.y - m_position.x) / 10;
  //Case 2: 
  //double value = std::abs(600 - m_position.y - m_position.x * 2) / 10; // 600 - y = 2x
  // Case 3:
  // double value = std::abs(300 + sin(2 * M_PI * ((int) m_position.x % 50) / 50) * 50 - m_position.y);
  if (value < 0){
    value = 0;
  }
  double ratio = std::exp(-value);
  if (ratio < 0){
    ratio = 0;
  } 
  m_firefly_light_intensity = ratio; 
}

void firefly_sim::Firefly::update(){

  // Position update
  double beta = attractiveness * std::exp(-gamma * std::pow(m_position || m_target_position,2));

  Position previous_pos = m_position;

  if (m_position.x + beta * (m_target_position.x - m_position.x) + alpha * (((double) (rand() % 1000))/ 1000.0 - 0.5) > 800){
    m_position.x -= beta * (m_target_position.x - m_position.x) + alpha * (((double) (rand() % 1000))/ 1000.0 - 0.5);
  }
  else if (m_position.x + beta * (m_target_position.x - m_position.x) + alpha * (((double) (rand() % 1000))/ 1000.0 - 0.5) < 0){
    m_position.x -= beta * (m_target_position.x - m_position.x) + alpha * (((double) (rand() % 1000))/ 1000.0 - 0.5);
  }
  else{
    m_position.x += beta * (m_target_position.x - m_position.x) + alpha * (((double) (rand() % 1000))/ 1000.0 - 0.5);
  }

  if (m_position.y + beta * (m_target_position.y - m_position.y) + alpha * (((double) (rand() % 1000))/ 1000.0 - 0.5) > 600){
    m_position.y -= beta * (m_target_position.y - m_position.y) + alpha * (((double) (rand() % 1000))/ 1000.0 - 0.5);
  }
  else if (m_position.y + beta * (m_target_position.y - m_position.y) + alpha * (((double) (rand() % 1000))/ 1000.0 - 0.5) < 0){
    m_position.y -= beta * (m_target_position.y - m_position.y) + alpha * (((double) (rand() % 1000))/ 1000.0 - 0.5);
  }
  else{
    m_position.y += beta * (m_target_position.y - m_position.y) + alpha * (((double) (rand() % 1000))/ 1000.0 - 0.5);
  }

  if ((previous_pos || m_position ) > 5.0){
    m_position = previous_pos + (m_position - previous_pos) / (m_position || previous_pos);
  }


  ///////////////////////////////////////////////////////////////////

  m_firefly_shiner_body = createGradientCircle_(m_size, colorBlend_("transparent", "FCF5ED", m_firefly_light_intensity), hex2Color_("FFCF96"));

  float radius = m_size * 6 / 5;
  int shine_layers = (int) (m_firefly_light_intensity * 100.0);
  float shineThickness = m_size * 2 / 5;
  sf::Color shineColor(255,255,255,40);

  // Create the shine layers (concentric circles with decreasing opacity)
  m_firefly_glow.clear();

  for (int i = 0; i < shine_layers; ++i) {
    sf::CircleShape shineCircle(radius + shineThickness * (i + 1));
    shineCircle.setFillColor(sf::Color::Transparent);
    shineCircle.setOutlineThickness(shineThickness);
    shineColor.a = static_cast<sf::Uint8>(shineColor.a * (1.0f - static_cast<float>(i) / shine_layers)); // Decrease alpha
    shineCircle.setOutlineColor(shineColor);
    shineCircle.setOrigin(radius + shineThickness * (i + 1), radius + shineThickness * (i + 1));
    shineCircle.setPosition(m_position.x, m_position.y);
    m_firefly_glow.push_back(shineCircle);
  }

  /////////////////////////////////////////////////////////////////////////////
}

void firefly_sim::Firefly::detectLight(){
  // B(r_ij) = B_0 * e^(-gamme * r_ij^2)
  int index_of_brightest = 0;
  double max_brightness = 0;
  double max_value = 0;
  for (int i = 0; i < all_fireflies.size(); i++){
    if (i != m_firefly_index && all_fireflies.at(i)->getLightIntensity() > 0.05){
      double brightness = all_fireflies.at(i)->getLightIntensity();
      target_brightness = attractiveness * std::exp(-gamma * std::pow(m_position || all_fireflies.at(i)->m_position, 2));
      if (target_brightness > max_value){
        index_of_brightest = i;
        max_brightness = target_brightness;
        max_value = target_brightness;
      }
    }
  }
  target_brightness = max_brightness;
  m_target_position = all_fireflies.at(index_of_brightest)->m_position;
}

void firefly_sim::Firefly::draw(sf::RenderTarget& target){
  sf::RenderStates states;
  states.transform.translate(m_position.x - m_size, m_position.y - m_size);
  target.draw(m_firefly_body, states);
  target.draw(m_firefly_shiner_body, states);
  for (auto &circle : m_firefly_glow){
    target.draw(circle);
  }
}

sf::Color firefly_sim::Firefly::hex2Color_(std::string hex){
  assert(hex.length() == 6);
  
  int red = std::stoi(hex.substr(0,2), nullptr, 16);
  int green = std::stoi(hex.substr(2,2), nullptr, 16);
  int blue = std::stoi(hex.substr(4,2), nullptr, 16);

  return sf::Color(red, green, blue);
}

sf::Color firefly_sim::Firefly::colorBlend_(std::string color1, std::string color2, double alpha){

  sf::Color colorA;
  sf::Color colorB;

  if (color1 == "transparent"){ colorA = sf::Color::Transparent; }
  else { colorA = hex2Color_(color1); }
    
  if (color2 == "transparent") { colorB = sf::Color::Transparent; }
  else { colorB = hex2Color_(color2); }

  sf::Color mixed_color = sf::Color(colorA.r * (1.0 - alpha) + colorB.r * alpha,
                                    colorA.g * (1.0 - alpha) + colorB.g * alpha,
                                    colorA.b * (1.0 - alpha) + colorB.b * alpha,
                                    colorA.a * (1.0 - alpha) + colorB.a * alpha);
  
  return mixed_color;
}

sf::VertexArray firefly_sim::Firefly::createGradientCircle_(float radius, const sf::Color& centerColor, const sf::Color& edgeColor) {
    sf::VertexArray vertices(sf::TriangleFan);
    // Center vertex
    vertices.append(sf::Vertex(sf::Vector2f(radius, radius), centerColor));
    // Circle vertices
    const int points = 100; // Number of triangles to form the circle
    for (int i = 0; i <= points; ++i) {
        float angle = (i * 2 * M_PI) / points;
        sf::Vector2f point(radius * cos(angle) + radius, radius * sin(angle) + radius);
        vertices.append(sf::Vertex(point, edgeColor));
    }
    return vertices;
}