function [pointReal] = getCoordinates(yz, xz)


x_camyz = yz(1);
y_camyz = yz(2);
x_camxz = xz(1);
d = 245;
dy = 230;
dx = 260;

pointReal = [-x_camxz+d-dx,-x_camyz+ dy,y_camyz];



end