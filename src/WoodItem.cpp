/*
 * WoodItem.cpp
 *
 *  Created on: Aug 24, 2015
 *      Author: Chris Walker
 */

#include "WoodItem.h"

/*
 * Empty constructor
 */
WoodItem::WoodItem() {
	type = "";
	baseDeliveryTime = 0.0;
	price = 0.0;
}

/*
 * Full constructor to initialize type of wood, the base delivery time, and the price per board foot
 */
WoodItem::WoodItem(std::string woodType, double deliveryTime, double itemPrice) {
	type = woodType;
	baseDeliveryTime = deliveryTime;
	price = itemPrice;
}

