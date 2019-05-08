#include <catch2/catch.hpp>

#include <aw/util/file/pathRegistry.hpp>

#include <string>

TEST_CASE("Test path registry functions")
{
  SECTION("Base paths should return true when checked")
  {
    REQUIRE(aw::path::isAsset(aw::path::asset()));
    REQUIRE(aw::path::isConfig(aw::path::config()));
    REQUIRE(aw::path::isInternal(aw::path::internal()));
  }

  SECTION("Check if create paths are valid")
  {
    REQUIRE(aw::path::isAsset(aw::path::asset("test.png")));
    REQUIRE(aw::path::isConfig(aw::path::config("test.png")));
    REQUIRE(aw::path::isInternal(aw::path::internal("test.png")));
  }

  SECTION("Check if invalids paths are not detected")
  {
    REQUIRE(!aw::path::isAsset("asfas"));
    REQUIRE(!aw::path::isConfig("asfasf"));
    REQUIRE(!aw::path::isInternal("asfaf"));
  }
}

