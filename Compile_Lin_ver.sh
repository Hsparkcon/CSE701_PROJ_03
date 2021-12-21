cmake -S . -B build/

cd build
make
cd ..

copy_execute_src="build/proj_r"
copy_example_data_src="example_data/observed_data.dvec "
copy_dest="execute"

mkdir execute
cp $copy_execute_src $copy_dest
cp $copy_example_data_src $copy_dest

remove_target="build" 
rm -r $remove_target