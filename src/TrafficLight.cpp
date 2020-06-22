#include <iostream>
#include <random>
#include <chrono>
#include "TrafficLight.h"

/* Implementation of class "MessageQueue" */

/* 
template <typename T>
T MessageQueue<T>::receive()
{
    // FP.5a : The method receive should use std::unique_lock<std::mutex> and _condition.wait() 
    // to wait for and receive new messages and pull them from the queue using move semantics. 
    // The received object should then be returned by the receive function. 
}

template <typename T>
void MessageQueue<T>::send(T &&msg)
{
    // FP.4a : The method send should use the mechanisms std::lock_guard<std::mutex> 
    // as well as _condition.notify_one() to add a new message to the queue and afterwards send a notification.
}
*/

/* Implementation of class "TrafficLight" */


TrafficLight::TrafficLight()
{
    _currentPhase = TrafficLightPhase::red;
}

void TrafficLight::waitForGreen()
{
    // FP.5b : add the implementation of the method waitForGreen, in which an infinite while-loop 
    // runs and repeatedly calls the receive function on the message queue. 
    // Once it receives TrafficLightPhase::green, the method returns.
}

TrafficLightPhase TrafficLight::getCurrentPhase()
{
    return _currentPhase;
}

void TrafficLight::simulate()
{
    // FP.2b : Finally, the private method „cycleThroughPhases“ should be started in a thread when the public method „simulate“ is called. To do this, use the thread queue in the base class. 
    threads.emplace_back(std::thread(&TrafficLight::cycleThroughPhases, this));
}

// virtual function which is executed in a thread
void TrafficLight::cycleThroughPhases()
{
    // FP.2a : Implement the function with an infinite loop that measures the time between two loop cycles 
    // and toggles the current phase of the traffic light between red and green and sends an update method 
    // to the message queue using move semantics. The cycle duration should be a random value between 4 and 6 seconds. 
    // Also, the while-loop should use std::this_thread::sleep_for to wait 1ms between two cycles.

    // Generate random value (source from Stackoverflow: https://stackoverflow.com/a/7560564)
    std::mt19937 gen(std::random_device{}()); // generator
    std::uniform_int_distribution<> distribution(4, 6); // range
    int cycleDuration = distribution(gen);

    // timestamp at the start of the simulation
    // the value will be updated inside the loop to indicate the timestamp recorded on the previous loop
    auto previousLoopTime = std::chrono::high_resolution_clock::now(); 
    
    while (true) { 
        std::this_thread::sleep_for(std::chrono::milliseconds(1)); // wait 1ms between two cycles

        auto currentLoopTime = std::chrono::high_resolution_clock::now(); // timestamp during the simulation

        // Make a cycle run for the given duration, by iteratively checking if the duration has been passed
        auto currentDuration = std::chrono::duration_cast<std::chrono::seconds>(currentLoopTime - previousLoopTime).count();
        
        if (currentDuration >= cycleDuration) {
            // Start a new cycle wiht toggled traffic light and new random duration
            if (_currentPhase == TrafficLightPhase::red) 
                _currentPhase = TrafficLightPhase::green;
            else 
                _currentPhase = TrafficLightPhase::red;
            
            // TODO: send an update to the message queue

            cycleDuration = distribution(gen);
            previousLoopTime = std::chrono::high_resolution_clock::now();
        }
    }
}