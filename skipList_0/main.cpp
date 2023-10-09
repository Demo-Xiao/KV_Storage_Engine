#include "SkipList.h"
#include<fstream>
#include<cstdlib>
int main() 
{
    // file operator
    /*
    std::ofstream _file_writer;
    std::ifstream _file_reader;

    _file_writer.open("kvstore");
    _file_writer << "name: xiao" << ":" << "age:" << 18 << '\n';
    _file_writer.flush();
    _file_writer.close();
    
    */
    
    
	SkipList sl(3);
	//sl.insert(1, 10);
    std::cout << "begin insert. press -1 to exit" << std::endl;
    sl.insert(2, 20);
    sl.insert(3, 30);
    sl.insert(4, 40);
    sl.insert(2, 40);

    /*
    int key, value;
    while (true) 
    {
        std::cout << "input your key:";
        std::cin >> key;

        if (key == -1) {
            std::cout << "exit..." << std::endl;
            break;
        }

        std::cout << "input your value:";
        std::cin >> value;

        sl.insert(key, value);  // 假设你的跳表类有一个名为 "insert" 的方法，用于插入键值对
        system("clear");
    }
    */
    sl.display();

	int val;
    if (sl.search(6, val)) {
        std::cout << "Found: " << val << std::endl;
    }
    else {
        std::cout << "Not found" << std::endl;
    }

    // Remove test
    if (sl.remove(3)) {
        std::cout << "Removed successfully" << std::endl;
    }
    else {
        std::cout << "Remove failed" << std::endl;
    }
    sl.dumpFile();
    //sl.display();
    
    return 0;
}

/*
    sl.insert(2, 20);
    sl.insert(3, 30);
    sl.insert(4, 40);
    sl.insert(5, 50);
    sl.insert(4, 40);
    sl.insert(5, 50);
    sl.insert(6, 60);
    sl.insert(7, 70);
    sl.insert(8, 80);
    sl.insert(9, 90);
    sl.insert(10, 100);
    sl.insert(11, 110);
    sl.insert(12, 120);
    sl.insert(13, 130);
    sl.insert(14, 140);
    sl.insert(15, 150);

*/