#ifndef TRAVEL_AGENCY_H
#define TRAVEL_AGENCY_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

// Глобальна змінна для демонстрації посилання в списку ініціалізації
extern const string g_GlobalAgencyName;

//  Клас Композиції: Паспорт тільки всередині тур
class Passport {
public:
    string passportNumber;
    string issueDate;

    Passport();
    Passport(string number, string date);
    ~Passport();
    void displayPassport() const;
};

//  Клас агрегації: Страховий поліс працює без тур
class InsurancePolicy {
public:
    string policyNumber;
    double coverageAmount;

    InsurancePolicy();
    InsurancePolicy(string number, double coverage);
    ~InsurancePolicy();
    void displayPolicy() const;
};

class TourPackage {
private:
    //  Початкові значення констант та посилань через список ініціалізації
    const int packageId;
    const string& agencyRef;

    string country;
    bool requiresVisa;
    double insuranceFee;
    bool flexibleDates;

public:
    string packageName;
    double basePrice;
    int durationDays;

    //Статичне поле даних для спільного використання
    static int totalPackagesCreated;

    // Конструктори: без параметрів, з параметрами, копіювання
    TourPackage();
    TourPackage(int id, const string& agency, string name, double price, int days, string cntr, bool visa, double ins, bool flex);
    TourPackage(const TourPackage& other); // Конструктор копіювання

    // Деструктор для відслідковування входження/виходу з блоків
    ~TourPackage();

    static void printTotalPackagesCount();

    // Методи класу
    void displayInfo() const;
    int getPackageId() const { return packageId; }
    string getCountry() const { return country; }
    bool getRequiresVisa() const { return requiresVisa; }
    double getInsuranceFee() const { return insuranceFee; }
    bool getFlexibleDates() const { return flexibleDates; }
};

//Основний клас Турист
class Tourist {
private:
    int touristId;
    string phone;
    double budget;
    bool visaApproved;

    //  Об'єкт Passport створюється і знищується разом із Tourist
    Passport passport;

    //  Вказівник на окремо існуючий об'єкт InsurancePolicy
    InsurancePolicy* insurance;

public:
    string fullName;
    int age;

    //  Конструктори
    Tourist();
    Tourist(int id, string name, int ag, string ph, double budg, bool visa, string passNum, string passDate, InsurancePolicy* pol = nullptr);
    Tourist(const Tourist& other); // Конструктор копіювання

    //  Деструктор
    ~Tourist();

    // Геттери та сеттери для агрегації
    void setInsurancePolicy(InsurancePolicy* pol) { insurance = pol; }
    InsurancePolicy* getInsurancePolicy() const { return insurance; }
    Passport getPassport() const { return passport; }

    void displayTourist() const;
    double getBudget() const { return budget; }
    bool getVisaApproved() const { return visaApproved; }
    void setBudget(double newBudget) { budget = newBudget; }
};

// Оформлення бронювання
class BookingTransaction {
private:
    Tourist* tourist;
    TourPackage* package;
    InsurancePolicy* insurance;
    string transactionDate;
    double totalCost;

public:
    BookingTransaction(Tourist* t, TourPackage* p, InsurancePolicy* i, string date);
    ~BookingTransaction();
    bool processBooking();
    void displayReceipt() const;
};

// Зовнішня функція
void calculatePackageDetails(TourPackage pkg);

//Перевантажена зовнішня функція
void calculatePackageDetails(const TourPackage* pkg);

// Функція, що повертає об'єкт класу
TourPackage createUpgradedPackage(const TourPackage& original, double priceMultiplier);

#endif // TRAVEL_AGENCY_H