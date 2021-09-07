g++ AES/src/AES.cpp -std=c++17 -c -o .cgp/Bin/obj/AES1.o -Iinclude -IAES/include -w
g++ AES/src/AES.c -std=c++17 -c -o .cgp/Bin/obj/AES2.o -Iinclude -IAES/include -w
g++ TUI/src/TUI.cpp -std=c++17 -c -o .cgp/Bin/obj/TUI.o -Iinclude -ITUI/include -w
g++ src/main.cpp -std=c++17 -c -o .cgp/Bin/obj/main.o -Iinclude -ITUI/include -ISHA1/include -w -IAES/include
g++ SHA1/src/SHA1.cpp -std=c++17 -c -o .cgp/Bin/obj/SHA1.o -Iinclude -ISHA1/include -w
g++ .cgp/Bin/obj/main.o .cgp/Bin/obj/TUI.o -o .cgp/Bin/cgp .cgp/Bin/obj/SHA1.o .cgp/Bin/obj/AES2.o
g++ src/Update.cpp -o .cgp/Bin/update-cgp -std=c++17
g++ src/CGPInstaller.cpp -std=c++17 -c -o .cgp/Bin/obj/ins.o -Iinclude -ITUI/include -w 

g++ .cgp/Bin/obj/ins.o .cgp/Bin/obj/TUI.o -o .cgp/Bin/install-cgp