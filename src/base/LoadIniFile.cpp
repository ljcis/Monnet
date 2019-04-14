#include "LoadIniFile.h"
#include "inifile.h"
#include <string.h>
#include <unistd.h>

int LoadIniFile::loadLogLevel()
{
    CIniFile iFile;
    iFile.OpenIniFile("etc/monnet.cfg");
    int retval =  iFile.ReadInt("setting", "loglevel", 3);
    iFile.CloseIniFile();
    return retval;
}

void LoadIniFile::setLogLevel( int level )
{
    CIniFile iFile;
    iFile.OpenIniFile("etc/monnet.cfg");
    iFile.WriteInt( "setting", "loglevel", level );
    iFile.WriteIniFile("etc/monnet.cfg");
    iFile.CloseIniFile();
}


