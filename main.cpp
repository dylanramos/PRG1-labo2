#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    cout << "Quel uber? Entrez 1 pour X, 2 pour POP ou 3 pour BLACK\n"
            "Combien de minutes ecoulees?\n"
            "Combien de kilometres parcourus?\n\n";

    int uberType;
    double minutes, kilometers;
    cin >> uberType >> minutes;

    bool isCanceled = true;

    if (minutes > 0) {
        isCanceled = false;
        cin >> kilometers;
    }

    const double uberValues[3][5] = {{3.0, 1.8,  0.3, 6.0,  6.0},
                                     {3.0, 1.35, 0.3, 6.0,  6.0},
                                     {8.0, 3.6,  0.6, 15.0, 10.0}};

    uberType--; // To match with the array of uber values

    double basePrice = uberValues[uberType][0], kilometerPrice = uberValues[uberType][1],
            minutePrice = uberValues[uberType][2], minimumPrice = uberValues[uberType][3],
            cancelPrice = uberValues[uberType][4];

    double total;
    const char billCornerCharacter = '+', billHorizontalCharacter = '-', billVerticalCharacter = '|',
            billSeparatorCharacter = ':';
    const string uberNames[] = {"uberX", "uberPOP", "uberBlack"};
    const string billLabels[] = {"Frais annulation", "distance", "temps ecoule", "Prix de base",
                                 "Prix distance", "Prix temps", "Total", "Prix", "(incl. TVA)"};

    // Find the longest string
    unsigned long long leftColumnSize = 0;

    for (unsigned long long i = 0; i < billLabels->length(); ++i) {
        if (billLabels[i].length() > leftColumnSize) {
            leftColumnSize = billLabels[i].length();
        }
    }

    cout << leftColumnSize;

    /*string uberName = uberNames[uberType];

    cout << billCornerCharacter << setw(billWidth) << setfill(billHorizontalCharacter) << billCornerCharacter;

    if (isCanceled) {
        total = cancelPrice;


        cout << "\n" << billVerticalCharacter << setw(billWidth) << setfill(' ') << billVerticalCharacter << "\n";
        cout << billVerticalCharacter << setw(billWidth) << setfill(' ') << billVerticalCharacter << "\n";
        cout << billVerticalCharacter << " Frais annulation" << setw(billLeftColumnWidth) << setfill(' ');
        cout << billSeparatorCharacter << cancelPrice << billVerticalCharacter << "\n";


    } else {
        minutes = ceil(minutes);
        kilometers = round(kilometers);

        double distancePrice, timePrice;

        distancePrice = kilometerPrice * kilometers,
        timePrice = minutePrice * minutes,
        total = basePrice + distancePrice + timePrice;

        if (total < minimumPrice) total = minimumPrice;

        distancePrice = round(distancePrice);
    }

    cout << billCornerCharacter << setw(billWidth) << setfill(billHorizontalCharacter) << billCornerCharacter;
*/
    return 0;
}
