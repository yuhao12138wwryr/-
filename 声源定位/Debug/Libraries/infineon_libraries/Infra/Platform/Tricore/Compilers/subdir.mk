################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Libraries/infineon_libraries/Infra/Platform/Tricore/Compilers/CompilerDcc.c \
../Libraries/infineon_libraries/Infra/Platform/Tricore/Compilers/CompilerGhs.c \
../Libraries/infineon_libraries/Infra/Platform/Tricore/Compilers/CompilerGnuc.c \
../Libraries/infineon_libraries/Infra/Platform/Tricore/Compilers/CompilerTasking.c 

OBJS += \
./Libraries/infineon_libraries/Infra/Platform/Tricore/Compilers/CompilerDcc.o \
./Libraries/infineon_libraries/Infra/Platform/Tricore/Compilers/CompilerGhs.o \
./Libraries/infineon_libraries/Infra/Platform/Tricore/Compilers/CompilerGnuc.o \
./Libraries/infineon_libraries/Infra/Platform/Tricore/Compilers/CompilerTasking.o 

COMPILED_SRCS += \
./Libraries/infineon_libraries/Infra/Platform/Tricore/Compilers/CompilerDcc.src \
./Libraries/infineon_libraries/Infra/Platform/Tricore/Compilers/CompilerGhs.src \
./Libraries/infineon_libraries/Infra/Platform/Tricore/Compilers/CompilerGnuc.src \
./Libraries/infineon_libraries/Infra/Platform/Tricore/Compilers/CompilerTasking.src 

C_DEPS += \
./Libraries/infineon_libraries/Infra/Platform/Tricore/Compilers/CompilerDcc.d \
./Libraries/infineon_libraries/Infra/Platform/Tricore/Compilers/CompilerGhs.d \
./Libraries/infineon_libraries/Infra/Platform/Tricore/Compilers/CompilerGnuc.d \
./Libraries/infineon_libraries/Infra/Platform/Tricore/Compilers/CompilerTasking.d 


# Each subdirectory must supply rules for building sources it contributes
Libraries/infineon_libraries/Infra/Platform/Tricore/Compilers/%.src: ../Libraries/infineon_libraries/Infra/Platform/Tricore/Compilers/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc26xb "-fE:/diansai/TC264_Library/TC264_Library/Example/PIT_Demo/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

Libraries/infineon_libraries/Infra/Platform/Tricore/Compilers/%.o: ./Libraries/infineon_libraries/Infra/Platform/Tricore/Compilers/%.src
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


