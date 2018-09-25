#include <iostream>
#include <random>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>
#include <boost/accumulators/framework/accumulator_set.hpp>
#include <boost/accumulators/statistics/extended_p_square.hpp>
#include <boost/array.hpp>

#include <folly/Memory.h>
#include <folly/executors/GlobalExecutor.h>
#include <folly/executors/CPUThreadPoolExecutor.h>
#include <folly/init/Init.h>
#include <folly/io/async/EventBase.h>
#include <folly/io/async/EventBaseManager.h>
#include <folly/fibers/FiberManager.h>
#include <folly/fibers/FiberManagerMap.h>
#include <folly/MPMCQueue.h>
#include <boost/lockfree/queue.hpp>
#include <fmt/format.h>
#include <signal.h>


using namespace folly::fibers;
using namespace folly;
using namespace boost::accumulators;


inline long long now() {
    auto ts = std::chrono::high_resolution_clock::now().time_since_epoch();
    return std::chrono::duration_cast<std::chrono::microseconds>(ts).count();
}

std::atomic<bool> runningProducer = true;
std::atomic<bool> runningConsumer = true;

#ifndef BOOST_LOCK_FREE
    std::string TYPE = "FOLLY";
    folly::MPMCQueue<long long> queue(1e6);
#else
    std::string TYPE = "BOOST_LOCK_FREE";
    boost::lockfree::queue<long long> queue(1e6);
#endif
void runProducer(int index) {
    std::cout<<"Running Producer "<<index<<std::endl;
    uint64_t numProduced = 0;
    uint64_t numFailures = 0;
    while (runningProducer) {
    #ifndef BOOST_LOCK_FREE
        queue.write(now()) ? numProduced++ : numFailures++;
    #else
        queue.push(now()) ? numProduced++ : numFailures++;
    #endif
    }
    std::cout<<fmt::format("Producer {} - Messages Produced {}, Failures {}", index, numProduced, numFailures)<<std::endl;
}

void runConsumer(int index) {
    std::cout<<"Running Consumer "<<index<<std::endl;
    static const boost::array<double, 4> probs = {0.5, 0.9, 0.99, 0.999};
    typedef accumulator_set<double, stats<tag::mean, tag::extended_p_square> > LatencyAccumulator;
    LatencyAccumulator accumulator(tag::extended_p_square::probabilities = probs);
    uint64_t numConsumed = 0;
    uint64_t numFailures = 0;
    long long val;
    while (runningConsumer) {
    #ifndef BOOST_LOCK_FREE
        if (queue.read(val)) {
    #else
        if (queue.pop(val)) {
    #endif
            numConsumed++;
            accumulator(now() - val);
        } else {
            numFailures++;
        }
    }

#ifndef BOOST_LOCK_FREE
    while(queue.read(val)) {
#else
    while(queue.pop(val)) {
#endif
        numConsumed++;
        accumulator(now() - val);
    }

    boost::accumulators::detail::extractor_result<LatencyAccumulator, tag::extended_p_square>::type latencies{extended_p_square(accumulator)};
    auto format = "Consumer {} - Messages Consumed {}, Failures {}\nLatencies [ 50pct: {} ms, 90pct: {} ms, 99pct: {} ms, 99.9pct: {} ms]";
    std::cout<<fmt::format(format, index, numConsumed, numFailures,latencies[0]/1e3,
                           latencies[1]/1e3, latencies[2]/1e3, latencies[3]/1e3)<<std::endl;
}

int main() {
    unsigned NUM_OF_PRODUCERS = 1;
    unsigned NUM_OF_CONSUMERS = 2;
    std::cout<<"+++++++++++++++++++++++++++++++++"<<std::endl;
    std::cout<<TYPE<<std::endl;
    std::cout<<"+++++++++++++++++++++++++++++++++"<<std::endl;
    unsigned RUN_TIME = 300;
    std::thread producers[NUM_OF_PRODUCERS];
    std::thread consumers[NUM_OF_CONSUMERS];
    for (unsigned i = 0 ; i<NUM_OF_PRODUCERS; i++) {
        producers[i] = std::thread(runProducer, i);
    }

    for (unsigned i = 0 ; i<NUM_OF_CONSUMERS; i++) {
        consumers[i] = std::thread(runConsumer, i);
    }

    std::cout<<"Sleeping for "<<RUN_TIME<<" seconds"<<std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(RUN_TIME));
    std::cout<<"Shutting down."<<std::endl;

    runningProducer = false;
    for (unsigned i = 0 ; i<NUM_OF_PRODUCERS; i++) {
        producers[i].join();
    }

    runningConsumer = false;
    for (unsigned i = 0 ; i<NUM_OF_CONSUMERS; i++) {
        consumers[i].join();
    }
}

//+++++++++++++++++++++++++++++++++
//FOLLY
//+++++++++++++++++++++++++++++++++
//Running Producer 0
//Sleeping for 300 seconds
//Running Consumer 1
//Running Consumer 0
//
//
//Shutting down.
//Producer 0 - Messages Produced 823254576, Failures 0
//Consumer 0 - Messages Consumed 411317598, Failures 4010279227
//Latencies [ 50pct: 0.000140736 ms, 90pct: 0.001 ms, 99pct: 0.489572 ms, 99.9pct: 10.3652 ms]
//Consumer 1 - Messages Consumed 411936978, Failures 4007299695
//Latencies [ 50pct: 0.000191879 ms, 90pct: 0.001 ms, 99pct: 0.830412 ms, 99.9pct: 14.5077 ms]


//+++++++++++++++++++++++++++++++++
//BOOST_LOCK_FREE
//+++++++++++++++++++++++++++++++++
//Running Producer 0
//Sleeping for 300 seconds
//Running Consumer 0
//Running Consumer 1
//
//
//Shutting down.
//Producer 0 - Messages Produced 809191816, Failures 0
//Consumer 1 - Messages Consumed 406318446, Failures 24419714771
//Latencies [ 50pct: 0.000820451 ms, 90pct: 0.001 ms, 99pct: 0.752264 ms, 99.9pct: 7.90698 ms]
//Consumer 0 - Messages Consumed 402873370, Failures 24590594077
//Latencies [ 50pct: 0.000768023 ms, 90pct: 0.00800529 ms, 99pct: 2.14518 ms, 99.9pct: 12.9976 ms]
