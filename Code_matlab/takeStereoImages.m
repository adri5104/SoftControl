CAM_LEFT_NAME = 'XiaoMi USB 2.0 Webcam';
CAM_RIGHT_NAME = 'DroidCam Source 3';
IMAGES_TO_TAKE = 20;

cam_left = webcam(CAM_LEFT_NAME);
cam_right = webcam(CAM_RIGHT_NAME);

for i = 1:IMAGES_TO_TAKE

    img_right = snapshot(cam_right);
    img_right_name ="C:\TFG_software\Code_matlab\cam_right\" + "right" + num2str(i) + ".jpeg";
    imwrite(img_right, img_right_name, 'jpeg');

    img_left = snapshot(cam_left);
    img_left_name ="C:\TFG_software\Code_matlab\cam_left\" + "left" + num2str(i) + ".jpeg";
    imwrite(img_left, img_left_name, 'jpeg');

    pause(0.1);
end

delete(cam_right);
delete(cam_left);