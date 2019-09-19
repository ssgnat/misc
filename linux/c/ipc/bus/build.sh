cd build
make clean
make
cd ./ubus_conduit/
adb push test_server_debug  /system/bin/
adb push libconduit_client.so /system/lib/
adb push libconduit_srv.so /system/lib/
adb push test_client_debug  /system/bin/
