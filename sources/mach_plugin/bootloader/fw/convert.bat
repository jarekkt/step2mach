echo #include "..\\stdafx.h" > fw.cpp
echo const char step2mach_ver = 'C'; >>  fw.cpp
perl.exe bin2hex.pl step2machRel.hex 1 >> fw.cpp

