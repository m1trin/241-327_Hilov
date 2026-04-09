from django.db import models

class Car(models.Model):
    model = models.CharField(
        max_length= 100,
        verbose_name= 'Модель',
    )

    brand = models.CharField(
        max_length= 50,
        verbose_name= 'Марка',
    )

    year = models.PositiveIntegerField(
        verbose_name= 'Год выпуска',
    )

    mileage = models.PositiveIntegerField(
        verbose_name= 'Пробег км',
    )

    price = models.DecimalField(
        max_digits= 10,
        decimal_places= 2,
        verbose_name= 'Цена руб',
    )

    description = models.TextField(
        blank= True,
        null= True,
        verbose_name= 'Описание',
    )

    date = models.DateField(
        auto_now_add= True,
        verbose_name='Дата добавления',
    )

    def __str__(self):
        return f'{self.brand} {self.model} ({self.year})'
