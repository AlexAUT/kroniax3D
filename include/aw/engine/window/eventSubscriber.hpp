#pragma once

#include <aw/engine/window/event.hpp>
#include <aw/util/message/subscriber.hpp>

namespace aw::engine
{
class WindowEventSubscriber
    : public aw::msg::Subscriber<WindowEventSubscriber, windowEvent::Closed, windowEvent::Resized,
                                 windowEvent::GainedFocus, windowEvent::LostFocus,
                                 windowEvent::MouseMoved, windowEvent::MouseButtonPressed,
                                 windowEvent::MouseButtonReleased, windowEvent::MouseWheelScrolled>
{
public:
  WindowEventSubscriber(aw::msg::Bus& bus) : Subscriber(bus) {}

  virtual void receive(const windowEvent::Closed& event) {}
  virtual void receive(const windowEvent::Resized& event) {}
  virtual void receive(const windowEvent::GainedFocus& event) {}
  virtual void receive(const windowEvent::LostFocus& event) {}
  virtual void receive(const windowEvent::MouseMoved& event) {}
  virtual void receive(const windowEvent::MouseButtonPressed& event) {}
  virtual void receive(const windowEvent::MouseButtonReleased& event) {}
  virtual void receive(const windowEvent::MouseWheelScrolled& event) {}
};
} // namespace aw::engine
