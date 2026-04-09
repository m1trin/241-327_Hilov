import os
import sys
import django
from faker import Faker
import random

# Добавляем путь к корневой папке проекта
sys.path.append(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

os.environ.setdefault('DJANGO_SETTINGS_MODULE', 'lab1.settings')

django.setup()


from mainapp.models import Car

def add_cars_to_db(count=100):
    """
    Добавляет указанное количество машин в базу данных
    """
    fake = Faker('ru_RU')  # Используем русскую локализацию для реалистичных данных
    
    brands_models = {
        'Toyota': ['Camry', 'Corolla', 'Land Cruiser', 'RAV4', 'Prius', 'Yaris', 'Avensis'],
        'BMW': ['X5', 'X3', '3 Series', '5 Series', '7 Series', 'M3', 'X6'],
        'Mercedes-Benz': ['E-Class', 'S-Class', 'C-Class', 'GLE', 'GLC', 'G-Class', 'A-Class'],
        'Audi': ['A4', 'A6', 'Q5', 'Q7', 'A3', 'Q3', 'A8'],
        'Volkswagen': ['Golf', 'Passat', 'Tiguan', 'Polo', 'Touareg', 'Jetta'],
        'Hyundai': ['Solaris', 'Santa Fe', 'Tucson', 'Elantra', 'Creta', 'Sonata'],
        'Kia': ['Rio', 'Sportage', 'Ceed', 'Optima', 'Sorento', 'K5'],
        'Renault': ['Logan', 'Duster', 'Sandero', 'Kaptur', 'Megane'],
        'Lada': ['Vesta', 'Granta', 'XRAY', 'Largus', 'Niva'],
        'Ford': ['Focus', 'Mondeo', 'Kuga', 'Fusion', 'Explorer'],
        'Nissan': ['X-Trail', 'Qashqai', 'Juke', 'Almera', 'Teana'],
        'Honda': ['Civic', 'Accord', 'CR-V', 'Pilot', 'Fit'],
        'Chevrolet': ['Cruze', 'Lacetti', 'Aveo', 'Captiva', 'Malibu'],
        'Skoda': ['Octavia', 'Rapid', 'Kodiaq', 'Karoq', 'Fabio'],
        'Mazda': ['6', 'CX-5', '3', 'CX-9', 'MX-5']
    }
    
    cars_to_create = []
    
    for i in range(count):
        # Выбираем случайную марку и модель
        brand = random.choice(list(brands_models.keys()))
        model = random.choice(brands_models[brand])
        
        # Генерируем год (от 1990 до 2024)
        year = random.randint(1990, 2024)
        
        if year >= 2020:
            mileage = random.randint(0, 50000)
        elif year >= 2015:
            mileage = random.randint(30000, 120000)
        elif year >= 2010:
            mileage = random.randint(80000, 200000)
        else:
            mileage = random.randint(120000, 350000)
        
        base_price = 0
        if brand in ['BMW', 'Mercedes-Benz', 'Audi']:
            base_price = random.randint(1500000, 8000000)
        elif brand in ['Toyota', 'Honda', 'Mazda']:
            base_price = random.randint(800000, 3500000)
        else:
            base_price = random.randint(300000, 2500000)
        
        age = 2024 - year
        price = base_price * (0.85 ** age)  
        price = price * (1 - mileage / 500000) 
        price = max(50000, int(price)) 
        
        if random.random() > 0.5:
            description_templates = [
                f"Автомобиль в хорошем состоянии.",
                f"Пробег {mileage} км.",
                f"{year} год выпуска.",
                f"Отличный вариант для города.",
                f"Автомобиль проходил регулярное ТО.",
                f"Состояние отличное. ",
                f"Экономичный расход топлива.",
                f"Богатая комплектация ",
            ]
            description = random.choice(description_templates)
        else:
            description = None
        
        car = Car(
            model=model,
            brand=brand,
            year=year,
            mileage=mileage,
            price=price,
            description=description
        )
        cars_to_create.append(car)
        
        # Выводим прогресс
        if (i + 1) % 10 == 0:
            print(f"Создано {i + 1} записей...")
    
    Car.objects.bulk_create(cars_to_create)
    print(f"\n Успешно добавлено {count} автомобилей в базу данных!")

def clear_cars():
    """
    Очищает таблицу Car
    """
    count = Car.objects.all().count()
    if count > 0:
        Car.objects.all().delete()
        print(f"  Удалено {count} записей из базы данных")
    else:
        print("База данных уже пуста")

if __name__ == "__main__":
    print("Добавление тестовых данных в базу данных")
    
    # Проверяем подключение к БД
    try:
        Car.objects.exists()
        print(" Подключение к базе данных успешно\n")
    except Exception as e:
        print(f" Ошибка подключения к БД: {e}")
        print("Проверьте настройки в lab1/settings.py")
        sys.exit(1)
    
    response = input("Очистить существующие записи перед добавлением? (y/n): ")
    if response.lower() == 'y':
        clear_cars()
    
    add_cars_to_db(100)
    
    print("\n Примеры добавленных автомобилей:")
    for car in Car.objects.all()[:5]:
        print(f"  - {car} | Пробег: {car.mileage:,} км | Цена: {car.price:,.0f} руб")
        if car.description:
            print(f"    Описание: {car.description[:100]}...")