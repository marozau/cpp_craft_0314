@echo off

set SOLUTION_NAME=puzzle_3_solution
set BOOST_ROOT=D:/Install/boost_1_55_0/boost_1_55_0
set BINARY_READER_ROOT=d:/cpp_craft_0314/solutions/kurman_vladimir/3/

set BUILD_TYPE=Debug
if [%1]==[Release] (
	set BUILD_TYPE=Release
)
set BUILD_FOLDER=_build_%BUILD_TYPE%_64

if not exist %BUILD_FOLDER% (
	mkdir %BUILD_FOLDER%
)

cd %BUILD_FOLDER%
cmake -DBOOST_STAGE_FOLDER_WITH_ADDRESS_MODEL=ON -DVERBOSE=OFF -DCMAKE_BUILD_TYPE=%BUILD_TYPE% -DSOLUTION_NAME=%SOLUTION_NAME%  -G "Visual Studio 12 Win64" ../ 
cd ../

echo "%BUILD_FOLDER%/%SOLUTION_NAME%.sln" > _start_msvc.bat
