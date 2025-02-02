#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>
using namespace std;

void displayMenu();
double convertCurrency(double amount, double fromRate, double toRate);
void adjustPromotionalRate(const double &rate, double &adjustedRate);

int main() {
    // 1. Data Initialization
    const double USD_TO_EUR = 0.93;
    const double USD_TO_GBP = 0.81;
    const double USD_TO_JPY = 130.45;
    const double USD_TO_USD = 1.0;

    double conversionRates[] = {USD_TO_USD, USD_TO_EUR, USD_TO_GBP, USD_TO_JPY};
    const string currencies[] = {"USD", "EUR", "GBP", "JPY"};
    const int numCurrencies = 4;

    int originalCurrency, convertedCurrency;
    double amount, result;

    try {
        while (true) {
            // 3. User Interaction
            //  console interface where users can input the amount and select currencies to convert from and to
            // Displaying using iostream manipulators
            cout << "\n== Currency Conversion System ==\n";
            displayMenu();
            cout << "chose the currency to convert from (0-3): ";
            cin >> originalCurrency;
            cout << "chose the currency to convert to (0-3): ";
            cin >> convertedCurrency;

            if (originalCurrency < 0 || originalCurrency >= numCurrencies || convertedCurrency < 0 || convertedCurrency >= numCurrencies) {
                throw out_of_range("Invalid currency selection. Please try again.");
            }

            cout << "Enter the amount to convert: ";
            cin >> amount;

            if (amount < 0) {
                throw invalid_argument("Amount cannot be negative. Please try again.");
            }

            // 2. Core Functionalities
            // function to convert currency
            result = convertCurrency(amount, conversionRates[originalCurrency], conversionRates[convertedCurrency]);

            // Display result with formatting
            cout << fixed << setprecision(2);
            cout << amount << " " << currencies[originalCurrency] << " = "
                 << result << " " << currencies[convertedCurrency] << "\n";

            // Specific Scenario: Promotional Rate Adjustment
            // Temporarily adjust a conversion rate using const_cast
            char promoOption;
            cout << "\nadd a promotional adjustment to the rate? (y/n): ";
            cin >> promoOption;

            if (promoOption == 'y' || promoOption == 'Y') {
                double promoRate = conversionRates[convertedCurrency];
                adjustPromotionalRate(conversionRates[convertedCurrency], promoRate);

                // Recalculate with the promotional rate
                result = convertCurrency(amount, conversionRates[originalCurrency], promoRate);
                cout << "\n=== Promotional Rate Applied ===\n";
                cout << amount << " " << currencies[originalCurrency] << " = "
                     << result << " " << currencies[convertedCurrency] << "\n";
            }

            // Prompt for another conversion
            char continueOpt;
            cout << "\nDo you want to perform another conversion? (y/n): ";
            cin >> continueOpt;

            if (continueOpt != 'y' && continueOpt != 'Y') {
                break;
            }
        }
    } catch (const exception &e) {
        // Error handling
        cerr << "Error: " << e.what() << "\n";
    }

    cout << "\nProgram finished\n";
    return 0;
}

// 3.  Displaying the menu of available currencies
void displayMenu() {
    cout << "Available currencies:\n";
    cout << "0: USD\n";
    cout << "1: EUR\n";
    cout << "2: GBP\n";
    cout << "3: JPY\n";
}

// 2. Core Functionalities: Function to convert one currency to another
double convertCurrency(double amount, double fromRate, double toRate) {
    return amount * (toRate / fromRate);
}

// Specific Scenario
void adjustPromotionalRate(const double &rate, double &adjustedRate) {
    adjustedRate = const_cast<double &>(rate) * 0.9;
    cout << "Promotional rate applied: " << adjustedRate << "\n";
}