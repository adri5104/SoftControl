% function to plot a sphere given the center, radius and color
% By: Hrishi Shah
function handle=plotsphere(X,r,color)
npoints=10;
phi=0:pi/npoints:2*pi; th=(0:pi/npoints:pi)';
handle=mesh(X(1)+r*sin(th)*cos(phi),X(2)+r*sin(th)*sin(phi),X(3)+r*cos(th)*ones(size(phi,1),size(phi,2)),...% all main in this line
    'FaceAlpha',0.2,'FaceColor',color,'EdgeColor',color,'EdgeAlpha',0.1); % all options in this line