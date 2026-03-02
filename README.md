🌱 Smart Irrigation System using ESP32

An IoT-based automatic plant watering system that monitors soil moisture in real time and activates a water pump only when required. The system also uploads live data to ThingSpeak for remote monitoring.

📖 Description

This project is built using ESP32 and a soil moisture sensor to create an automated irrigation system.

When the soil becomes dry:

💧 Water pump turns ON

🔔 Buzzer alerts

💡 LED glows

☁️ Data is uploaded to ThingSpeak

When the soil becomes wet:

🚫 Pump turns OFF

🔕 Buzzer stops

💡 LED turns OFF

This helps in:

Water conservation

Smart agriculture

Home gardening automation

Learning IoT & embedded systems


⚡ System Working

The soil moisture sensor reads soil condition.

ESP32 processes the analog value.

If moisture value > threshold → Soil is DRY.

Relay activates the pump.

Data is sent to ThingSpeak.

When soil becomes wet → Pump turns OFF automatically.


☁ ThingSpeak Setup

Create a channel with:

Field 1 → Soil Moisture

Field 2 → Motor Status

Field 3 → Soil Condition

Copy:

Channel ID

Write API Key

Paste them into the code.


🎥 Live Demonstration

A full working demo of the Clean Air Sentinel project is available on YouTube.

▶️ Watch here: https://youtu.be/w3F0ACZtN0c
https://img.youtube.com/vi/w3F0ACZtN0c/maxresdefault.jpg
