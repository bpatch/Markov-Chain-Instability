clc; clear all;
N = 3000;
Y_stable_local = csvread('Y_local_SamplePath_ell=0.400000_sample=1.000000.csv');
T_stable_local = csvread('T_local_SamplePath_ell=0.400000_sample=1.000000.csv');
Y_unstable_local = csvread('Y_local_SamplePath_ell=0.600000_sample=1.000000.csv');
T_unstable_local = csvread('T_local_SamplePath_ell=0.600000_sample=1.000000.csv');

Y_stable_global = csvread('Y_global_SamplePath_ell=0.400000_sample=1.000000.csv');
T_stable_global = csvread('T_global_SamplePath_ell=0.400000_sample=1.000000.csv');
Y_unstable_global = csvread('Y_global_SamplePath_ell=0.600000_sample=1.000000.csv');
T_unstable_global = csvread('T_global_SamplePath_ell=0.600000_sample=1.000000.csv');

subplot(1,2,1)
plot(1:N, Y_stable_global(1:N)./T_stable_global(1:N),1:N, Y_unstable_global(1:N)./T_unstable_global(1:N))
set(gca, 'YScale', 'log')
subplot(1,2,2)
plot(1:N, Y_stable_local(1:N)./T_stable_local(1:N),1:length(Y_unstable_local), Y_unstable_local(1:length(Y_unstable_local))./T_unstable_local(1:length(Y_unstable_local)))
set(gca, 'YScale', 'log')