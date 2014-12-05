tic %начало отсчета
X0 = [1; 1];
eps = 0.3;
syms S;
S = 1;
C=0; %counter
syms ans;
syms B;



syms X1 X2 %переменные по которым будем брать производные
f = (X1^2 + X2 -11)^2 + (X1 + X2^2 - 7)^2;
%f = 9*X1*X1 +X2*X2; 
df1 = diff(f,'X1'); %производная по переменной X1
df2 = diff(f,'X2');

%подставляем значения X0 в производную f'(x) и умножаем на (-1) получаем d0
d1 = double((-1)*subs(df1, {X1, X2},{X0(1,1), X0(2,1)}));
d2 = double((-1)*subs(df2, {X1, X2},{X0(1,1), X0(2,1)}));

counter = 1;
syms pX pY

while S > eps
  syms L;
  syms K; 
    
  C = C + 1;  
 
%строим X
X = ([X0(1,1) + L*d1; X0(2,1) + L*d2]);
%подставляем значение X в f
L0 = subs(f, {X1, X2}, {X(1,1), X(2,1)});

% производная по L
Ld = (diff(L0, L));
L = solve(Ld);
steps = real(double(L)); 
K = max(steps);

X = [X0(1,1) + K*d1; X0(2,1) + K*d2]; 
  
  %критерий остановки
 
  %подставляем значения X0 в производную f'(x)
  res1 = double(subs(df1, {X1, X2},{X0(1,1), X0(2,1)}));
  res2 = double(subs(df2, {X1, X2},{X0(1,1), X0(2,1)}));
  %подставляем значения X в производную f'(x)
  res3 = double(subs(df1, {X1, X2},{X(1,1), X(2,1)}));
  res4 = double(subs(df2, {X1, X2},{X(1,1), X(2,1)}));
  
  fX1 = double([res3; res4]);
  S = double(abs(subs(f, {X1, X2},{X(1,1), X(2,1)}) - subs(f, {X1, X2},{X0(1,1), X0(2,1)})));
  %S = double(sqrt((fX11^2 + fX12^2)));
  
  if S > 100
      disp('');
  end
  
  %Строим В

  
  
  B = abs(res3^2 + res4^2) / abs(res1^2 + res2^2); 
  
  dN = [(-1)*res3 + B*d1; (-1)*res4 + B*d2];
  
  
  disp('Continue');
  
  X0(1,1) = X(1,1);
  X0(2,1) = X(2,1);  
  
  d1 = dN(1,1);
  d2 = dN(2,1);

  pX(counter,1) = double(X(1,1));
  pY(counter,1) = double(X(2,1));
  counter = counter + 1;
end

 

  disp(double(X));
  disp(C);   

toc %конец отсчета


hold on

x = -4 : .2 : 4;  
[CX1, CX2] = meshgrid(x);
Z = (CX1.^2 + CX2 -11)^2 + (CX1 + CX2.^2 -7)^2;
contour(CX1, CX2, Z);

plot(pX, pY, '-or');

hold off
 

 
 






