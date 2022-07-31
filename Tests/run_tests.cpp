#include "gtest/gtest.h"
#include "Sha256_test.h"
#include "Key_test.h"
#include "Signature_test.h"

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}