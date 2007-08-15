#include"FCS2.hpp"
#include<fstream>
#include<sstream>
#include<map>
#include<iostream>
#include<string>

void show_help ();

void open_filenames (std::vector<FCSTools::FCS<std::size_t> >&,
		     std::vector<std::string> const& names);

int main (int argc, char *argv[])
{

  std::vector<std::string> args;
  for (int i=0; i<argc; ++i)
    args.push_back (argv[i]);

  if (1 == argc)
    {
      show_help ();
      return 0;
    }

  std::string Command = argv[1];

  if ("merge" == Command)
    {
      // fcsconvert merge file ... file out filename
      //    1        2      3            4    5
      if (args.size () < 5)
	{
	  std::cout << "Not enough parameters." << std::endl;
 	  return 0;
	}
      std::vector<std::string> filenames (args.begin () + 2, args.end () - 2);
      std::string outname = args.back ();
      std::vector<FCSTools::FCS<std::size_t> > fcses;
    }

  return 0;
}

bool open_filenames (std::vector<FCSTools::FCS<std::size_t> > fcses&,
		     std::vector<std::string> const& names)
{
  for (std::size_t i=0; i<fcses.size (); ++i)
    {
      std::fstream fs (filenames[i].c_str (), std::ios::in|std::ios::binary);
      if (! fs)
	{
	  std::cout << "Could not open the file named \"" << filenames[i] << "\"!" << std::endl;
	  return false;
	}
      try
	{
	  FCSTools::FCS<std::size_t> fcs = FCSTools::Reader<std::size_t> (fs);
	}
      catch (FCSTools::fcs_error ferr)
	{
	  std::cout << ferr.what () << std::endl;
	  return false;
	}
    }
  return true;
}

void show_help ()
{
  std::cout << "fcsconvert command files... [out filename]" << std::endl;
  std::cout << "\tWhere command is one of: merge, cat, "
	    << "\t  datatype, width, trunc, resample;" << std::endl
	    << "\tand \"files...\" is a list of files;" << std::endl
	    << "\tand \'filename\' is the name of the output file." << std::endl;
  std::cout << std::endl;
  std::cout << "\tmerge files... out filename:" << std::endl
	    << "\t  add the columns of the files into a single" << std::endl
	    << "\t  file whose name is \'filename\' only if" << std::endl
	    << "\t  the columns are the same length." << std::endl;
  std::cout << std::endl;
  std::cout << "\tcat files... out filename:" << std::endl
	    << "\t  append the files into a single file called" << std::endl
	    << "\t  \'filename\' only if they have the same number"
	    << "\t  of rows." << std::endl;
  std::cout << std::endl;
  std::cout << "\twidth N file out filename" << std::endl
	    << "\t ... or ..." << std::endl
	    << "\twidth! N files...:" << std::endl
	    << "\t  Change the number of bits (to N) that the Integer data"
	    << std::endl
	    << "\t  is stored in. The first form saves \'file\'" << std::endl
	    << "\t  in at \'filename\'. The second form saves in place."
	    << std::endl;
  std::cout << std::endl;
  std::cout << "\ttrunc N file out filename" << std::endl
	    << "\t ... or ..." << std::endl
	    << "\ttrunc! N files..." << std::endl
	    << "\t  Remove the first N elements from the dataset." << std::endl
	    << "\t  Alternately, -N removes the last N elements" << std::endl
	    << "\t  from the dataset. The first form saves to \'file\'" << std::endl
	    << "\t  and the second form saves in place." << std::endl;
  std::cout << std::endl;
  std::cout << "\tresample N K file out filename" << std::endl
	    << "\t ... or ..." << std::endl
	    << "\tresample! N K files..." << std::endl;
}
