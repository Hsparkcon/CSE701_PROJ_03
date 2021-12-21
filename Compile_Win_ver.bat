set compiler_path="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\MSBuild.exe"
set compiler_mode="/property:Configuration=Release"
set compile_target="build\CSE701_PROJ_03.sln"

cmake -S . -B build\
%compiler_path% %compile_target% %compiler_mode%



set copy_execute_src="build\Release\proj_r.exe"
set copy_example_data_src="example_data\observed_data.dvec "
set copy_dest="execute"

mkdir execute
copy %copy_execute_src% %copy_dest%
copy %copy_example_data_src% %copy_dest%
@RD -r /s /q build
