#include <catch2/catch.hpp>

#include <aw/util/message/bus.hpp>

#include <string>

struct MessageA
{
  std::string msg;
};

struct MessageB
{
  std::string msg;
};

TEST_CASE("Message bus")
{
  aw::msg::Bus bus;
  bus.channel<MessageA>().broadcast(MessageA{"Hallo"});

  SECTION("One receiver")
  {
    INFO("Check if subscription safely works");
    MessageA message{"Message1"};
    MessageA received;
    {
      auto sub = bus.channel<MessageA>().subscribe([&](const auto& msg) { received = msg; });
      bus.channel<MessageA>().broadcast(message);
      CHECK(received.msg == message.msg);
    }
    received.msg = "";
    REQUIRE(received.msg != message.msg);
    bus.channel<MessageA>().broadcast(message);
    INFO("Check if unsubscribe works on destructor");
    CHECK(received.msg != message.msg);
  }

  SECTION("Multiple message types")
  {
    MessageA messageA{"A"};
    MessageB messageB{"B"};
    MessageA recA;
    MessageB recB;
    {
      auto subA = bus.channel<MessageA>().subscribe([&](const auto& msg) { recA = msg; });
      {
        auto subB = bus.channel<MessageB>().subscribe([&](const auto& msg) { recB = msg; });
        bus.channel<MessageA>().broadcast(messageA);
        bus.channel<MessageB>().broadcast(messageB);
        CHECK(recA.msg == messageA.msg);
        CHECK(recB.msg == messageB.msg);
      }
      recA.msg = "";
      recB.msg = "";
      bus.channel<MessageA>().broadcast(messageA);
      bus.channel<MessageB>().broadcast(messageB);
      CHECK(recA.msg == messageA.msg);
      CHECK(recB.msg != messageB.msg);
    }
    recA.msg = "";
    recB.msg = "";
    bus.channel<MessageA>().broadcast(messageA);
    bus.channel<MessageB>().broadcast(messageB);
    CHECK(recA.msg != messageA.msg);
    CHECK(recB.msg != messageB.msg);
  }

  SECTION("Test out of order messages")
  {
    MessageA messageA{"A"};
    MessageB messageB{"B"};
    MessageA recA;
    MessageB recB;
    aw::msg::Bus bus2;
    auto subB = bus2.channel<MessageB>().subscribe([&](const auto& msg) { recB = msg; });
    bus2.channel<MessageB>().broadcast(messageB);
    CHECK(recB.msg == messageB.msg);

    bus2.channel<MessageA>().broadcast(messageA);
    auto subA = bus2.channel<MessageA>().subscribe([&](const auto& msg) { recA = msg; });
    bus2.channel<MessageA>().broadcast(messageA);

    CHECK(recA.msg == messageA.msg);
  }
}
