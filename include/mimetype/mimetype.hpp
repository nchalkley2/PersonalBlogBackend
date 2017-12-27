#pragma once
#include <cstring>
#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <vector>

namespace mimetype
{
	namespace detail
	{
		class mimeTypes
		{
		private:
			std::map<std::string, std::string> mimeMap;

			mimeTypes()
			{
				// Load the mimetype file
				std::ifstream is("/etc/mime.types");
				
				// Iterate over the file line by line
				std::string line;
				while (getline(is, line))
				{
					// If there is a hash in the line, then don't read that line
					if (line.find('#') != std::string::npos)
						continue;
					
					// Look for the tab char, its the file delimiter
					// then split up the lines into key/value pairs
					size_t pos;
					if ((pos = line.find('\t')) != std::string::npos)
					{
						std::string mimeType = line.substr(0, pos);
						std::string fileType = line.substr(pos);
					
						// Strip the tabs from the filetype	
						size_t tabpos;
						while ((tabpos = fileType.find('\t')) 
								!= std::string::npos)
						{
							fileType = fileType.substr(tabpos + 1);
						}

						// Tokenize the filetype into an array
						std::vector<std::string> fileTypes;
						char fileTypeStr[fileType.size()];
						std::strcpy(fileTypeStr, fileType.c_str());
						char* token = std::strtok(fileTypeStr, " ");
						while (token != nullptr)
						{
							fileTypes.push_back(std::string(token));
							token = strtok(NULL, " ");
						}

						// Now we can finally map the file type to the mime type
						for (auto& fileType : fileTypes)
						{
							mimeMap[fileType] = mimeType;
						}
					}
				}
			}

		public:
			static mimeTypes& getInst()
			{
				static mimeTypes mimeTypesInst;
				return mimeTypesInst;
			}

			const std::string operator[](std::string index)
			{
				return mimeMap[index];
			};
		};
	}

	static std::string getMimeType(std::string filePath)
	{
		size_t periodpos;
		if ((periodpos = filePath.find('.')) != std::string::npos
				&& periodpos + 1 < filePath.length())
			filePath = filePath.substr(periodpos + 1);

		detail::mimeTypes& mimeTypeInst = detail::mimeTypes::getInst();

		return mimeTypeInst[filePath];
	}
}
