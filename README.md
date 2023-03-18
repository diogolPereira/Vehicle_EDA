# Vehicle Rental System

This is a simple command-line application written in C that simulates a vehicle rental system. The program allows users to rent and return vehicles, and managers to add and remove vehicles from the fleet.

## Features

- Users can rent and return vehicles
- Managers can add and remove vehicles from the fleet
- Data is read from a CSV file and persisted in a binary file

## Installation

1. Clone the repository: `git clone https://github.com/diogolPereira/Vehicle_EDA`
2. Build the project: `make`
3. Run the program: `./vehicle-rental-system`


## Data Storage

The program reads data from a CSV file `vehicle.csv` and presist data in binary files like `vehicle.bin`. When the app start try to load data from the past session by the binary files if you want to add more data you only need to inser or in vehicles or users csv file.

