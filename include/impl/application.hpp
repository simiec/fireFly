#include "application.h"

firefly_sim::Application::Application(const int FPS, const int WIDTH, const int HEIGHT)
: WINDOW_WIDTH(WIDTH)
, WINDOW_HEIGHT(HEIGHT)
, m_fps(FPS)
, m_swarm_sample_count(200)
{
  m_frame = 0;
  m_paused = false;

  sf::ContextSettings settings;
  settings.antialiasingLevel = 16;

  m_background_color = hex2Color_("222831");

  m_window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Firefly Simulation", sf::Style::Default, settings);
  m_window.setFramerateLimit(m_fps);

  sf::View view = m_window.getDefaultView();
  view.setSize(view.getSize().x, -view.getSize().y);
  m_window.setView(view);

  for (int i = 0; i < m_swarm_sample_count; i++){
    swarm.push_back(new firefly_sim::Firefly(firefly_sim::Position((double) (rand() % 800), (double)(rand()%600))));
  }
}

firefly_sim::Application::~Application(){
  /* void */
}

void firefly_sim::Application::resetSimulator_(){
  for (auto &firefly : swarm){
    firefly->~Firefly();
  }
  swarm.clear();

  for (int i = 0; i < m_swarm_sample_count; i++){
    swarm.push_back(new firefly_sim::Firefly(firefly_sim::Position((double) (rand() % 800), (double)(rand()%600))));
  }
}

void firefly_sim::Application::update(){
  if(!m_paused){
    m_window.clear(m_background_color);
    backgroundDrawer_();
    Firefly::updateAll(m_window);
    eventHandler_();
  }
  else{
    eventHandler_();
    sf::Font font;
    if (!font.loadFromFile("/home/ugurcan/Desktop/pythonScripts/stateMachine/Gameplay.ttf")){
      std::cout << "Font Error!" << std::endl;
    }

    sf::Text text;
    text.setFont(font);
    text.setString("Paused");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    text.setPosition(WINDOW_WIDTH * 4/5, WINDOW_HEIGHT * 9 / 10);
    text.setScale(1.f, -1.f);
    m_window.draw(text);
  }
  m_window.display();
}

void firefly_sim::Application::eventHandler_(){
  sf::Event event;

  while (m_window.pollEvent(event)){
    if (event.type == sf::Event::Closed){
      m_window.close();
    }

    if (event.type == sf::Event::KeyPressed){
      // Check for 'Space' key pressed
      if (event.key.code == sf::Keyboard::Space){
        m_paused = !m_paused;
      }
      if (event.key.code == sf::Keyboard::Q){
        m_window.close();
      }
      if (event.key.code == sf::Keyboard::R){
        resetSimulator_();
      }
    }
  }
}

sf::RectangleShape firefly_sim::Application::getLine_(sf::Vector2f startPoint, sf::Vector2f endPoint, double lineThickness, std::string color, int alpha){
  float thickness = lineThickness;
  sf::Vector2f direction = endPoint - startPoint;
  float length = sqrt(direction.x * direction.x + direction.y * direction.y);
  direction /= length;

  sf::RectangleShape line(direction * length);
  line.setPosition(startPoint);
  sf::Color sf_color = hex2Color_(color);
  sf_color.a = alpha;
  line.setFillColor(sf_color);
  line.setSize(sf::Vector2f(length, thickness));
  line.setOrigin(0, thickness / 2);
  line.setRotation(atan2(direction.y, direction.x) * 180.0f / 3.14159265f);

  return line;
}

void firefly_sim::Application::backgroundDrawer_(){

  for (int i = 0; i < 800; i++){
    // Case 1
    // x = y
    
    sf::CircleShape circle(1);
    circle.setPosition(i, i);
    m_window.draw(circle);
    

    // Case 2
    // 600 - y = 2x
    /*
    sf::CircleShape circle(1);
    circle.setPosition((600 - i) / 2, i);
    m_window.draw(circle);
    */

    // Case 3: Sinus
    /*
    sf::CircleShape circle(1);
    circle.setPosition(i, 300 + sin(2 * M_PI * (i % 50) / 50) * 50);
    m_window.draw(circle);
    */
  }

  for (int i = -std::min(WINDOW_WIDTH,WINDOW_HEIGHT) / 10; i < std::max(WINDOW_WIDTH, WINDOW_HEIGHT) + 2 * std::min(WINDOW_WIDTH,WINDOW_HEIGHT) / 10; i+= std::min(WINDOW_WIDTH,WINDOW_HEIGHT) / 10){

    m_window.draw(getLine_(sf::Vector2f(i, -std::min(WINDOW_WIDTH,WINDOW_HEIGHT) / 10),sf::Vector2f(i, WINDOW_HEIGHT + std::min(WINDOW_WIDTH,WINDOW_HEIGHT) / 10), 2));
    m_window.draw(getLine_(sf::Vector2f(-std::min(WINDOW_WIDTH,WINDOW_HEIGHT) / 10, i), sf::Vector2f(WINDOW_WIDTH + std::min(WINDOW_WIDTH,WINDOW_HEIGHT) / 10, i), 2));

    m_window.draw(getLine_(sf::Vector2f(i + std::min(WINDOW_WIDTH,WINDOW_HEIGHT) / 20, -std::min(WINDOW_WIDTH,WINDOW_HEIGHT) / 10), sf::Vector2f(i + std::min(WINDOW_WIDTH,WINDOW_HEIGHT) / 20, WINDOW_HEIGHT + std::min(WINDOW_WIDTH,WINDOW_HEIGHT) / 10), 0.6));
    m_window.draw(getLine_(sf::Vector2f(-std::min(WINDOW_WIDTH,WINDOW_HEIGHT) / 10,i+std::min(WINDOW_WIDTH,WINDOW_HEIGHT) / 20), sf::Vector2f(WINDOW_WIDTH + std::min(WINDOW_WIDTH,WINDOW_HEIGHT) / 10 + std::min(WINDOW_WIDTH,WINDOW_HEIGHT) / 10,i+std::min(WINDOW_WIDTH,WINDOW_HEIGHT) / 20), 0.6));

    m_window.draw(getLine_(sf::Vector2f(i + std::min(WINDOW_WIDTH,WINDOW_HEIGHT) / 40, -std::min(WINDOW_WIDTH,WINDOW_HEIGHT) / 10), sf::Vector2f(i + std::min(WINDOW_WIDTH,WINDOW_HEIGHT) / 40, WINDOW_HEIGHT + std::min(WINDOW_WIDTH,WINDOW_HEIGHT) / 10), 0.2));
    m_window.draw(getLine_(sf::Vector2f(-std::min(WINDOW_WIDTH,WINDOW_HEIGHT) / 10,i+std::min(WINDOW_WIDTH,WINDOW_HEIGHT) / 40), sf::Vector2f(WINDOW_WIDTH + std::min(WINDOW_WIDTH,WINDOW_HEIGHT) / 10,i+std::min(WINDOW_WIDTH,WINDOW_HEIGHT) / 40), 0.2));

    m_window.draw(getLine_(sf::Vector2f(i + std::min(WINDOW_WIDTH,WINDOW_HEIGHT) * 3 / 40, -std::min(WINDOW_WIDTH,WINDOW_HEIGHT) / 10), sf::Vector2f(i + std::min(WINDOW_WIDTH,WINDOW_HEIGHT) * 3 / 40, WINDOW_HEIGHT + std::min(WINDOW_WIDTH,WINDOW_HEIGHT) / 10), 0.2));
    m_window.draw(getLine_(sf::Vector2f(-std::min(WINDOW_WIDTH,WINDOW_HEIGHT) / 10,i+std::min(WINDOW_WIDTH,WINDOW_HEIGHT) * 3 / 40), sf::Vector2f(WINDOW_WIDTH + std::min(WINDOW_WIDTH,WINDOW_HEIGHT) / 10,i+std::min(WINDOW_WIDTH,WINDOW_HEIGHT) * 3 / 40), 0.2));
  }
}

sf::Color firefly_sim::Application::hex2Color_(std::string hex){
  assert(hex.length() == 6);
  
  int red = std::stoi(hex.substr(0,2), nullptr, 16);
  int green = std::stoi(hex.substr(2,2), nullptr, 16);
  int blue = std::stoi(hex.substr(4,2), nullptr, 16);

  return sf::Color(red, green, blue);
}
