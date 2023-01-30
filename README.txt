-----------------------------------------------------------------------------------

			Megaventory project

-----------------------------------------------------------------------------------

Author: Karydis Emmanouil
		
This file contains information about the project and its functionality.

The code is written in C++ 11 using Visual Studio 2019.
Some external libraries are used:
	- curl : In order to perform HTTP requests
	- JsonCPP : In order to create and manipulate JSON objects and values
Classes for Products, SupplierClients and InventoryLocations are provided. They
contain the appropriate functions to convert their data into a JSON value, which
is required for the insertion of new data.
Furthermore utility functions are provided which send requests by combining
curl and JsonCpp.

The project though is not functional. The Insertions are not done correctly.
Also steps 3-5 are not implemented at all.

