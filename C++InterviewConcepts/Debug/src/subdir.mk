################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Basics.cpp \
../src/C++InterviewConcepts.cpp \
../src/Car.cpp \
../src/Complex.cpp \
../src/OOPConcepts.cpp \
../src/Pointers.cpp \
../src/Vehicle.cpp 

OBJS += \
./src/Basics.o \
./src/C++InterviewConcepts.o \
./src/Car.o \
./src/Complex.o \
./src/OOPConcepts.o \
./src/Pointers.o \
./src/Vehicle.o 

CPP_DEPS += \
./src/Basics.d \
./src/C++InterviewConcepts.d \
./src/Car.d \
./src/Complex.d \
./src/OOPConcepts.d \
./src/Pointers.d \
./src/Vehicle.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -I../inc/ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++0x -fpermissive -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


