# Azure IoT Edge Hands On Labs

## Overview

This hands-on lab demonstrates setting up, configuring, and developing modules for [Azure IoT Edge](https://azure.microsoft.com/en-us/services/iot-edge/).  The intent of these labs is not to cover exhaustively every IoT Edge topic, but rather cover a scenario that allows the student to learn and understand the basics of IoT Edge, develop modules and Edge ASA jobs, and perform Edge configuration, all in a pseudo-realistic use case.

In this workshop you will:

* Setup and configure a simple IoT Device, based on the [MXChip IoT DevKit](https://aka.ms/iot-devkit), to simply send sensor data over the serial port usign a custom protocol every 3 seconds
* Create an "IoT Device" that reads the data from the serial port and connects to IoT Hub __**through**__ IoT Edge
* Create an IoT Edge module that reads the simple CSV temp/humidity data from the device and converts to JSON and passes the message along
* Create an Azure Stream Analytics module that a) aggregates the "every 3 seconds" data to a 30 second frequency to send to IoT Hub in the cloud and b) looks for temperatures above a certain threshold.  When a threshold violation occurs, the module will drop an "alert" message on Edge
* create an IoT Edge module that reads the "alert" message from ASA and sends a Direct Method call to the IoT Device to light up an "alert" LED

The labs are broken up into the following modules:

* [Module 1](module1) - Prerequisites and IoT Edge setup
* [Module 2](module2) - Setup and program the "IoT Device" using on of the following options
* [Module 3](module3) - Develop "Formatter" module
* [Module 4](module4) - Azure Stream Analytics Edge job
* [Module 5](module5) - Develop "Alert" module

If you have questions or issues for the lab, check out our [troubleshooting](troubleshooting.md) guide!

Below is a conceptual flow for the labs to help visualize what is taking place and how the data is flowing through the system  ("T/H" is short for "temperature and humidity)

![conceptual drawing](/images/IoT-Edge-Labs-Conceptual-Design.png)

## Hardware

For this lab, for simplicity of setup, we are using our Windows 10 desktops (running Docker and Linux containers) as the Edge device.  For the sensor device, we leverage an Arduino Uno or an MXChip IoT DevKit. Alternatively you are free to use any device that can send data over serial.

## Prerequisites

>Note: For the lab exercises, we need an IoT Hub created in an Azure Subscription for which you have administrative access.

In order to execute the hands-on labs, there are a number of pre-requisites that need to be installed and configured.  Unless otherwise noted, the default installation of the items below are fine

* Windows 10 Fall Creators Update (build 16299)
* [Docker for Windows](https://docs.docker.com/docker-for-windows/install/)   ** the "community edition" is fine.  Make sure you install the STABLE version.  A reboot may be required to enable Hyper-V

>NOTE:  The labs are intended to be run with Linux containers (on a Windows host).  Please ensure that you are running Linux containers.  The best way to tell is to right-click on the "whale" in your notification bar and make sure you see "Switch to Windows containers" in the context menu.  That shows that you are currently running Linux containers.  If not, please make the switch.

* [Visual Studio Code](https://code.visualstudio.com/)
* [.NET Core SDK](https://www.microsoft.com/net/core#windowscmd)
* [Arduino IDE](http://www.arduino.cc/)
* [Open SSL](https://sourceforge.net/projects/openssl/)
    * for the lab instructions later, create a c:\utils folder and unzip the downloaded OpenSSL zip to c:\utils\ 
    (so you should a folder structure that looks like this->    c:\utils\OpenSSL)
* [git](https://git-scm.com/downloads/)   ** installation of the default components and default configurations are fine

* [Python 2.7 for Windows](https://www.python.org/downloads/)  -- __**make sure it's 2.7.x, NOT 3.x.x**__
    * during setup, elect to "add python 2.7 folder to the path"  (see screenshot below -- You will need to SCROLL DOWN to see it)

![python_install](/images/python_install.png)

[MXChip IoT DevKit](https://aka.ms/iot-devkit) requires the installation of some additional libraries and toolchains. Whilst These can be installed [manually](https://microsoft.github.io/azure-iot-developer-kit/docs/installation/), We encourage you to use the following [one-click installation process](https://microsoft.github.io/azure-iot-developer-kit/docs/get-started/#install-development-environment) to prepare the development environment. This will install a complete development environment including:
* Node.js and Yarn: Runtime for the setup script and automated tasks.
* Azure CLI 2.0 MSI - Cross-platform command-line experience for managing Azure resources. The MSI contains dependent Python and pip.
* Visual Studio Code (VS Code): Lightweight code editor for DevKit development.
* Visual Studio Code extension for Arduino: Extension that enables Arduino development in Visual Studio Code.
* Arduino IDE: The extension for Arduino relies upon this tool.
* DevKit Board Package: Tool chains, libraries, and projects for the DevKit.
* ST-Link Utility: Essential tools and drivers.

If you already have any these installed, the script will detect that and skip them.

Get Started with [Module 1](module1)
