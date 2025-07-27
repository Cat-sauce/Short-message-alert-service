# Offline ESP-to-ESP Messaging System using ESP-NOW

## 🔍 Project Overview

This project demonstrates a simple offline communication system between two ESP32 microcontrollers using the **ESP-NOW protocol**. Each device has five predefined buttons for sending short messages and an OLED display to show both **sent** and **received** messages. A buzzer provides an audible notification on message reception.

No Wi-Fi router or internet connection is needed — communication happens directly between the two ESP devices via **Wi-Fi signals**, in a peer-to-peer manner.

---

## 💡 Problem Statement

In scenarios where internet access is unavailable, unreliable, or unnecessary — such as isolated workstations, smart homes, or emergency response sites — there is often a need for **direct local communication** between devices. This project solves that by creating a **compact, low-power, offline communication system** using ESP-NOW, allowing short predefined messages to be exchanged between ESP32 devices.

---

## 🚀 Features

* 📤 Send predefined messages using physical buttons
* 📥 Receive and display incoming messages
* 🧠 Dual OLED displays (one on each ESP) show both sent and received texts
* 🔔 Buzzer notifies message reception
* ✅ Fully offline: No Wi-Fi or internet needed

---

## 🧰 Hardware Used

* 2 × ESP32 development boards
* 2 × OLED displays (I2C)
* 2 × Passive or Active Buzzers (used for notification)
* 10 × Push Buttons (5 per ESP)
* Breadboard and jumper wires

### GPIO Configuration (Same on both ESPs):

| Component | Pin                                |
| --------- | ---------------------------------- |
| OLED SDA  | GPIO 21                            |
| OLED SCL  | GPIO 22                            |
| Button 1  | GPIO 13                            |
| Button 2  | GPIO 12                            |
| Button 3  | GPIO 14                            |
| Button 4  | GPIO 27                            |
| Button 5  | GPIO 26                            |
| Buzzer    | GPIO (user-defined, e.g., GPIO 25) |

---

## 📡 How ESP-NOW Works Here

* Devices communicate via Wi-Fi radio, **without needing a router**
* Each ESP32 device is identified by its **MAC address**
* Messages are sent **directly to the MAC address** of the receiving ESP
* Supports **instant communication** within \~30 to 50 meters (line-of-sight)

---

## 🎯 Use Cases

* 📟 **Local Alert System** between machines and supervisor nodes
* 🏠 **Smart Home Modules** for internal commands
* 🧪 **Lab-to-Lab Message Passing** (e.g., school/university projects)
* 🚫 **Offline Communication** for rescue operations or blackouts

---

## 🔧 Future Enhancements

* Add **more ESP nodes** to build a messaging mesh
* Use **custom text input** (instead of predefined)
* Add **message history** via SD card or EEPROM
* Integrate with **Wi-Fi fallback** or Bluetooth for dual-mode support
* Add **encryption** for secure transmission

---

## 📍 Limitations

* Limited to short-range (\~30m)
* No direct support for dynamic typing of messages
* Not designed for high-throughput communication

---

## 🧠 Conclusion

This project provides a lightweight, reliable solution for direct messaging between ESP32 devices without any Wi-Fi infrastructure. Ideal for demonstrating **peer-to-peer communication**, **IoT messaging systems**, and **offline alert systems** in a small range and low-power context.

---

> 💬 "Offline doesn't mean disconnected — with ESP-NOW, your ESPs can still talk."
