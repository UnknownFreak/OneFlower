// Lab.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <module/ModuleManager.hpp>
#include <module/logger/OneLogger.hpp>
#include <utils/config/parser.hpp>
#include <module/window/GraphicsProxy.hpp>

#include <File/FileId.hpp>
#include <utils/common/uuid.hpp>
#include <utils/common/string.hpp>

#include <file/archive/Requestor.hpp>
#include <cereal/archives/binary.hpp>

#include "Derived.hpp"

int main()
{
	std::shared_ptr<Custom> c;// = std::make_shared<Derived>();
	std::shared_ptr<Custom> d = std::make_shared<Custom>();
	d->a = "foo2";
	//c->a = "foo";
	//((Derived*)c.get())->b = "bar";
	//{
	//	try
	//	{
	//		std::ofstream os("out.cereal", std::ios::binary);
	//		cereal::BinaryOutputArchive archive(os);
	//		archive(c);
	//		archive(d);
	//	}
	//	catch (std::exception e)
	//	{
	//		std::cout << e.what();
	//	}
	//}
	c.reset();
	d.reset();
	{
		std::ifstream os("out.cereal", std::ios::binary);
		cereal::BinaryInputArchive archive(os);
		try
		{

			archive(c);
			archive(d);
		}
		catch (std::exception e)
		{
			std::cout << e.what();
		}
	}

    system("pause");
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
