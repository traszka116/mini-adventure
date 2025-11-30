```
     _______. _______   __       ____          .______   .______        ______          __   _______   ______ .___________.   
    /       ||       \ |  |     |___ \         |   _  \  |   _  \      /  __  \        |  | |   ____| /      ||           |   
   |   (----`|  .--.  ||  |       __) |  ______|  |_)  | |  |_)  |    |  |  |  |       |  | |  |__   |  ,----'`---|  |----`   
    \   \    |  |  |  ||  |      |__ <  |______|   ___/  |      /     |  |  |  | .--.  |  | |   __|  |  |         |  |        
.----)   |   |  '--'  ||  `----. ___) |        |  |      |  |\  \----.|  `--'  | |  `--'  | |  |____ |  `----.    |  |        
|_______/    |_______/ |_______||____/         | _|      | _| `._____| \______/   \______/  |_______| \______|    |__|        
                                                                                                                              
.___________. _______ .___  ___. .______    __          ___   .___________. _______                                           
|           ||   ____||   \/   | |   _  \  |  |        /   \  |           ||   ____|                                          
`---|  |----`|  |__   |  \  /  | |  |_)  | |  |       /  ^  \ `---|  |----`|  |__                                             
    |  |     |   __|  |  |\/|  | |   ___/  |  |      /  /_\  \    |  |     |   __|                                            
    |  |     |  |____ |  |  |  | |  |      |  `----./  _____  \   |  |     |  |____                                           
    |__|     |_______||__|  |__| | _|      |_______/__/     \__\  |__|     |_______|                                          
```

This is a ready to use template for SDL3 project with few utility macros and functions, and ready to use makefile script.

Setup:

if your libs/SDL directory is empty, run 
```git submodule update --init```
this will pull in SDL library from github

to build sdl library call ```scripts/build-sdl.sh``` from main directory of project

Build:

to build project use ```make```, 
make has options:
- `DEBUG` - disables compiler optimizations (-o0), adds debugging info (-g)
- `RELEASE` - enables compiler optimization (-o2) 
- by default - no optimisations are enabled (-o0)

Run:

intermidiate files from compilation (.o) will be put inside ```build``` directory

resulting executable from compilation will be put into ```dest/program``` file


