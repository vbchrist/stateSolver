python $HOME/emsdk/emscripten/1.38.6/tools/webidl_binder.py glue.idl glue
emcc -v -I$PROJ_DIR/boost_1_67_0/ -std=c++11 -s WASM=1 -o index.js core.cpp --post-js glue.js
