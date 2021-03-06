/*
 *
 * Copyright 2017 Asylo authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include "asylo/platform/common/time_util.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace asylo {

namespace {

const int64_t kNanosecondsPerMicrosecond = 1000;

// Test converting between time formats.
TEST(TimeTests, Conversions) {
  std::vector<int64_t> values = {
      1,          -1,          0,         1,           573291173,  1088178268,
      869064257,  -3989335159, 36916388,  -1908624439, 1824021628, -407955685,
      2324227069, -1827186485, INT64_MAX, INT64_MIN,
  };

  // Timespec tests.
  for (int64_t value : values) {
    struct timespec ts;
    NanosecondsToTimeSpec(&ts, value);
    EXPECT_EQ(TimeSpecToNanoseconds(&ts), value);
  }

  // Timeval tests.
  for (int64_t value : values) {
    struct timeval tv;
    NanosecondsToTimeVal(&tv, value);
    // TimeVal measures microseconds, so make our expectation precise to
    // microseconds.
    int64_t expectation = value - value % kNanosecondsPerMicrosecond;
    EXPECT_EQ(TimeValToNanoseconds(&tv), expectation);
  }
}

// Test of range checks.
TEST(TimeTests, Range) {
  for (int i = 0; i < 64; i++) {
    struct timespec ts;
    ts.tv_sec = INT64_C(1) << i;
    EXPECT_EQ(IsRepresentableAsNanoseconds(&ts), i < 34);
    ts.tv_sec *= -1;
    EXPECT_EQ(IsRepresentableAsNanoseconds(&ts), i < 34);
  }

  for (int i = 0; i < 64; i++) {
    struct timeval tv;
    tv.tv_sec = INT64_C(1) << i;
    EXPECT_EQ(IsRepresentableAsNanoseconds(&tv), i < 34);
    tv.tv_sec *= -1;
    EXPECT_EQ(IsRepresentableAsNanoseconds(&tv), i < 34);
  }
}

}  // namespace
}  // namespace asylo
