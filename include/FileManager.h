/*! \brief Class FileManager.h.
 *
 *  Handle with file operations.
*/
#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <sstream>

/*! FileManager class */
class FileManager
{
	/*!
     * Public section
	*/
	public:

		/*! Functions */
		FileManager( void );  /*!< Constructor */
		~FileManager( void ); /*!< Destructor */

		/*! Load content from file */
		void LoadContent( const char* filename, std::vector<std::vector<std::string>> &attributes,
			std::vector<std::vector<std::string>> &contents );

	/*!
     * Protected section
	*/
	protected:

	/*!
     * Private section
	*/
	private:

		/*! Attributes */
		std::vector<std::string> tempAttributes;
		std::vector<std::string> tempContents;

};

#endif // FILEMANAGER_H

