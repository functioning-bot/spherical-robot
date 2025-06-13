# Spherical Robot using Arduino

This project is a simple and affordable implementation of a spherical robot controlled using an Arduino Uno and RF modules. The robot moves by shifting its internal center of mass using motors, which allows the outer spherical shell to roll in different directions. It's controlled wirelessly using a joystick and nRF24L01 transceivers.

We developed this as part of our undergraduate mini project with the goal of exploring alternative robot designs that are compact, sealed, and capable of navigating smooth surfaces.

## What it does

- Moves forward and backward based on joystick input
- Turns using a pendulum-based steering mechanism
- Communicates wirelessly using Arduino and nRF24L01 modules
- Built inside a spherical shell, which protects the inner components

## Why a spherical robot?

Spherical robots are interesting because:
- They’re fully enclosed and safe to use in different environments
- Their movement is smooth and omnidirectional
- They can be used for things like surveillance, entertainment, or even educational demos

We focused on making something that’s practical, fun to build, and works reliably on flat surfaces.

## How it works

The remote controller has a joystick connected to an Arduino that sends data over RF. Inside the robot, another Arduino receives the data and moves motors accordingly. A pendulum mechanism is used to shift the center of mass and control rolling and turning.

## Components Used

- Arduino Uno
- nRF24L01 RF Modules
- L298N Motor Driver
- DC Motors
- MG995 Servo Motors
- Joystick Module
- 9V and 12V Batteries
- Spherical Shell (outer body)

## Future ideas

We’d like to try:
- Adding gesture-based control using an accelerometer glove
- Mounting a camera for remote viewing
- Improving obstacle detection and climbing
- Making it semi-autonomous with basic sensors

## Authors

- T. Ashmitha  
- Aduwala Sai Preeth  
- Vanaparthi Sriram Santhosh

Project under the guidance of Mr. Shakeel Ahmed, Sr. Assistant Professor, CVR College of Engineering.
