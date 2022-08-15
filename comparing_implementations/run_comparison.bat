:: Batch file that runs the comparison between cpp and Python implementations
python create_synth_data.py
cd ..\\combineall_cpp\\
.\my_combineall.exe
cd ..\\martin_kreisssig_cpp\\
.\kreissig_cpp.exe
cd ..\\comparing_implementations\\
python create_synth_data.py
cd ..\\combineall_python\\
python combineall_python.py
