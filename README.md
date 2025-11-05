<!-- Improved compatibility of back to top link: See: https://github.com/othneildrew/Best-README-Template/pull/73 -->

<a id="readme-top"></a>

<!-- PROJECT SHIELDS -->

<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->

<!-- Update YOUR_USERNAME and YOUR_REPO_NAME for these to work -->

[][contributors-url]
[][forks-url]
[][stars-url]
[][issues-url]
[][license-url]
[][linkedin-url]

<!-- PROJECT LOGO -->

<br />
<div align="center">
<h3 align="center">🌿 Smart Plant Monitoring with Alert System 🌿</h3>

<p align="center">
A complete Arduino project that monitors your room's environment and your plant's soil moisture. It provides real-time data on an LCD and uses a bright RGB LED and a buzzer for clear visual and audible alerts.
<br />
<a href="#-pin-definitions-and-wiring"><strong>Explore the Wiring »</strong></a>
<br />
<br />
<a href="https://www.google.com/search?q=https://www.tinkercad.com/things/YOUR_PROJECT_ID_HERE">View Demo on Tinkercad</a>
·
<a href="https://www.google.com/search?q=https://github.com/YOUR_USERNAME/YOUR_REPO_NAME/issues">Report Bug</a>
·
<a href="https://www.google.com/search?q=https://github.com/YOUR_USERNAME/YOUR_REPO_NAME/issues">Request Feature</a>
</p>
</div>

<!-- TABLE OF CONTENTS -->

<details>
<summary>Table of Contents</summary>
<ol>
<li>
<a href="#-about-the-project">About The Project</a>
<ul>
<li><a href="#-built-with">Built With</a></li>
</ul>
</li>
<li>
<a href="#-getting-started">Getting Started</a>
<ul>
<li><a href="#-prerequisites">Prerequisites</a></li>
<li><a href="#-installation--wiring">Installation & Wiring</a></li>
</ul>
</li>
<li><a href="#-usage-calibration">Usage & Calibration</a></li>
<li><a href="#-troubleshooting">Troubleshooting</a></li>
<li><a href="#-contributing">Contributing</a></li>
<li><a href="#-license">License</a></li>
<li><a href="#-contact">Contact</a></li>
<li><a href="#-acknowledgments">Acknowledgments</a></li>
</ol>
</details>

<!-- ABOUT THE PROJECT -->

🌿 About The Project

This project transforms a simple Arduino Uno into an intelligent monitoring station. It's designed to keep your plants healthy by providing a constant stream of data about their environment.

Key features:

Environment Sensing: Reads ambient room temperature and humidity using a DHT11 sensor.

Soil Monitoring: Uses a capacitive soil moisture sensor to check for dryness. To prevent corrosion, the sensor is only powered on during a reading.

Clear Display: All data is presented on a 16x2 I2C LCD screen.

Alert System: A bright RGB LED and a piezo buzzer provide immediate, color-coded, and audible alerts based on the plant's needs (Too Dry, Normal, Too Wet).

<p align="right">(<a href="#readme-top">back to top</a>)</p>

🛠️ Built With

This project uses the following hardware and software.

Hardware:

🖥️ Arduino Uno

💧 Capacitive Soil Moisture Sensor

🌡️ DHT11 Sensor

📟 16x2 I2C LCD Display

💡 Common Cathode RGB LED

🔊 Piezo Buzzer

Software:

Arduino IDE

Tinkercad (Optional)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- GETTING STARTED -->

🚀 Getting Started

Follow these steps to get your monitoring system up and running.

📚 Prerequisites

Before uploading the code, you must install these libraries via the Arduino IDE (Tools > Manage Libraries...):

LiquidCrystal_I2C (by Frank de Brabander)

DHT sensor library (by Adafruit)

Adafruit Unified Sensor (a dependency for the DHT library)

🔌 Installation & Wiring

This project uses the following pin layout. The provided code file (plant_monitor.ino) is already configured for this setup.

Component

Pin

Connected to Arduino

I2C LCD

SDA

A4



SCL

A5



VCC

5V



GND

GND

Soil Sensor

AOUT

A0 (Analog Input)



VCC

D8 (Digital Output)



GND

GND

DHT11

Data

A1 (Digital Input)



VCC

5V



GND

GND

RGB LED

Red

D9 (PWM)



Blue

D10 (PWM)



Green

D11 (PWM)



Cathode (GND)

GND

Buzzer

Positive (+)

D13



Negative (-)

GND

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- USAGE EXAMPLES -->

🌡️ Usage & Calibration

This is the most important part of the project.

1. Temperature & Humidity

The DHT11 sensor reads the ambient room temperature (in °C) and humidity (%).

If the sensor is disconnected, the LCD will display DHT11 Error, but the rest of the system will continue to work.

2. Soil Moisture (CRITICAL STEP)

You MUST calibrate your sensor for accuracy:

Upload the plant_monitor.ino code to your Arduino.

Open the Arduino IDE's Serial Monitor (Tools > Serial Monitor) and set the baud rate to 115200.

Find DRY Value: Hold the sensor in the open air. Note the "Soil Raw" value from the Serial Monitor. This is your DRY_VALUE.

Find WET Value: Submerge the sensor's measurement part in a glass of water. Note the "Soil Raw" value. This is your WET_VALUE.

Update these two lines in the code with your new values:

const int DRY_VALUE = 590; // <-- Change this
const int WET_VALUE = 240; // <-- Change this


3. Alerts

The system uses the thresholds in the code (DRY_THRESHOLD and WET_THRESHOLD) to change alerts.

Status

Soil %

LED Color

Buzzer

"Dry"

< 35%

Red

Beeps (Low Pitch)

"Normal"

35% - 65%

Green

Silent

"Wet"

> 65%

Blue

Beeps (High Pitch)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

💡 Troubleshooting

LCD is blank or shows squares:

Check your SDA (A4) and SCL (A5) connections.

The I2C address might be wrong. The code uses 0x27, which is common. If that fails, try 0x3F.

Soil moisture always reads 100% or 0%:

You must calibrate the DRY_VALUE and WET_VALUE. Your sensor's values are different from the defaults.

Ensure the sensor is powered from pin D8 (for VCC) and not the main 5V rail.

DHT11 Error on LCD:

Check your A1 data pin connection.

The sensor may be broken. The system is designed to keep working even if the DHT11 fails.

LED Color is Wrong:

Your RGB LED pins might be in a different order. The code assumes R=9, B=10, G=11. You can swap the wires or change the pin definitions at the top of the code.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTRIBUTING -->

🤝 Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are greatly appreciated.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

Fork the Project

Create your Feature Branch (git checkout -b feature/AmazingFeature)

Commit your Changes (git commit -m 'Add some AmazingFeature')

Push to the Branch (git push origin feature/AmazingFeature)

Open a Pull Request

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- LICENSE -->

📝 License

Distributed under the MIT License. See LICENSE.txt for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- CONTACT -->

📧 Contact

Your Name - YOUR_EMAIL@gmail.com

Project Link: https://github.com/YOUR_USERNAME/YOUR_REPO_NAME

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- ACKNOWLEDGMENTS -->

🙏 Acknowledgments

Adafruit (for the DHT-sensor-library)

Frank de Brabander (for the LiquidCrystal_I2C library)

Othneil Drew (for this README template)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- MARKDOWN LINKS & IMAGES -->

<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->

[]: #
[contributors-url]: https://www.google.com/search?q=https://github.com/YOUR_USERNAME/YOUR_REPO_NAME/graphs/contributors
[]: #
[forks-url]: https://www.google.com/search?q=https://github.com/YOUR_USERNAME/YOUR_REPO_NAME/network/members
[]: #
[stars-url]: https://www.google.com/search?q=https://github.com/YOUR_USERNAME/YOUR_REPO_NAME/stargazers
[]: #
[issues-url]: https://www.google.com/search?q=https://github.com/YOUR_USERNAME/YOUR_REPO_NAME/issues
[]: #
[license-url]: https://www.google.com/search?q=https://github.com/YOUR_USERNAME/YOUR_REPO_NAME/blob/master/LICENSE.txt
[]: #
[linkedin-url]: https://www.google.com/search?q=https://linkedin.com/in/YOUR_LINKEDIN