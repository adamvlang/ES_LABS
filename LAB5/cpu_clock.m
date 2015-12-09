clear all; close all; clc;
% If you improve this m-file, please send it to hbjo@kth.se 
% and it will be used in the course in the future.
% pm_pll_setup(&AVR32_PM, 0,  // pll.
%	               10,  // mul sets PLLMUL
%	               1,   // div sets PLLDIV
%	               0,   // osc sets PLLOSC osc0 gives 12MHz
%	               16); // lockcount.

% Frequency ranges:
% VCO -> 80 - 240 MHz


%% Parameters
% Define parameters
% F_VCO
PLLMUL=3; 
PLLDIV=0;
% F_PLL
PLLDIV2=1;
% F_CPU
CPUSEL=1;

% Predifined
fosc0=12e6;     % Oscillator frequency [Hz]
fosc=fosc0;

%% Calculations
if PLLDIV==0
    f_vco=2*(PLLMUL+1)*fosc;
    plldiv_str = 'f_vco=2*(PLLMUL+1)*fosc'; 
    plldiv_str_num = sprintf('f_vco=2*(%i+1)*%i', PLLMUL, fosc*1e-6);
end
if PLLDIV>0
    f_vco=(PLLMUL+1)*fosc/PLLDIV;
    plldiv_str = 'f_vco=(PLLMUL+1)*fosc/PLLDIV';
    plldiv_str_num = sprintf('f_vco=(%i+1)*%i/%i', PLLMUL, fosc, PLLDIV);
end
%pm_pll_set_option(&AVR32_PM, 0, // pll  
%	                    1,  // pll_freq sets frequency range
%	                    1,  // pll_div2 sets PLLDIV (PLLOPT(1))
%	                    0); // pll_wbwdisable

%Frequency range of PLL
%0 = between 160 and 240 MHz
%1 = between 80 and 180 MHz
if PLLDIV2==0
    f_pll=f_vco;
    plldiv2_str = 'f_pll=f_vco';
    plldiv2_str_num = sprintf('f_pll=%i', f_vco*1e-6);
end
if PLLDIV2==1
    f_pll=f_vco/2;
    plldiv2_str = 'f_pll=f_vco/2';
    plldiv2_str_num = sprintf('f_pll=%i/2', f_vco*1e-6);
end
%pm_cksel(&AVR32_PM,
%	           1, 0,   // pbadiv, pbasel.
%	           1, 0,   // pbbdiv, pbbsel.
%	           1, 0);  // hsbdiv, hsbsel.
%(CPU clock = HSB clock gives CPUSEL=hsbsel)
f_main=f_pll;
f_cpu=f_main/(2^(CPUSEL+1));
fcpu_str = 'f_cpu=f_main/(2^(CPUSEL+1))';
fcpu_str_num = sprintf('f_cpu=%i/(2^(%i+1))', f_main*1e-6, CPUSEL);


%% Put all variables in array for printing in table form
Variables = {'PLLMUL', 'PLLDIV', 'PLLDIV2', 'CPUSEL'}';
Values = [PLLMUL, PLLDIV, PLLDIV2, CPUSEL]';

% Define table
resultTable = table(Variables, Values);
% Print outs
disp(resultTable)
disp(plldiv_str)
disp(plldiv_str_num)
fprintf('VCO Frequency is %0.2f MHz\n', f_vco*1e-6)
disp('----------------------------')
fprintf('PLLDIV2 = %i\n', PLLDIV2)
disp(plldiv2_str)
disp(plldiv2_str_num)
fprintf('PLL Frequency is %0.2f MHz\n', f_pll*1e-6)
disp('----------------------------')
disp('f_main=f_pll')
fprintf('MAIN Frequency is %0.2f MHz\n', f_main*1e-6)
disp('----------------------------')
disp(fcpu_str)
disp(fcpu_str_num)
fprintf('CPU Frequency is %0.2f MHz\n', f_cpu*1e-6)







