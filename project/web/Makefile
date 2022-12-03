installemsdk: 
	cd ../.. && git clone https://github.com/emscripten-core/emsdk.git
	cd ../../emsdk && emsdk install latest && emsdk activate latest && emsdk_env.bat && emcc ../project/main.c ../project/utils.c ../project/web/funcs.c -I ../project/include -o ../build/game.html -sSINGLE_FILE -sASYNCIFY
buildweb:
	cd ../../emsdk && emsdk activate latest && emsdk_env.bat && emcc ../project/main.c ../project/utils.c ../project/web/funcs.c -I ../project/include -o ../build/game.html -sSINGLE_FILE -sASYNCIFY
