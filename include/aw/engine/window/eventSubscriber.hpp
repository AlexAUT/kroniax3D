#pragma once

#include <aw/engine/window/event.hpp>
#include <aw/util/message/subscriber.hpp>

namespace aw::engine
{
class WindowEventSubscriber
    : public aw::msg::Subscriber<WindowEventSubscriber, windowEvent::Closed, windowEvent::Resized,
                                 windowEvent::GainedFocus, windowEvent::LostFocus>
{
public:
  WindowEventSubscriber(aw::msg::Bus& bus) : Subscriber(bus) {}

  virtual void receive(const windowEvent::Closed& event) {}
  virtual void receive(const windowEvent::Resized& event) {}
  virtual void receive(const windowEvent::GainedFocus& event) {}
  virtual void receive(const windowEvent::LostFocus& event) {}
};
} // namespace aw::engine
