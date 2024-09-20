REM Automatically generated from Makefile
mkdir obj
.\gbdk\bin\lcc  -Wm-yC -c -o obj\coin.o src\coin.c
.\gbdk\bin\lcc  -Wm-yC -c -o obj\cursor.o src\cursor.c
.\gbdk\bin\lcc  -Wm-yC -c -o obj\fish.o src\fish.c
.\gbdk\bin\lcc  -Wm-yC -c -o obj\food.o src\food.c
.\gbdk\bin\lcc  -Wm-yC -c -o obj\main.o src\main.c
.\gbdk\bin\lcc  -Wm-yC -c -o obj\background.o res\background.c
.\gbdk\bin\lcc  -Wm-yC -c -o obj\blank_tile.o res\blank_tile.c
.\gbdk\bin\lcc  -Wm-yC -c -o obj\coin_sprite.o res\coin_sprite.c
.\gbdk\bin\lcc  -Wm-yC -c -o obj\cursor_sprite.o res\cursor_sprite.c
.\gbdk\bin\lcc  -Wm-yC -c -o obj\food_sprite.o res\food_sprite.c
.\gbdk\bin\lcc  -Wm-yC -c -o obj\guppy_sprite.o res\guppy_sprite.c
.\gbdk\bin\lcc  -Wm-yC -o obj\pocket_aquarium.gbc obj\coin.o obj\cursor.o obj\fish.o obj\food.o obj\main.o obj\background.o obj\blank_tile.o obj\coin_sprite.o obj\cursor_sprite.o obj\food_sprite.o obj\guppy_sprite.o 
