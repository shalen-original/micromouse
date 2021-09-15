# Micromouse WiSe2021

## Project members:

* Philipp Hagenlocher
* Hendrik Möller
* Matteo Nardini
* Congnan "Jonas" Wang

## Goal and milestone:
The goal of this project is to build a micromouse from scatch and solve the maze challenge offerred by TUM. 

- [x] **22. Febuary: board design review** 
- [x] **1. March: board design fixed**
- [ ] **10.March: board ready**
- [ ] **31.March: project finshed**

## Maze definition:
>The micromouse maze shall comprise **16 x 16** multiples of an **18cm x 18cm** unit square.
The walls constituting the micromouse maze shall be **5cm high** and **1.2cm thick**. 

According to UK Micromouse Maze Solver Rules:
<https://www.cs.york.ac.uk/micromouse/Rules/Maze_Solver_Rules.pdf>


## Project functionalities

* PCB Design
* Hardware Design
* HAL
* Closed Loop Control
* Maze-solver
* Communication and UI

## TODOs

#### PCB design:
- [ ] Understand voltage regulator thermal details and pick the one that are actually needed

#### Hardware design:
- [ ] Pick the distance sensors
- [ ] Pick the HBridges

#### HAL:
- [ ] To be filled

#### Closed Loop Control:
- [x] Classify controll scenarios
	* Straight: 3 scenarios
		* corridor
		* one side opening
		* both sides opening
	* Turn: switch off distance sensors
	* Spin: switch off distance sensors
- [x] Determine controller types
	* PI controller
- [x] Determine motionControl APIs
	* move (rawVelocity)
	* turn (rawVelocity)
	* spin (rawVelocity)
	* update (xxx)
- [ ] Coding controllers in c#
	* [x] connect controller to HAL
	* [x] build PI controller
	* [ ] impliment control logic
		* [x] distance controller
		* [x] velocity controller
		* [x] Lookup table for pwm 
		* [ ] update()
		* [ ] upper limit for accumulated error of controllers
		* [ ] Error notification in error.h
	* [x] wire motionControl.h API with controllers
- [ ] Theory for tuning controller parameters 
- [ ] Debug controller on board

#### Maze-solver
- [x] Classic Flood Fill

#### Communication and UI
- [ ] To be filled

# Code Notation/Styling:
```
* Name Formatting:
	- functions: camelCase - getSomething()
	- `#define: CAPSLOCK_WITH_UNDERSCORE - CONFIG_H`
	- Variables: camelCase - timerInterruptFrequency
* Use "init" instead of "setup" (if there is no difference)
* Use in-line brackets only for "} else {" or similiar lines
* Code-Comments in-line for single important statements (or declarations)
* Code-Comments before function headers in c-file
* One empty line between sections of code, ordered as follows:
	- Header file: 
		Guard condition, 
		includes, 
		`#defines (namespace)`
		extern variable declarations
		function headers
	- C file: 
		includes,
		`#define (for constants)`
		member variables
		function implementations
