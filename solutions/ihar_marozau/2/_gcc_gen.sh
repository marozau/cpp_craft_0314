
export SOLUTION_NAME=solutions_s_example_with_test_data_generating

export BOOST_ROOT=/Users/rilley_elf/_dev/cpp_objc/boost_1_47_0

export BUILD_TYPE=Debug
if [ "$1" == 'Release' ];
then
	export BUILD_TYPE=Release
fi

export BUILD_FOLDER=_build_"$BUILD_TYPE"_32

if [ ! -d $BUILD_FOLDER ];
then
	mkdir $BUILD_FOLDER
fi

cd $BUILD_FOLDER
cmake -DVERBOSE=ON -DBOOST_STAGE_FOLDER_WITH_ADDRESS_MODEL=ON -DSOLUTION_NAME=$SOLUTION_NAME -DCMAKE_BUILD_TYPE=$BUILD_TYPE -G "Unix Makefiles" ../ 
cd ../

