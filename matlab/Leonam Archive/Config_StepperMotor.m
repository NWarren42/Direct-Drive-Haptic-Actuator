%% Force Sensor
NanoCalibration;
F_M_Direction = [1 1 1 -1 -1 -1]; %Fx Fy Fz Tx Ty Tz


%% Stepper Motor
% Resolution = (360/200 * 1/2);
Resolution = (360/200 * 1/64); % For AnVE step excitation
% Resolution = (360/200 * 1/250);

Kp_SM = 0.15;

