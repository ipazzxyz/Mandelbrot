#include "app.hpp"

#include <iostream>

#include "complex.hpp"

App::App()
    : window_size_(window_height_, window_width_),
      window_(sf::VideoMode(window_height_, window_width_), "Mandelbrot",
              sf::Style::None) {
  Setup();
  Run();
}
void App::Setup() {
  views_.emplace(sf::Vector2f(8, 4.5));
  views_.top().setPosition(-4, -2.25);
  selection_.setFillColor(sf::Color(0, 0, 255, 100));
  selection_.setOutlineThickness(1);
  selection_.setOutlineColor(sf::Color(0, 0, 255));
  CalculateFractal();
}
void App::Run() {
  Render();
  while (window_.isOpen()) {
    Loop();
  };
}
void App::Loop() {
  HandleEvents();
  RenderSelection();
}
void App::HandleEvents() {
  sf::Event event;
  while (window_.pollEvent(event)) {
    HandleEvent(event);
  }
}
void App::HandleEvent(const sf::Event& event) {
  if (event.type == sf::Event::KeyPressed) {
    HandleKeyPress(event.key);
    return;
  }
  if (event.type == sf::Event::MouseButtonPressed) {
    HandleMousePress(event.mouseButton);
    return;
  }
}
void App::HandleKeyPress(const sf::Event::KeyEvent& key) {
  if (key.code == sf::Keyboard::Escape) {
    window_.close();
    return;
  }
  if (key.code == sf::Keyboard::Space) {
    if (selecting_) {
      selecting_ = false;
      Render();
      return;
    }
    if (views_.size() > 1) {
      views_.pop();
      RenderFractal();
    }
    return;
  }
  if (key.code == sf::Keyboard::LShift) {
    accurate_ = !accurate_;
    return;
  }
}
void App::HandleMousePress(const sf::Event::MouseButtonEvent& mouse) {
  if (selecting_) {
    selecting_ = false;
    CalculateView();
    return;
  }
  selecting_ = true;
  selection_.setPosition(sf::Vector2f(mouse.x, mouse.y));
}
void App::RenderSelection() {
  CalculateSelection();
  Render();
}
void App::CalculateSelection() {
  sf::Vector2i mouse = sf::Mouse::getPosition(window_);
  if (accurate_) {
    selection_.setSize(sf::Vector2f(
        mouse.x - selection_.getPosition().x,
        (mouse.y < selection_.getPosition().y ? -1 : 1) *
            std::abs(mouse.x - selection_.getPosition().x) * 9 / 16.));
    return;
  }
  selection_.setSize(sf::Vector2f(mouse.x - selection_.getPosition().x,
                                  mouse.y - selection_.getPosition().y));
}
void App::PreRender() {
  window_.clear(sf::Color::Black);
  window_.draw(fractal_);
  window_.display();
}
void App::Render() {
  window_.clear(sf::Color::Black);
  window_.draw(fractal_);
  if (selecting_) {
    window_.draw(selection_);
  }
  window_.display();
}
void App::RenderFractal() {
  PreRender();
  CalculateFractal();
  Render();
}
void App::CalculateFractal() {
  img_.create(window_height_, window_width_);
  for (int x = 0; x < window_height_; ++x) {
    for (int y = 0; y < window_width_; ++y) {
      float res = Check(views_.top().getPosition().x +
                            x / static_cast<double>(window_height_) *
                                views_.top().getSize().x,
                        views_.top().getPosition().y +
                            y / static_cast<double>(window_width_) *
                                views_.top().getSize().y);
      if (res > 0) {
        img_.setPixel(x, y, sf::Color(255, 0, 255, res * 255));
      }
    }
  }
  texture_.loadFromImage(std::move(img_));
  fractal_.setScale(1, 1);
  fractal_.setPosition(0, 0);
  fractal_.setTexture(texture_);
}
float App::Check(const double& x, const double& y) {
  Complex z, c(x, y);
  for (int i = 1; i <= n_; ++i) {
    z = z * z + c;
    if (z.a * z.a + z.b * z.b > 4) {
      return i / static_cast<float>(n_);
    }
  }
  return 0;
}
void App::CalculateView() {
  sf::RectangleShape new_view(
      sf::Vector2f(selection_.getSize().x / static_cast<float>(window_height_) *
                       views_.top().getSize().x,
                   selection_.getSize().y / static_cast<float>(window_width_) *
                       views_.top().getSize().y));
  new_view.setPosition(sf::Vector2f(selection_.getPosition().x /
                                        static_cast<float>(window_height_) *
                                        views_.top().getSize().x,
                                    selection_.getPosition().y /
                                        static_cast<float>(window_width_) *
                                        views_.top().getSize().y) +
                       views_.top().getPosition());
  views_.push(new_view);
  RenderFractal();
}