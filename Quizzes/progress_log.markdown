# C Programming Training Progress Log

This file tracks my daily progress in C programming quizzes and challenges, with the goal of maintaining a 70% success rate per sub-topic and increasing difficulty as I improve.

## Session: July 7, 2025 (New Session)

**Date and Time**: July 7, 2025, 01:37 PM CEST  
**Difficulty Level**: Extremely Hard  
**Hardware**: ESP32 (confirmed)  
**FreeRTOS**: Confirmed  

**Sub-Topic Scores** (Updated with Final Challenge):
- **Fundamentals**: 7/7 (100%) [No new quizzes]
- **Control Structures**: 30/36 (83.33%) [No new challenge contribution]
- **Arrays**: 17/20 (85%) [No new quizzes]
- **Pointers**: 36/44 (81.82%) [+1/1 from Challenge]
- **Functions**: 9/9 (100%) [No new quizzes]
- **Strings**: 22.5/30 (75%) [+1/1 from Challenge]
- **Structures**: 8/9 (88.89%) [No new quizzes]
- **File Handling**: 8/8 (100%) [No new quizzes]
- **Dynamic Memory Allocation**: 15/18 (83.33%) [No new quizzes]
- **Preprocessing**: 9/10 (90%) [No new quizzes]
- **Bit Fields**: 2/2 (100%) [No new quizzes]
- **Volatile Variables**: 12/14 (85.71%) [+1/1 from Challenge]
- **IoT Protocols**: 8/10 (80%) [+1/1 from Challenge]
- **Embedded AI**: 5/5 (100%) [No new challenge contribution]
- **Memory-Mapped I/O**: 13/15 (86.67%) [+1/1 from Challenge]
- **DMA**: 2/2 (100%) [No new quizzes]
- **Real-Time Constraints**: 2/2 (100%) [No new quizzes]
- **Low-Power Modes**: 1/1 (100%) [No new quizzes]
- **Watchdog Timers**: 1/1 (100%) [No new quizzes]
- **Task Scheduling**: 7/8 (87.5%) [+1/1 from Challenge]
- **Challenge (Strings, Volatile Variables, Memory-Mapped I/O, IoT Protocols, Task Scheduling, Pointers)**: 19/28 (67.86%) [+4/4 from first challenge, +2/4 from second challenge, +2/4 from third challenge, +2/4 from fourth challenge, +3/4 from fifth challenge]

**Overall Score**: 209/249 (83.94%) [+3/4 from final challenge]

**Weak Areas**:
- **Strings (75%)**: Improved with `snprintf`, but buffer size mismatch (18 vs. 16 bytes) shows need for constraint checking.  
- **IoT Protocols (80%)**: Improved, but buffer size issue affects MQTT correctness.  
- **Pointers (81.82%)**: Stable; reinforce volatile pointer arrays.  
- **Control Structures (83.33%)**: Stable; practice complex bit manipulation.  
- **Volatile Variables (85.71%)**: Stable; continue ISR-safe shared variables.  
- **Memory-Mapped I/O (86.67%)**: Stable; maintain ISR precision.  
- **Task Scheduling (87.5%)**: Improved; focus on FreeRTOS `xSemaphoreTake`/`xSemaphoreGive` and `vTaskDelay`.

**Notes**:
- Quiz score: 10/10 (100%), showing mastery in weak areas and new topics.  
- Fifth challenge scored 75% due to buffer size mismatch (18 vs. 16 bytes).  
- Overall score slightly dropped to 83.94% due to cumulative challenge errors, but still near 90% goal.  
- FreeRTOS confirmed; challenges will use FreeRTOS tasks/semaphores.  
- Style: Correct `snprintf` usage, but verify buffer sizes. Comment pseudo-delays (e.g., `// Simulate vTaskDelay(1000)`).  
- ESP32 confirmed; challenges align with ESP32 and FreeRTOS.  
- Buffer constraint (16 bytes) was unrealistic; future challenges will use 24 bytes.

**Next Steps**:
- **Strings**: Add 2 quizzes on MQTT payload formatting with `snprintf` and buffer size checks.  
- **IoT Protocols**: Add 2 quizzes on MQTT payload validation and formatting.  
- **Task Scheduling**: Add 2 quizzes on FreeRTOS semaphores and task delays.  
- **Volatile Variables**: Add 1 quiz on ISR-safe shared variables.  
- **Memory-Mapped I/O**: Add 1 quiz on ISR-driven GPIO handling.  
- **Pointers**: Add 1 quiz on volatile pointer arrays.  
- **Embedded AI**: Add 1 quiz on TinyML inference.  
- **Challenge**: Design an ESP32 FreeRTOS task with ISR and semaphore to process sensor data for MQTT.  
- **Hardware**: Continue with ESP32 and FreeRTOS.  
- Share this log at the start of the next session.