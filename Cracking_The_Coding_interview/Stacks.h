#include<iostream>
#include<stdio.h>
#include<string.h>
#include<peripherals.h>
using namespace std;
#ifndef STACKS_H
#define STACKS_H


class Stacks
{
    public:
        /** Default destructor */
        virtual ~Stacks();
        /** Copy constructor
         *  \param other Object to copy from
         */
        Stacks(const Stacks& other);
        Stacks(int size=5);
        void push(int);
        int peek(int index=-1);
        void print();
        static void learn();
        bool pop();
        int size();
        bool isEmpty();
    protected:
        int top;
        int* start;
        int  curSize;
    private:
};

#endif // STACKS_H
