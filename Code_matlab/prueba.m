

camyz = webcam(2);
camxz = webcam(4);

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
    set(gca,'XLim',[-800 800],'YLim',[-800 800],'ZLim',[-800 800])
    %plot3(p(1), p(2), p(3), 'o');
    disp(p);
    

end