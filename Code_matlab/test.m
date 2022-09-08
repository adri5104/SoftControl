% Test file for intersp3.m which calculates the intersection of three spheres
% By: Hrishi Shah
clc;
x1=0; y1=0.5; z1=0.25; x2=1; y2=1; z2=0.2; x3=2; y3=1; z3=1;
r1=2.5; r2=2.6; r3=2.7; % TEST DATA
P1=interx([x1 y1 z1],[x2 y2 z2],[x3  y3 z3],r1,r2,r3,0);
P2=interx([x1 y1 z1],[x2 y2 z2],[x3  y3 z3],r1,r2,r3,1);
% Visualization for the intersection point
if(~isnan(P1))
    figure; hold on; view(-24,8);
    plotsphere([x1 y1 z1],r1,'r');
    plotsphere([x2 y2 z2],r2,'b');
    plotsphere([x3 y3 z3],r3,'y');
    plot3(P1(1),P1(2),P1(3),'ro','linewidth',3);
    plot3(P2(1),P2(2),P2(3),'ro','linewidth',3);
    hold off;
end