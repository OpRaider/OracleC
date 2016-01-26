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
#include "WoodItem.h"

using namespace std;

vector<WoodItem> woodTypes;

/*
 * Main method
 * Gets valid user input, passes it to readInputFile
 */
int main() {
	
	string userInput;
	ifstream orderFile;

	initWoodTypes();

	while (cout << "Enter desired filename: " && getline(cin, userInput) {
		orderFile.open(userInput.c_str(), in);

		if (orderFile.is_open()) {
			readInputFile(userInput, orderFile);
			close(orderFile);
			break;
		}

		cerr << "Invalid filename, try again.\n";
	}

	cout << "Press any key to exit..." << endl;
	cin.get();
	return 0;
}

void initWoodTypes() {
	woodTypes.insert(new WoodItem("Cherry", 2.5, 5.95));
	woodTypes.insert(new WoodItem("Curly Maple", 1.5, 6.00));
	woodTypes.insert(new WoodItem("Genuine Mahogany", 3, 9.60));
	woodTypes.insert(new WoodItem("Wenge", 5, 22.35));
	woodTypes.insert(new WoodItem("White Oak", 2.3, 6.70));
	woodTypes.insert(new WoodItem("Sawdust", 1, 1.50));
}

/*
 * Method to read the input file
 */
void readInputFile(string inputFilePath, ifstream orderFile) {

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
	while (ch != ';') {
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
	string type = "", amountString = "";
	int amount;
	int total = 0;
	double maxDeliveryTime = 0;

	cout << "List of ordered wood:\n\n";
	while (orderFile.good()) {
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

		amount = stoi(amountString); 

		cout << type << ':' << amountString << "BF\nPrice: ";

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
	cout << defaultfloat << "Estimated delivery time: " << maxDeliveryTime << " hours\n";
	cout << setprecision(2) << fixed << "Total price: " << total << endl << endl;
}

/*
 * Method to compute the deliveryTime
 */
double deliveryTime(int amount) {
	if      (amount > 500)	return 5.5;
	else if (amount > 400)	return 5;
	else if (amount > 300)	return 4;
	else if (amount > 200)	return 3;
	else if (amount > 100)	return 2;
	else					return 1;
}
