#include "TravelAgency.h"

void main() {
    setlocale(LC_ALL, "Ukrainian");

    // Демонстрація статичного поля та статичного методу
    TourPackage::printTotalPackagesCount();

    //Демонстрація ТРЬОХ способів створення об'єктів за допомогою конструкторів
    cout << "\nТри способи створення об'єктів" << endl;

    // Спосіб 1: Простий виклик
    TourPackage package1(101, g_GlobalAgencyName, "Римські Канікули", 800.0, 7, "Італія", true, 50.0, true);

    // Спосіб 2: Явний виклик
    TourPackage package2 = TourPackage(102, g_GlobalAgencyName, "Альпійський Скі", 1200.0, 10, "Австрія", true, 80.0, false);

    // Спосіб 3: Скорочена уніфікована ініціалізація
    TourPackage package3{ 103, g_GlobalAgencyName, "Токіо Дрифт", 2500.0, 12, "Японія", true, 120.0, true };

    package1.displayInfo();
    package2.displayInfo();
    package3.displayInfo();

    // Перевірка зміни статичного поля
    TourPackage::printTotalPackagesCount();

    // Демонстрація конструктора копіювання
    cout << "\nДемонстрація конструктора копіювання" << endl;
    TourPackage packageCopy = package1; // Викликається конструктор копіювання
    packageCopy.displayInfo();

    // Демонстрація АГРЕГАЦІЇ (InsurancePolicy існує як окремий об'єкт)
    cout << "\nСценарій взаємодії за агрегацією" << endl;
    InsurancePolicy globalPolicy("INS-999888", 15000.0); // Окремий об'єкт

    //  Використання покажчиків, статична та динамічна пам'ять
    // Створення об'єкта Tourist (містить у собі Passport за КОМПОЗИЦІЄЮ)
    Tourist staticTourist(1, "Кравець Іван", 20, "067-123-4567", 3500.0, true, "KM123456", "2021-05-10", &globalPolicy);
    cout << "Статичний об'єкт туриста з агрегованою страховкою:" << endl;
    staticTourist.displayTourist();

    // Динамічна пам'ять
    cout << "\nОб'єкти у динамічній пам'яті ---" << endl;
    Tourist* dynTourist = new Tourist(2, "Петренко Олексій", 22, "050-987-6543", 1000.0, false, "KM654321", "2022-08-15");
    dynTourist->displayTourist();

    // Масив об'єктів
    cout << "\nМасив об'єктів" << endl;
    TourPackage packageArray[2] = {
        TourPackage(201, g_GlobalAgencyName, "Прага Вікенд", 450.0, 4, "Чехія", false, 30.0, true),
        TourPackage(202, g_GlobalAgencyName, "Париж Романтик", 950.0, 6, "Франція", true, 60.0, false)
    };
    for (int i = 0; i < 2; i++) {
        packageArray[i].displayInfo();
    }

    // Сценарій взаємодії трьох об'єктів через клас асоціацій
    cout << "\nСценарій взаємодії 3-х об'єктів" << endl;
    BookingTransaction transaction(&staticTourist, &package1, &globalPolicy, "2026-05-20");
    if (transaction.processBooking()) {
        transaction.displayReceipt();
    }

    // Демонстрація перевантажених зовнішніх функцій
    cout << "\nВиклики перевантажених зовнішніх функцій" << endl;
    calculatePackageDetails(package1);       // Пункт 5 (передача за значенням)
    calculatePackageDetails(&package2);      // Пункт 6 (передача за адресою)

    // Виклик функції, що повертає об'єкт класу
    cout << "\nФункція, що повертає об'єкт" << endl;
    TourPackage upgraded = createUpgradedPackage(package1, 1.3);
    upgraded.displayInfo();

    // Демонстрація деструкторів під час входження/виходу з локального блоку
    cout << "\nВідслідковування входження та виходу з локального блоку" << endl;
    {
        cout << "   [Вхід у локальний блок]" << endl;
        TourPackage tempPackage(999, g_GlobalAgencyName, "Тимчасовий тур", 100.0, 1, "Україна", false, 0.0, true);
        tempPackage.displayInfo();
        cout << "   [Вихід з локального блоку]" << endl;
    } // Тут локальний об'єкт tempPackage автоматично знищується викликаючи деструктор

    // Очищення динамічної пам'яті
    cout << "\n--- Звільнення динамічної пам'яті ---" << endl;
    delete dynTourist;

    cout << "\nЗавершення виконання програми...." << endl;
    cin.get();
}