# Transformer Information Management System

This project aims to manage and analyze transformer data, including serial numbers, problem types, feeders, and vault numbers. The system allows users to add, remove, display, lookup, and edit transformer information. Additionally, it generates a table displaying the count of each problem type per month and year.

## Overview

The Transformer Information Management System is designed to help manage transformer maintenance data efficiently. It allows you to keep track of transformer issues, locate specific transformers by their serial numbers, and update their information as needed. This tool is particularly useful for utility companies and maintenance teams who need to monitor and resolve transformer problems systematically.

## Features

1. **Add Transformer**: Add new transformer information to the collection.
2. **Remove Transformer**: Remove transformer information from the collection by serial number.
3. **Display All Transformers**: Display all transformer information stored in the collection.
4. **Lookup Transformer**: Search for a transformer by its serial number and display its information.
5. **Edit Transformer**: Edit the problem type, feeder, or vault number of an existing transformer.
6. **Generate Problem Type Table**: Generate a table that displays the count of each problem type for each month and year.

## Classes and Functions

### Class: TransformerInfo
This class stores the following information about a transformer:
- Serial Number (`SERIALNUMBER`)
- Problem Type (`PROBLEM`)
- Feeder (`FEEDER`)
- Vault (`VAULT`)
- Year (`YEAR`)
- Month (`MONTH`)

### Class: InfoCollection
This class manages a collection of `TransformerInfo` objects and provides the following functionalities:
- `addInfo(const TransformerInfo& info)`: Adds a new transformer to the collection and updates the problem type data.
- `removeInfo(const string& SERIALNUMBER)`: Removes a transformer from the collection by serial number.
- `displayInfo()`: Displays all transformer information in the collection.
- `lookupInfo(const string& SERIALNUMBER)`: Looks up a transformer by its serial number and returns its information.
- `performLookup(const InfoCollection& collection, const string& targetSerial)`: Performs a lookup and displays the transformer information.
- `editInfo()`: Edits the problem type, feeder, or vault number of a transformer by serial number.
- `generateProblemTypeData()`: Generates problem type data for the collection.
- `getProblemTypeData() const`: Returns the problem type data.
- `getInfoList() const`: Returns the list of transformers.

### Functions
- `TransformerInfo initializeTransformer(InfoCollection& collection)`: Initializes a new transformer and adds it to the collection.
- `int displayMenu()`: Displays the menu and returns the user's choice.
- `void performOperation(InfoCollection& collection, int choice)`: Performs the operation based on the user's choice.
- `void generateProblemTypeTable(const vector<string>& months, const vector<int>& years, const map<string, vector<int>>& problemTypeData)`: Generates and displays a table showing the count of each problem type per month and year.

## Getting Started

### Prerequisites
- C++ compiler

### Installation
1. Clone the repository or download the source code.
2. Compile the code using a C++ compiler.
   ```bash
   g++ -o transformer_management_system main.cpp
