#include <catch2/catch.hpp>

#include <aw/util/containers/ringBuffer.hpp>

TEST_CASE("Ring buffer put/get")
{
  constexpr unsigned size = 5;
  aw::RingBuffer<int, size> buffer;

  SECTION("Size inserts and gets")
  {
    for (unsigned i = 0; i < size; i++)
      buffer.put(i);

    REQUIRE(buffer.full());

    for (unsigned i = 0; i < 5; i++)
    {
      REQUIRE(!buffer.empty());
      REQUIRE(buffer.get() == i);
    }
    REQUIRE(buffer.empty());
  }
}

TEST_CASE("Ring buffer tryPut")
{
  constexpr unsigned size = 5;
  aw::RingBuffer<int, size> buffer;

  SECTION("Size inserts and gets")
  {
    for (unsigned i = 0; i < size; i++)
    {
      auto inserted = buffer.tryPut(i);
      REQUIRE(inserted);
    }
    REQUIRE(!buffer.tryPut(6));

    for (unsigned i = 0; i < 5; i++)
    {
      REQUIRE(!buffer.empty());
      REQUIRE(buffer.get() == i);
    }
    REQUIRE(buffer.empty());
  }
}

TEST_CASE("Ring buffer empty/full")
{
  constexpr auto size = 5;
  aw::RingBuffer<int, size> buffer;

  SECTION("Adding element should make read available")
  {
    REQUIRE(buffer.empty());
    buffer.put(1);
    REQUIRE(!buffer.empty());
  }
  SECTION("Adding elements should make read available")
  {
    REQUIRE(buffer.empty());
    for (int i = 0; i < size; i++)
    {
      buffer.put(1);
      REQUIRE(!buffer.empty());
    }
  }
  SECTION("Reading last element should make read unavailable")
  {
    buffer.put(1);
    REQUIRE(!buffer.empty());
    [[maybe_unused]] auto temp = buffer.get();
    REQUIRE(buffer.empty());
  }
  SECTION("Adding size elements should make the buffer full")
  {
    for (int i = 0; i < size; i++)
    {
      REQUIRE(!buffer.full());
      buffer.put(i);
    }

    REQUIRE(buffer.full());
  }
}

TEST_CASE("Ringbuffer partial fill and read")
{
  constexpr auto size = 10;
  aw::RingBuffer<int, size> buffer;

  for (int i = 0; i < 5; i++)
  {
    buffer.put(i);
    REQUIRE(!buffer.empty());
    REQUIRE(!buffer.full());
  }

  for (int i = 0; i < 3; i++)
  {
    REQUIRE(!buffer.empty());
    REQUIRE(buffer.get() == i);
    REQUIRE(!buffer.full());
  }

  for (int i = 5; i < 9; i++)
  {
    buffer.put(i);
    REQUIRE(!buffer.empty());
    REQUIRE(!buffer.full());
  }

  for (int i = 3; i < 9; i++)
  {
    REQUIRE(!buffer.empty());
    REQUIRE(buffer.get() == i);
    REQUIRE(!buffer.full());
  }

  REQUIRE(buffer.empty());
  REQUIRE(!buffer.full());
}
