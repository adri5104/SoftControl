obj = serialport('COM22', 9600);
desinflar(obj, 2000);


writeOneValveMillis(obj, 7, 1000);
pause(1.5)

writeOneValveMillis(obj, 8, 1000);
writeOneValveMillis(obj, 7, -1500);
pause(1.5)

writeOneValveMillis(obj, 9, 1000);
writeOneValveMillis(obj, 8, -1500);
pause(1.5)

writeOneValveMillis(obj, 7, 1000);
writeOneValveMillis(obj, 9, -1500);
pause(1.5)

writeOneValveMillis(obj, 8, 1000);
writeOneValveMillis(obj, 7, -1500);
pause(1.5)

writeOneValveMillis(obj, 9, 1000);
writeOneValveMillis(obj, 8, -1500);
pause(1.5)



desinflar(obj, 2000);
pause(2);

delete(obj);