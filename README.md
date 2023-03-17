# Vehicle Rental System

This is a simple command-line application written in C that simulates a vehicle rental system. The program allows users to rent and return vehicles, and managers to add and remove vehicles from the fleet.

## Features

- Users can rent and return vehicles
- Managers can add and remove vehicles from the fleet
- Data is read from a CSV file and persisted in a binary file

## Installation

1. Clone the repository: `git clone https://github.com/your-username/vehicle-rental-system.git`
2. Build the project: `make`
3. Run the program: `./vehicle-rental-system`


## Data Storage

The program reads data from a CSV file `vehicles.csv`, and writes data to a binary file `vehicles.dat`. When the program is started, it reads the data from the CSV file and stores it in memory. When the program exits, it writes the data to the binary file. This ensures that the data is persisted between runs of the program.

