/*
 * Copyright (c) 2014-2016, Siemens AG. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <embb/containers/lock_free_tree_value_pool.h>
#include <embb/containers/wait_free_array_value_pool.h>
#include <embb/containers/wait_free_spsc_queue.h>
#include <embb/containers/object_pool.h>
#include <embb/containers/lock_free_stack.h>
#include <embb/containers/blocking_stack.h>
#include <embb/containers/lock_free_mpmc_queue.h>
#include <embb/containers/blocking_queue.h>
#include <embb/containers/blocking_priority_queue.h>
#include <embb/containers/blocking_set.h>
#include <embb/containers/blocking_map.h>
#include <embb/base/c/memory_allocation.h>

#include <partest/partest.h>
#include <embb/base/thread.h>

#include "./pool_test.h"
#include "./queue_test.h"
#include "./blocking_queue_test.h"
#include "./stack_test.h"
#include "./blocking_stack_test.h"
#include "./hazard_pointer_test.h"
#include "./object_pool_test.h"
#include "./set_test.h"
#include "./map_test.h"

#define COMMA ,

using embb::containers::WaitFreeArrayValuePool;
using embb::containers::LockFreeTreeValuePool;
using embb::containers::WaitFreeSPSCQueue;
using embb::containers::LockFreeMPMCQueue;
using embb::containers::BlockingQueue;
using embb::containers::BlockingPriorityQueue;
using embb::containers::LockFreeStack;
using embb::containers::BlockingStack;
using embb::containers::LockFreeTreeValuePool;
using embb::containers::WaitFreeArrayValuePool;
using embb::containers::BlockingSet;
using embb::containers::BlockingMap;
using embb::containers::test::PoolTest;
using embb::containers::test::HazardPointerTest;
using embb::containers::test::QueueTest;
using embb::containers::test::BlockingQueueTest;
using embb::containers::test::StackTest;
using embb::containers::test::BlockingStackTest;
using embb::containers::test::SetTest;
using embb::containers::test::ObjectPoolTest;
using embb::containers::test::HazardPointerTest2;
using embb::containers::test::MapTest;

PT_MAIN("Data Structures C++") {
  unsigned int max_threads = static_cast<unsigned int>(
    2 * partest::TestSuite::GetDefaultNumThreads());
  embb_thread_set_max_count(max_threads);
  PT_RUN(PoolTest< WaitFreeArrayValuePool<int COMMA -1> >);
  PT_RUN(PoolTest< LockFreeTreeValuePool<int COMMA -1> >);
  PT_RUN(HazardPointerTest);
  PT_RUN(HazardPointerTest2);
  PT_RUN(QueueTest< WaitFreeSPSCQueue< ::std::pair<size_t COMMA int> > >);
  PT_RUN(QueueTest< LockFreeMPMCQueue< ::std::pair<size_t COMMA int> >
    COMMA true COMMA true >);
  PT_RUN(BlockingQueueTest< BlockingQueue<int> >);
  PT_RUN(BlockingQueueTest< BlockingPriorityQueue<int> >);
  PT_RUN(StackTest< LockFreeStack<int> >);
  PT_RUN(BlockingStackTest< BlockingStack<int> >);
  PT_RUN(SetTest< BlockingSet<int> >);
  PT_RUN(MapTest<BlockingMap<int COMMA int> >);
  PT_RUN(ObjectPoolTest< LockFreeTreeValuePool<bool COMMA false > >);
  PT_RUN(ObjectPoolTest< WaitFreeArrayValuePool<bool COMMA false> >);
  PT_EXPECT(embb_get_bytes_allocated() == 0);
}
