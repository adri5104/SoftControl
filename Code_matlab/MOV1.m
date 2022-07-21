obj = serialport('COM22', 9600);
millisdesinflar = "w,1,-5000,-5000,-5000,-5000,-5000,-5000,-5000,-5000,-5000";
writeline(obj, millisdesinflar);
pause(5);
writeOneValveMillis(obj, 1, 2400);
pause(2.4);
writeOneValveMillis(obj, 4, 2400);
pause(1.6);
millisdesinflar = "w,1,-5000,0,-5000,-5000,-5000,-5000,-5000,-5000,-5000";
writeline(obj, millisdesinflar);
pause(3);


writeOneValveMillis(obj, 6, 2400);
pause(3);
writeOneValveMillis(obj, 4, -1600);
writeOneValveMillis(obj, 4, 1600);
millisdesinflar = "w,1,-6000,-6000,-10000,-6000,-6000,-6000,-6000,-6000,-6000";
writeline(obj, millisdesinflar);
pause(6);


delete(obj)