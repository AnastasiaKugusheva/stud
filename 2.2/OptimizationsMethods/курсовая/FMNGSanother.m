tic %начало отсчета
X0 = [-7; 7];
eps = 0.05;
syms S;
S = 1;

C=0; %counter
syms ans;
syms p;

syms X1 X2 %переменные по которым будем брать производные
f = (X1^2 + X2 -11)^2 + (X1 + X2^2 - 7)^2;

df1 = diff(f,'X1'); %производная по переменной X1
df2 = diff(f,'X2');

counter = 1;
syms pX pY
pX(counter,1) = double(X0(1,1));
pY(counter,1) = double(X0(2,1));
counter = counter + 1;

while S > eps
  syms L;
  syms K; 
    
  C = C + 1;  
 
%подставляем значения X0 в производную (f'(x))
res1 = double(subs(df1, {X1, X2},{X0(1,1), X0(2,1)}));
res2 = double(subs(df2, {X1, X2},{X0(1,1), X0(2,1)}));



%строим X
X = ([X0(1,1) - L*res1; X0(2,1) - L*res2]);
%подставляем значение X в f
L0 = subs(f, {X1, X2}, {X(1,1), X(2,1)});

% нахождение минимума методом золотого сечения
syms a b c d;
a = -2;
b = 3;
c = a + (b - a) * (3 - sqrt(5))/2;
d = a + (b - a) * (sqrt(5) - 1)/2;
while (abs(a - b) > 2 * eps) 
fc = double(subs(L0, {L}, c));
fd = double(subs(L0, {L}, d));

if fc <= fd
    b = d;
    d = c;
    c = a + (b - a) * (3 - sqrt(5))/2;
else
    a = c;
    c = d;
    d = a + (b - a) * (sqrt(5) - 1)/2;
end    
end
K = (a + b) / 2;

% производная по L
%Ld = (diff(L0, L));
%L = solve(Ld);
%steps = real(double(L)); 
%Kold = max(steps);
%disp(Kold);  

X = ([X0(1,1) - K*res1; X0(2,1) - K*res2]); 
  

  %критерий остановки
 
  fX11 = double(subs(df1, {X1, X2}, {X(1,1), X(2,1)}));
  fX12 = double(subs(df2, {X1, X2}, {X(1,1), X(2,1)}));
  
  fX1 = [ fX11; fX12];
  S = double(sqrt((fX11^2 + fX12^2)));
    
  X0(1,1) = X(1,1);
  X0(2,1) = X(2,1);  

  pX(counter,1) = double(X(1,1));
  pY(counter,1) = double(X(2,1));
  counter = counter + 1;
end

 

  disp(double(X));
  disp(C);   

toc %конец отсчета

%нету точки X0 (начальной, из которой выходим)
hold on

x = -10 : 0.2 : 10;
[CX1, CX2] = meshgrid(x);
Z = (CX1.^2 + CX2 -11)^2 + (CX1 + CX2.^2 -7)^2;
contour(CX1, CX2, Z, 4);

plot(pX, pY, '-or');

hold off

 
 






