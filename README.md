# Event Ease
We've created Event Ease, a C++ project that uses the Qt framework to provide a graphical user interface. Our team designed the application to manage and analyze event data from various years.
# Project Info( Only for files inside mainCal folder)

## Project Structure

The project is organized as follows:

- **.vscode/**
  - `settings.json`
  
- **assets/**
  - **data/**
    - `1992/`
    - ...
    - `2031/`
  - `data.json`
  - `icons/`
  - `package.json`
  - `scraper.js`
  
- `event_ease.pro`
- `main.cpp`
- `mainwindow.cpp`
- `mainwindow.h`
- `mainwindow.ui`
- `styles.qss`


## Components
Here are the main components of our project:

- `mainwindow.cpp`: This file defines the main window of the application, including its layout and functionality. It includes features like displaying Nepali and English dates simultaneously, navigation via combo boxes for months and years, highlighting the current date with a distinct style, offering a sidebar for adding notes for each day, and converting between Nepali and English dates.

- `main.cpp`: This is the entry point of the application.

- `assets/data/`: This directory contains subdirectories for each year, which hold data for events in those years.

- `assets/scraper.js`: We use this JavaScript file for web scraping to gather event data.

- `assets/icons/`: This directory contains the icons we use in the application.

- `styles.qss`: This file contains the styles for the Qt widgets used in the application.

## Build Instructions

To run the program, please follow these steps:

1. Change the build settings to use the Release build mode.
2. Disable Shadow Build.

Alternatively, you can directly use `qmake` and `make` from the terminal, which was the method our team used during development.
# Group Members
### Siddhanta Adhikari
### Prabin Aryal
### Bikesh Khatri
### Nabin Kafle
