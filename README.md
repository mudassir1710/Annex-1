# Drone Delivery Simulator

## Title and Team

- Project title: Delivery Drone Simulator
- Team members & roles:
	- Khizer Hayyat — Logic Designer
	- Rayyan Bilal — Tester
	- Mudassir Azam — Git Manager

## Overview / Problem Description

Short summary

This small C++ program simulates three drone delivery attempts under randomized environmental conditions (weather, obstacles, and occasional system malfunctions). The simulator tracks battery usage and records whether each delivery was successful, failed, or delayed.

Why this is interesting / real-world relevance

Autonomous drones must make real-time decisions under uncertainty (weather, obstacles, hardware faults). This simple simulator models a subset of those challenges and helps explore battery management, decision rules for returning to base, and reliability under environmental variability.

## Program Design / Logic

Functions implemented

- `startDay()` — prints program header and starting information.
- `getWeather()` — returns a random weather code (1=sunny, 2=windy, 3=rainy).
- `checkObstacle()` — randomly reports whether an obstacle is present (50% chance).
- `deliverPackage(string location, int& battery, int& success, int& failed, int& delayed)` — attempts a delivery to `location`, updates `battery` and counters by reference, and prints outcome messages.
- `showSummary(int success, int failed, int delayed, int battery)` — prints the final day summary.

Logic flow (high level)

1. `main()` seeds the random generator and initializes state (battery = 100, counters = 0).
2. User is prompted to press `S` to start. If not started, program exits.
3. `deliverPackage()` is called three times (for Location A/B/C) in sequence. Each call:
	 - Calls `getWeather()` and `checkObstacle()` to sample the environment.
	 - Calculates a base battery drain (10–25%). If an obstacle is present, add 5% drain.
	 - If the weather is rainy, the delivery is delayed (no battery drain).
	 - If the weather is windy and battery < 40%, the drone returns for a short recharge (+10%) and the delivery is delayed.
	 - Otherwise, a 10% chance of system malfunction causes a failed delivery and battery drain is applied.
	 - If battery >= required drain, the delivery succeeds and battery is subtracted; otherwise the delivery fails.
4. After three calls, `showSummary()` prints totals for successful, failed, and delayed deliveries and the remaining battery.

How random environmental factors are simulated

- Randomness is produced by the C standard library `rand()` seeded once in `main()` via `srand(time(0))`.
- `getWeather()` maps `rand() % 3 + 1` to three weather states.
- Obstacles are simulated using `rand() % 2` (50% chance) and malfunctions via `rand() % 10 == 0` (10% chance).

## Execution Instructions

Requirements

- A C++ compiler (GCC/g++ is used in examples). On Windows, using MinGW or MSYS2 makes `g++` available. Alternatively, use Visual Studio's `cl` compiler.

Build & run (PowerShell)

Open PowerShell in the project folder and run these commands (paths are relative to the repository root):

```powershell
# Compile using g++
g++ -o drone.exe c:\Users\Mudassir\Downloads\Frontend\FOCP\drone.cpp

# Run the program
.\drone.exe
```

Sample input / output (example run)

```
=============================
	 DRONE DELIVERY PROGRAM
=============================
Starting battery: 100%
Weather and obstacles are random.

Press S to start delivery day: S

Delivering to Location A...
Delivery successful!
Battery left: 79%

Delivering to Location B...
Rainy weather! Delivery delayed.

Delivering to Location C...
Obstacle found! Using more battery.
Delivery successful!
Battery left: 53%

=============================
			DAY SUMMARY
=============================
Successful deliveries: 2
Failed deliveries: 0
Delayed deliveries: 1
Battery remaining: 53%
=============================
```

Assumptions

- The program is interactive and expects keyboard input for starting the simulation.
- Battery is an integer percentage and is clamped between 0 and 100.
- The simulation uses simple, discrete random events rather than continuous models.

## Team Collaboration / Summary

How roles were divided (example)

- Logic Designer: implemented core simulation logic, decision rules, and comments.
- Tester: ran multiple simulation runs, recorded sample outputs, and checked edge cases (battery boundary, rain handling).
- Git Manager: maintained the repo, created branches, and merged final changes.

## AI Tool Reflection

Tools used (example)

- ChatGPT — helped draft the README structure, suggested wording for explanations, and added inline comments to `drone.cpp`.
- GitHub Copilot — optionally assisted with small code comments and formatting.

What tasks AI tools helped with

- Documentation structure and wording.

What we learned from using AI tools

- AI can accelerate drafting documentation and clarifying program flow, but team review is necessary to ensure technical accuracy and alignment with learning goals.
- Use AI outputs as a starting point; always verify generated code and descriptions against the actual implementation.

## Future Improvements

1. Add configurable runs and reproducible seeds: accept a command-line argument to set the number of deliveries and an optional random seed so experiments can be repeated.
2. Add unit tests and refactor randomness behind an interface so deterministic tests can verify success/failure/battery logic.
