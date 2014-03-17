
<<<<<<< HEAD
export SOLUTION_NAME=puzzle_1_3_solution
=======
export SOLUTION_NAME=puzzle_1_solution
>>>>>>> 3d99139d22c27f11b1908e6fa8ccf896e79994f3

export BUILD_TYPE=Debug
if [ "$1" == 'Release' ];
then
	export BUILD_TYPE=Release
fi

<<<<<<< HEAD
export BUILD_FOLDER=_build_"$BUILD_TYPE"_32
=======
export BUILD_FOLDER=_build_"$BUILD_TYPE"_64
>>>>>>> 3d99139d22c27f11b1908e6fa8ccf896e79994f3

if [ ! -d $BUILD_FOLDER ];
then
	mkdir $BUILD_FOLDER
fi

cd $BUILD_FOLDER
<<<<<<< HEAD
cmake -DVERBOSE=OFF -DSOLUTION_NAME=$SOLUTION_NAME -DCMAKE_BUILD_TYPE=$BUILD_TYPE -G "Eclipse CDT4 - Unix Makefiles" -D_ECLIPSE_VERSION=3.6 ../ 
=======
cmake -DVERBOSE=OFF -DSOLUTION_NAME=$SOLUTION_NAME -DCMAKE_BUILD_TYPE=$BUILD_TYPE -G "Unix Makefiles" ../ 
>>>>>>> 3d99139d22c27f11b1908e6fa8ccf896e79994f3
cd ../

