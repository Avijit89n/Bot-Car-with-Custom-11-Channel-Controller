# 🚀 Bot Car with Custom 11-Channel Controller  

## 🏆 Achievements  
✅ **Secured 31st position** in **IIT KGP Techfest** 🎉  

## 📌 Project Overview  
This project is a **custom-built bot car** controlled using a **self-designed 11-channel controller**. It uses **NRF24L01** modules for **long-range wireless communication**, making it a highly responsive and reliable system. The **transmitter features two joysticks and three buttons**, allowing fine control over movement and additional functions.  

## 🔧 Hardware Components  
### 🖥 Microcontrollers  
- **Arduino Uno** – Main processing unit  
- **Arduino Nano** – Handles control transmission and reception  

### 📡 Communication  
- **NRF24L01 (Long Range Version)** – Wireless data transmission  
- **UART Protocol** – Used for data sharing between the receiver and main microcontroller  

### 🎮 Controller & Mechanism  
- **Custom 11-Channel Controller** – Designed from scratch for precise movement control  
- **Two Joysticks** – Controls movement and direction  
- **Three Buttons** – Used for additional bot functionalities  

### ⚙️ Motor Control  
- **BTS7960 Modules** – Motor drivers for precise movement  

### 🔋 Power Supply  
- **2200mAh LiPo Battery** – Powers the complete system  

## 🎮 How It Works  
1. The **custom transmitter** sends signals using **NRF24L01**.  
2. The **Arduino Nano** on the receiver side processes the data and transfers it to **Arduino Uno** via **UART**.  
3. The **two joysticks** control movement (e.g., forward, backward, turning).  
4. The **three buttons** trigger special functions.  
5. The **BTS7960 motor drivers** execute the movement commands.  

## 📌 Features  
✅ **Custom 11-Channel Controller** – Provides precise control  
✅ **Two Joysticks & Three Buttons** – Offers flexible movement and actions  
✅ **Long-Range Wireless Communication** – Uses **NRF24L01** for reliable data transmission  
✅ **Compact & Powerful** – Powered by **2200mAh LiPo battery**  
✅ **Used in IIT KGP Techfest** – Successfully performed in a competitive environment  

## 🚀 Future Enhancements  
- **Improved Speed Control** – Using PID for better motor handling  
- **FPV Camera Integration** – For real-time monitoring  
- **Autonomous Mode** – Adding AI-based navigation

## 📜 License
This project is licensed under the **MIT License**.  
See the [LICENSE](./LICENSE) file for details.

---

🔧 **Developed by:** Avijit Biswas  
📅 **Last Updated:** 2025-03-21  
