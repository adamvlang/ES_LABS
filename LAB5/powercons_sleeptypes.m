clc, close all, clear all
% Power consumtion with sleep - different types
U = 5;
sleep_type = {'Idle' 'Frozen' 'Standby' 'Stop' 'Deep stop' 'Static'}';
blink = {'yes' 'yes' 'yes' 'yes' 'yes' 'no'}';
I_sleep = [101 93 85 85 87 87]';  % [mW]

P_sleep = I_sleep*U;

table(sleep_type, blink, P_sleep)