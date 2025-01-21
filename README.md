# Implementation of PCP and PIP Using Arduino

This project demonstrates the implementation of **Priority Ceiling Protocol (PCP)** and **Priority Inheritance Protocol (PIP)** using an **Arduino**. These protocols are fundamental in real-time systems for managing task priorities and preventing priority inversion.

---

## Project Description
1. **Priority Ceiling Protocol (PCP)**:
   - Ensures that no lower-priority task can block a higher-priority task longer than necessary by assigning resources a ceiling priority.

2. **Priority Inheritance Protocol (PIP)**:
   - Temporarily raises the priority of a task holding a resource to the highest priority of the tasks waiting for that resource.

The implementation uses LEDs to simulate tasks and critical section management under these protocols.

---

## Hardware Requirements
- **Arduino Mega 2560**
- LEDs (for simulating tasks)
- Breadboard and jumper wires

---

## Software Requirements
- **Arduino IDE**
- **VScode**

---

## How to Run
1. Clone the repository:
   ```bash
   git clone https://github.com/Kishore-09/PIP-and-PCP-implementation-using-Arduino
