tic %������ �������
X0 = [-7; 7];
eps = 0.05;
syms S;
S = 1;
L=1;
C=0; %counter

syms X1 X2 %���������� �� ������� ����� ����� �����������
f = (X1^2 + X2 - 11)^2 + (X1 + X2^2 -7)^2;
%f = 9*X1*X1 + X2*X2;
df1 = diff(f,'X1'); %����������� �� ���������� X1
df2 = diff(f, 'X2');

counter = 1;
syms pX pY
pX(counter,1) = double(X0(1,1));
pY(counter,1) = double(X0(2,1));
counter = counter + 1;


Km = 0.01;
K = 1;
 
while S > eps
    C= C+1;
  %����������� �������� X0 � ����������� (f'(x))
  res1 = double(subs(df1, {X1, X2},{X0(1,1), X0(2,1)}));
  res2 = double(subs(df2, {X1, X2},{X0(1,1), X0(2,1)}));


  %������ X
  X = double([X0(1,1) - L*K*res1; X0(2,1) - L*K*res2]);  

  %��������� ������� f(x)-f(x0)<-L*E*||f'(x0)||
  fX = double(subs(f, {X1, X2}, {X(1,1), X(2,1)}));
  fX0 = double(subs(f,{X1, X2}, {X0(1,1), X0(2,1)}));

  %��������� �����
  N = double((res1*res1 + res2*res2)); 
    
  left = double(fX-fX0);
  right = double(-1*L*K*eps*N);
  
  if fX-fX0 >= -1*L*K*eps*N
      K = K*Km; 
      %������������� X      
      X = double([X0(1,1) - L*K*res1; X0(2,1) - L*K*res2]);        
      
  end
    
  %�������� ���������
 
  fX11 = double(subs(df1, {X1, X2}, {X(1,1), X(2,1)}));
  fX12 = double(subs(df2, {X1, X2}, {X(1,1), X(2,1)})); 
    
  S = sqrt((fX11*fX11 + fX12*fX12));
  
  disp('Continue');
  
  X0(1,1) = X(1,1);
  X0(2,1) = X(2,1);
  
  res1 = fX11;
  res2 = fX12;
  
  pX(counter,1) = double(X(1,1));
  pY(counter,1) = double(X(2,1));
  counter = counter + 1;

end

  pX(counter,1) = double(X(1,1));
  pY(counter,1) = double(X(2,1));
  counter = counter + 1;

 % format short;

  disp(double(X));
  disp(C);    
  
toc %����� �������

hold on


[CX1, CX2] = meshgrid(-10 : 0.2 : 10);
Z = (CX1.^2 + CX2 - 11)^2 + (CX1 + CX2.^2 - 7)^2;
contour(CX1, CX2, Z, 4);

plot(pX, pY, '-or');

hold off
 
 






