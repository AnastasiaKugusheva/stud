tic %������ �������
X0 = [1; 1];
eps = 0.01;
syms S;
S = 1;
syms L;
C=2; %counter(�.�. 2 ���� �� MNGS)
syms ans;
syms p;
syms Y;



syms X1 X2 %���������� �� ������� ����� ����� �����������
f = (X1^2 + X2 -11)^2 + (X1 + X2^2 - 7)^2;
df1 = diff(f,'X1'); %����������� �� ���������� X1
df2 = diff(f,'X2');


i=0;

counter = 1;
syms pX pY

%������ 2 ���� �� ������ ������������� ������������ ������ (MNGS)
while i < 2
   i = i + 1;
   syms L;
   syms K; 
   
%����������� �������� X0 � ����������� (f'(x))
res1 = subs(df1, {X1, X2},{X0(1,1), X0(2,1)});
res2 = subs(df2, {X1, X2},{X0(1,1), X0(2,1)});



%������ X
X = [X0(1,1) - L*res1; X0(2,1) - L*res2];
%����������� �������� X � f
L0 = subs(f, {X1, X2}, {X(1,1), X(2,1)});

% ����������� �� L
Ld = (diff(L0, L));
L = solve(Ld);
steps = real(double(L)); 
K = max(steps);
    
X = ([X0(1,1) - K*res1; X0(2,1) - K*res2]); 
    
  fX11 = subs(df1, {X1, X2}, {X(1,1), X(2,1)});
  fX12 = subs(df2, {X1, X2}, {X(1,1), X(2,1)});
    
  X0(1,1) = X(1,1);
  X0(2,1) = X(2,1);
  
  pX(counter,1) = double(X(1,1));
  pY(counter,1) = double(X(2,1));
  counter = counter + 1;
  
end    



Y(1,1) = X(1,1);
Y(2,1) = X(2,1);

X0 = [1; 1]; 


   
while S > eps
  C = C + 1;  
  syms L;
  syms K;

%������ X
X = [X0(1,1) + K*(Y(1,1) - X0(1,1)); X0(2,1) + K*(Y(2,1) - X0(2,1))];
%����������� �������� X � f
L0 = subs(f, {X1, X2}, {X(1,1), X(2,1)});

% ����������� �� L
Ld = (diff(L0, K));
L = solve(Ld);
steps = real(double(L)); 
K = max(steps);
    

%L = ans;
X = [X0(1,1) + K*(Y(1,1) - X0(1,1)); X0(2,1) + K*(Y(2,1) - X0(2,1))];  
  
  %�������� ���������
    
  S = double(abs(subs(f, {X1, X2},{X(1,1), X(2,1)}) - (subs(f, {X1, X2},{X0(1,1), X0(2,1)}))));
 
   disp('Continue');
  
  X0(1,1) = X(1,1);
  X0(2,1) = X(2,1);

 
  pX(counter,1) = double(X(1,1));
  pY(counter,1) = double(X(2,1));
  counter = counter + 1;
end
 

  disp(double(X));
  disp(C);   

toc %����� �������

hold on

x = 1 : .2 : 4;  
[CX1, CX2] = meshgrid(x);
Z = (CX1.^2 + CX2 -11)^2 + (CX1 + CX2.^2 -7)^2;
contour(CX1, CX2, Z);

plot(pX, pY, '-or');

hold off


 
 






