/*
 * Copyright (c) 2015 peeracle contributors
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "third_party/googletest/gtest/include/gtest/gtest.h"
#include "peeracle/DataStream/FileDataStream.h"
#include "peeracle/DataStream/MemoryDataStream.h"
#include "peeracle/Media/ISOBMFFMedia.h"

namespace peeracle {

namespace Media {

unsigned char _expectedInitBytes[] = {
  0x00, 0x00, 0x00, 0x24, 0x66, 0x74, 0x79, 0x70, 0x69, 0x73, 0x6f, 0x35,
  0x00, 0x00, 0x00, 0x01, 0x61, 0x76, 0x63, 0x31, 0x69, 0x73, 0x6f, 0x35,
  0x64, 0x73, 0x6d, 0x73, 0x6d, 0x73, 0x69, 0x78, 0x64, 0x61, 0x73, 0x68,
  0x00, 0x00, 0x00, 0x08, 0x66, 0x72, 0x65, 0x65, 0x00, 0x00, 0x00, 0x4a,
  0x66, 0x72, 0x65, 0x65, 0x49, 0x73, 0x6f, 0x4d, 0x65, 0x64, 0x69, 0x61,
  0x20, 0x46, 0x69, 0x6c, 0x65, 0x20, 0x50, 0x72, 0x6f, 0x64, 0x75, 0x63,
  0x65, 0x64, 0x20, 0x77, 0x69, 0x74, 0x68, 0x20, 0x47, 0x50, 0x41, 0x43,
  0x20, 0x30, 0x2e, 0x35, 0x2e, 0x32, 0x2d, 0x44, 0x45, 0x56, 0x2d, 0x72,
  0x65, 0x76, 0x33, 0x31, 0x33, 0x2d, 0x67, 0x33, 0x35, 0x62, 0x31, 0x36,
  0x62, 0x33, 0x2d, 0x6d, 0x61, 0x73, 0x74, 0x65, 0x72, 0x00, 0x00, 0x00,
  0x03, 0x39, 0x6d, 0x6f, 0x6f, 0x76, 0x00, 0x00, 0x00, 0x6c, 0x6d, 0x76,
  0x68, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x03, 0xe8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
  0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x48, 0x6d, 0x76,
  0x65, 0x78, 0x00, 0x00, 0x00, 0x10, 0x6d, 0x65, 0x68, 0x64, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x4e, 0x20, 0x00, 0x00, 0x00, 0x20, 0x74, 0x72,
  0x65, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
  0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x74, 0x72, 0x65, 0x70, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x02, 0x1b, 0x74, 0x72,
  0x61, 0x6b, 0x00, 0x00, 0x00, 0x5c, 0x74, 0x6b, 0x68, 0x64, 0x00, 0x00,
  0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0xd1, 0xdb, 0xc3, 0xe0, 0x00, 0x00,
  0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00,
  0x00, 0x00, 0x07, 0x7d, 0xc2, 0x77, 0x03, 0x58, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x24, 0x65, 0x64, 0x74, 0x73, 0x00, 0x00, 0x00, 0x1c, 0x65, 0x6c,
  0x73, 0x74, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
  0x01, 0x93, 0x6d, 0x64, 0x69, 0x61, 0x00, 0x00, 0x00, 0x20, 0x6d, 0x64,
  0x68, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x15, 0xc7,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x2d, 0x68, 0x64, 0x6c, 0x72, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x76, 0x69, 0x64, 0x65, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x56, 0x69,
  0x64, 0x65, 0x6f, 0x48, 0x61, 0x6e, 0x64, 0x6c, 0x65, 0x72, 0x00, 0x00,
  0x00, 0x01, 0x3e, 0x6d, 0x69, 0x6e, 0x66, 0x00, 0x00, 0x00, 0x14, 0x76,
  0x6d, 0x68, 0x64, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x64, 0x69, 0x6e, 0x66, 0x00,
  0x00, 0x00, 0x1c, 0x64, 0x72, 0x65, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x0c, 0x75, 0x72, 0x6c, 0x20, 0x00,
  0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xfe, 0x73, 0x74, 0x62, 0x6c, 0x00,
  0x00, 0x00, 0xb2, 0x73, 0x74, 0x73, 0x64, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0xa2, 0x61, 0x76, 0x63, 0x31, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07,
  0x80, 0x03, 0x58, 0x00, 0x48, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x18, 0xff, 0xff, 0x00, 0x00, 0x00, 0x10, 0x70, 0x61, 0x73,
  0x70, 0x00, 0x00, 0x03, 0x58, 0x00, 0x00, 0x03, 0x59, 0x00, 0x00, 0x00,
  0x3c, 0x61, 0x76, 0x63, 0x43, 0x01, 0x64, 0x00, 0x28, 0xff, 0xe1, 0x00,
  0x1f, 0x67, 0x64, 0x00, 0x28, 0xac, 0xd9, 0x40, 0x78, 0x06, 0xdf, 0x97,
  0xff, 0x03, 0x58, 0x03, 0x59, 0x10, 0x00, 0x00, 0x03, 0x00, 0x10, 0x00,
  0x00, 0x03, 0x03, 0x00, 0xf1, 0x83, 0x19, 0x60, 0x01, 0x00, 0x06, 0x68,
  0xeb, 0xe3, 0xcb, 0x22, 0xc0, 0xfc, 0xf8, 0xf8, 0x00, 0x00, 0x00, 0x00,
  0x10, 0x73, 0x74, 0x74, 0x73, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x10, 0x73, 0x74, 0x73, 0x63, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x73, 0x74, 0x73,
  0x7a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x10, 0x73, 0x74, 0x63, 0x6f, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x62, 0x75, 0x64, 0x74,
  0x61, 0x00, 0x00, 0x00, 0x5a, 0x6d, 0x65, 0x74, 0x61, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x21, 0x68, 0x64, 0x6c, 0x72, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x6d, 0x64, 0x69, 0x72, 0x61, 0x70, 0x70,
  0x6c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x2d, 0x69, 0x6c, 0x73, 0x74, 0x00, 0x00, 0x00, 0x25, 0xa9, 0x74,
  0x6f, 0x6f, 0x00, 0x00, 0x00, 0x1d, 0x64, 0x61, 0x74, 0x61, 0x00, 0x00,
  0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x4c, 0x61, 0x76, 0x66, 0x35, 0x36,
  0x2e, 0x33, 0x36, 0x2e, 0x31, 0x30, 0x30
};

unsigned int _expectedInitLength = 943;

class ISOBMFFMediaTest : public testing::Test {
 protected:
  ISOBMFFMediaTest() : _media(NULL), _ISOBMFFToTest(NULL) {
  }

  virtual void SetUp() {
    _media = new ISOBMFFMedia();
    _media->Load(NULL);
  }

  virtual void TearDown() {
    delete _media;
  }

  std::vector<uint32_t> _expectedTimecodes;

  ISOBMFFMedia *_media;
  DataStreamInterface *_ISOBMFFToTest;
};

TEST_F(ISOBMFFMediaTest, getInitSegment) {
  DataStreamInit actualDSInit;
  DataStreamInterface *actualDS = new MemoryDataStream(actualDSInit);

  uint8_t *actualBytes;

  _media->getInitSegment(actualDS);

  ASSERT_EQ(_expectedInitLength, actualDS->length());

  actualBytes = new uint8_t[actualDS->length()];
  actualDS->read(reinterpret_cast<char*>(actualBytes), actualDS->length());

  for (std::streamsize i = 0; i < _expectedInitLength; ++i) {
    EXPECT_EQ(_expectedInitBytes[i], actualBytes[i]);
  }

  delete actualBytes;
  delete actualDS;
}

TEST_F(ISOBMFFMediaTest, getMediaSegment) {
  std::stringstream filestrm;
  const std::vector<uint32_t> &actualTimecodes = _media->getTimecodes();

  ASSERT_EQ(_expectedTimecodes.size(), actualTimecodes.size());
  for (size_t i = 0; i < _expectedTimecodes.size(); ++i) {
    EXPECT_EQ(_expectedTimecodes[i], actualTimecodes[i]);
  }
}

}  // namespace Media

}  // namespace peeracle
