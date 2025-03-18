path="$(pwd)"
cd "${path}/extern/tools"
make -f makeL
make -f makeA


cd "${path}/tools"
make
make test.exe
