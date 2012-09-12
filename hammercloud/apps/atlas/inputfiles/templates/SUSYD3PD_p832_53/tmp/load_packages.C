#include <fstream>
#include <iostream>
#include <TSystem.h>

void load_packages (){
  const char *root_core_dir = gSystem->Getenv ("ROOTCOREDIR");
  if (root_core_dir == 0)
    throw std::string ("ROOTCOREDIR not set, try sourcing RootCoreDir/setup.sh");
  const std::string dir (root_core_dir);

  const std::string include_dir = dir + "/include";
  if (gSystem->AccessPathName (include_dir.c_str()) == 1)
    throw std::string ("failed to find " + include_dir);
  gSystem->AddIncludePath (("-I\"" + include_dir + "\"").c_str());
  cout << "gSystem->AddIncludePath(\"-I" <<include_dir<<"\");"<<endl;
  
  const std::string lib_dir = dir + "/lib";
  if (gSystem->AccessPathName (lib_dir.c_str()) == 1)
    throw std::string ("failed to find " + lib_dir);

  {
    std::ifstream preload_file ((dir + "/preload").c_str());
    std::string preload;
    while (std::getline (preload_file, preload))
    {
      if (!preload.empty() && preload[0] != '#')
      {
	if (gSystem->Load (preload.c_str()) < 0)
	  throw std::string ("failed to load library " + preload);
        cout << "gSystem->Load(\"" <<preload<<"\");"<<endl;
      };
    };
  };

  const std::string lib_pkg = dir + "/packages";
  if (gSystem->AccessPathName (lib_pkg.c_str()) == 1)
    throw std::string ("failed to find " + lib_pkg);
  {
    std::ifstream pkg_file ((dir + "/packages").c_str());
    std::string package;
    while (std::getline (pkg_file, package))
    {
      if (!package.empty() && package[0] != '#')
      {
	const std::string name = package.substr (package.rfind ('/') + 1);

	if (name.empty())
	  throw std::string ("failed to parse package name " + package);

	const std::string glob_lib = lib_dir + "/lib" + name + ".so";
	if (gSystem->Load (glob_lib.c_str()) < 0)
	  throw std::string ("failed to load library " + glob_lib);
        cout << "gSystem->Load(\"" <<glob_lib<<"\");"<<endl;
      };
    };
  };
}
