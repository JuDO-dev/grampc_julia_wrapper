function [vec,grampc,figNr] = startMPC(figNr,compile,varargin)
% This function runs the PMSM example. It compiles the c-Code,
% initializes the grampc struct, runs the simulation and plots the results.
%
% Input arguments are:
% 1) figNr - number of the first plot
% 2) compile - flag whether to compile the whole toolbox or/and the problem function: 
%              1: only the problem function is compiled
%              2: the whole toolbox and the problem function is compiled
%              else or empty input: nothing is compiled
% 3 - end) - flags for the compilation (e.g. 'debug' or 'verbose') see 
%            make.m in the matlab folder for more details
%
%
% This file is part of GRAMPC - (https://sourceforge.net/projects/grampc/)
%
% GRAMPC -- A software framework for embedded nonlinear model predictive
% control using a gradient-based augmented Lagrangian approach
%
% Copyright 2014-2019 by Tobias Englert, Knut Graichen, Felix Mesmer,
% Soenke Rhein, Andreas Voelz, Bartosz Kaepernick (<v2.0), Tilman Utz (<v2.0).
% All rights reserved.
%
% GRAMPC is distributed under the BSD-3-Clause license, see LICENSE.txt
%

%% Check input arguments
if nargin < 1 || isempty(figNr)
    figNr = 1;
end
if nargin < 2 || isempty(compile)
    compile = 0;
end


%% Parameters
% path to grampc root
grampc_root_path = '../../';
addpath([grampc_root_path 'matlab/mfiles']);
% name of problem function
probfct = 'probfct_PMSM.c';

% plot predicted trajectories
PLOT_PRED = 1;
% plot solution trajectories
PLOT_TRAJ = 1;
% plot optimization statistics
PLOT_STAT = 1;
% update plots after N steps
PLOT_STEPS = 100;
% pause after each plot
PLOT_PAUSE = 0;

% problem-specific plot
PLOT = 1;

% Options for the reference simulation
odeopt =  [];%odeset('RelTol',1e-6,'AbsTol',1e-8);


%% Compilation
% compile toolbox
if compile > 1 || ~exist([grampc_root_path 'matlab/bin'], 'dir')
    grampc_make_toolbox(grampc_root_path, varargin{:});
end
% compile problem
if compile > 0 || ~exist('+CmexFiles', 'dir')
    grampc_make_probfct(grampc_root_path, probfct, varargin{:});
end


%% Initialization
% init GRAMPC and print options and parameters
[grampc,Tsim] = initData;
CmexFiles.grampc_printopt_Cmex(grampc);
CmexFiles.grampc_printparam_Cmex(grampc);

% init solution structure
vec = grampc_init_struct_sol(grampc, Tsim);

% init plots and store figure handles
if PLOT_PRED
    phpP = grampc_init_plot_pred(grampc,figNr);
    figNr = figNr+1;
end
if PLOT_TRAJ
    phpT = grampc_init_plot_sim(vec,figNr);
    figNr = figNr+1;
end
if PLOT_STAT
    phpS = grampc_init_plot_stat(vec,grampc,figNr);
    figNr = figNr+1;
end


%% MPC loop
i = 1;
while 1
    % set current time and current state
    grampc = CmexFiles.grampc_setparam_Cmex(grampc,'t0',vec.t(i));
    grampc = CmexFiles.grampc_setparam_Cmex(grampc,'x0',vec.x(:,i));
    
    % run MPC and save results
    [grampc,vec.CPUtime(i)] = CmexFiles.grampc_run_Cmex(grampc);
    vec = grampc_update_struct_sol(grampc, vec, i);
    
    % print solver status
    printed = CmexFiles.grampc_printstatus_Cmex(grampc.sol.status,'Error');
    if printed
        fprintf('at simulation time %f.\n --------\n', vec.t(i));    
    end
    
    % check for end of simulation
    if i+1 > length(vec.t)
        break;
    end
    
    % simulate system
    [~,xtemp] = ode45(@CmexFiles.grampc_ffct_Cmex,vec.t(i)+[0 double(grampc.param.dt)],vec.x(:,i),odeopt,vec.u(:,i),vec.p(:,i),grampc.userparam);
    vec.x(:,i+1) = xtemp(end,:);
        
    % evaluate time-dependent constraints 
    % to obtain h(x,u,p) instead of max(0,h(x,u,p))
    vec.constr(:,i) = CmexFiles.grampc_ghfct_Cmex(vec.t(i), vec.x(:,i), vec.u(:,i), vec.p(:,i), grampc.userparam);
    
    % update iteration counter
    i = i + 1;
    
    % plot data
    if mod(i,PLOT_STEPS) == 0 || i == length(vec.t)
        if PLOT_PRED
            grampc_update_plot_pred(grampc,phpP);
        end
        if PLOT_TRAJ
            grampc_update_plot_sim(vec,phpT);
        end
        if PLOT_STAT
            grampc_update_plot_stat(vec,grampc,phpS);
        end
        drawnow
        if PLOT_PAUSE
            pause;
        end
    end
end


%% Additional code
if PLOT == 1
    figure(figNr)
    clf
    figNr = figNr+1;
    umax = sqrt(grampc.userparam(9));
    imax = sqrt(grampc.userparam(10));
    
    subplot(1,3,1)
    rectangle('Position',[-imax -imax 2*imax 2*imax],'Curvature',[1 1],'EdgeColor',[0 0 0],'LineStyle','--'),hold on
    plot(vec.x(1,:),vec.x(2,:)), hold off, axis equal, 
    xlim([-11 11]), ylim([-11,11]), xlabel('x_1'), ylabel('x_2')
    
    % Transformation of the dq-voltages into alpha beta coordinates
    vec.u_ab = zeros(2,length(vec.t));
    for i = 1:length(vec.t)
        vec.u_ab(:,i) = [cos(vec.x(4,i)) -sin(vec.x(4,i));sin(vec.x(4,i)) cos(vec.x(4,i))]*vec.u(:,i);
    end
    
    subplot(1,3,2)
    plot(vec.u_ab(1,:),vec.u_ab(2,:)),hold on
    rectangle('Position',[-umax -umax 2*umax 2*umax],'Curvature',[1 1],'EdgeColor',[0 0 0],'LineStyle','--'), hold off, axis equal, 
    xlim([-400 400]),ylim([-400,400]), xlabel('u_\alpha'),ylabel('u_\beta')
    
    subplot(1,3,3)
    plot(vec.t,vec.x(3,:)/(2*pi*3)*60),xlabel('time'),ylabel('mechanical rotor speed in rpm')
end
end