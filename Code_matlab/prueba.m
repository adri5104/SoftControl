

camyz = webcam(4);
camxz = webcam(2);

[rotyz, transyz] = findCameraPose(camyz, cameraParams);
[rotxz, transxz] = findCameraPose(camxz, cameraParams);

hold off

figure

pcshow([0,0,0]);
hold off;



while(true)

    iyz = snapshot(camyz);
    ixz = snapshot(camxz);

    greenyz = findPoint(iyz, 'g');
    greenxz = findPoint(ixz, 'g');

    yz = pointsToWorld(cameraParams.Intrinsics, rotyz, transyz, greenyz);
    xz = pointsToWorld(cameraParams.Intrinsics, rotxz, transxz, greenxz);

    p = getCoordinates(yz, xz);
    scatter3(p(1), p(2), p(3), '*');
    set(gca,'XLim',[-400 400],'YLim',[-400 400],'ZLim',[-400 400])
    %plot3(p(1), p(2), p(3), 'o');
    disp(p);
    

end