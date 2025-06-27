# C Code Training Program for Embedded SW and AIoT Development

## Program Overview
This 12-week program is designed for an advanced Python developer transitioning to embedded software and AI-on-the-edge (AIoT) development using C. It covers C programming fundamentals, embedded systems, real-time programming, and lightweight AI implementations. Each week includes theory, exercises, and hands-on projects using affordable hardware (e.g., STM32, ESP32, or Raspberry Pi).

---

## Week 1–2: C Programming Fundamentals
**Objective**: Master C syntax and concepts, leveraging Python knowledge.
- **Topics**:
  - C syntax: variables, data types, operators, control structures (if, loops, switch)
  - Functions, scope, and pass-by-value vs. pass-by-reference
  - Arrays, strings, and basic I/O (printf, scanf)
  - Compilation process (preprocessor, compiler, linker)
- **Exercises**:
  - Write a program to calculate factorial using iterative and recursive functions.
  - Implement a string manipulation library (e.g., reverse, concatenate).
- **Project**:
  - Create a command-line calculator supporting basic arithmetic operations.
- **Resources**:
  - Book: "C Programming Language" by Kernighan & Ritchie
  - Online: Learn-C.org, GeeksforGeeks C tutorials

## Week 3–4: Pointers and Memory Management
**Objective**: Understand pointers, memory allocation, and low-level data handling.
- **Topics**:
  - Pointers: declaration, dereferencing, pointer arithmetic
  - Dynamic memory: malloc, free, memory leaks
  - Structures, unions, and bitfields
  - Memory alignment and padding
- **Exercises**:
  - Implement a linked list with dynamic memory allocation.
  - Write a program to manipulate a structure representing sensor data.
- **Project**:
  - Build a dynamic memory-based task manager storing task names and priorities.
- **Resources**:
  - Book: "Understanding and Using C Pointers" by Richard Reese
  - Online: Pointer tutorials on TutorialsPoint

## Week 5–6: Embedded Systems Basics
**Objective**: Apply C to microcontrollers and hardware interfacing.
- **Topics**:
  - Microcontroller architecture (e.g., STM32 or ESP32)
  - GPIO programming: digital I/O, LEDs, buttons
  - Timers and PWM (Pulse Width Modulation)
  - Embedded development tools: STM32CubeIDE, PlatformIO
- **Exercises**:
  - Blink an LED on an STM32 or ESP32 board.
  - Read a button press to toggle an LED state.
- **Project**:
  - Create a PWM-based LED dimmer controlled by a potentiometer.
- **Hardware**: STM32 Nucleo or ESP32 DevKit
- **Resources**:
  - STM32CubeIDE documentation
  - ESP32 technical reference manual

## Week 7–8: Real-Time Programming and Interrupts
**Objective**: Master real-time systems and interrupt-driven programming.
- **Topics**:
  - Interrupt handling: ISRs (Interrupt Service Routines)
  - Real-time concepts: latency, priority, scheduling
  - RTOS basics (e.g., FreeRTOS tasks, queues)
  - Serial communication (UART, SPI, I2C)
- **Exercises**:
  - Write an ISR to handle a timer interrupt for periodic tasks.
  - Implement UART communication to send sensor data to a PC.
- **Project**:
  - Build a temperature monitoring system using a sensor (e.g., DHT11) and UART.
- **Resources**:
  - FreeRTOS documentation
  - Book: "Real-Time Concepts for Embedded Systems" by Qing Li

## Week 9–10: AIoT and TinyML Integration
**Objective**: Implement lightweight AI models on embedded devices.
- **Topics**:
  - Introduction to TinyML and edge AI
  - TensorFlow Lite for Microcontrollers (TFLM)
  - Model conversion: Python (TensorFlow) to C (TFLM)
  - Sensor data preprocessing for AI inference
- **Exercises**:
  - Convert a simple Python-based ML model (e.g., sine wave predictor) to TFLM.
  - Run inference on an STM32 or ESP32 using TFLM.
- **Project**:
  - Deploy a pre-trained model (e.g., gesture recognition) on an ESP32 with sensor input.
- **Hardware**: ESP32 or STM32 with accelerometer
- **Resources**:
  - TensorFlow Lite Micro documentation
  - Book: "TinyML" by Pete Warden

## Week 11–12: Capstone Project
**Objective**: Combine embedded C and AIoT skills in a real-world application.
- **Project**:
  - Develop an AIoT system for environmental monitoring:
    - Use sensors (e.g., temperature, humidity, air quality) to collect data.
    - Implement a TinyML model to predict anomalies (e.g., high pollution levels).
    - Send alerts via UART or Wi-Fi (ESP32) to a host device.
- **Tasks**:
  - Write C code for sensor interfacing and data preprocessing.
  - Integrate a TFLM model for edge inference.
  - Optimize code for memory and performance.
- **Deliverables**:
  - Functional prototype on STM32 or ESP32
  - Documentation: code, design decisions, and performance analysis
- **Resources**:
  - Hardware datasheets
  - GitHub repositories for TinyML examples

---

## Weekly Schedule
- **Theory (2–3 hours)**: Read assigned materials and watch tutorials.
- **Exercises (4–6 hours)**: Complete coding tasks to reinforce concepts.
- **Project (4–6 hours)**: Apply skills to hands-on projects.
- **Review**: Use Git for version control; test code on hardware.

## Tools and Setup
- **Software**: GCC, STM32CubeIDE or PlatformIO, Python (for model training), TensorFlow
- **Hardware**: STM32 Nucleo, ESP32 DevKit, sensors (DHT11, accelerometer)
- **Version Control**: Git (GitHub or GitLab)
- **Debugging**: Serial monitors, JTAG debuggers

## Tips for Success
- Leverage your Python skills for scripting and model training.
- Focus on understanding C’s low-level behavior (e.g., pointers, memory).
- Test incrementally on hardware to avoid debugging complexity.
- Document code and project progress for clarity.

## Evaluation
- Weekly: Complete exercises and mini-projects.
- Final: Capstone project functionality, code quality, and documentation.
