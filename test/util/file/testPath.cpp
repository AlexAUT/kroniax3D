#include <catch2/catch.hpp>

#include <aw/util/file/path.hpp>

#include <string>

TEST_CASE("Test valid paths")
{
  SECTION("Empty path")
  {
    auto path = "";
    REQUIRE(aw::filePath::fileName(path) == path);
    REQUIRE(aw::filePath::extension(path) == "");
    REQUIRE(aw::filePath::stem(path) == "");
    REQUIRE(aw::filePath::parentPath(path) == "");
    REQUIRE(!aw::filePath::isAbsolute(path));
    REQUIRE(aw::filePath::isRelative(path));
  }
  SECTION("Simple file without path")
  {
    auto path = "text.txt";
    REQUIRE(aw::filePath::fileName(path) == path);
    REQUIRE(aw::filePath::extension(path) == ".txt");
    REQUIRE(aw::filePath::stem(path) == "text");
    REQUIRE(aw::filePath::parentPath(path) == "");
    REQUIRE(!aw::filePath::isAbsolute(path));
    REQUIRE(aw::filePath::isRelative(path));
  }
  SECTION("Simple hidden file without path")
  {
    auto path = ".test.txt";
    REQUIRE(aw::filePath::fileName(path) == path);
    REQUIRE(aw::filePath::extension(path) == ".txt");
    REQUIRE(aw::filePath::stem(path) == ".test");
    REQUIRE(aw::filePath::parentPath(path) == "");
    REQUIRE(!aw::filePath::isAbsolute(path));
    REQUIRE(aw::filePath::isRelative(path));
  }
  SECTION("Just a point")
  {
    auto path = ".";
    REQUIRE(aw::filePath::fileName(path) == path);
    REQUIRE(aw::filePath::extension(path) == "");
    REQUIRE(aw::filePath::stem(path) == ".");
    REQUIRE(aw::filePath::parentPath(path) == "");
    REQUIRE(!aw::filePath::isAbsolute(path));
    REQUIRE(aw::filePath::isRelative(path));
  }
  SECTION("Two points")
  {
    auto path = "..";
    REQUIRE(aw::filePath::fileName(path) == path);
    REQUIRE(aw::filePath::extension(path) == "");
    REQUIRE(aw::filePath::stem(path) == "..");
    REQUIRE(aw::filePath::parentPath(path) == "");
    REQUIRE(!aw::filePath::isAbsolute(path));
    REQUIRE(aw::filePath::isRelative(path));
  }
  SECTION("Relative path")
  {
    auto path = "test/foo/bar.txt";
    REQUIRE(aw::filePath::fileName(path) == "bar.txt");
    REQUIRE(aw::filePath::extension(path) == ".txt");
    REQUIRE(aw::filePath::stem(path) == "bar");
    REQUIRE(aw::filePath::parentPath(path) == "test/foo");
    REQUIRE(!aw::filePath::isAbsolute(path));
    REQUIRE(aw::filePath::isRelative(path));
  }
  SECTION("Relative path with hidden file")
  {
    auto path = "test/foo/.bar.txt";
    REQUIRE(aw::filePath::fileName(path) == ".bar.txt");
    REQUIRE(aw::filePath::extension(path) == ".txt");
    REQUIRE(aw::filePath::stem(path) == ".bar");
    REQUIRE(aw::filePath::parentPath(path) == "test/foo");
    REQUIRE(!aw::filePath::isAbsolute(path));
    REQUIRE(aw::filePath::isRelative(path));
  }
  SECTION("Absolute path")
  {
    auto path = "/test/foo/bar.txt";
    REQUIRE(aw::filePath::fileName(path) == "bar.txt");
    REQUIRE(aw::filePath::extension(path) == ".txt");
    REQUIRE(aw::filePath::stem(path) == "bar");
    REQUIRE(aw::filePath::parentPath(path) == "/test/foo");
    REQUIRE(aw::filePath::isAbsolute(path));
    REQUIRE(!aw::filePath::isRelative(path));
  }
  SECTION("Absolute path with hidden file")
  {
    auto path = "/test/foo/.bar.txt";
    REQUIRE(aw::filePath::fileName(path) == ".bar.txt");
    REQUIRE(aw::filePath::extension(path) == ".txt");
    REQUIRE(aw::filePath::stem(path) == ".bar");
    REQUIRE(aw::filePath::parentPath(path) == "/test/foo");
    REQUIRE(aw::filePath::isAbsolute(path));
    REQUIRE(!aw::filePath::isRelative(path));
  }
  SECTION("File with multiple points")
  {
    auto path = ".test.foo.bar.txt";
    REQUIRE(aw::filePath::fileName(path) == path);
    REQUIRE(aw::filePath::extension(path) == ".txt");
    REQUIRE(aw::filePath::stem(path) == ".test.foo.bar");
    REQUIRE(aw::filePath::parentPath(path) == "");
    REQUIRE(!aw::filePath::isAbsolute(path));
    REQUIRE(aw::filePath::isRelative(path));
  }
  SECTION("Relative path with file with multiple dots")
  {
    auto path = "test/foo/.bar.foo.bar.txt";
    REQUIRE(aw::filePath::fileName(path) == ".bar.foo.bar.txt");
    REQUIRE(aw::filePath::extension(path) == ".txt");
    REQUIRE(aw::filePath::stem(path) == ".bar.foo.bar");
    REQUIRE(aw::filePath::parentPath(path) == "test/foo");
    REQUIRE(!aw::filePath::isAbsolute(path));
    REQUIRE(aw::filePath::isRelative(path));
  }
  SECTION("Absolute path with file with multiple dots")
  {
    auto path = "/test/foo/bar.foo.bar.txt";
    REQUIRE(aw::filePath::fileName(path) == "bar.foo.bar.txt");
    REQUIRE(aw::filePath::extension(path) == ".txt");
    REQUIRE(aw::filePath::stem(path) == "bar.foo.bar");
    REQUIRE(aw::filePath::parentPath(path) == "/test/foo");
    REQUIRE(aw::filePath::isAbsolute(path));
    REQUIRE(!aw::filePath::isRelative(path));
  }
}

