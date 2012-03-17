clear;
clc;

fprintf('building...\n');
mex src/mex_api.cpp build/example_mex_and_omp-darwin-i686.a

fprintf('running...\n');
v = mex_api([5 8], [3 -3.2]);
disp(v);
