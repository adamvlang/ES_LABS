clc, clear all, close all
U = 5;
I = 136;        %[mA]

I = I*1e-3;

fprintf('Power consumtion: %0.2f mW\n',  U*I*1e3)