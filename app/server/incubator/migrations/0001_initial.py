# Generated by Django 4.0.2 on 2022-02-26 15:36

from django.db import migrations, models


class Migration(migrations.Migration):

    initial = True

    dependencies = [
    ]

    operations = [
        migrations.CreateModel(
            name='DataParam',
            fields=[
                ('id', models.BigAutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('dryTemp', models.IntegerField()),
                ('wetTemp', models.IntegerField()),
                ('recieved', models.DateTimeField(auto_now_add=True)),
            ],
        ),
    ]
