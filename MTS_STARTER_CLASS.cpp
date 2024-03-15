/* MTS STARTER CLASS */

/*

in terms of storing the data, this code works as intended.
the issue however seems to be correctly outputting the data and generating a table.
the goal is now to be able to use a database to extract data and organize it in a class.

*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <iomanip>
#include <numeric>

using namespace std;


class TransformerInfo {
public:
    string SERIALNUMBER;
    string PROBLEM;
    string FEEDER;
    string VAULT;
    int YEAR;
    string MONTH;
};


class InfoCollection {
public:
    void addInfo(const TransformerInfo& info) {
        infoList.push_back(info);

        // Update problemTypeData
        problemTypeData[info.PROBLEM + "-" + info.MONTH].push_back(1);
        problemTypeData[info.PROBLEM + "-" + info.MONTH].back() += 1;   // Increment the last element (count) in the vector

    }



    void removeInfo(const string& SERIALNUMBER) {
        auto iterator = find_if(infoList.begin(), infoList.end(), [&SERIALNUMBER](const TransformerInfo& info) {
            return info.SERIALNUMBER == SERIALNUMBER;
        });

        infoList.erase(iterator, infoList.end());
    }

    void displayInfo() {
        for (const auto& info : infoList) {
            cout << "Transformer Information:" << endl;
            cout << "Serial Number: " << info.SERIALNUMBER << endl;
            cout << "Problem Type: " << info.PROBLEM << endl;
            cout << "Feeder: " << info.FEEDER << endl;
            cout << "Vault: " << info.VAULT << endl;
            cout << "----------------------------------------" << endl;
        }
    }

    TransformerInfo* lookupInfo(const string& SERIALNUMBER) {
        auto iterator = find_if(infoList.begin(), infoList.end(), [&SERIALNUMBER](const TransformerInfo& info) {
            return info.SERIALNUMBER == SERIALNUMBER;
        });

        if (iterator != infoList.end()) {
            return &(*iterator);
        }

        return nullptr;
    }

    void performLookup(const InfoCollection& collection, const string& targetSerial) {
        TransformerInfo* foundInfo = lookupInfo(targetSerial);

        if (foundInfo) {
            cout << "Transformer Information: " << endl;
            cout << "Serial Number: " << foundInfo->SERIALNUMBER << endl;
            cout << "Problem Type: " << foundInfo->PROBLEM << endl;
            cout << "Feeder: " << foundInfo->FEEDER << endl;
            cout << "Vault: " << foundInfo->VAULT << endl;
        } else {
            cout << "Serial Number Not Found :(" << endl;
        }
    }

    void editInfo() {
        string SERIALNUMBER;
        string userInput;

        cout << "Please provide a valid serial number: ";
        cin >> SERIALNUMBER;

        TransformerInfo* transformer = lookupInfo(SERIALNUMBER);

        if (transformer) {
            cout << "What would you like to edit? (problem type: p, feeder: f, vault: v) ";
            cin >> userInput;
        
            if (userInput == "p"){
                string newProblem;
                cout << "Please enter the new problem type: ";
                cin >> newProblem;
                transformer->PROBLEM = newProblem;
            } else if (userInput == "f"){
                string newFeeder;
                cout << "Please enter the new feeder: ";
                cin >> newFeeder;
                transformer->FEEDER = newFeeder;
            } else if (userInput == "v") {
                string newVault;
                cout << "Please enter the new vault: ";
                cin >> newVault;
                transformer->VAULT = newVault;
            } else {
                cout << "Invalid Input" << endl;
            }
        } else {
            cout << "Transformer could not be found." << endl;
        }
    }

    const vector<TransformerInfo>& getInfoList() const {
        return infoList;
    }

    void generateProblemTypeData() {
        problemTypeData.clear();

        for (const auto& info : infoList) {
            // Increment the count for the respective problem type and month
            problemTypeData[info.PROBLEM + "-" + info.MONTH].push_back(1);
        }
    }

    const map<string, vector<int>>& getProblemTypeData() const {
        return problemTypeData;
    }

private:
    vector<TransformerInfo> infoList;
    map<string, vector<int>> problemTypeData;
};


TransformerInfo initializeTransformer(InfoCollection& collection) {
    TransformerInfo transformer;

    cout << "What is the year? " << endl;
    cin >> transformer.YEAR;
    cout << "What is the month? " << endl;
    cin >> transformer.MONTH;
    cout << "What is the serial number?" << endl;
    cin >> transformer.SERIALNUMBER;
    cout << "What is your problem type?" << endl;
    cin >> transformer.PROBLEM;
    cout << "What is the feeder number?" << endl;
    cin >> transformer.FEEDER;
    cout << "What is the vault number?" << endl;
    cin >> transformer.VAULT;

    // Add the transformer to the collection
    collection.addInfo(transformer);

    // Update problemTypeData
    collection.generateProblemTypeData();  // Add a function in InfoCollection to generate problemTypeData

    return transformer;
}

int displayMenu() {
    cout << "\nMenu:" << endl;
    cout << "1. Add Transformer" << endl;
    cout << "2. Remove Transformer" << endl;
    cout << "3. Display All Transformers" << endl;
    cout << "4. Lookup Transformer" << endl;
    cout << "5. Edit Transformer" << endl;
    cout << "6. Exit" << endl;
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;
    return choice;
}

void performOperation(InfoCollection& collection, int choice) {
    if (choice == 1) {
        initializeTransformer(collection);
    } else if (choice == 2) {
        string serialNumber;
        cout << "Enter the serial number to remove: ";
        cin >> serialNumber;
        collection.removeInfo(serialNumber);
    } else if (choice == 3) {
        cout << "Displaying all information in the collection: " << endl;
        collection.displayInfo();
        cout << "----------------------------------------" << endl;
    } else if (choice == 4) {
        string targetSerial;
        cout << "Enter a serial number to lookup: ";
        cin >> targetSerial;
        collection.performLookup(collection, targetSerial);
        cout << "----------------------------------------" << endl;
    } else if (choice == 5) {
        collection.editInfo();
        cout << "----------------------------------------" << endl;
    } else if (choice == 6) {
        cout << "Exiting the program. We are finished!" << endl;
        exit(0);
    } else {
        cout << "Invalid choice. Please try again." << endl;
    }
}




/* MONTLY DATA DISPLAY FEATURE */


void generateProblemTypeTable(const vector<string>& months, const vector<int>& years, const map<string, vector<int>>& problemTypeData) {
    // Get unique months and problem types
    vector<string> uniqueMonths = months;
    sort(uniqueMonths.begin(), uniqueMonths.end());
    uniqueMonths.erase(unique(uniqueMonths.begin(), uniqueMonths.end()), uniqueMonths.end());

    vector<string> uniqueProblemTypes;
    for (const auto& pair : problemTypeData) {
        uniqueProblemTypes.push_back(pair.first);
    }
    sort(uniqueProblemTypes.begin(), uniqueProblemTypes.end());

    // Display the table header
    cout << setw(10) << "Year" << setw(10) << "Month";
    for (const auto& type : uniqueProblemTypes) {
        cout << setw(10) << type;
    }
    cout << setw(10) << "Total" << endl;

    // Display the table content
    for (const auto& year : years) {
        for (const auto& month : uniqueMonths) {
            int monthlyTotal = 0;

            cout << setw(10) << year << setw(10) << month;

            for (const auto& type : uniqueProblemTypes) {
                // Find the counts for the specific month, year, and problem type
                auto it = find_if(problemTypeData.at(type).begin(), problemTypeData.at(type).end(),
                    [&month, &year, &type](int entry) {
                        return (to_string(entry) == to_string(year) + "-" + type + "-" + month);
                    });

                int count = (it != problemTypeData.at(type).end()) ? 1 : 0;  // Update based on your data structure
                monthlyTotal += count;

                cout << setw(10) << count;
            }

            cout << setw(10) << monthlyTotal << endl;
        }
    }

    // Display the table totals
    cout << setw(10) << "Total" << setw(10) << "";
    for (const auto& type : uniqueProblemTypes) {
        int typeTotal = accumulate(problemTypeData.at(type).begin(), problemTypeData.at(type).end(), 0);
        cout << setw(10) << typeTotal;
    }
    cout << setw(10) << "" << endl;
}






int main() {
    InfoCollection collection;
    
    // Initialize months, years, and problemTypeData before entering the loop
    vector<string> months;
    vector<int> years;
    map<string, vector<int>> problemTypeData;

    int choice = displayMenu();

    while (choice != 6) {
        performOperation(collection, choice);
        choice = displayMenu();
    }

    // Generate and display the problem type table
    for (const auto& info : collection.getInfoList()) {
        // Add months and years
        months.push_back(info.MONTH);
        years.push_back(info.YEAR);

        // Increment the count for the respective problem type
        problemTypeData[info.PROBLEM].push_back(1);
    }

    // Generate and display the problem type table
    cout << "Generating Table...." << endl;
    generateProblemTypeTable(months, years, problemTypeData);

    return 0;
}





/*

***
TESTING CODE TO ENSURE THE SYSTEM WORKS AS INTENDED
***

    InfoCollection collection;


    collection.addInfo(initializeTransformer());
    collection.addInfo(initializeTransformer());
    collection.addInfo(initializeTransformer());


    cout << "Displaying all information in the collection:" << endl;
    collection.displayInfo();
    cout << "----------------------------------------" << endl;


    string targetSerial;
    cout << "Enter a serial number to lookup: ";
    cin >> targetSerial;
    collection.performLookup(collection, targetSerial);
    cout << "----------------------------------------" << endl;


    collection.editInfo();
    cout << "----------------------------------------" << endl;


    cout << "Displaying all information in the collection after edits:" << endl;
    collection.displayInfo();

    return 0;



*/