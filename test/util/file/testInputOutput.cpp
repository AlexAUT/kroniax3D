#include <catch2/catch.hpp>

#include <aw/util/file/inputStream.hpp>
#include <aw/util/file/outputStream.hpp>
#include <aw/util/file/path.hpp>
#include <aw/util/file/pathRegistry.hpp>

// Just simple tests, because we are basically just testing fstream
TEST_CASE("Test file input output streams")
{
  SECTION("Read written file")
  {
    auto path = "./test.txt";
    {
      aw::file::OutputStream output(path);
      REQUIRE(output.isOpen());
      output << 1 << 2 << 3 << 4 << std::endl;
    }

    {
      aw::file::InputStream input(path);
      REQUIRE(input.isOpen());
      int read;
      input >> read;
      REQUIRE(read == 1234);
    }
  }
}
