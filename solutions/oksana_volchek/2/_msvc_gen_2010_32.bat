@echo off

set SOLUTION_NAME=puzzle_2_solution
set BOOST_ROOT=g:/boost/boost_1_55_0
rem set BOOST_LIBRARYDIR=g:/boost/boost_1_55_0/stage/lib

set BUILD_TYPE=Debug
if [%1]==[Release] (
	set BUILD_TYPE=Release
)
set BUILD_FOLDER=_build_%BUILD_TYPE%_32

if not exist %BUILD_FOLDER% (
	mkdir %BUILD_FOLDER%
)

cd %BUILD_FOLDER%
cmake -DBOOST_STAGE_FOLDER_WITH_ADDRESS_MODEL=ON -DVERBOSE=OFF -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DSOLUTION_NAME=%SOLUTION_NAME% -G "Visual Studio 10" ../ 
cd ../

echo "%BUILD_FOLDER%/%SOLUTION_NAME%.sln" > _start_msvc.bat
