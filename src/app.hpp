#pragma once

#include <SFML/Graphics.hpp>
#include <stack>

class App {
 public:
  App();
  App(int, double, double);

  static constexpr int window_height = 1440, window_width = 810, n = 100;

 private:
  sf::RenderWindow window_;
  std::stack<sf::RectangleShape> views_;
  bool selecting_, accurate_, mandelbrot_;
  sf::RectangleShape selection_;
  sf::Texture texture_;
  sf::Sprite fractal_;
  sf::Image img_;
  int p_;
  double a_, b_;

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
  virtual float Check(const double& x, const double& y);
};