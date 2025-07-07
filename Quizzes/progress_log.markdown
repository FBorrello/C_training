# C Programming Training Progress Log

This file tracks my daily progress in C programming quizzes and challenges, with the goal of maintaining a 70% success rate per sub-topic and increasing difficulty as I improve.

## Session: July 7, 2025

**Date and Time**: July 7, 2025, 09:36 AM CEST  
**Difficulty Level**: Extremely Hard  
**Hardware**: ESP32 (confirmed)  

**Sub-Topic Scores** (Updated with Today’s Results):
- **Fundamentals**: 7/7 (100%) [+1 from Quiz 7]
- **Control Structures**: 29/35 (82.86%) [+0/1 from Quiz 5]
- **Arrays**: 17/20 (85%) [No new quizzes]
- **Pointers**: 31/39 (79.49%) [+1/2 from Quizzes 4, 10]
- **Functions**: 9/9 (100%) [No new quizzes]
- **Strings**: 18.5/22 (84.09%) [+1/1 from Quiz 6]
- **Structures**: 8/9 (88.89%) [No new quizzes]
- **File Handling**: 8/8 (100%) [No new quizzes]
- **Dynamic Memory Allocation**: 15/18 (83.33%) [No new quizzes]
- **Preprocessing**: 9/10 (90%) [No new quizzes]
- **Bit Fields**: 2/2 (100%) [+1/1 from Quiz 7]
- **Volatile Variables**: 5/6 (83.33%) [+1/1 from Quiz 3]
- **IoT Protocols**: 3/3 (100%) [+1/1 from Quiz 6]
- **Embedded AI**: 3/3 (100%) [+1/1 from Quiz 9]
- **Memory-Mapped I/O**: 5/6 (83.33%) [+2/2 from Quizzes 1, 2, +2/2 from Challenge]
- **DMA**: 2/2 (100%) [No new quizzes]
- **Real-Time Constraints**: 2/2 (100%) [No new quizzes]
- **Low-Power Modes**: 1/1 (100%) [No new quizzes]
- **Watchdog Timers**: 1/1 (100%) [No new quizzes]
- **Task Scheduling**: 1/1 (100%) [+1/1 from Quiz 8]
- **Challenge (Memory-Mapped I/O)**: 4/4 (100%) [+4/4 from revised submission]

**Overall Score**: 182/211 (86.26%) [+12/13 from today]

**Weak Areas**:
- **Pointers (79.49%)**: Missed Quiz 4 (volatile pointer arithmetic). Reinforce volatile pointer handling in embedded systems.
- **Control Structures (82.86%)**: Missed Quiz 5 (bit manipulation). Practice complex bit checks in IoT contexts.
- **Volatile Variables (83.33%)**: Improved but needs ISR-specific practice.
- **Strings (84.09%)**: Stable; continue MQTT parsing practice.
- **Memory-Mapped I/O (83.33%)**: Improved significantly with perfect challenge score; maintain consistency in bit manipulation and ISR handling.

**Notes**:
- Quiz score: 8/10 (80%), meeting 70% target but below 90% goal.
- Revised challenge corrected bit mask (`0x0020` for bit 5), null check (`&&`), and counter handling, achieving 100%.
- Clarified bit numbering confusion (0x0010 = bit 4, 0x0020 = bit 5); mentor error in feedback noted.
- Strong in new topics: Task Scheduling, Embedded AI (100%).
- ESP32 confirmed; future challenges will align with ESP32 GPIO/interrupt APIs (e.g., `gpio_config`, `gpio_isr_handler_add`).
- Progress improved (86.26% vs. 85.86%) dueosi: System: **Next Steps**:
- **Memory-Mapped I/O**: Add 2 quizzes on GPIO bit manipulation and ISR counter handling.
- **Pointers**: Add 1 quiz on volatile pointer arithmetic in embedded systems.
- **Control Structures**: Add 1 quiz on complex bit manipulation for IoT.
- **Volatile Variables**: Add 1 quiz on ISR-safe handling.
- **Strings**: Add 1 quiz on MQTT payload parsing with edge cases.
- **New Topics**: Expand task scheduling (e.g., FreeRTOS basics) and embedded AI (e.g., TinyML inference).
- **Challenge**: Design an ESP32 interrupt-driven sensor task with correct GPIO and ISR handling.
- **Hardware**: Continue using ESP32; consider FreeRTOS integration.
- Share this log at the start of the next session.