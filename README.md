# Philosophers

Ce projet a été réalisé dans le cadre de l'école 42, dans le but de comprendre les notions de threads et de mutex en langage C.

## Description

Le projet consiste à simuler un dîner de philosophes autour d'une table ronde. Sur la table se trouve un plat de spaghetti et autant de fourchettes que de philosophes. Ces derniers doivent continuellement manger, dormir et penser tant qu'

*Philosophers* utilise des _threads_ pour symboliser les philosophes, et des _mutex_ pour gérer l'accès aux fourchettes.

Les philosophes doivent continuellement manger, penser et dormir.
et chaque philosophe doit en avoir deux pour manger. Ils doivent donc se les partager de façon synchronisée, pour éviter que quelqu'un meurt.

Le programme doit être exécuté avec les paramètres suivants : le nombre de philosophes, le temps maximum avant mourir de faim, le temps qu'ils prennent pour manger, le temps qu'ils prennent pour dormir, et le nombre de fois que chaque philosophe doit manger.

## Fonctionnement


Chaque fois qu'un philosophe souhaite manger, il doit acquérir deux mutex représentant les deux fourchettes à sa gauche et à sa droite. S'il ne peut pas acquérir les deux mutex, il doit attendre jusqu'à ce qu'ils soient disponibles.

## Utilisation

* Compilez le code avec ```make```
* Lancez la simulation avec ```./philo nb_philo time_to_die time_to_eat time_to_sleep [nb_meals]```
 
  ![Screenshot from 2023-04-04 23-01-17](https://user-images.githubusercontent.com/31923839/229920557-e6606272-bbce-40d0-9292-a77c139f6758.png)
