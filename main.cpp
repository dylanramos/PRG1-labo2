#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    cout << "Quel uber? Entrez 1 pour X, 2 pour POP, 3 pour BLACK ou 4 pour ULTIMATE" << endl;
    int uberType;
    cin >> uberType;

    while (uberType < 1 || uberType > 4) {
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

    cout << endl; // Blank space before the bill

    const double UBER_VALUES[4][5] = {{3.0, 1.8,  0.3, 6.0,  6.0},
                                      {5.0, 1.35, 0.3, 8.0,  10.0},
                                      {8.0, 3.6,  0.6, 15.0, 10.0},
                                      {10.0, 4.9, 0.9, 20.0, 25.0}};

    --uberType; // To match with the array of uber values

    double basePrice = UBER_VALUES[uberType][0], kilometerPrice = UBER_VALUES[uberType][1],
            minutePrice = UBER_VALUES[uberType][2], minimumPrice = UBER_VALUES[uberType][3],
            cancelPrice = UBER_VALUES[uberType][4];

    minutes = ceil(minutes);
    kilometers = round(kilometers * 10) / 10; // Round to the nearest 100 meters

    const double TVA = 7.7;
    double distancePrice, timePrice, total, price, tvaPrice;

    distancePrice = round(kilometerPrice * kilometers * 20) / 20, // Round to nearest .05
    timePrice = round(minutePrice * minutes * 20) / 20,
    total = basePrice + distancePrice + timePrice;
    price = total;

    if (isCanceled) {
        price = cancelPrice;
    } else if (total < minimumPrice) {
        price = minimumPrice;
    }

    tvaPrice = (price / (100 + TVA)) * TVA;

    const array<string, 2> UNITS = {"km", "min"}; // Units at the end of values

    // Prepare the strings containing the different values
    ostringstream strCancelPrice, strDistance, strElapsedTime, strBasePrice, strDistancePrice, strTimePrice, strTotal,
            strPrice, strTva;

    strCancelPrice << fixed << setprecision(2) << " " << cancelPrice << " ";
    strDistance << fixed << setprecision(1) << " " << kilometers << " " << UNITS[0] << " ";
    strElapsedTime << fixed << setprecision(0) << " " << minutes << " " << UNITS[1] << " ";
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
            rightColumnSize = billValue.length();
        }
    }

    rightColumnSize += 3; // + 3 whitespaces

    // Find the longest string to size the left column of the bill
    const array<string, 10> BILL_LABELS = {"Frais annulation", "distance", "temps ecoule", "Prix de base",
                                           "Prix distance", "Prix temps", "Total", "Course minimale", "Prix",
                                           "(incl. TVA)"};
    int leftColumnSize = 0;

    for (auto &billLabel: BILL_LABELS) {
        if (billLabel.length() > leftColumnSize) {
            leftColumnSize = billLabel.length();
        }
    }

    leftColumnSize += 5; // + 5 whitespaces

    const char BILL_CORNER_CHAR = ' ', BILL_HEAD_CHAR = 'v', BILL_FOOT_CHAR = '^', BILL_LEFT_CHAR = '>',
            BILL_RIGHT_CHAR = '<', BILL_SEPARATOR_CHAR = ':';
    const array<string, 4> UBER_NAMES = {"uberX", "uberPOP", "uberBLACK", "uberULTRA"};

    string uberName = UBER_NAMES[uberType];

    int billWidth = leftColumnSize + rightColumnSize + 3; // 1 for the separator and 2 for the whitespaces
    int widthForCenter = (billWidth / 2 + uberName.length() / 2) + 1; // To center the title, + 1 is for the left border

    // Store redundant string in variable
    ostringstream sectionSeparator;

    sectionSeparator << BILL_LEFT_CHAR << setw(billWidth) << setfill(' ') << BILL_RIGHT_CHAR << endl;

    // Header
    cout << BILL_CORNER_CHAR << setw(billWidth) << setfill(BILL_HEAD_CHAR) << BILL_CORNER_CHAR << endl;
    cout << sectionSeparator.str();
    cout << BILL_LEFT_CHAR << setw(widthForCenter) << setfill(' ') << uberName
         << setw(billWidth - widthForCenter) << BILL_RIGHT_CHAR << endl;
    cout << sectionSeparator.str();

    if (isCanceled) {
        cout << BILL_LEFT_CHAR << " " << setw(leftColumnSize) << left << BILL_LABELS[0] << BILL_SEPARATOR_CHAR
             << setw(rightColumnSize) << right << billValues[0] << BILL_RIGHT_CHAR << endl;
        cout << sectionSeparator.str();
    } else {
        // Distance - Elapsed time - Base price - Distance price - Time price - Total
        for (int i = 1; i <= 6; ++i) {
            cout << BILL_LEFT_CHAR << " " << setw(leftColumnSize) << left << BILL_LABELS[i]
                 << BILL_SEPARATOR_CHAR << setw(rightColumnSize) << right << billValues[i] << BILL_RIGHT_CHAR
                 << endl;

            if (i == 2 || i == 6) cout << sectionSeparator.str();
        }

        // Minimum price
        if (total < minimumPrice) {
            cout << BILL_LEFT_CHAR << " " << setw(leftColumnSize) << left << BILL_LABELS[7]
                 << BILL_SEPARATOR_CHAR << setw(rightColumnSize) << right << billValues[7] << BILL_RIGHT_CHAR
                 << endl;
            cout << sectionSeparator.str();
        }
    }

    // Price
    cout << BILL_LEFT_CHAR << " " << setw(leftColumnSize) << left << BILL_LABELS[8] << BILL_SEPARATOR_CHAR
         << setw(rightColumnSize) << right << billValues[7] << BILL_RIGHT_CHAR << endl;
    // TVA
    cout << BILL_LEFT_CHAR << " " << setw(leftColumnSize) << left << BILL_LABELS[9] << BILL_SEPARATOR_CHAR
         << setw(rightColumnSize) << right << billValues[8] << BILL_RIGHT_CHAR << endl;
    // Footer
    cout << sectionSeparator.str();
    cout << BILL_CORNER_CHAR << setw(billWidth) << setfill(BILL_FOOT_CHAR) << BILL_CORNER_CHAR << endl;

    return 0;
}
