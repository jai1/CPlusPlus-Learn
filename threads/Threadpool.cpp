#include <iostream>
#include <queue>
#include <vector>
#include <thread>
#include <cstdlib>

using namespace std;

/*
 * Write code in C++ for a class ImageProcessorService that has function void processImage(std::vector<float> image)
 * and that uses function int neuralNetwork(std::vector<float> image) to process it. This runs a neural network on the CPU.
Assume that the neuralNetwork() function is slow.
processImage() must be fast and never block the caller for a long time. It can be called at random intervals.
You don’t have to compile and run your solution, but we expect you to write C++ code that would comp
 */

// Threadpool
//- Size -> CPU core
//- lock
//- Signaling (Wait)
//- Deletion
//- Error handling

class ThreadPool {
private:
    size_t num_of_threads;
    vector<thread> threads;
    condition_variable cv;
    mutex queue_lock;
    queue<function<void()>> task_list;
    bool stopped;
public:
    ThreadPool(size_t num_of_threads) {
        this->num_of_threads = num_of_threads;
        // Initialize threads
        for (size_t i =0; i<num_of_threads; i++) {
            threads.emplace_back([this] {
                while(true) {
                    function<void()> task;
                    {
                        unique_lock<mutex> lock(queue_lock);
                        cv.wait(lock, [this]{
                            return !task_list.empty() || stopped;
                        });

                        if (stopped && task_list.empty()) {
                            return;
                        }

                        task = task_list.front(); // TODO: can be moved
                        task_list.pop();
                    }
                    task(); // TODO: binding
                }
            });
        }
    }

    void enqueue(function<void()> task) {
        {
            unique_lock<mutex> lock(queue_lock);
            task_list.emplace(task);
        }
        cv.notify_one();
    }

    ~ThreadPool() {
        {
            unique_lock<mutex> lock(queue_lock);
            stopped = true;
        }
        cv.notify_all();

        for(size_t i = 0; i<num_of_threads; i++) {
            threads[i].join();
        }
    }
};

class ImageProcessorService {
public:
    ImageProcessorService() : pool(4) {
    }

    void processImage(std::vector<float> image) {
        pool.enqueue([this, image] {
            int result = neuralNetwork(image);
            {
                // histogram logic
            }
        });
    }
private:
    int neuralNetwork(std::vector<float> image) {
        int random = rand() % 10000;
        cout<<"Thread id is "<<this_thread::get_id()<<". Sleeping for "<<random<<endl;
        this_thread::sleep_for(chrono::milliseconds(random));
        return 0;
    }

    ThreadPool pool;
    std::unordered_map<int, int> results; // Handle locking
};


int main() {
    std::cout << "Starting Thread Pool !!!" << std::endl;

    vector<float> image;
    ImageProcessorService service;
    for (int i = 0; i<100; i++) {
        service.processImage(image);
    }
    return 0;
}

