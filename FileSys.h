#ifndef FILESYSTEM_H
#define FILESYSTEM_H
#include "stdafx.h"

namespace nvs
{
	class myFileSystem
	{
	private:
		std::fstream fst;
		std::ofstream ofs;

		std::string p;

		bool checkFile(std::string path);
	public:

		myFileSystem();
		virtual ~myFileSystem();


		virtual void save(std::string path,sf::Vector2f* data);
		virtual void load(std::string path);
	
		
	};


}
#endif // !FILESYSTEM_H

