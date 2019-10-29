#include <iostream>
#include <stdexcept>   
#include "calc.h"

int main(int argc, const char* argv[])
{
	switch (argc) {
    	case 1:
    	    std::cout << "Not enough arguments" << std::endl;
    	    return -1;
    	case 2:
    		try {
    			double answer = processing(argv[1]);
    			std::cout << answer << std::endl; 
  			} 
			catch (const std::invalid_argument& ia) {
				std::cout << "Invalid argument: " << ia.what() << '\n';
		  	}
			break;
    	default:
    		std::cout << "Too many arguments" << std::endl;
    		return -1;
	}
    return 0;
}
