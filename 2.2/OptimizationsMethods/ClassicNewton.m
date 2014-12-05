tic %начало отсчета

syms S;
S = 1;
X0 = [1; 1];
eps = 0.05;
C=0;
syms d;

syms X1 X2; %переменные по которым будем брать производные
f = (X1^2 + X2 -11)^2 + (X1 + X2^2 -7)^2;
df1 = diff(f,'X1'); %производная по переменной X1
df2 = diff(f, 'X2');

counter = 1;
syms pX pY

while S > eps
    C = C+1;

%подставляем значения X0 в производную (f'(x))
res1 = double(subs(df1, {X1, X2},{X0(1,1), X0(2,1)}));
res2 = double(subs(df2, {X1, X2},{X0(1,1), X0(2,1)}));

%строим вторую производную
ddf1 = diff(df1, 'X1');
ddf2 = diff(df2, 'X2');

%подставляем значение X0 в производную (f''(x))
dres1 = double(subs(ddf1, {X1, X2},{X0(1,1), X0(2,1)}));
dres2 = double(subs(ddf2, {X1, X2},{X0(1,1), X0(2,1)}));

%-1 степень
d1 = [(dres1)^(-1); (dres2)^(-1)];

%строим X
X= double([X0(1,1) - d1(1,1)*res1; X0(2,1) - d1(2,1)*res2]);


  %критерий остановки
 
  fX11 = double(subs(df1, {X1, X2}, {X(1,1), X(2,1)}));
  fX12 = double(subs(df2, {X1, X2}, {X(1,1), X(2,1)})); 
  
  fX1 = [ fX11; fX12;];
  S = double(sqrt((fX11*fX11 + fX12*fX12)));
 
   
  
  disp('Continue');
  
  X0(1,1) = X(1,1);
  X0(2,1) = X(2,1);
 
  pX(counter,1) = double(X(1,1));
  pY(counter,1) = double(X(2,1));
  counter = counter + 1;

end


disp(double(X));
  disp(C); 
toc  %конеч отсчета

hold on

x = -3 : .2 : 0.5;  
[CX1, CX2] = meshgrid(x);
Z = (CX1.^2 + CX2 -11)^2 + (CX1 + CX2.^2 -7)^2;
contour(CX1, CX2, Z);

plot(pX, pY, '-or');

hold off
 
