#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    cout << "Quel uber? Entrez 1 pour X, 2 pour POP ou 3 pour BLACK" << endl
         << "Combien de minutes ecoulees?" << endl;

    int uberType;
    double minutes, kilometers = 0;
    cin >> uberType >> minutes;

    bool isCanceled = true;

    if (minutes > 0) {
        isCanceled = false;

        cout << "Combien de kilometres parcourus?" << endl;
        cin >> kilometers;
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

    if (isCanceled) rightColumnSize--; // The spacing is different when the run is canceled

    // Find the longest string to size the left column of the bill
    const array<string, 10> billLabels = {" Frais annulation ", " distance ", " temps ecoule ", " Prix de base ",
                                          " Prix distance ", " Prix temps ", " Total ", " Course mimimale ", " Prix ",
                                          " (incl. TVA) "};

    int leftColumnSize = 0;

    for (auto &billLabel: billLabels) {
        if (billLabel.length() > leftColumnSize) {
            leftColumnSize = billLabel.length();
        }
    }

    const char BILL_CORNER_CHARACTER = '+', BILL_HORIZONTAL_CHARACTER = '-', BILL_VERTICAL_CHARACTER = '|',
            BILL_SEPARATOR_CHARACTER = ':';
    const array<string, 3> UBER_NAMES = {"uberX", "uberPOP", "uberBLACK"};

    string uberName = UBER_NAMES[uberType];

    int billWidth = leftColumnSize + rightColumnSize + 2; // 1 for the separator character and 1 for the right border
    int widthForCenter = (billWidth / 2 + uberName.length() / 2) + 1; // To center the title, + 1 is for the left border

    // Store redundant strings in variables
    ostringstream horizontalBorder, sectionSeparator;

    horizontalBorder << BILL_CORNER_CHARACTER << setw(billWidth) << setfill(BILL_HORIZONTAL_CHARACTER)
                     << BILL_CORNER_CHARACTER << endl;
    sectionSeparator << BILL_VERTICAL_CHARACTER << setw(billWidth) << setfill(' ') << BILL_VERTICAL_CHARACTER
                     << endl;

    // Header
    cout << horizontalBorder.str();
    cout << sectionSeparator.str();
    cout << BILL_VERTICAL_CHARACTER << setw(widthForCenter) << uberName << setw(billWidth - widthForCenter)
         << BILL_VERTICAL_CHARACTER << endl;
    cout << sectionSeparator.str();

    if (isCanceled) {
        cout << BILL_VERTICAL_CHARACTER << setw(leftColumnSize) << left << billLabels[0] << BILL_SEPARATOR_CHARACTER
             << setw(rightColumnSize) << right << billValues[0] << BILL_VERTICAL_CHARACTER << endl;
        cout << sectionSeparator.str();
    } else {
        // Distance
        cout << BILL_VERTICAL_CHARACTER << setw(leftColumnSize) << left << billLabels[1] << BILL_SEPARATOR_CHARACTER
             << setw(rightColumnSize) << right << billValues[1] << BILL_VERTICAL_CHARACTER << endl;
        // Elapsed time
        cout << BILL_VERTICAL_CHARACTER << setw(leftColumnSize) << left << billLabels[2] << BILL_SEPARATOR_CHARACTER
             << setw(rightColumnSize) << right << billValues[2] << BILL_VERTICAL_CHARACTER << endl;
        cout << sectionSeparator.str();
        // Base price
        cout << BILL_VERTICAL_CHARACTER << setw(leftColumnSize) << left << billLabels[3] << BILL_SEPARATOR_CHARACTER
             << setw(rightColumnSize) << right << billValues[3] << BILL_VERTICAL_CHARACTER << endl;
        // Distance price
        cout << BILL_VERTICAL_CHARACTER << setw(leftColumnSize) << left << billLabels[4] << BILL_SEPARATOR_CHARACTER
             << setw(rightColumnSize) << right << billValues[4] << BILL_VERTICAL_CHARACTER << endl;
        // Time price
        cout << BILL_VERTICAL_CHARACTER << setw(leftColumnSize) << left << billLabels[5] << BILL_SEPARATOR_CHARACTER
             << setw(rightColumnSize) << right << billValues[5] << BILL_VERTICAL_CHARACTER << endl;
        // Total
        cout << BILL_VERTICAL_CHARACTER << setw(leftColumnSize) << left << billLabels[6] << BILL_SEPARATOR_CHARACTER
             << setw(rightColumnSize) << right << billValues[6] << BILL_VERTICAL_CHARACTER << endl;
        cout << sectionSeparator.str();
        // Minimum price
        if (total < minimumPrice) {
            cout << BILL_VERTICAL_CHARACTER << setw(leftColumnSize) << left << billLabels[7]
                 << BILL_SEPARATOR_CHARACTER << setw(rightColumnSize) << right << billValues[7]
                 << BILL_VERTICAL_CHARACTER << endl;
            cout << sectionSeparator.str();
        }
    }

    // Price
    cout << BILL_VERTICAL_CHARACTER << setw(leftColumnSize) << left << billLabels[8] << BILL_SEPARATOR_CHARACTER
         << setw(rightColumnSize) << right << billValues[7] << BILL_VERTICAL_CHARACTER << endl;
    // TVA
    cout << BILL_VERTICAL_CHARACTER << setw(leftColumnSize) << left << billLabels[9] << BILL_SEPARATOR_CHARACTER
         << setw(rightColumnSize) << right << billValues[8] << BILL_VERTICAL_CHARACTER << endl;
    // Footer
    cout << sectionSeparator.str();
    cout << horizontalBorder.str();

    return 0;
}
