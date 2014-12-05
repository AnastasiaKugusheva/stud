tic %начало отсчета
X0 = [-7; 7];
eps = 0.05;
syms S;
S = 1;
C=0; %counter
k = 0;
m = 2;
syms ans;
syms B;



syms X1 X2 %переменные по которым будем брать производные
f = (X1^2 + X2 -11)^2 + (X1 + X2^2 - 7)^2;
%f = 9*X1^2 +X2^2; 
df1 = diff(f,'X1'); %производная по переменной X1
df2 = diff(f,'X2');

%подставляем значения X0 в производную f'(x) и умножаем на (-1) получаем d0
d1 = double((-1)*subs(df1, {X1, X2},{X0(1,1), X0(2,1)}));
d2 = double((-1)*subs(df2, {X1, X2},{X0(1,1), X0(2,1)}));

counter = 1;
syms pX pY
pX(counter,1) = double(X0(1,1));
pY(counter,1) = double(X0(2,1));
counter = counter + 1;

while S > eps
  syms L;
  syms K; 
    
  C = C + 1;  
  k = k + 1;
  
%строим X
X = ([X0(1,1) + L*d1; X0(2,1) + L*d2]);
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

X = [X0(1,1) + K*d1; X0(2,1) + K*d2]; 
 
 
  %подставляем значения X0 в производную f'(x)
  res1 = double(subs(df1, {X1, X2},{X0(1,1), X0(2,1)}));
  res2 = double(subs(df2, {X1, X2},{X0(1,1), X0(2,1)}));
  %подставляем значения X в производную f'(x)
  res3 = double(subs(df1, {X1, X2},{X(1,1), X(2,1)}));
  res4 = double(subs(df2, {X1, X2},{X(1,1), X(2,1)}));
  
  %S = double(abs(subs(f, {X1, X2},{X(1,1), X(2,1)}) - subs(f, {X1, X2},{X0(1,1), X0(2,1)})));
  S = double(sqrt((res3 - res1)^2 + (res4 - res2)^2));
       
  %Строим В
  B = abs(res3^2 + res4^2) / abs(res1^2 + res2^2); 
  if k == m
      B = 0;
      k = 0;
  end;
    
  dN = [(-1)*res3 + B*d1; (-1)*res4 + B*d2];
  
  X0(1,1) = X(1,1);
  X0(2,1) = X(2,1);  
  
  d1 = dN(1,1);
  d2 = dN(2,1);

  pX(counter,1) = double(X(1,1));
  pY(counter,1) = double(X(2,1));
  counter = counter + 1;
end

%проверяем является ли X точкой минимума
 En = double(subs(f, {X1, X2}, {X(1,1), X(2,1)}));
 En1 = double(subs(f, {X1, X2}, {X(1,1) + 0.0001, X(2,1) + 0.0001}));
 En2 = double(subs(f, {X1, X2}, {X(1,1) - 0.0001, X(2,1) - 0.0001}));
 if En < En1 && En < En2
       disp('Результат является точкой минимума :)');
   end;

  disp(double(X));
  disp(C);   

toc %конец отсчета


hold on

x = -10 : .2 : 10;  
[CX1, CX2] = meshgrid(x);
Z = (CX1.^2 + CX2 -11)^2 + (CX1 + CX2.^2 -7)^2;
contour(CX1, CX2, Z, 4);

plot(pX, pY, '-or');

hold off
 

 
 






