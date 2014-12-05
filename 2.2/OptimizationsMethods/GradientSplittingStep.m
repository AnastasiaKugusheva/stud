tic %начало отсчета
X0 = [1; 1];
eps = 0.05;
syms S;
S = 1;
L=1;
K= 0.1;
C=0; %counter

syms X1 X2 %переменные по которым будем брать производные
f = (X1*X1 + X2 -11)^2 + (X1 + X2*X2 -7)^2;
%f = 9*X1*X1 + X2*X2;
df1 = diff(f,'X1'); %производная по переменной X1
df2 = diff(f, 'X2');

counter = 1;
syms pX pY

while S > eps
    C= C+1;
    K=0.01;
%подставляем значения X0 в производную (f'(x))
res1 = double(subs(df1, {X1, X2},{X0(1,1), X0(2,1)}));
res2 = double(subs(df2, {X1, X2},{X0(1,1), X0(2,1)}));


%строим X
X = [X0(1,1) - L*res1; X0(2,1) - L*res2];

%проверяем условие f(x)-f(x0)<-L*E*||f'(x0)||
fX = double(subs(f, {X1, X2}, {X(1,1), X(2,1)}));
fX0 = double(subs(f,{X1, X2}, {X0(1,1), X0(2,1)}));

  %вычиление нормы
  N = double(sqrt((res1*res1 + res2*res2))); 
  
  
  if fX-fX0 >= -1*L*eps*N
      X = double([X0(1,1) - L*K*res1; X0(2,1) - L*K*res2]);  
      
      K = K*K; 
  end
    
  %критерий остановки
 
  fX11 = double(subs(df1, {X1, X2}, {X(1,1), X(2,1)}));
  fX12 = double(subs(df2, {X1, X2}, {X(1,1), X(2,1)})); 
  
  fX1 = [ fX11; fX12;];
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

 % format short;

  disp(double(X));
  disp(C);    
  
toc %конец отсчета

hold on

x = 1 : .2 : 4;  
[CX1, CX2] = meshgrid(x);
Z = (CX1.^2 + CX2 -11)^2 + (CX1 + CX2.^2 -7)^2;
contour(CX1, CX2, Z);

plot(pX, pY, '-or');

hold off
 
 






