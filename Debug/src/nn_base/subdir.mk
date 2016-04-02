################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/nn_base/Network.cpp \
../src/nn_base/Neuron.cpp \
../src/nn_base/functions.cpp 

OBJS += \
./src/nn_base/Network.o \
./src/nn_base/Neuron.o \
./src/nn_base/functions.o 

CPP_DEPS += \
./src/nn_base/Network.d \
./src/nn_base/Neuron.d \
./src/nn_base/functions.d 


# Each subdirectory must supply rules for building sources it contributes
src/nn_base/%.o: ../src/nn_base/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I"/home/petz/workspaces/eclipse/NNcpp/include" -I/usr/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


