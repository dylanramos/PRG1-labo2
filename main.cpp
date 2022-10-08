#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    cout << "Quel uber? Entrez 1 pour X, 2 pour POP ou 3 pour BLACK" << endl;
    int uberType;
    cin >> uberType;

    while (uberType < 1 || uberType > 3) {
        cout << "Ce type de uber n'existe pas" << endl;
        cin >> uberType;
    }

    cout << "Combien de minutes ecoulees?" << endl;
    double minutes, kilometers = 0;
    cin >> minutes;

    bool isCanceled = true;

    if (minutes > 0) {
        isCanceled = false;

        cout << "Combien de kilometres parcourus?" << endl;
        cin >> kilometers;

        while (kilometers < 0.) {
            cout << "Impossible de faire des kilometres negatifs" << endl;
            cin >> kilometers;
        }
    }

    cout << endl; // Blank spaces before the bill

    const double UBER_VALUES[3][5] = {{3.0, 1.8,  0.3, 6.0,  6.0},
                                      {3.0, 1.35, 0.3, 6.0,  6.0},
                                      {8.0, 3.6,  0.6, 15.0, 10.0}};

    uberType--; // To match with the array of uber values

    double basePrice = UBER_VALUES[uberType][0], kilometerPrice = UBER_VALUES[uberType][1],
            minutePrice = UBER_VALUES[uberType][2], minimumPrice = UBER_VALUES[uberType][3],
            cancelPrice = UBER_VALUES[uberType][4];

    minutes = ceil(minutes);
    kilometers = round(kilometers * 10) / 10; // Round to the nearest 100 meters

    const int TVA = 8;
    double distancePrice, timePrice, total, price, tvaPrice;

    distancePrice = round(kilometerPrice * kilometers * 100) / 100,
    timePrice = minutePrice * minutes,
    total = basePrice + distancePrice + timePrice;
    price = total;

    if (isCanceled) {
        price = cancelPrice;
    } else if (total < minimumPrice) {
        price = minimumPrice;
    }

    tvaPrice = (price / (100 + TVA)) * TVA;

    // Prepare the strings containing the different values
    ostringstream strCancelPrice, strDistance, strElapsedTime, strBasePrice, strDistancePrice, strTimePrice, strTotal,
            strPrice, strTva;

    strCancelPrice << fixed << setprecision(2) << " " << cancelPrice << " ";
    strDistance << fixed << setprecision(1) << " " << kilometers << " km ";
    strElapsedTime << fixed << setprecision(0) << minutes << " min ";
    strBasePrice << fixed << setprecision(2) << " " << basePrice << " ";
    strDistancePrice << fixed << setprecision(2) << " " << distancePrice << " ";
    strTimePrice << fixed << setprecision(2) << " " << timePrice << " ";
    strTotal << fixed << setprecision(2) << " " << total << " ";
    strPrice << fixed << setprecision(2) << " " << price << " ";
    strTva << fixed << setprecision(2) << " " << tvaPrice << " ";

    // Find the longest string to size the right column of the bill
    array<string, 9> billValues = {strCancelPrice.str(), strDistance.str(), strElapsedTime.str(), strBasePrice.str(),
                                   strDistancePrice.str(), strTimePrice.str(), strTotal.str(), strPrice.str(),
                                   strTva.str()};
    int rightColumnSize = 0;

    for (auto &billValue: billValues) {
        if (billValue.length() > rightColumnSize) {
            rightColumnSize = billValue.length() + 3;
        }
    }

    // Find the longest string to size the left column of the bill
    const array<string, 10> BILL_LABELS = {"Frais annulation", "distance", "temps ecoule", "Prix de base",
                                           "Prix distance", "Prix temps", "Total", "Course mimimale", "Prix",
                                           "(incl. TVA)"};

    if (isCanceled) rightColumnSize--; // The spacing is different when the run is canceled

    int leftColumnSize = 0;

    for (auto &billLabel: BILL_LABELS) {
        if (billLabel.length() > leftColumnSize) {
            leftColumnSize = billLabel.length() + 1;
        }
    }

    const char BILL_CORNER_CHAR = '+', BILL_HORIZONTAL_CHAR = '-', BILL_VERTICAL_CHAR = '|', BILL_SEPARATOR_CHAR = ':';
    const array<string, 3> UBER_NAMES = {"uberX", "uberPOP", "uberBLACK"};

    string uberName = UBER_NAMES[uberType];

    int billWidth = leftColumnSize + rightColumnSize + 3; // 1 for the separator character and 1 for the right border
    int widthForCenter = (billWidth / 2 + uberName.length() / 2) + 1; // To center the title, + 1 is for the left border

    // Store redundant strings in variables
    ostringstream horizontalBorder, sectionSeparator;

    horizontalBorder << BILL_CORNER_CHAR << setw(billWidth) << setfill(BILL_HORIZONTAL_CHAR)
                     << BILL_CORNER_CHAR << endl;
    sectionSeparator << BILL_VERTICAL_CHAR << setw(billWidth) << setfill(' ') << BILL_VERTICAL_CHAR
                     << endl;

    // Header
    cout << horizontalBorder.str();
    cout << sectionSeparator.str();
    cout << BILL_VERTICAL_CHAR << setw(widthForCenter) << uberName << setw(billWidth - widthForCenter)
         << BILL_VERTICAL_CHAR << endl;
    cout << sectionSeparator.str();

    if (isCanceled) {
        cout << BILL_VERTICAL_CHAR << " " << setw(leftColumnSize) << left << BILL_LABELS[0]
             << BILL_SEPARATOR_CHAR
             << setw(rightColumnSize) << right << billValues[0] << BILL_VERTICAL_CHAR << endl;
        cout << sectionSeparator.str();
    } else {
        // Distance
        cout << BILL_VERTICAL_CHAR << " " << setw(leftColumnSize) << left << BILL_LABELS[1]
             << BILL_SEPARATOR_CHAR
             << setw(rightColumnSize) << right << billValues[1] << BILL_VERTICAL_CHAR << endl;
        // Elapsed time
        cout << BILL_VERTICAL_CHAR << " " << setw(leftColumnSize) << left << BILL_LABELS[2]
             << BILL_SEPARATOR_CHAR
             << setw(rightColumnSize) << right << billValues[2] << BILL_VERTICAL_CHAR << endl;
        cout << sectionSeparator.str();
        // Base price
        cout << BILL_VERTICAL_CHAR << " " << setw(leftColumnSize) << left << BILL_LABELS[3]
             << BILL_SEPARATOR_CHAR
             << setw(rightColumnSize) << right << billValues[3] << BILL_VERTICAL_CHAR << endl;
        // Distance price
        cout << BILL_VERTICAL_CHAR << " " << setw(leftColumnSize) << left << BILL_LABELS[4]
             << BILL_SEPARATOR_CHAR
             << setw(rightColumnSize) << right << billValues[4] << BILL_VERTICAL_CHAR << endl;
        // Time price
        cout << BILL_VERTICAL_CHAR << " " << setw(leftColumnSize) << left << BILL_LABELS[5]
             << BILL_SEPARATOR_CHAR
             << setw(rightColumnSize) << right << billValues[5] << BILL_VERTICAL_CHAR << endl;
        // Total
        cout << BILL_VERTICAL_CHAR << " " << setw(leftColumnSize) << left << BILL_LABELS[6]
             << BILL_SEPARATOR_CHAR
             << setw(rightColumnSize) << right << billValues[6] << BILL_VERTICAL_CHAR << endl;
        cout << sectionSeparator.str();
        // Minimum price
        if (total < minimumPrice) {
            cout << BILL_VERTICAL_CHAR << " " << setw(leftColumnSize) << left << BILL_LABELS[7]
                  << BILL_SEPARATOR_CHAR << setw(rightColumnSize) << right << billValues[7]
                 << BILL_VERTICAL_CHAR << endl;
            cout << sectionSeparator.str();
        }
    }

    // Price
    cout << BILL_VERTICAL_CHAR << " " << setw(leftColumnSize) << left << BILL_LABELS[8] << BILL_SEPARATOR_CHAR
         << setw(rightColumnSize) << right << billValues[7] << BILL_VERTICAL_CHAR << endl;
    // TVA
    cout << BILL_VERTICAL_CHAR << " " << setw(leftColumnSize) << left << BILL_LABELS[9] << BILL_SEPARATOR_CHAR
         << setw(rightColumnSize) << right << billValues[8] << BILL_VERTICAL_CHAR << endl;
    // Footer
    cout << sectionSeparator.str();
    cout << horizontalBorder.str();

    return 0;
}
