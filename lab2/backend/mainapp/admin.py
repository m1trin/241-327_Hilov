from django.contrib import admin
from .models import Car

@admin.register(Car)
class Caradmin(admin.ModelAdmin):
    list_display = ('model', 'brand', 'year', 'price', 'date')
    list_filter = ('brand', 'year', 'date')
    search_fields = ('brand', 'model')

# admin
# 123
