tic %начало отсчета

syms S;
S = 1;
X0 = [1; 1; 1];
eps = 0.05;
C=0;
syms d;

syms X1 X2 X3; %переменные по которым будем брать производные
f = 3*X1^2 + 5*X2^2 + 4*X3^2 +2*X1*X2 - X1*X3 - X2*X3 +7*X1 + X3;
df1 = diff(f,'X1'); %производная по переменной X1
df2 = diff(f, 'X2');
df3 = diff(f,'X3');



while S > eps
    C = C+1;

%подставляем значения X0 в производную (f'(x))
res1 = double(subs(df1, {X1, X2, X3},{X0(1,1), X0(2,1), X0(3,1)}));
res2 = double(subs(df2, {X1, X2, X3},{X0(1,1), X0(2,1), X0(3,1)}));
res3 = double(subs(df3, {X1, X2, X3},{X0(1,1), X0(2,1), X0(3,1)}));
%строим вторую производную
ddf1 = diff(df1, 'X1');
ddf2 = diff(df2, 'X2');
ddf3 = diff(df3, 'X3');

%подставляем значение X0 в производную (f''(x))
dres1 = double(subs(ddf1, {X1, X2, X3},{X0(1,1), X0(2,1), X0(3,1)}));
dres2 = double(subs(ddf2, {X1, X2, X3},{X0(1,1), X0(2,1), X0(3,1)}));
dres3 = double(subs(ddf3, {X1, X2, X3},{X0(1,1), X0(2,1), X0(3,1)}));
%-1 степень
d1 = [(dres1)^(-1); (dres2)^(-1); (dres3)^(-1)];

%строим X
X= double([X0(1,1) - d1(1,1)*res1; X0(2,1) - d1(2,1)*res2;  X0(3,1) - d1(3,1)*res3]);


  %критерий остановки
 
  fX11 = double(subs(df1, {X1, X2, X3}, {X(1,1), X(2,1), X(3,1)}));
  fX12 = double(subs(df2, {X1, X2, X3}, {X(1,1), X(2,1), X(3,1)})); 
  fX13 = double(subs(df3, {X1, X2, X3}, {X(1,1), X(2,1), X(3,1)}));
   
  fX1 = [ fX11; fX12; fX13];
  S = double(sqrt((fX11*fX11 + fX12*fX12 + fX13*fX13)));
 
   
  
  disp('Continue');
  
  X0(1,1) = X(1,1);
  X0(2,1) = X(2,1);
  X0(3,1) = X(3,1);
  
  %res1 = fX11;
  %res2 = fX12;
end


disp(double(X));
  disp(C); 
toc  %конеч отсчета