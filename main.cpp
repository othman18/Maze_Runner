//
//  main.cpp
//  CPP_EX1
//  Created by othman wattad on 24.03.19.
//

#include "extractMaze.h"
#include "player.h"
#include "mazeManager.h"


int main(int argc, char *argv[]) {
    if (argc < 3){
        if (argc == 2){
            std::cout <<"Missing maze file argument in command line"<<std::endl;
        } else if (argc == 1){
            std::cout <<"Missing output file argument in command line" <<std::endl;
        }
        return 0;
    }
    const std::string inputPath = argv[1], outputPath = argv[2];

    Extractor ex;
    ex.readFile(inputPath);
    ex.writeFile(outputPath);

    if (ex.everyThingIsOkay){
//        std::cout<<"finished successfuly, player obj can run"<<std::endl;
        Player player(ex.getMaxSteps());
        MazeManager manager(&ex, &player);
        bool success = manager.manageMaze();
        std::ofstream myFile;
        myFile.open(outputPath);
        while(!manager.Q.empty()){
            switch(manager.Q.front()){
                case 0:
                    myFile<<"UP\n";
                    break;
                case 1:
                    myFile<<"LEFT\n";
                    break;
                case 2:
                    myFile<<"DOWN\n";
                    break;
                case 3:
                    myFile<<"RIGHT\n";
                    break;
                case 4:
                    myFile<<"BOOKMARK\n";
                    break;
            }
            manager.Q.pop();
        }
        if(success){
            myFile<<"!\n";
            std::cout<<"Succeeded in "<<manager.steps<<" steps"<<std::endl;
        }else{
            myFile<<"X\n";
        }
        myFile.close();
    }
//    else
//        std::cout<<"something went wrong, don't run the player obj"<<std::endl;
    return 0;
}
