#include "gtest/gtest.h"
#include "buffer.h"
#include "config.h"


class QuickTest : public testing::Test {
 protected:
  // Remember that SetUp() is run immediately before a test starts.
  // This is a good place to record the start time.

  virtual void SetUp() {

  }
  virtual void TearDown() { }
};
