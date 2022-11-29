project:
	gcc -std=c99 -Wall -Wpedantic utils.c main.c -o ../build/main.exe
	../build/main.exe
installemsdk: 
	cd .. && git clone https://github.com/emscripten-core/emsdk.git
	cd ../emsdk && emsdk install latest && emsdk activate latest && emsdk_env.bat && emcc ../project/main.c ../project/utils.c -o ../build/game.html -sSINGLE_FILE
buildweb:
    cd ../emsdk && emsdk activate latest && emsdk_env.bat && emcc ../project/main.c ../project/utils.c -o ../build/game.html -sSINGLE_FILE