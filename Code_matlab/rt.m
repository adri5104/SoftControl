cam1 = webcam(2);
cam2 = webcam(4);


while(1 < 2)
    
    img1 = snapshot(cam1);
    img2 = snapshot(cam2);

    imshow(img1);
    hold on;

    [xb1,yb1] = findPoint(img1, 'b');
    [xg1,yg1] = findPoint(img1, 'g');
    [xo1,yo1] = findPoint(img1, 'o');
    
    

    if xb1 ~= -1 && xg1 ~= -1
    plot([xb1 xg1], [yb1 yg1], 'g');
    end
    if xo1 ~= -1 && xb1 ~= -1
    plot([xb1 xo1], [yb1 yo1], 'b');
    end
    if xo1 ~= -1 && xg1 ~= -1
    plot([xg1 xo1], [yg1 yo1], 'r');
    end

    hold off;

    imshow(img2);
    hold on;

    [xb2,yb2] = findPoint(img2, 'b');
    [xg2,yg2] = findPoint(img2, 'g');
    [xo2,yo2] = findPoint(img2, 'o');
    
    

    if xb2 ~= -1 && xg2 ~= -1
    plot([xb2 xg2], [yb2 yg2], 'g');
    end
    if xo2 ~= -1 && xb2 ~= -1
    plot([xb2 xo2], [yb2 yo2], 'b');
    end
    if xo2 ~= -1 && xg2 ~= -1
    plot([xg2 xo2], [yg2 yo2], 'r');
    end
    
    hold off;


    %[BW, ~] = imageThresholdBlue(img);
    %imshow(BW);

    





end