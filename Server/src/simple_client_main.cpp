#include "lib/ClientSocket.h"
#include "lib/SocketException.h"
#include <iostream>
#include <string>

int main ( int argc, char *argv[] )
{

    try
      {

        ClientSocket client_socket ( "localhost", 30000 );

//         std::cout << "povezano!";

        std::string reply;

        try
  	{

      std::string action = argv[1];
      std::string fileName = argv[2];

      std::string message = action+fileName;

  	  client_socket << message;
//       std::cout << "Poslato!";
      std::cout.flush();
  	  client_socket >> reply;
  	}
        catch ( SocketException& ) {std::cout<<"Exception";}

        std::cout << reply ;

      }
    catch ( SocketException& e )
      {
        std::cout << "Exception was caught:" << e.description() << "\n";
        return 0;
      }

  return 0;
}
