g++ TUI/src/TUI.cpp -std=c++17 -c -o .cgp/Bin/obj/TUI.o -Iinclude -ITUI/include -w
g++ src/main.cpp -std=c++17 -c -o .cgp/Bin/obj/main.o -Iinclude -ITUI/include -w
g++ src/SHA1.cpp -std=c++17 -c -o .cgp/Bin/obj/SHA1.o -Iinclude -w
g++ .cgp/Bin/obj/main.o .cgp/Bin/obj/TUI.o -o .cgp/Bin/cgp .cgp/Bin/obj/SHA1.o
g++ src/Update.cpp -o .cgp/Bin/update-cgp -std=c++17
g++ src/CGPInstaller.cpp -std=c++17 -c -o .cgp/Bin/obj/ins.o -Iinclude -w 

g++ .cgp/Bin/obj/ins.o .cgp/Bin/obj/TUI.o -o .cgp/Bin/install-cgp