set cmake_op_source_path=-S .
set cmake_op_build_path=-B build\
set cmake_op_compiler=-G "MinGW Makefiles"
cmake %cmake_op_source_path% %cmake_op_build_path% %cmake_op_compiler%

cd build
make.exe
cd ..

set copy_execute_src="build\proj_r.exe"
set copy_example_data_src="example_data\observed_data.dvec"
set copy_dest="execute"

mkdir execute
copy %copy_execute_src% %copy_dest%
copy %copy_example_data_src% %copy_dest%
@RD -r /s /q build
