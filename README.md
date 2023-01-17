# snake-game
The project for practicing Qt — framework.

## Build
- Selected OSs - Windows and Android
- Version of C++ - 20
- Version of Qt - 5.15.2
- Version of JDK - 17.0.4.1
- Version of Android SDK - 33
- Build Tools Version - 28.0.3
- Version of Gradle - 7.0.0

## A brief review of the application
This project is a snake game where you increase your score by eating an apple, and you have limits like the walls and snake body. You can win the game when ~70% of the field is covered by a snake body. You can hear sounds when you eat an apple or hit the body and wall. Also, the best record is saved to the .ini file. This project also works for android, and you can play with your fingers in that game.

## Saving
To save best score, properties of the field and the properties of the window (only on Windows), I use QSettings, where I keep data nearby to a .exe file and in .ini format:
<p align="center">
  <img src="https://user-images.githubusercontent.com/34779566/212923622-ce78c0a1-8dab-4c08-aed4-0d4f0306cb22.png" height="300" alt="The ini (save) file">
</p>

## General application view
1. Windows
<p align="center">
  <img src="https://user-images.githubusercontent.com/34779566/212923763-5fac989d-027e-4650-940a-bcfe82edaf22.png" height="500" alt="Windows application view">
</p>

2. Android
<p align="center">
  <img src="https://user-images.githubusercontent.com/34779566/212924331-85e88b83-204c-4424-8470-7a12b3bf4305.png" height="500" alt="Android application view">
</p>

## Demonstration of application
(Grid through a small picture)
<p align="center">
  <img src="https://user-images.githubusercontent.com/34779566/212925752-9cd5f635-a927-4ee5-a384-eb08dcb9ab69.gif" height="400" alt="Gif - Demonstration of application">
</p>
