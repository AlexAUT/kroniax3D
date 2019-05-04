#pragma once

#include <atomic>
#include <cassert>
#include <utility>

namespace aw
{
class RingBufferController
{
public:
  RingBufferController(unsigned size);

  unsigned reader() const;
  unsigned writer() const;

  unsigned increaseReader();
  unsigned increateWriter();

  bool empty() const;
  bool full() const;

private:
  unsigned mSize;
  unsigned mReadLocation{0};
  unsigned mWriteLocation{0};
  bool mFull{false};
};

// Simple one consumer on producer lock free ringbuffer
template <typename DataType, unsigned size>
class RingBuffer
{
public:
  // Will put data into the ringbuffer, if there is no space it will override the current reader and delete all not
  // queried data
  void put(const DataType& obj);
  void put(DataType&& obj);

  // This will only insert data if there is space before the reader.
  bool tryPut(const DataType& obj);
  bool tryPut(DataType&& obj);

  DataType get();

  bool empty() const;
  bool full() const;

private:
private:
  DataType mBuffer[size];
  RingBufferController mState{size};
};
} // namespace aw

// Implementation
namespace aw
{
inline RingBufferController::RingBufferController(unsigned size) : mSize{size} {}

inline unsigned RingBufferController::reader() const
{
  return mReadLocation;
}

inline unsigned RingBufferController::writer() const
{
  return mWriteLocation;
}

inline unsigned RingBufferController::increaseReader()
{
  mReadLocation = (mReadLocation != mSize - 1) ? mReadLocation + 1 : 0;
  mFull = false;
  return mReadLocation;
}

inline unsigned RingBufferController::increateWriter()
{
  assert(!mFull);
  mWriteLocation = (mWriteLocation != mSize - 1) ? mWriteLocation + 1 : 0;
  if (mWriteLocation == mReadLocation)
    mFull = true;
  return mWriteLocation;
}

inline bool RingBufferController::full() const
{
  return mFull;
}

inline bool RingBufferController::empty() const
{
  return mReadLocation == mWriteLocation && !full();
}

template <typename DataType, unsigned size>
void RingBuffer<DataType, size>::put(const DataType& obj)
{
  mBuffer[mState.writer()] = obj;
  std::atomic_thread_fence(std::memory_order_seq_cst);
  mState.increateWriter();
}

template <typename DataType, unsigned size>
void RingBuffer<DataType, size>::put(DataType&& obj)
{
  mBuffer[mState.writer()] = std::move(obj);
  std::atomic_thread_fence(std::memory_order_seq_cst);
  mState.increateWriter();
}

template <typename DataType, unsigned size>
bool RingBuffer<DataType, size>::tryPut(const DataType& obj)
{
  if (mState.full())
    return false;

  mBuffer[mState.writer()] = obj;
  std::atomic_thread_fence(std::memory_order_seq_cst);
  mState.increateWriter();
  return true;
}

template <typename DataType, unsigned size>
bool RingBuffer<DataType, size>::tryPut(DataType&& obj)
{
  if (mState.full())
    return false;

  mBuffer[mState.writer()] = std::move(obj);
  std::atomic_thread_fence(std::memory_order_seq_cst);
  mState.increateWriter();
  return true;
}

template <typename DataType, unsigned size>
DataType RingBuffer<DataType, size>::get()
{
  assert(!mState.empty());
  auto returnValue = std::move(mBuffer[mState.reader()]);
  std::atomic_thread_fence(std::memory_order_seq_cst);
  mState.increaseReader();
  return returnValue;
}

template <typename DataType, unsigned size>
bool RingBuffer<DataType, size>::full() const
{
  return mState.full();
}

template <typename DataType, unsigned size>
bool RingBuffer<DataType, size>::empty() const
{
  return mState.empty();
}

} // namespace aw
