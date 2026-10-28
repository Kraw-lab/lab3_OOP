#include "TravelAgency.h"

// Ініціалізація глобальних та статичних змінних
const string g_GlobalAgencyName = "ApexTravel Agency";

// Ініціалізація статичного поля даних
int TourPackage::totalPackagesCreated = 0;

// Реалізація Passport
Passport::Passport() : passportNumber("UA000000"), issueDate("2022-01-01") {}
Passport::Passport(string number, string date) : passportNumber(number), issueDate(date) {}
Passport::~Passport() {}
void Passport::displayPassport() const {
    cout << "   [Паспорт] Номер: " << passportNumber << ", Виданий: " << issueDate << endl;
}

// Реалізація агрегації
InsurancePolicy::InsurancePolicy() : policyNumber("INS-000"), coverageAmount(5000.0) {}
InsurancePolicy::InsurancePolicy(string number, double coverage) : policyNumber(number), coverageAmount(coverage) {}
InsurancePolicy::~InsurancePolicy() {
    cout << "   Страховий поліс " << policyNumber << " вивантажено з пам'яті." << endl;
}
void InsurancePolicy::displayPolicy() const {
    cout << "   [Страховка] Поліс №: " << policyNumber << ", Покриття: " << coverageAmount << " EUR" << endl;
}

// Реалізація TourPackage
// Конструктор за замовчуванням зі списком ініціалізації
TourPackage::TourPackage()
    : packageId(0), agencyRef(g_GlobalAgencyName), country("Україна"), requiresVisa(false),
    insuranceFee(0.0), flexibleDates(false), packageName("Базовий"), basePrice(0.0), durationDays(1) {
    totalPackagesCreated++;
}

// Конструктор з параметрами (ініціалізація const та посилання)
TourPackage::TourPackage(int id, const string& agency, string name, double price, int days, string cntr, bool visa, double ins, bool flex)
    : packageId(id), agencyRef(agency), country(cntr), requiresVisa(visa),
    insuranceFee(ins), flexibleDates(flex), packageName(name), basePrice(price), durationDays(days) {
    totalPackagesCreated++;
}

// Конструктор копіювання
TourPackage::TourPackage(const TourPackage& other)
    : packageId(other.packageId + 1000), agencyRef(other.agencyRef), country(other.country),
    requiresVisa(other.requiresVisa), insuranceFee(other.insuranceFee), flexibleDates(other.flexibleDates),
    packageName(other.packageName + " (Копія)"), basePrice(other.basePrice), durationDays(other.durationDays) {
    totalPackagesCreated++;
    cout << "Створено копію путівки: " << packageName << endl;
}

// Деструктор
TourPackage::~TourPackage() {
    cout << "Путівку ID=" << packageId << " ('" << packageName << "') знищено." << endl;
}

// Статичний метод
void TourPackage::printTotalPackagesCount() {
    cout << "Загальна кількість створених путівок: " << totalPackagesCreated << endl;
}

void TourPackage::displayInfo() const {
    cout << "[Путівка ID: " << packageId << "] Назва: " << packageName
        << " | Агенція: " << agencyRef << " | Країна: " << country
        << " | Ціна: " << basePrice << " USD | Днів: " << durationDays << endl;
}

// Реалізація Tourist
Tourist::Tourist()
    : touristId(0), fullName("Невідомо"), age(18), phone("000-000"), budget(0.0),
    visaApproved(false), passport("UA000000", "2020-01-01"), insurance(nullptr) {
}

Tourist::Tourist(int id, string name, int ag, string ph, double budg, bool visa, string passNum, string passDate, InsurancePolicy* pol)
    : touristId(id), fullName(name), age(ag), phone(ph), budget(budg),
    visaApproved(visa), passport(passNum, passDate), insurance(pol) {
}

// Конструктор копіювання
Tourist::Tourist(const Tourist& other)
    : touristId(other.touristId + 500), fullName(other.fullName + " (Копія)"), age(other.age),
    phone(other.phone), budget(other.budget), visaApproved(other.visaApproved),
    passport(other.passport), insurance(other.insurance) {
    cout << "Створено копію туриста: " << fullName << endl;
}

Tourist::~Tourist() {
    cout << "Об'єкт Туриста ID=" << touristId << " (" << fullName << ") знищено." << endl;
}

void Tourist::displayTourist() const {
    cout << "[Турист ID: " << touristId << "] ПІБ: " << fullName << ", Вік: " << age
        << ", Бюджет: " << budget << " USD, Віза: " << (visaApproved ? "Є" : "Відсутня") << endl;
    passport.displayPassport();
    if (insurance != nullptr) {
        insurance->displayPolicy();
    }
    else {
        cout << "   [Страховка] Не оформлена" << endl;
    }
}

// Реалізація Класу Асоціацій
BookingTransaction::BookingTransaction(Tourist* t, TourPackage* p, InsurancePolicy* i, string date)
    : tourist(t), package(p), insurance(i), transactionDate(date), totalCost(0.0) {
}

BookingTransaction::~BookingTransaction() {}

bool BookingTransaction::processBooking() {
    if (!tourist || !package) return false;

    totalCost = package->basePrice + package->getInsuranceFee();
    if (insurance) {
        totalCost += 100.0; // Додатковий збір за розширений поліс
    }

    if (package->getRequiresVisa() && !tourist->getVisaApproved()) {
        cout << "Бронювання скасовано: У туриста " << tourist->fullName << " немає візи до " << package->getCountry() << "!" << endl;
        return false;
    }

    if (tourist->getBudget() < totalCost) {
        cout << "Бронювання скасовано: Недостатньо коштів на рахунку туриста " << tourist->fullName << "!" << endl;
        return false;
    }

    tourist->setBudget(tourist->getBudget() - totalCost);
    cout << "Транзакцію від " << transactionDate << " успішно проведено!" << endl;
    return true;
}

void BookingTransaction::displayReceipt() const {
    cout << "\n================ ЧЕК БРОНЮВАННЯ ================" << endl;
    cout << "Дата транзакції: " << transactionDate << endl;
    cout << "Турист: " << tourist->fullName << endl;
    cout << "Напрямок: " << package->packageName << " (" << package->getCountry() << ")" << endl;
    cout << "Підсумкова вартість: " << totalCost << " USD" << endl;
    cout << "Залишок бюджету: " << tourist->getBudget() << " USD" << endl;
    cout << "===============================================\n" << endl;
}

// --- [Пункт 5] Зовнішня функція (за значенням) ---
void calculatePackageDetails(TourPackage pkg) {
    cout << "\n Обробка путівки '" << pkg.packageName << "':" << endl;
    double tax = pkg.basePrice * 0.05;
    cout << "   Базова ціна: " << pkg.basePrice << " USD | ПДВ (5%): " << tax
        << " USD | Разом: " << (pkg.basePrice + tax) << " USD" << endl;
}

// --- [Пункт 6] Перевантажена зовнішня функція (за адресою) ---
void calculatePackageDetails(const TourPackage* pkg) {
    cout << "\n Обробка путівки '" << pkg->packageName << "':" << endl;
    double totalWithInsurance = pkg->basePrice + pkg->getInsuranceFee();
    cout << "   Ціна путівки: " << pkg->basePrice << " USD | Страховий збір: "
        << pkg->getInsuranceFee() << " USD | Сума: " << totalWithInsurance << " USD" << endl;
}

// --- [Пункт 7] Функція, що повертає об'єкт класу ---
TourPackage createUpgradedPackage(const TourPackage& original, double priceMultiplier) {
    TourPackage upgraded = original;
    upgraded.packageName += " VIP Premium";
    upgraded.basePrice *= priceMultiplier;
    upgraded.durationDays += 3;
    cout << "\nСтворено та повернуто покращений об'єкт класу TourPackage!" << endl;
    return upgraded;
}