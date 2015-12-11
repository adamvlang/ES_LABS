clc, close all, clear all
% Power consumtion with sleep - idle
U = 5;
I_sleep = [112 116 122]'; %[mW]
I_swdelay = [117 129 143]';  % [mW]
cpu = [12 33 66]';

P_sleep = I_sleep*U;
P_swdelay = I_swdelay*U;

table(cpu, P_sleep, P_swdelay)