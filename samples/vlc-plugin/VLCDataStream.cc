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

#include <cstring>
#include <sstream>
#include "samples/vlc-plugin/VLCDataStream.h"
#include "samples/vlc-plugin/plugin.h"

VLCDataStream::VLCDataStream(stream_t *stream) : _stream(stream),
                                                 _bigEndian(true) {
}

bool VLCDataStream::open() {
  return true;
}

void VLCDataStream::close() {
  stream_Delete(this->_stream);
}

std::streamsize VLCDataStream::length() const {
  return static_cast<std::streamsize>(stream_Size(this->_stream));
}

std::streamsize VLCDataStream::seek(std::streamsize offset) {
  return stream_Seek(this->_stream, static_cast<uint64_t>(offset));
}

std::streamsize VLCDataStream::tell() const {
  return static_cast<std::streamsize>(stream_Tell(this->_stream));
}

std::streamsize VLCDataStream::read(char *buffer,
                                    std::streamsize length) {
  return stream_Read(this->_stream, buffer, static_cast<int>(length));
}

std::streamsize VLCDataStream::read(int8_t *buffer) {
  return _read(buffer);
}

std::streamsize VLCDataStream::read(uint8_t *buffer) {
  return _read(buffer);
}

std::streamsize VLCDataStream::read(int16_t *buffer) {
  return _read(buffer);
}

std::streamsize VLCDataStream::read(uint16_t *buffer) {
  return _read(buffer);
}

std::streamsize VLCDataStream::read(int32_t *buffer) {
  return _read(buffer);
}

std::streamsize VLCDataStream::read(uint32_t *buffer) {
  return _read(buffer);
}

std::streamsize VLCDataStream::read(float *buffer) {
  return _read(buffer);
}

std::streamsize VLCDataStream::read(double *buffer) {
  return _read(buffer);
}

std::streamsize VLCDataStream::read(std::string *buffer) {
  int8_t c;
  std::streamsize i;
  std::stringstream strm;

  for (i = 0; i < 32768; ++i) {
    if (this->_read(&c) < 1 || c == '\0') {
      break;
    }
    strm << c;
  }

  *buffer = strm.str();
  return i;
}

template <typename T>
std::streamsize VLCDataStream::_read(T *buffer) {
  T value;
  T finalValue;
  uint8_t *originalData;
  uint8_t *finalData;
  int ret;

  ret = stream_Read(this->_stream, &value, sizeof(T));
  if (_bigEndian && sizeof(T) > 1) {
    originalData = reinterpret_cast<uint8_t*>(&value);
    finalData = reinterpret_cast<uint8_t*>(&finalValue);
    for (int i = 0; i < sizeof(T); ++i) {
      finalData[i] = originalData[(sizeof(T) - i) - 1];
    }
    value = finalValue;
  }

  *buffer = value;
  return sizeof(T);
}

std::streamsize VLCDataStream::peek(uint8_t *buffer, std::streamsize length) {
  int ret;
  const uint8_t *peek;

  ret = stream_Peek(this->_stream, &peek, static_cast<int>(length));
  memcpy(buffer, peek, static_cast<size_t>(length));
  return ret;
}

std::streamsize VLCDataStream::peek(int8_t *buffer) {
  return _peek(buffer);
}

std::streamsize VLCDataStream::peek(uint8_t *buffer) {
  return _peek(buffer);
}

std::streamsize VLCDataStream::peek(int16_t *buffer) {
  return _peek(buffer);
}

std::streamsize VLCDataStream::peek(uint16_t *buffer) {
  return _peek(buffer);
}

std::streamsize VLCDataStream::peek(int32_t *buffer) {
  return _peek(buffer);
}

std::streamsize VLCDataStream::peek(uint32_t *buffer) {
  return _peek(buffer);
}

std::streamsize VLCDataStream::peek(float *buffer) {
  return _peek(buffer);
}

std::streamsize VLCDataStream::peek(double *buffer) {
  return _peek(buffer);
}

std::streamsize VLCDataStream::peek(std::string *buffer) {
  return 0;
}

template <typename T>
std::streamsize VLCDataStream::_peek(T *buffer) {
  T value;
  T finalValue;
  uint8_t *originalData;
  uint8_t *finalData;
  int ret;
  const uint8_t *peek;

  ret = stream_Peek(this->_stream, &peek, sizeof(T));
  value = *peek;
  if (_bigEndian && sizeof(T) > 1) {
    originalData = reinterpret_cast<uint8_t*>(&value);
    finalData = reinterpret_cast<uint8_t*>(&finalValue);
    for (int i = 0; i < sizeof(T); ++i) {
      finalData[i] = originalData[(sizeof(T) - i) - 1];
    }
    value = finalValue;
  }

  *buffer = value;
  return sizeof(T);
}

std::streamsize VLCDataStream::write(const char *buffer,
                                     std::streamsize length) {
  return 0;
}

std::streamsize VLCDataStream::write(int8_t value) {
  return 0;
}

std::streamsize VLCDataStream::write(uint8_t value) {
  return 0;
}

std::streamsize VLCDataStream::write(int16_t value) {
  return 0;
}

std::streamsize VLCDataStream::write(uint16_t value) {
  return 0;
}

std::streamsize VLCDataStream::write(int32_t value) {
  return 0;
}

std::streamsize VLCDataStream::write(uint32_t value) {
  return 0;
}

std::streamsize VLCDataStream::write(float value) {
  return 0;
}

std::streamsize VLCDataStream::write(double value) {
  return 0;
}

std::streamsize VLCDataStream::write(const std::string &value) {
  return 0;
}
