//============================================================================
// Name        : HardwoodSellerC.cpp
// Author      : Esteban Parra
// Version     : 1
// Copyright   : It's free
// Description : Main class for the Hardwood Seller
// Editor      : Chris Walker
//============================================================================

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>

#include "WoodItem.h"

using namespace std;

vector<WoodItem> woodTypes;

void initWoodTypes() {
	woodTypes.push_back(WoodItem("Cherry", 2.5, 5.95));
	woodTypes.push_back(WoodItem("Curly Maple", 1.5, 6.00));
	woodTypes.push_back(WoodItem("Genuine Mahogany", 3, 9.60));
	woodTypes.push_back(WoodItem("Wenge", 5, 22.35));
	woodTypes.push_back(WoodItem("White Oak", 2.3, 6.70));
	woodTypes.push_back(WoodItem("Sawdust", 1, 1.50));
}
/*
 * Method to compute the base deliveryTime
 */
double deliveryTime(int amount) {
	if      (amount > 500)	return 5.5;
	else if (amount > 400)	return 5;
	else if (amount > 300)	return 4;
	else if (amount > 200)	return 3;
	else if (amount > 100)	return 2;
	else					return 1;
}

/*
 * Method to read the input file
 */
void readInputFile(string inputFilePath, ifstream &orderFile) {

	char ch = orderFile.get();

	// Print buyer's name
	cout << "Buyer's name: ";
	while (ch != ';') {
		cout << ch;
		ch = orderFile.get();
	}
	ch = orderFile.get();
	cout << endl;

	// Print buyer's address
	cout << "Buyer's address: ";
	while (ch != ';') {
		cout << ch;
		ch = orderFile.get();
	}
	ch = orderFile.get();
	cout << endl;

	// Skip date
	while (ch != '\n') {
		ch = orderFile.get();
	}

	// Print list of ordered wood
	// Example Format:
	// List of ordered wood:
	//
	// <Type1>:<Amount>
	// Price: <Price>
	//
	// <Type2>:<Amount>
	// Price: <Price>
	// <etc...>
	string type, amountString;
	int amount;
	double total = 0;
	double maxDeliveryTime = 0;

	cout << "List of ordered wood:\n\n";
	while (orderFile.good()) {
		type = "";
		amountString = "";

		ch = orderFile.get();

		// Print type
		while (ch != ':') {
			type += ch;
			ch = orderFile.get();
		}
		ch = orderFile.get();

		// Print amount
		while (ch != ';' && orderFile.good()) {
			amountString += ch;
			ch = orderFile.get();
		}

		amount = atoi(amountString.c_str()); 

		if (*(amountString.end() - 1) == '\n')
			amountString.erase(amountString.end() - 1);

		cout << type << ": " << amountString << " BF\nPrice: $";

		// Print subtotal price of type, add subtotal to total, and save max delivery time
		for (int i = 0; i < woodTypes.size(); i++) {
			if (woodTypes[i].type == type) {
				double typeSubtotal = amount * woodTypes[i].price;
				cout << setprecision(2) << fixed << typeSubtotal << endl << endl;
				total += typeSubtotal;
				if (deliveryTime(amount) * woodTypes[i].baseDeliveryTime > maxDeliveryTime)
					maxDeliveryTime = deliveryTime(amount) * woodTypes[i].baseDeliveryTime;

				break;
			}
		}
	}
	cout.unsetf(ios_base::floatfield);
	cout << "Estimated delivery time: " << maxDeliveryTime << " hours\n";
	cout << setprecision(2) << fixed << "Total price: $" << total << endl << endl;
}

/*
 * Main method
 * Gets valid user input, passes it to readInputFile
 */
int main() {
	
	string userInput;
	ifstream orderFile;

	initWoodTypes();

	while (cout << "Enter desired filename: " && getline(cin, userInput)) {
		orderFile.open(userInput.c_str(), ifstream::in);

		if (orderFile.is_open()) {
			readInputFile(userInput, orderFile);
			orderFile.close();
			break;
		}

		cerr << "Invalid filename, try again.\n";
	}

	return 0;
}
