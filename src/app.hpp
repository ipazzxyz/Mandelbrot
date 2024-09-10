#pragma once

#include <SFML/Graphics.hpp>
#include <stack>

class App {
 public:
  App();

 private:
  static constexpr int window_height_ = 1440, window_width_ = 810, n_ = 100;

  sf::RenderWindow window_;
  std::stack<sf::RectangleShape> views_;
  bool selecting_ = false, accurate_ = true;
  sf::RectangleShape selection_;
  sf::Texture texture_;
  sf::Sprite fractal_;
  sf::Image img_;

  void Setup();
  void Run();
  void Loop();
  void HandleEvents();
  void HandleEvent(const sf::Event&);
  void HandleKeyPress(const sf::Event::KeyEvent&);
  void HandleMousePress(const sf::Event::MouseButtonEvent&);
  void RenderSelection();
  void RenderFractal();
  void Render();
  void PreRender();
  void CalculateView();
  void CalculateFractal();
  void CalculateSelection();
  float Check(const double& x, const double& y);
};