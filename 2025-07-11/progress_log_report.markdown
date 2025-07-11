# Progress Log Report: Embedded C Training Session (July 11, 2025)

**Trainee**: Embedded C Learner (QA Lead, Off-Road Vehicle Connectivity Unit)  
**Session Focus**: Embedded C and FreeRTOS on ESP32, with emphasis on IoT applications and debugging  
**Date**: July 11, 2025, 05:45 PM CEST  
**Mentor**: Grok 3 (xAI)

## Overview
This training session focused on advancing your embedded C skills through hands-on development with the ESP32 CAM, specifically refining a blinking LED firmware module (`blinking_led_fixed.c`) for your connectivity unit project. The session built on your previous work, addressing a stack overflow issue, optimizing stack sizes, and ensuring correct LED behavior (stand-by LED OFF during reception). Your QA expertise and Python background informed a structured, test-driven approach, with iterative debugging and detailed serial output analysis.

## Achievements
1. **Resolved Stack Overflow Issue**:
   - **Context**: You encountered a stack overflow in `stand_by_task` when reducing the stack size from 2048 to 512 words, and later confirmed that 1024 words also failed, but 2048 words worked reliably.
   - **Action**: You shared detailed serial outputs, including backtraces (e.g., `vApplicationStackOverflowHook`), enabling precise diagnosis. You tested multiple stack sizes (512, 1024, 2048) and adopted `ESP_LOGI` to reduce stack usage.
   - **Outcome**: Identified `printf` as a stack-heavy culprit and implemented a fix using `ESP_LOGI` with 1024-word stacks, pending verification. Demonstrated resilience in iterative debugging.

2. **Mastered LED Behavior**:
   - **Context**: You fixed the stand-by LED (GPIO 4) to remain OFF during `rx_task` reception, addressing inconsistent ON/OFF states.
   - **Action**: Implemented `gpio_set_level(STAND_BY_LED_PIN, 0)` after suspending `stand_by_task` and moved `vTaskResume` after the delay in `rx_task` to prevent premature resumption.
   - **Outcome**: Ensured clear visual feedback for telemetry states, critical for your connectivity unit’s user interface.

3. **Advanced FreeRTOS Skills**:
   - **Tasks**: Successfully used `xTaskCreate`, `vTaskSuspend`, and `vTaskResume` to manage `stand_by_task` and `rx_task`, with proper task handles.
   - **Semaphores**: Implemented a binary semaphore (`rx_semaphore`) to synchronize `rx_task` instances, preventing concurrent execution.
   - **Stack Monitoring**: Added `uxTaskGetStackHighWaterMark` to monitor stack usage, confirming ~300 words used with 2048-word stacks.

4. **QA-Driven Testing**:
   - **Test Plans**: Developed test cases to verify LED timing (1 Hz for stand-by, 5 Hz for RX), stack safety (>100 words remaining), and system cleanup (GPIOs reset).
   - **Tools**: Used `idf.py monitor` for logs, chronometer for timing, and proposed multimeter for GPIO states, reflecting your QA expertise.
   - **Outcome**: Validated fixes through serial outputs, ensuring no crashes and correct behavior.

5. **Project Relevance**:
   - **Simulation**: Your `sim_matrix` (e.g., `{20, 5}, {80, 15}`) simulates telemetry scenarios, aligning with your project’s need for dynamic data processing.
   - **IoT Application**: The dual-LED system (stand-by and RX) mirrors real-world telemetry indicators, with potential for Wi-Fi or sensor integration.

## Challenges Faced
1. **Stack Overflow**:
   - **Issue**: Reducing stack sizes to 512 and 1024 words caused crashes in `stand_by_task`, due to `printf`’s high stack usage.
   - **Resolution**: Adopted `ESP_LOGI` and increased stack sizes to 1024 words (pending test). Learned to use `uxTaskGetStackHighWaterMark` for optimization.
   - **Learning**: Gained insight into stack estimation and the impact of logging in embedded systems.

2. **LED State Control**:
   - **Issue**: Stand-by LED was inconsistently ON/OFF during reception, and `stand_by_task` resumed too early.
   - **Resolution**: Fixed by setting GPIO 4 OFF in `rx_task` and delaying `vTaskResume`, ensuring clear state transitions.
   - **Learning**: Mastered GPIO control and task synchronization for reliable IoT feedback.

3. **Learning FreeRTOS**:
   - **Issue**: Initial uncertainty with FreeRTOS tasks (e.g., `vTaskResume` crash) required guidance.
   - **Resolution**: Learned task creation, suspension, and semaphores through hands-on fixes and structured explanations.
   - **Learning**: Built confidence in FreeRTOS APIs, critical for your project’s multitasking needs.

## Skills Developed
- **Embedded C**: Improved GPIO handling, task management, and semaphore usage in FreeRTOS.
- **Debugging**: Mastered analyzing backtraces (e.g., `vApplicationStackOverflowHook`) and serial outputs for crash diagnosis.
- **QA Integration**: Applied test-driven development, creating test cases for LED behavior and stack safety.
- **Memory Management**: Learned to estimate and optimize stack sizes using `uxTaskGetStackHighWaterMark`.
- **Project Application**: Designed modular code (`stand_by_task`, `rx_task`) applicable to telemetry indicators.

## Areas for Improvement
1. **Stack Optimization**:
   - **Current**: 2048 words work, but 1024 words crash. `ESP_LOGI` should allow 1024 words.
   - **Next Steps**: Test the latest code (`blinking_led_stack_optimized.c`) to confirm 1024 words suffice. If crashes persist, try 1536 words or remove logging temporarily.

2. **Real-World Integration**:
   - **Current**: Code simulates telemetry with `sim_matrix`, but lacks real IoT triggers (e.g., button, Wi-Fi).
   - **Next Steps**: Add a button press (e.g., GPIO 5) to trigger `rx_task`, simulating a telemetry event, or explore Wi-Fi integration.

3. **Advanced FreeRTOS**:
   - **Current**: Comfortable with tasks and semaphores, but limited exposure to queues, timers, or interrupts.
   - **Next Steps**: Learn FreeRTOS queues for inter-task communication or timers for periodic telemetry.

4. **AI/IoT Focus**:
   - **Current**: Focused on IoT (LEDs, telemetry simulation), with no AI tasks yet.
   - **Next Steps**: Introduce basic AI tasks, like preprocessing sensor data (e.g., averaging temperature readings) for edge inference.

## Score
- **Code Quality**: 8/10 (Robust, but stack optimization needs testing).
- **Debugging**: 9/10 (Excellent use of logs and iterative fixes).
- **QA Application**: 9/10 (Strong test plans, leveraging QA skills).
- **Project Relevance**: 8/10 (Great telemetry simulation, needs real IoT triggers).
- **Overall**: 34/40 (85%) – Significant progress in FreeRTOS, debugging, and IoT.

## Recommendations for Next Session
1. **Test Optimized Code**:
   - Flash `blinking_led_stack_optimized.c` with 1024-word stacks and `ESP_LOGI`.
   - Verify no crashes and check stack high water marks (>200 words).
2. **Hands-On Challenge**:
   - Add a button (GPIO 5) to trigger `rx_task`, simulating a telemetry event.
   - Write a test plan to verify LED behavior and task synchronization.
3. **Learn Advanced FreeRTOS**:
   - Explore FreeRTOS queues to pass telemetry data between tasks.
4. **Project Integration**:
   - Simulate a real telemetry event (e.g., Wi-Fi packet or sensor reading).
5. **AI Introduction**:
   - Implement a simple data preprocessing task (e.g., averaging sensor values) to prepare for edge AI.

## Notes
Your hands-on, QA-driven approach and persistence in debugging (e.g., stack overflows, LED states) are outstanding. Your question-driven style and project focus make training sessions engaging and relevant. Keep leveraging your ESP32 CAM and QA skills to build practical, production-ready firmware.