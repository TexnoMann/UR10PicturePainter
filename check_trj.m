data = csvread('trj/trj10.csv',2);
x =data(:,1);
y = data(:,2);
z =data(:,3);
t =data(:,4);
% plot3([-0.0335,0.3479, 0.5268]);

%% Trj
T=[0.9943         0    0.1068   -0.0335;
    0.1027    0.2763   -0.9556    0.3479;
   -0.0295    0.9611    0.2747    0.5268;
         0         0         0    1.0000];
% data(:,4) = ones(size(data,1),1);    
% dataT = (T*data')';
% plot3(dataT(:,1),dataT(:,2),dataT(:,3),'*');
xlabel('x');
ylabel('y');
zlabel('z');
% hold on
plot3(data(:,1),data(:,2),data(:,3),'*');