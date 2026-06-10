// ============================================================
// Name    : Sunny Rodrigues
// Course  : COSC 1437 - Programming Fundamentals II
// Date    : June 9, 2026
// Program : Chapter 4 Major Project
// Option  : [A - Hotel Billing
// Purpose : Calculates a hotel customer's bill by applying
// room discounts, loyalty discounts, and sales tax.
// ============================================================

/*
// ============================================================
    SECTION 1 - PSEUDOCODE DESIGN BLOCK
// ============================================================

START PROGRAM

INPUT nightlyRate, rooms, nights, taxRate

IF nightlyRate <= 0
    STOP (invalid input)
ELSE IF rooms <= 0
    STOP (invalid input)
ELSE IF nights <= 0
    STOP (invalid input)
ELSE IF taxRate < 0
    STOP (invalid input)

IF rooms >= 30
    discountTier = 3
ELSE IF rooms >= 20
    discountTier = 2
ELSE IF rooms >= 10
    discountTier = 1
ELSE
    discountTier = 0

IF nights >= 3 AND rooms > 0
    apply loyalty discount after room discount
ELSE
    no loyalty discount

COMPUTE subtotal = rooms * nights * nightlyRate
APPLY room discount
APPLY loyalty discount
COMPUTE tax
COMPUTE total

SWITCH discountTier
    CASE 3 -> "30% discount"
    CASE 2 -> "20% discount"
    CASE 1 -> "10% discount"
    DEFAULT -> "No discount"

PRINT receipt

END PROGRAM
=========================================================
*/

#include <iostream>
#include <iomanip>
#include <cassert>
#include <cmath>

using namespace std;

int main()
{
// ============================================================
// SECTION 2 - INPUT & VALIDATION
// ============================================================

const int MIN_ROOMS_TIER1 = 10;
const int MIN_ROOMS_TIER2 = 20;
const int MIN_ROOMS_TIER3 = 30;

const int MIN_NIGHTS_LOYALTY = 3;

const double DISCOUNT_TIER1 = 0.10;
const double DISCOUNT_TIER2 = 0.20;
const double DISCOUNT_TIER3 = 0.30;

const double LOYALTY_DISCOUNT = 0.05;

const double EPSILON = 0.0001;

double nightlyRate;
int roomCount;
int nightsStayed;
double taxRate;

cout << "Enter nightly room rate: $";
cin >> nightlyRate;

// Room rate must be positive.
assert(nightlyRate > 0.0);

cout << "Enter number of rooms booked: ";
cin >> roomCount;

// Must reserve at least one room.
assert(roomCount > 0);

cout << "Enter number of nights stayed: ";
cin >> nightsStayed;

// Stay length must be positive.
assert(nightsStayed > 0);

cout << "Enter sales tax rate (%): ";
cin >> taxRate;

// Tax rate cannot be negative.
assert(taxRate >= 0.0);

// ============================================================
// SECTION 3 - OPERATOR PRECEDENCE REFERENCE
// ============================================================

/*
Expression:

!(rooms > 0) || (rate >= 50.0 && rooms != nights)

Sample Values:
    rooms = 15
    rate = 100
    nights = 4

!(15 > 0) || (100 >= 50.0 && 15 != 4)

!(true) || (true && true)

false || true

Result: true
*/

// ============================================================
// SECTION 4 - CORE LOGIC
// ============================================================

double discountPercent;
int discountTier;

if (roomCount >= MIN_ROOMS_TIER3)
{
    discountPercent = DISCOUNT_TIER3;
    discountTier = 3;
}
else if (roomCount >= MIN_ROOMS_TIER2)
{
    discountPercent = DISCOUNT_TIER2;
    discountTier = 2;
}
else if (roomCount >= MIN_ROOMS_TIER1)
{
    discountPercent = DISCOUNT_TIER1;
    discountTier = 1;
}
else
{
    discountPercent = 0.0;
    discountTier = 0;
}

double subtotal =
    roomCount * nightsStayed * nightlyRate;

// Apply room discount first
double discounted = subtotal * (1.0 - discountPercent);

// Apply loyalty discount if eligible
if (discountTier > 0 && nightsStayed >= MIN_NIGHTS_LOYALTY)
{
    discounted *= (1.0 - LOYALTY_DISCOUNT);
}

// Compound Boolean expression using &&
// Checks whether customer qualifies for both discounts.
if (roomCount >= MIN_ROOMS_TIER1 && nightsStayed >= MIN_NIGHTS_LOYALTY)
{
    cout << "\nCustomer qualifies for both discounts.\n";
}

double taxAmount =
    discounted * (taxRate / 100.0);

double totalBill =
    discounted + taxAmount;

// ============================================================
// SECTION 5 - SWITCH STATEMENT
// ============================================================

switch (discountTier)
{
    case 0:
        cout << "\nDiscount Tier: No Discount\n";
        cout << "Customer booked fewer than 10 rooms.\n";
        break;

    case 1:
        cout << "\nDiscount Tier 1 (10%)\n";
        cout << "Customer booked at least 10 rooms.\n";
        break;

    case 2:
        cout << "\nDiscount Tier 2 (20%)\n";
        cout << "Customer booked at least 20 rooms.\n";
        break;

    case 3:
        cout << "\nDiscount Tier 3 (30%)\n";
        cout << "Customer booked at least 30 rooms.\n";
        break;

    default:
        cout << "\nError: Invalid discount tier.\n";
}

// ============================================================
// SECTION 6 - RELATIONAL & LOGICAL OPERATOR SHOWCASE
// ============================================================

if (roomCount > MIN_ROOMS_TIER1)
    cout << "Operator > demonstrated.\n";

if (roomCount < MIN_ROOMS_TIER3)
    cout << "Operator < demonstrated.\n";

if (roomCount >= MIN_ROOMS_TIER1)
    cout << "Operator >= demonstrated.\n";

if (roomCount <= MIN_ROOMS_TIER3)
    cout << "Operator <= demonstrated.\n";

if (discountTier == 0)
    cout << "Operator == demonstrated.\n";

if (roomCount != nightsStayed)
    cout << "Operator != demonstrated.\n";

if (roomCount >= MIN_ROOMS_TIER3 ||
    nightsStayed >= MIN_NIGHTS_LOYALTY)
    cout << "Operator || demonstrated.\n";

if (!(roomCount <= 0))
    cout << "Operator ! demonstrated.\n";

// ============================================================
// SECTION 7 - FLOATING-POINT BUG GUARD
// ============================================================

/*
Floating-Point Equality Warning

Using == with floating-point values is unreliable
because decimal values are stored approximately.

This program uses an epsilon comparison.

fabs(value1 - value2) < EPSILON

EPSILON = 0.0001
*/

if (fabs(taxAmount - 0.0) < EPSILON)
{
    cout << "No sales tax applied.\n";
}

// ============================================================
// SECTION 8 - FORMATTED OUTPUT / RECEIPT
// ============================================================

cout << fixed << showpoint << setprecision(2);

cout << "\n=========================================\n";
cout << "          HOTEL BILLING RECEIPT\n";
cout << "=========================================\n";

cout << left << setw(30)
     << "Nightly Rate:"
     << "$" << nightlyRate << endl;

cout << left << setw(30)
     << "Discount Percent Applied:"
     << discountPercent * 100 << "%" << endl;

cout << left << setw(30)
     << "Discounted Subtotal:"
     << "$" << discounted << endl;

cout << left << setw(30)
     << "Rooms Booked:"
     << roomCount << endl;

cout << left << setw(30)
     << "Nights Stayed:"
     << nightsStayed << endl;

cout << left << setw(30)
     << "Subtotal Before Tax:"
     << "$" << subtotal << endl;

cout << left << setw(30)
     << "Sales Tax Amount:"
     << "$" << taxAmount << endl;

cout << left << setw(30)
     << "Total Billing Amount:"
     << "$" << totalBill << endl;

cout << "=========================================\n";

return 0;
}

// ============================================================
// SECTION 9 — KNOWN BUG RISKS
// ============================================================

/*
1. Missing break statement in switch:
   Risk: Without break statements, execution could "fall through"
   into the next case, causing multiple discount messages or incorrect
   tier output.
   Prevention: Added a break; at the end of every case and included
   a default clause to handle unexpected values safely.

2. Incorrect order of calculations:
   Risk: If subtotal, discounts, and tax are not calculated in the correct order,
   the final billing amount could be incorrect (e.g., applying tax before discounts).
   Prevention: Followed a strict sequence: calculate subtotal first, then apply
   discounts, then calculate tax, and finally compute the total bill.

3. Floating-point precision errors:
   Risk: Floating-point values may not be stored exactly, which can cause
   inaccurate comparisons when using ==.
   Prevention: Used EPSILON tolerance with fabs() to safely compare values.

*/
