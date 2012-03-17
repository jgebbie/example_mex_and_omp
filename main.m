clear all;
clc;

%%
fprintf('building...\n');
!make
mex -v ...
    CFLAGS="\$CFLAGS -fopenmp" ...
    CXXFLAGS="\$CXXFLAGS -fopenmp" ...
    LDFLAGS="\$LDFLAGS -fopenmp" ...
    src/mex_api.cpp ...
    build/example_mex_and_omp-darwin-i686.a

%%
clc

fprintf('running...\n');
vIn = rand(round(1000000),2);

ntrials = 10;
measured_times = nan(ntrials,2);

for n = -2:ntrials
    
    vOut = nan(size(vIn,1),1);
    
    tic;
    vOut = vIn(:,1).*vIn(:,2);
    m1 = toc;
    
    tic;
    vOut = mex_api(vIn(:,1), vIn(:,2));
    m2 = toc;
    
    if n >= 1
        measured_times(n,:) = [m1 m2];
    end
    
end

fprintf('%15s: %20.10f\n', 'matlab', mean(measured_times(:,1)));
fprintf('%15s: %20.10f\n', 'native', mean(measured_times(:,2)));
