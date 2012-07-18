/**
* 
* @file     console
* @brief    Copyright (C) 2012  yayanyang All Rights Reserved 
* @author   yayanyang
* @version  1.0.0.0  
* @date     2012/01/14
*/
#ifndef LEMON_CXX_UNITTEST_CONSOLE_HPP
#define LEMON_CXX_UNITTEST_CONSOLE_HPP
#include <string>
#include <iomanip>
#include <iostream>
#include <lemonxx/assembly.h>
#include <lemonxx/unittest/dsel.hpp>
#include <lemonxx/sys/exception.hpp>
#include <lemonxx/sys/errorcode.hpp>
#include <lemonxx/sys/datetime.hpp>

namespace lemon{namespace unittest{namespace cxx{

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @class	ConsoleRunner
	///
	/// @brief	Console runner. 
	///
	/// @author	Yuki
	/// @date	2012/1/14
	////////////////////////////////////////////////////////////////////////////////////////////////////

	class ConsoleRunner : private nocopyable
	{
	public:

		////////////////////////////////////////////////////////////////////////////////////////////////////
		/// @fn	ConsoleRunner(int args, char ** argv)
		///
		/// @brief	Constructor. 
		///
		/// @author	Yuki
		/// @date	2012/1/14
		///
		/// @param	args			The arguments. 
		/// @param [in,out]	argv	If non-null, the argv. 
		////////////////////////////////////////////////////////////////////////////////////////////////////

		ConsoleRunner(const char * name,int args, char ** argv)
			:_args(args),_argv(argv),_name(name)
		{}

		int Run()
		{
			std::cout << "Lemon Unittest Console Runner, Version " 
				<< LEMONXX_VERSION.Major << "." << LEMONXX_VERSION.Minor 
				<< "." << LEMONXX_VERSION.Build << "." << LEMONXX_VERSION.Reversion << std::endl;

			std::cout << "Copyright (C) 2012  yayanyang All Rights Reserved" << std::endl;

			std::cout << "[Package] " << _name << std::endl;

			try
			{
				CheckCmdline();

				RunUrl();

				std::cout << "bingo !!!!!!!!!!!!!!!!" << std::endl;

				return 0; 
			}
			catch(const ConditionException& e)
			{
				std::cerr << "error!!! catch unittest exception:" << e.what() << std::endl;

				std::cerr << "\tfile:" << e.ErrorCode().File << std::endl;

				std::cerr << "\tlins:" << e.ErrorCode().Lines << std::endl;

				return 1;
			}
			catch(const lemon::Exception & e)
			{
				std::cerr << "error!!!" << e.what() << std::endl;

				std::cerr << e.ErrorInfo() << std::endl;

				return 3;
			}
			catch(const std::exception & e)
			{
				std::cerr << "error!!! " << e.what() << std::endl;

				return 2;
			}

			
		}

	private:

		void CheckCmdline()
		{
			_url = "/";

			if(_args > 3) throw std::runtime_error("invalid command line.");

			if(_args > 1) _url = _argv[2];

			if(_args == 3) _times = atoi(_argv[3]);
		}

		void RunUrl()
		{
			Package * package = Package::Singleton();

			Package::TestSuites::const_iterator iter,end = package->Children().end();

			for(iter = package->Children().begin(); iter != end; ++ iter)
			{
				std::cout << "run test suite @" << iter->second->Name() << std::endl;

				void * context = iter->second->Create();

				try
				{
					TestSuite::TestCases::const_iterator iter1,end1 = iter->second->Children().end();

					for(iter1 = iter->second->Children().begin(); iter1 != end1; ++ iter1)
					{
						std::cout << "run test case @@" << (*iter1)->Name() << std::endl;

						time_duration duration;


						try
						{
							timer_t timer;

							(*iter1)->Run(context);

							duration = timer.duration();
						}
						catch(...)
						{
							std::cout << "run test case @@" << (*iter1)->Name() << " -- failed" << std::endl;

							throw;
						}
						

						std::cout << "run test case @@" << (*iter1)->Name() 
							
							<< " -- success(" << duration / 10000000 << "." 
							
							<< std::setw(6) << std::setfill('0') <<(duration % 10000000) / 10 
							
							<< " s)" << std::endl;
					}
				}
				catch(...)
				{
					iter->second->Release(context);

					std::cout << "run test suite @" << iter->second->Name() << " -- failed" << std::endl;

					throw;
				}

				iter->second->Release(context);

				std::cout << "run test suite @" << iter->second->Name() << " -- success" << std::endl;
			}
		}

	private:

		int					_args;

		char				**_argv;

		std::string			_name;

		std::string			_url;

		size_t				_times;
	};

}}}

#endif //LEMON_CXX_UNITTEST_CONSOLE_HPP
